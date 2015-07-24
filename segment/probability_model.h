/** 
 *  ==============================================================================
 * 
 *          \file   probability_model.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-10-19 16:24:58.037756
 *  
 *  \Description:   利用sun拼音的概率模型做了一个对外封装的接口
 *  ==============================================================================
 */

#ifndef PROBABILITY_MODEL_H_
#define PROBABILITY_MODEL_H_
#include <boost/algorithm/string.hpp>
#include "slmthread/slm.h"
#include "gbk_datrie.h"
namespace segment
{
class PrModel
{
public:
    PrModel()
    {
    }
    PrModel(const string& trie, const string& encode, const string& pr_model)
    : m_datrie(trie, encode)
    {
        m_slm.load(pr_model.c_str(), false);
    }
    void load(const string& trie, const string& encode, const string& pr_model)
    {
        m_datrie.load(trie, encode);
        m_slm.load(pr_model.c_str(), false);
    }
    ~PrModel()
    {
        m_slm.free();
    }
    /**一个词的概率，unigram*/
    double getWordPr(const string& key)
    {
        CThreadSlm::TState tstate;
        int word_id;
        m_datrie.search(key, word_id);
        return m_slm.transfer(CThreadSlm::TState(), word_id, tstate);
    }
    double getSentencePr(const string& key)
    {
        vector<string> words;
        boost::algorithm::split(words, key, boost::is_any_of(" "));
        return getSentencePr(words);
    }
    double getSentencePr(const vector<string>& words)
    {
        CThreadSlm::TState pre_state, state;
        double pr, result;
//        result = 1.0;
        result = 0;
        int word_id;
        for (size_t i = 0; i < words.size(); i++)
        {
            if (!m_datrie.search(words[i], word_id))
            {
                word_id = 0;
            }
            Pval(word_id);
            pr = m_slm.transferNegLog(pre_state, word_id, state);
            pre_state = state;
            Pval(pr);
//            result *= pr;
            result += pr;
        }
        return result;
    }
    segment::GBK_DATrie& getDict()
    {
        return m_datrie;
    }
    bool search(const string& key)
    {
        return m_datrie.search(key);
    }
private:
    segment::GBK_DATrie m_datrie;
    CThreadSlm m_slm;
};

} //----end of namespace segment

#endif  //----end of PROBABILITY_MODEL_H_
