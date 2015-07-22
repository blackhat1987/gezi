/** 
 *  ==============================================================================
 * 
 *          \file   bsegmentor.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-09 12:01:38.460053
 *  
 *  \Description:  baidu segmentor C++简单包装
 *
 *                TODO 
 *                多线程支持？open seg, close seg 属于线程范围
 *                多线程的问题是handle是线程范围，dict_ptr字典数据应该共有 所以应该单独提到外面
 *
 *  测试文件参考 test_bsementor.h
 *  ==============================================================================
 */

#ifndef BSEGMENTOR_H_
#define BSEGMENTOR_H_

#include "isegment.h"
#include "ipostag.h"
#include "property.h"
#include "ul_log_help.h"
/**
 *Dict数据相关，进程范围线程共有
 */
class SegDict
{
private:
    friend class Segmentor;
    dict_ptr_t _dict_ptr;
public:
    SegDict()
    {
    }
    ~SegDict()
    {
        seg_dict_close(_dict_ptr);
    }
    bool open(const char* dict_path)
    {
        _dict_ptr = seg_dict_open(dict_path);
        if (!_dict_ptr)
        {
            LOG_ERROR("Error: can't load the dictionary %s.\n", dict_path);
            return false;
        }
        return true;
    }
};
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
    bool open(const char* dict_path)
    {
        if (tag_open(dict_path))
        {
            LOG_ERROR("Error: can't load the dictionary %s.\n", dict_path);
            return false;
        }
        return true;
    }

};

const int MAX_TERM_COUNT_DEFAULT = 4096;
/**
 * 分词器，线程范围，共享一个Dict
 */
class Segmentor
{
protected:
    handle_t _handle;
public:
    Segmentor()
    {

    }
    ~Segmentor()
    {
        seg_close(_handle);
    }
    int segment(const string& line, token_t tokens[], uint32_t max_term_count)
    {
        return seg_segment(_handle, line.c_str(), line.size(), tokens, max_term_count);
    }
    int segment(const char* line, int len, token_t tokens[], uint32_t max_term_count)
    {
        return seg_segment(_handle, line, len, tokens, max_term_count);
    }
    int tokenize(token_t token, uint32_t type, token_t subtokens[], uint32_t max)
    {
        return seg_tokenize(_handle, token, type, subtokens, max);
    }
    bool open(const SegDict& dict, int max_term_count = MAX_TERM_COUNT_DEFAULT)
    {
        _handle = seg_open(dict._dict_ptr, max_term_count);
        if (!_handle)
        {
            LOG_ERROR("Error: can't create handle for segment.\n");
            return false;
        }
        return true;
    }
};

typedef Segmentor BSegmentor;
typedef SegDict BSegDict;
inline void print_seg_result(token_t tokens[], int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s  ", tokens[i].buffer);
        Pval(tokens[i].length);
        Pval(tokens[i].offset);
    }
    printf("\n");
}
extern const char* get_pos_str(unsigned int nPOS); // from libpostag.a
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
#endif  //----end of BSEGMENTOR_H_
