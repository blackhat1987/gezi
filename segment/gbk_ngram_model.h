/** 
 *  ==============================================================================
 * 
 *          \file   gbk_ngram_model.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-10-27 11:29:24.206132
 *  
 *  \Description:   包装ngram_model, gbk encoder
 *                  提供直接处理字符，句子的ngram模型接口
 *  ==============================================================================
 */

#ifndef GBK_NGRAM_MODEL_H_
#define GBK_NGRAM_MODEL_H_
#include "ngram_model.h"
#include "gbk_datrie.h"
#include "ngram_model/ngram_model.h"
#include "seg_type.h"
namespace segment {
class GBK_NgramModel
{
private:
    GBK_DATrie m_datrie;
    ngram::Model m_ngramModel;
public:
    GBK_NgramModel()
    {
    }
    GBK_NgramModel(const string& dir)
    {
        load(dir);
    }
public:
    void load(const string& dir = "ngram_model")
    {
        string datrie_file = dir + "/datrie.idx";
        string encode_file = dir + "/encode.idx";
        string model_file = dir + "/ngram_model.idx";
        load(datrie_file, encode_file, model_file);
    }
    void load(const string& datrie_file, const string& encode_file, const string& model_file)
    {
        m_datrie.load(datrie_file, encode_file);
        m_ngramModel.load(model_file);
        LOG(INFO) << "Successfully load datie and ngram model" << "\n";
    }
    double getSentencePr(const vector<string>& sentence)
    {
        vector<ngram::WordID> vec;
        int word_id = 0;
        for (int i = 0; i < sentence.size(); i++)
        {
            m_datrie.search(sentence[i], word_id);
            vec.push_back((ngram::WordID)word_id);
        }
        vec.push_back(ngram::kGapID);
        return m_ngramModel.getSentencePr(vec);
    }
    segment::GBK_DATrie& getDict()
    {
        return m_datrie;
    }

};

} //----end of namespace segment

#endif  //----end of GBK_NGRAM_MODEL_H_
