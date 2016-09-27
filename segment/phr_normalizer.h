/** 
 *  ==============================================================================
 * 
 *          \file   phr_normalizer.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-24 16:14:58.163923
 *  
 *  \Description:   类似phrase_normalizer不过直接存储编号identifer
 *  ==============================================================================
 */

#ifndef PHR_NORMALIZER_H_
#define PHR_NORMALIZER_H_

#include "gbk_ch_converter.h"
#include "string_help.h"
#include "segmentor.h" //分词
#include "segment_prob_impl_identifer.h"
#include "segment_impl_basic_identifer.h"
namespace phr_norm
{

using namespace segment;

template<typename Ter>
struct ResultFunc_Identifer
{

    ResultFunc_Identifer()
    {
    }

    ResultFunc_Identifer(const string & key)
    {
    }

    void operator()(std::set<int>& out, int val, int len, int level) const
    {
        if (val != ngram::kUnknownID && !len)
            out.insert(val);
    }

    void operator()(std::vector<int>& out, int val, int len, int level) const
    {
        if (val != ngram::kUnknownID && !len)
            out.push_back(val);
    }
};

class PhrNormalizer
{
private:
    typedef SegmentorT< SegmentorImpl_Basic_Identifer<PuncSegmentor_AlNumNoSeg, SegmentorProbIdentiferImpl >, ResultFunc_Identifer > Segmentor_;
    ch_convert::ChConverter m_converter;
    Segmentor_ m_seg;
    //    ProbSegmentor m_seg;
public:

    PhrNormalizer()
    {

    }

    PhrNormalizer(const string& seg_dir)
    {
        init(seg_dir);
    }

    void init(const string& seg_dir)
    {
        m_seg.init(seg_dir);
    }

    void normalize(const string& input, std::set<int>& set_)
    {
        string phrase;
        //step1-------------------------繁体转简体，转半角，小写化
        phrase = m_converter.Normalize(input);
        if (phrase.empty())
            return;
        phrase = filterString2(phrase);
        if (phrase.empty())
            return;
        m_seg.segment_(phrase, set_);
        //        m_seg.segment(phrase, set_);
    }

    void norm(const string& phrase, std::set<int>& set_)
    {
        m_seg.segment_(phrase, set_);
        //        m_seg.segment(phrase, set_);
    }
};

} //----end of namespace phr_norm

#endif  //----end of PHR_NORMALIZER_H_
