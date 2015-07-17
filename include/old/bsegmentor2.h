/** 
 *  ==============================================================================
 * 
 *          \file   bsegmentor2.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-27 21:20:01.479252
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef BSEGMENTOR2_H_
#define BSEGMENTOR2_H_
#include "bsegmentor.h"
#include "ul_dict.h"
/**
 * 这个提供根据用户新加入的词典，确定把这些词需要进一步按照内部phrase切分
 */
class Segmentor2 : public Segmentor
{
private:
    Sdict_search* pdict;
    Segmentor2()
    : pdict(NULL)
    {

    }
    ~Segmentor2()
    {
        ds_del(pdict);
    }
    int init_user_dict(const char * path, const char * filename)
    {
        pdict = ds_load((char*)path, (char*)filename);
    }
    int split_tokenize(token_t token, token_t subtokens[], int tcnt)
    {
        return seg_split_tokenize(pdict, _handle, token, subtokens, tcnt);
    }
    int segment(const string& line, token_t tokens_temp[], token_t tokens[],
            uint32_t max_term_count, uint32_t max_term_count2 = 32)
    {
        int count = seg_segment(_handle, line.c_str(), line.size(), tokens_temp, max_term_count);
        int cur = 0;
        token_t subtokens[max_term_count2];
        for (int i = 0; i < count; i++)
        {
            int count2 = seg_split_tokenize(pdict, _handle, tokens_temp[i], subtokens, max_term_count2);
            for (int j = 0; j < count2; j++)
            {
                tokens[cur++] = subtokens[j];
            }
        }
        return cur;
    }
    int segment(const char* line, int len, token_t tokens_temp[], token_t tokens[],
            uint32_t max_term_count, uint32_t max_term_count2 = 32 )
    {
        int count = seg_segment(_handle, line, len, tokens_temp, max_term_count);
        int cur = 0;
        token_t subtokens[max_term_count2];
        for (int i = 0; i < count; i++)
        {
            int count2 = seg_split_tokenize(pdict, _handle, tokens_temp[i], subtokens, max_term_count2);
            for (int j = 0; j < count2; j++)
            {
                tokens[cur++] = subtokens[j];
            }
        }
        return cur;
    }
};

#endif  //----end of BSEGMENTOR2_H_
