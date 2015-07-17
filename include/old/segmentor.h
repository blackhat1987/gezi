/** 
 *  ==============================================================================
 * 
 *          \file   segmentor.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-06-11 13:54:56.342973
 *  
 *  \Description:   包装baidu分词器
 *                  TODO 1 写一个更简洁的 单线程版本包装
 *                       2 封装一个python版本的
 *  ==============================================================================
 */

#ifndef SEGMENTOR_H_
#define SEGMENTOR_H_
#include <iostream>
#include "scwdef.h"
#include "isegment.h"
#include "ipostag.h"
#include "property.h"
#include "ul_dict.h"
#include "ul_log_help.h"
extern int scw_get_token_1(scw_out_t* pout, int type, token_t result[], unsigned max); // from libsegment.a
extern const char* get_pos_str(unsigned int nPOS); // from libpostag.a
namespace bseg {
using namespace std;
const char* k_user_dict_name = "need_split";
const char* k_dict_path = "worddict";
const char* k_postag_path = "tagdict";
const char* k_userdict_path = "need_split";
/**
 *Dict数据相关，进程范围线程共有
 */
class SegDict
{
private:
    friend class Segmentor;
    scw_worddict_t * _pwdict;
public:
    SegDict()
    : _pwdict(NULL)
    {
    }
    virtual ~SegDict()
    {
        //---关闭分词字典
        if (_pwdict)
            scw_destroy_worddict(_pwdict);
    }
    bool load(const string& dict_path)
    {
        if ((_pwdict = scw_load_worddict(dict_path.c_str())) == NULL)
        {
            LOG_ERROR("Error: can't load the dictionary %s.\n", dict_path.c_str());
            return false;
        }
        return true;
    }
};
/**
 * 词性标注器
 */
class PostTagger
{
public:
    PostTagger()
    {
    }
    ~PostTagger()
    {
        tag_close();
    }
    bool load(const string& dict_path)
    {
        if (tag_open(dict_path.c_str()))
        {
            LOG_ERROR("Error: can't load the dictionary %s.\n", dict_path.c_str());
            return false;
        }
        return true;
    }

};

const int MAX_TERM_COUNT_DEFAULT = 4096;
/**
 * 分词器，线程范围，共享一个Dict,每个线程独立开辟一个Segmentor
 */
class Segmentor
{
protected:
    scw_out_t *_pout;
    scw_worddict_t * _pwdict;

public:
    Segmentor()
    : _pout(NULL), _pwdict(NULL)
    {

    }
    virtual ~Segmentor()
    {
        if (_pout)
            scw_destroy_out(_pout);
    }
    bool init(const SegDict& dict, int max_term_count = MAX_TERM_COUNT_DEFAULT)
    {
        _pwdict = dict._pwdict;
        u_int scw_out_flag = SCW_OUT_ALL | SCW_OUT_PROP;
        if ((_pout = scw_create_out(max_term_count, scw_out_flag)) == NULL)
        {
            LOG_ERROR("Initializing the output buffer error");
            return false;
        }
        return true;
    }
    int segment(const string& line, token_t tokens[], uint32_t max_term_count)
    {
        if (scw_segment_words(_pwdict, _pout, line.c_str(), line.length()) < 0)
        {
            LOG_ERROR("Segment fail");
            return -1;
        }

        return scw_get_token_1(_pout, SCW_OUT_WPCOMP, tokens, max_term_count);
    }
    int segment(const char* line, int len, token_t tokens[], uint32_t max_term_count)
    {
        if (scw_segment_words(_pwdict, _pout, line, len) < 0)
        {
            LOG_ERROR("Segment fail");
            return -1;
        }

        return scw_get_token_1(_pout, SCW_OUT_WPCOMP, tokens, max_term_count);
    }
    //之所以写两个函数，而不用默认参数是为了Segmentor2重载方便
    int segment(const string& line, token_t tokens[], uint32_t max_term_count, int seg_type)
    {
        if (scw_segment_words(_pwdict, _pout, line.c_str(), line.length()) < 0)
        {
            LOG_ERROR("Segment fail");
            return -1;
        }

        return scw_get_token_1(_pout, seg_type, tokens, max_term_count);
    }
    int segment(const char* line, int len, token_t tokens[], uint32_t max_term_count, int seg_type)
    {
        if (scw_segment_words(_pwdict, _pout, line, len) < 0)
        {
            LOG_ERROR("Segment fail");
            return -1;
        }

        return scw_get_token_1(_pout, seg_type, tokens, max_term_count);
    }
    int get(token_t tokens[], uint32_t max_term_count, int seg_type)
    {
        return scw_get_token_1(_pout, seg_type, tokens, max_term_count);
    }
};



/**
 * 增加支持用户自定义词典
 */
class SegDict2 : public SegDict
{
private:
    friend class Segmentor2;
    Sdict_search* _split_dict; ///自定义不需要在分词字典中去除内部再切分的字典资源
public:
    SegDict2()
    : _split_dict(NULL)
    {
    }
    ~SegDict2()
    {
        //---关闭用户需要内部切分字典
        if (_split_dict)
            ds_del(_split_dict);
    }
    bool load(const string& dict_path, const string& user_dict_path)
    {
        if (!SegDict::load(dict_path))
            return false;
        _split_dict = ds_load((char *) user_dict_path.c_str(), (char *) k_user_dict_name);
        if (!_split_dict)
        {
            LOG_ERROR("Do not find user defined dict");
            return false;
        }
        return true;
    }
};
/**
 * SegInitor 做了进一步封装，包括了标注器
 */
class SegInitor : public SegDict
{
private:
    PostTagger _pos_tagger;
public:
    bool load(const string& seg_dir)
    {
        //-------------载入词典
        char dict_path[2048];
        sprintf(dict_path, "%s/%s", seg_dir.c_str(), k_dict_path);
        if (!SegDict::load(dict_path))
            return false;
        //--------------启动标注
        char tag_dict_path[2048];
        sprintf(tag_dict_path, "%s/%s", seg_dir.c_str(), k_postag_path);
        if (!_pos_tagger.load(tag_dict_path))
            return false;
        return true;
    }
};
class SegInitor2 : public SegDict2
{
private:
    PostTagger _pos_tagger;
public:
    bool load(const string& seg_dir)
    {
        //-------------载入词典,用户自定义需要切分词典
        char dict_path[2048];
        sprintf(dict_path, "%s/%s", seg_dir.c_str(), k_dict_path);
        char user_dict_path[2048];
        sprintf(user_dict_path, "%s/%s", seg_dir.c_str(), k_userdict_path);
        if (!SegDict2::load(dict_path, user_dict_path))
            return false;
        //--------------启动标注
        char tag_dict_path[2048];
        sprintf(tag_dict_path, "%s/%s", seg_dir.c_str(), k_postag_path);
        if (!_pos_tagger.load(tag_dict_path))
            return false;
        return true;
    }
};
class Segmentor2 : public Segmentor
{
protected:
    Sdict_search* _split_dict; ///自定义不需要在分词字典中去除内部再切分的字典资源
public:
    Segmentor2()
    : _split_dict(NULL)
    {

    }
    ~Segmentor2()
    {
    }
    bool init(const SegDict2& dict, int max_term_count = MAX_TERM_COUNT_DEFAULT)
    {
        _split_dict = dict._split_dict;
        if (!Segmentor::init(dict, max_term_count))
            return false;
        return true;
    }
    int segment(const string& line, token_t tokens[], uint32_t max_term_count= MAX_TERM_COUNT_DEFAULT)
    {
        if (scw_segment_words(_pwdict, _pout, line.c_str(), line.length()) < 0)
        {
            LOG_ERROR("Segment fail");
            return -1;
        }

        return seg_split(_split_dict, _pout, tokens, max_term_count);
    }
    int segment(const char* line, int len, token_t tokens[], uint32_t max_term_count= MAX_TERM_COUNT_DEFAULT)
    {
        if (scw_segment_words(_pwdict, _pout, line, len) < 0)
        {
            LOG_ERROR("Segment fail");
            return -1;
        }
        return seg_split(_split_dict, _pout, tokens, max_term_count);
    }
};
/**
 * 对应Segmentor, Segmentor2的单线程版本
 */
class BSegmentor : public Segmentor
{
private:
    PostTagger _pos_tagger;
public:
    ~BSegmentor()
    {
        //---关闭分词字典
        if (_pwdict)
            scw_destroy_worddict(_pwdict);
    }
    bool init(const string& seg_dir, int max_term_count = MAX_TERM_COUNT_DEFAULT)
    {
        //-------------载入词典
        char dict_path[2048];
        sprintf(dict_path, "%s/%s", seg_dir.c_str(), k_dict_path);
        if ((_pwdict = scw_load_worddict(dict_path)) == NULL)
        {
            LOG_ERROR("Error: can't load the dictionary %s.\n", dict_path);
            return false;
        }
        //--------------启动标注
        char tag_dict_path[2048];
        sprintf(tag_dict_path, "%s/%s", seg_dir.c_str(), k_postag_path);
        if (!_pos_tagger.load(tag_dict_path))
            return false;
        u_int scw_out_flag = SCW_OUT_ALL | SCW_OUT_PROP;
        if ((_pout = scw_create_out(max_term_count, scw_out_flag)) == NULL)
        {
            LOG_ERROR("Initializing the output buffer error");
            return false;
        }
        return true;
    }
};
class BSegmentor2 : public Segmentor2
{
private:
    PostTagger _pos_tagger;
public:
    ~BSegmentor2()
    {
        //---关闭分词字典
        if (_pwdict)
            scw_destroy_worddict(_pwdict);
        //---关闭用户需要内部切分字典
        if (_split_dict)
            ds_del(_split_dict);
    }
    bool init(const string& seg_dir, int max_term_count = MAX_TERM_COUNT_DEFAULT)
    {
        char user_dict_path[2048];
        sprintf(user_dict_path, "%s/%s", seg_dir.c_str(), k_userdict_path);
        _split_dict = ds_load(user_dict_path, (char *) k_user_dict_name);
        if (!_split_dict)
        {
            LOG_ERROR("Do not find user defined dict");
            return false;
        }
        //-------------载入词典
        char dict_path[2048];
        sprintf(dict_path, "%s/%s", seg_dir.c_str(), k_dict_path);
        if ((_pwdict = scw_load_worddict(dict_path)) == NULL)
        {
            LOG_ERROR("Error: can't load the dictionary %s.\n", dict_path);
            return false;
        }
        //--------------启动标注
        char tag_dict_path[2048];
        sprintf(tag_dict_path, "%s/%s", seg_dir.c_str(), k_postag_path);
        if (!_pos_tagger.load(tag_dict_path))
            return false;
        u_int scw_out_flag = SCW_OUT_ALL | SCW_OUT_PROP;
        if ((_pout = scw_create_out(max_term_count, scw_out_flag)) == NULL)
        {
            LOG_ERROR("Initializing the output buffer error");
            return false;
        }
        return true;
    }
};
inline void print_seg_result(token_t tokens[], int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s  ", tokens[i].buffer);
    }
    printf("\n");
}
inline void print_seg_posttag_result(token_t tokens[], int count)
{
    for (int i = 0; i < count; i++)
    {
        const char* stag = get_pos_str(tokens[i].type);
        if (stag)
            printf("%s/%s  ", tokens[i].buffer, stag);
        else
            printf("%s  ", tokens[i].buffer);
    }
    printf("\n");
}
inline void print_seg_result(token_t tokens[], int count, std::ostream& os)
{
    for (int i = 0; i < count; i++)
    {
        os << tokens[i].buffer << " ";
    }
    os << std::endl;
}
inline void print_seg_posttag_result(token_t tokens[], int count, std::ostream& os)
{
    for (int i = 0; i < count; i++)
    {
        const char* stag = get_pos_str(tokens[i].type);
        if (stag)
            os << tokens[i].buffer << "/" << stag << " ";
        else
            os << tokens[i].buffer << " ";
    }
    os << std::endl;
}
}
#endif  //----end of SEGMENTOR_H_
