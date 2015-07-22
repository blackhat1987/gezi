/** 
 *  ==============================================================================
 * 
 *          \file   signdict_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-07-23 21:21:42.472348
 *  
 *  \Description:   ���string ��signdict��װ,�ṩһ��SignStrDict value Ϊint
 *                  һ��SignStrSet value Ϊbool
 *                  TODO�ܷ�Ҫvalue�ռ�?����std::set  value�������ó�����0��
 *  ����sign dictҪ��key����ǩ�������˳����룬������һ����װ���ڲ���������
 *
 * std::numeric_limits<int>::max() ------- 2147483647
 * ע�⵱ǰ֧�����ݲ����������max  21��
 * ./test_signdict
I0724 12:31:21.618008 27087 test_signdict.cc:46] Begin loading
I0724 12:32:31.154959 27087 test_signdict.cc:48] End loading
status ------- 1
dict.size() ------- 58609624
val ------- 948300
dict.id("����") ------- 948300
dict.id("�̻ݸ�") ------- -1
I0724 12:32:31.155061 27087 test_signdict.cc:56] Begin saving
I0724 12:32:31.545855 27087 test_signdict.cc:58] End saving
I0724 12:32:31.710110 27087 test_signdict.cc:60] Begin loading binary
I0724 12:32:32.162943 27087 test_signdict.cc:62] End loading binary
dict.id("����") ------- 948300
dict.id("�̻ݸ�") ------- -1

 �ڴ�ռ��561M
 1B �����ռ�� 392M

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
        //����SignDict��ָ������ǰ׺���ȡ���ǰ֧�ֵ�ǰ׺������1-3�ֽڷ�Χ�ڡ�
        //�����ϣ���ֶ�ָ��ǰ׺���ȣ�����ʹ�ô���0��Ϊ������ֵ����ʱ���򽫸��ݾ���ֵѡ����ѵ�ǰ׺����
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
     * ͨ�������ֵ䴴��
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
     * ��������ֵ�
     */
    void save(const std::string& file) {
        FILE* fp = fopen(file.c_str(), "wb");
        signdict_dump(_dict, fp);
        fclose(fp);
    }

    /**
     * ����������ֵ�
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
    //----------------��ѯ

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
 * �ƺ�value ����1B...
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
        //����SignDict��ָ������ǰ׺���ȡ���ǰ֧�ֵ�ǰ׺������1-3�ֽڷ�Χ�ڡ�
        //�����ϣ���ֶ�ָ��ǰ׺���ȣ�����ʹ�ô���0��Ϊ������ֵ����ʱ���򽫸��ݾ���ֵѡ����ѵ�ǰ׺����
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
     * ͨ�������ֵ䴴��
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
     * ��������ֵ�
     */
    void save(const std::string& file) {
        FILE* fp = fopen(file.c_str(), "wb");
        signdict_dump(_dict, fp);
        fclose(fp);
    }

    /**
     * ����������ֵ�
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
    //----------------��ѯ

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
