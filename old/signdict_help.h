/** 
 *  ==============================================================================
 * 
 *          \file   signdict_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-07-23 21:21:42.472348
 *  
 *  \Description:   针对string 的signdict包装,提供一个SignStrDict value 为int
 *                  一个SignStrSet value 为bool
 *                  TODO能否不要value空间?类似std::set  value可以设置长度是0吗
 *  另外sign dict要求key按照签名排序的顺序插入，这里做一个封装，内部处理排序
 *
 * std::numeric_limits<int>::max() ------- 2147483647
 * 注意当前支持数据不超过上面的max  21亿
 * ./test_signdict
I0724 12:31:21.618008 27087 test_signdict.cc:46] Begin loading
I0724 12:32:31.154959 27087 test_signdict.cc:48] End loading
status ------- 1
dict.size() ------- 58609624
val ------- 948300
dict.id("可乐") ------- 948300
dict.id("程惠阁") ------- -1
I0724 12:32:31.155061 27087 test_signdict.cc:56] Begin saving
I0724 12:32:31.545855 27087 test_signdict.cc:58] End saving
I0724 12:32:31.710110 27087 test_signdict.cc:60] Begin loading binary
I0724 12:32:32.162943 27087 test_signdict.cc:62] End loading binary
dict.id("可乐") ------- 948300
dict.id("程惠阁") ------- -1

 内存占用561M
 1B 的情况占用 392M

 TODO HDICT
 *  ==============================================================================
 */

#ifndef SIGNDICT_HELP_H_
#define SIGNDICT_HELP_H_
#include "signdict.h"
#include "ul_sign.h"
#include <limits>
#include <string>
#include <algorithm>
#include <functional>
//#include <boost/filesystem.hpp>
#include "ul_log_help.h"

class SignStrDict {
public:

    SignStrDict()
    : _dict(NULL) {

    }

    ~SignStrDict() {
        if (_dict)
            signdict_delete(_dict);
    }

    struct Node {
        u_int sign[2];
        int value;

        Node(u_int a, u_int b, int v)
        : value(v) {
            sign[0] = a;
            sign[1] = b;
        }

        bool operator<(const Node & other) const {
            return sign[0] < other.sign[0] || (sign[0] == other.sign[0] && sign[1] < other.sign[1]);
        }
    };

    void clear() {
        signdict_delete(_dict);
        _dict = NULL;
    }

    inline void add(const std::string& phrase, int value = 0) {
        u_int sign1, sign2;
        creat_sign_md64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        _vec.push_back(Node(sign1, sign2, value));
    }
    
    bool finalize() {
        std::sort(_vec.begin(), _vec.end());
        //创建SignDict可指定索引前缀长度。当前支持的前缀长度在1-3字节范围内。
        //如果不希望手动指定前缀长度，可以使用传入0作为参数的值，此时程序将根据经验值选择最佳的前缀长度
        int len = _vec.size();
        int prefix_len = 0;
        int value_len = 4;
        _dict = signdict_new(len, prefix_len, value_len);
        if (!_dict)
            return false;
        for (int i = 0; i < len; i++) {
            signdict_insert_one(_dict, _vec[i].sign, (u_char*) (&_vec[i].value));
        }
        _vec.clear();
        signdict_finalize_insertion(_dict);
        return true;
    }

    /**
     * 通过明文字典创建
     */
    bool create(const std::string& file) {
        std::ifstream ifs(file.c_str());
        if (!ifs.is_open()) {
            LOG_ERROR("Open %s failed\n", file.c_str());
            return false;
        }

        std::string line, key;
        int id = 0;
        while (std::getline(ifs, line)) {
            int pos = line.find("\t");
            if (pos == std::string::npos) {
                key = line;
            } else {
                key = line.substr(0, pos);
            }
            add(key, id++);
        }
        return finalize();
    }

    int size() {
        return signdict_size(_dict);
    }

    /**
     * 存二进制字典
     */
    void save(const std::string& file) {
        FILE* fp = fopen(file.c_str(), "wb");
        signdict_dump(_dict, fp);
        fclose(fp);
    }

    /**
     * 读入二进制字典
     */
    bool load(const std::string& file) {
        FILE* fp = fopen(file.c_str(), "rb");
        if ((_dict = signdict_load(fp)) == NULL) {
            fclose(fp);
            return false;
        }
        fclose(fp);
        return true;
    }
    //----------------查询

    inline bool has(const std::string& phrase) const {
        u_int sign[2];
        int value;
        //        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        creat_sign_md64((char *) phrase.c_str(), phrase.size(), &sign[0], &sign[1]);
        //        bool find = signdict_search(_dict, sign, (u_char*) & value_buf);
        return (signdict_search(_dict, sign, (u_char*) & value) == SIGNDICT_OK);
    }

