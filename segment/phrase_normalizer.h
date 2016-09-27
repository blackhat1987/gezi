/** 
 *  ==============================================================================
 * 
 *          \file   phrase_normalizer.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-24 11:30:22.321769
 *  
 *  \Description:  һ���������Ķ����һ������,
 *                 ���𷱼���ת����filterstring, �ִʣ�ȥ��ͣ�ôʣ��ظ��ʣ�����ת��һ����ʽ�����������ȵ���������
 *
 *   ���������� �ֿ��Ĵ� ����� �Ͳ�����ƴ���� u��
 *   �Ƿ���� ��Ӣ�Ĳ�ǿ�Ʒֿ�������? TODO
 *
 *   Ӧ������ Ů�˶�Ь �˶�ЬŮ
 *
 *   ��� ���˶�����Ӧ�����ֵ���
 *   �˶�Ь -> �˶�����Ь   �������ʺϰ�����չ�ʴ����
 *   ��Ȼ ���˶���Ь�� ����ƥ��������Ҳ���ԣ����ǶԹ����˵��̫��
 *   TODO ��Ҫ��ʼ����ȥ���ո���
 *  ==============================================================================
 */

#ifndef PHRASE_NORMALIZER_H_
#define PHRASE_NORMALIZER_H_

#include "ch_stoper.h"
#include "gbk_ch_converter.h"
#include "string_help.h"
#include "segmentor.h" //�ִ�

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
        //step1-------------------------����ת���壬ת��ǣ�Сд��
        phrase = m_converter.Normalize(input);
        if (phrase.empty())
            return "";
        phrase = filterString2(phrase);
        if (phrase.empty())
            return "";
        //step2-------------------------�ִ�
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
        //step1-------------------------����ת���壬ת��ǣ�Сд��
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
