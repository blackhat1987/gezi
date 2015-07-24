/** 
 *  ==============================================================================
 * 
 *          \file   key2ngram.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-04 17:48:00.722358
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef KEY2NGRAM_H_
#define KEY2NGRAM_H_
#include "ngram_model.h"
#include "gbk_datrie.h"
#include "ngram_model/ngram_model.h"
#include "seg_type.h"
namespace segment
{

class Key2NgramHelper
{
private:
    GBK_DATrie m_datrie;
public:

    Key2NgramHelper()
    {

    }

    Key2NgramHelper(const string& datrie_file, const string& encode_file)
    {
        init(datrie_file, encode_file);
    }

    void init(const string& datrie_file, const string& encode_file)
    {
        m_datrie.load(datrie_file, encode_file);
    }

    void convert(const vector<string>& vec, ngram::WordID* ngram)
    {//外部保证ngram不越界。。。
        int word_id;
        for (size_t i = 0; i < vec.size(); i++)
        {
            if (vec[i] == "b" || vec[i] == "10")
            {
                word_id = ngram::kGapID;
            }
            else
            {
                if (!m_datrie.search(vec[i], word_id))
                {
                    word_id = ngram::kGapID;
                    LOG(WARNING) <<vec[i] << " is not in the dict" << endl;
                }
            }
            ngram[i] = (ngram::WordID)word_id;
        }
    }

    void convert(const vector<string>& vec, vector<ngram::WordID>& ngram_vec)
    {//外部保证ngram不越界。。。
        int word_id;
        for (size_t i = 0; i < vec.size(); i++)
        {
            if (vec[i] == "b" || vec[i] == "10")
                word_id = ngram::kGapID;
            else
                m_datrie.search(vec[i], word_id);
            ngram_vec.push_back((ngram::WordID)word_id);
        }
    }
};
}//----end of namespace segment
#endif  //----end of KEY2NGRAM_H_