    inline bool get(const std::string& phrase, int & value) const {
        u_int sign[2];
        //        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        creat_sign_md64((char *) phrase.c_str(), phrase.size(), &sign[0], &sign[1]);
        //        bool find = signdict_search(_dict, sign, (u_char*)&value_buf);
        return signdict_search(_dict, sign, (u_char*) & value) == SIGNDICT_OK;
    }

    inline int id(const std::string& phrase) const {
        u_int sign[2];
        int value;
        //        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        creat_sign_md64((char *) phrase.c_str(), phrase.size(), &sign[0], &sign[1]);
        bool find = (signdict_search(_dict, sign, (u_char*) & value) == SIGNDICT_OK);
        if (find) {
            return value;
        } else {
            return null_id;
        }
    }

    inline int operator[](const char* phrase) const {
        u_int sign[2];
        int value;
        //        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        creat_sign_md64(phrase, strlen(phrase), &sign[0], &sign[1]);
        bool find = (signdict_search(_dict, sign, (u_char*) & value) == SIGNDICT_OK);
        if (find) {
            return value;
        } else {
            return null_id;
        }
    }


public:
    static const int null_id = -1;
    SignDict* _dict;
    std::vector<Node> _vec;
};

/**
 * 似乎value 至少1B...
 */
class SignStrSet {
public:

    SignStrSet()
    : _dict(NULL) {

    }

    ~SignStrSet() {
        if (_dict)
            signdict_delete(_dict);
    }

    struct Node {
        u_int sign[2];

        Node(u_int a, u_int b) {
            sign[0] = a;
            sign[1] = b;
        }

        bool operator<(const Node & other) const {
            return sign[0] < other.sign[0] || (sign[0] == other.sign[0] && sign[1] < other.sign[1]);
        }
    };

    void clear() {
        signdict_delete(_dict);
        _dict = NULL;
    }

    inline void add(const std::string& phrase) {
        u_int sign1, sign2;
        creat_sign_md64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        _vec.push_back(Node(sign1, sign2));
    }

    bool finalize() {
        std::sort(_vec.begin(), _vec.end());
        //创建SignDict可指定索引前缀长度。当前支持的前缀长度在1-3字节范围内。
        //如果不希望手动指定前缀长度，可以使用传入0作为参数的值，此时程序将根据经验值选择最佳的前缀长度
        int len = _vec.size();
        int prefix_len = 0;
        int value_len = 1;
        _dict = signdict_new(len, prefix_len, value_len);
        if (!_dict)
            return false;
        u_char value;
        for (int i = 0; i < len; i++) {
            signdict_insert_one(_dict, _vec[i].sign, (u_char*) (&value));
        }
        _vec.clear();
        signdict_finalize_insertion(_dict);
        return true;
    }

    /**
     * 通过明文字典创建
     */
    bool create(const std::string& file) {
        std::ifstream ifs(file.c_str());
        if (!ifs.is_open()) {
            LOG_ERROR("Open %s failed\n", file.c_str());
            return false;
        }

        std::string line, key;
        while (std::getline(ifs, line)) {
            int pos = line.find("\t");
            if (pos == std::string::npos) {
                key = line;
            } else {
                key = line.substr(0, pos);
            }
            add(key);
        }
        return finalize();
    }

    int size() {
        return signdict_size(_dict);
    }

    bool empty() {
        return this->size() == 0;
    }

    /**
     * 存二进制字典
     */
    void save(const std::string& file) {
        FILE* fp = fopen(file.c_str(), "wb");
        signdict_dump(_dict, fp);
        fclose(fp);
    }

    /**
     * 读入二进制字典
     */
    bool load(const std::string& file) {
        FILE* fp = fopen(file.c_str(), "rb");
        if (!fp) {
            return false;
        }

        if ((_dict = signdict_load(fp)) == NULL) {
            fclose(fp);
            return false;
        }
        fclose(fp);
        return true;
    }
    //----------------查询

    inline bool has(const std::string& phrase) const {
        u_int sign[2];
        //        creat_sign_fs64((char *) phrase.c_str(), phrase.size(), &sign1, &sign2);
        creat_sign_md64((char *) phrase.c_str(), phrase.size(), &sign[0], &sign[1]);
        //        bool find = signdict_search(_dict, sign, (u_char*) & value_buf);
        u_char value;
        return (signdict_search(_dict, sign, (u_char*) & value) == SIGNDICT_OK);
    }
public:
    SignDict* _dict;
    std::vector<Node> _vec;
};
#endif  //----end of SIGNDICT_HELP_H_
