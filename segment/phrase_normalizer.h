/** 
 *  ==============================================================================
 * 
 *          \file   phrase_normalizer.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-24 11:30:22.321769
 *  
 *  \Description:  一个轻量级的短语归一化工具,
 *                 负责繁简体转换，filterstring, 分词，去掉停用词，重复词，排序转归一化形式，不负责纠错等等其它任务
 *
 *   它的问题是 分开的词 排序后 就不好再拼接了 u盘
 *   是否采用 中英文不强制分开的流程? TODO
 *
 *   应该这样 女运动鞋 运动鞋女
 *
 *   广告 “运动包”应该在字典中
 *   运动鞋 -> 运动休闲鞋   这种是适合按照扩展词处理的
 *   当然 “运动，鞋” 这样匹配两个词也可以，但是对广告来说不太好
 *   TODO 需要开始就先去掉空格吗？
 *  ==============================================================================
 */

#ifndef PHRASE_NORMALIZER_H_
#define PHRASE_NORMALIZER_H_

#include "ch_stoper.h"
#include "gbk_ch_converter.h"
#include "string_help.h"
#include "segmentor.h" //分词

namespace phr_norm {
using namespace segment;
template<typename Ter>
struct SegResultFunc
{
    const string& key_;
    const CHStoper stoper_;
    SegResultFunc(const string & key)
    : key_(key)
    {
    }
    void operator()(std::set<string>& out, int start, int len, int level) const
    {
        string s = key_.substr(start, len);
        // if (!(s.size() == 1 && std::isspace(s[0])))
        if (!(s == " ") && !(stoper_.isStopWord(s)))
        {
            out.insert(s);
        }
    }
};
class PhraseNormalizer
{
private:
    typedef SegmentorT< SegmentorImpl_Basic<PuncSegmentor_AlNumNoSeg, SegmentorProbImpl >, SegResultFunc > Segmentor_;
    ch_convert::ChConverter m_converter;
    Segmentor_ m_seg;
    //    ProbSegmentor m_seg;
public:
    PhraseNormalizer()
    {

    }
    PhraseNormalizer(const string& seg_dir)
    {
        init(seg_dir);
    }
    void init(const string& seg_dir)
    {
        m_seg.init(seg_dir);
    }
    string normalize(const string& input)
    {
        string phrase;
        //step1-------------------------繁体转简体，转半角，小写化
        phrase = m_converter.Normalize(input);
        if (phrase.empty())
            return "";
        phrase = filterString2(phrase);
        if (phrase.empty())
            return "";
        //step2-------------------------分词
        std::set<string> set_;
        m_seg.segment(phrase, set_);
        string rphrase;
        for (std::set<string>::iterator iter = set_.begin(); iter != set_.end(); ++iter)
        {
            rphrase += *iter;
        }
        return rphrase;
    }
    void normalize(const string& input, std::set<string>& set_)
    {
        string phrase;
        //step1-------------------------繁体转简体，转半角，小写化
        phrase = m_converter.Normalize(input);
        if (phrase.empty())
            return;
        phrase = filterString2(phrase);
        if (phrase.empty())
            return;
        m_seg.segment(phrase, set_);
    }
    string norm(const string& phrase)
    {
        std::set<string> set_;
        m_seg.segment(phrase, set_);
        string rphrase;
        for (std::set<string>::iterator iter = set_.begin(); iter != set_.end(); ++iter)
        {
            rphrase += *iter;
        }
        return rphrase;
    }
    void norm(const string& phrase, std::set<string>& set_)
    {
        m_seg.segment(phrase, set_);
    }
};
} //end of namespace phr_norm
#endif  //----end of PHRASE_NORMALIZER_H_
