/** 
 *  ==============================================================================
 * 
 *          \file   segmentor.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-09-28 20:53:10.658920
 *  
 *  \Description:   最大切分流程
 *                  1. 外部保证传过来的string经过normalize
 *                  2. 编码遇到没有编码的符号 单独成词 比如, 全角, 这是唯一的预处理切分
 *                     注意如果是空格连续的空格保留一个
 * 
 *                     之后如果串是全中文 则全中文处理
 *                     如果是全非中文 则 整个作为一个term
 *                     如果是中英文混合 考虑下面情况
 *                     adidas中国 -> adidas 中国
 *                     u盘 -> u盘 //成词中英文 不分开
 *                     哆拉A梦   //成词中英文 不分开
 *                     adidasab中国 -> adidasab 中国 英文词即使单独是字典里的串也不分开
 *                     ?是否字典里面不允许单独的英文词
 *
 *                     现在逻辑这样把
 *                     如果是英文开始的  判断最大查询
 *                     1. u盘 有返回结果 并且结果末尾是汉字的 继续
 *                     2. adidasab中国 有返回结果结尾是非汉字的尝试吞并后面的英文和数字
 *                     maxSegment提供上述功能，
 *                     MaxSegment提供原有方案即直接单字节双字节先切开。
 *
 *
 *      目标 对用户而言 确定使用不同的segmentor,或者相同的segmentor设置不同的策略参数
 *      调用相同的分词接口，只有4个
 *      1.最大切分
 *      2.最小切分
 *      3.全切分
 *      4.按字切分
 *
 *      提供如下策略
 *      1.是否反向匹配
 *      2.是否数字英文切分开
 *      3.是否允许单双字节混合的词 u盘
 *
 *  ==============================================================================
 */

#ifndef SEGMENTOR_H_
#define SEGMENTOR_H_
#include <iostream>

#include "compat.h"
#include "seg_type.h"
#include "gbk_encoder.h"
#include "datrie.h"
#include "segment_result_func.h"
#include "segment_impl_basic.h" //暂时只使用
#include "segment_prob_impl.h" //概率分词
#include "segment_punc.h"
#include "segment_result_func.h"
#include "segment_prob_impl_omni.h"

namespace segment {
template<typename SegmentorImpl, template<typename Ter> class ResultFunc_ = ResultFunc>
class SegmentorT
{ //当前只有两个模板参数，如果多了，可以考虑多一个间接层写Strategy配置
public:
    SegmentorT(const string& datrie_file, const string& encoder_file)
    : m_seg(datrie_file, encoder_file)
    {
    }
    SegmentorT(const string& datrie_file, const string& encoder_file, const string& model_file)
    : m_seg(datrie_file, encoder_file, model_file)
    {
    }
    SegmentorT(const string& dir)
    : m_seg(dir)
    {

    }
    SegmentorT()
    {

    }
    bool init(const string& datrie_file, const string& encoder_file)
    {
        return m_seg.init(datrie_file, encoder_file);
    }
    bool init(const string& datrie_file, const string& encoder_file, const string& model_file)
    {
       return m_seg.init(datrie_file, encoder_file, model_file);
    }
    bool init(const string& datrie_file, const string& encoder_file, const string& model_file, const string& ambi_file)
    {
        return m_seg.init(datrie_file, encoder_file, model_file, ambi_file);
    }
    bool init(const string& dir)
    {
        return m_seg.init(dir);
    }
    /**
     * 概率分词器可以先设置不使用岐义信息
     */
    void setNoAmbi()
    {
        m_seg.setNoAmbi();
    }
    /**
     * 默认切分
     */
    template<typename T>
    void segment(const string& key, T& out)
    {
        segment(key, out, MaxSegWithAmbi());
    }
    /**
     * 切分存储编号identifer
     */
    template<typename T>
    void segment_(const string& key, T& out)
    {
        segment(key, out, MaxSegWithIdentifer());
    }
    /**
     * 最大切分，不考虑离线岐义
     */
    template<typename T>
    void maxSegment_withoutAmbi(const string& key, T& out)
    {
        segment(key, out, MaxSegType()); //before we use MaxSeg
    }
    /**
     * 最大切分，考虑离线岐义
     */
    template<typename T>
    void maxSegment(const string& key, T& out)
    {
        segment(key, out, MaxSegWithAmbi());
    }
    /**
     * 以下函数均考虑了离线岐义，事实上只要不载入岐义词典 就相当于去掉了离线岐义
     * 全切分完整版,考虑离线岐义,尽量但是不保证补全路径
     */
    template<typename T>
    void omniSegment_fullAmbi(const string& key, T& out)
    {
        segment(key, out, OmniSegWithAmbiFull());
    }
    /**
     * 模仿IK的全切分,尽量不提出无意义单字
     */
    template<typename T>
    void omniSegment_IKAmbi(const string& key, T& out)
    {
        segment(key, out, OmniSegWithAmbiIK());
    }
    /**
     * 全切分并且完全补全路径
     */
    template<typename T>
    void omniSegment_fullAmbiPath(const string& key, T& out)
    {
        segment(key, out, OmniSegWithAmbiFullPath());
    }
    /**
     * 全切分（只考虑最大+最小切分并集),考虑离线岐义
     */
    template<typename T>
    void omniSegment(const string& key, T& out)
    {
        segment(key, out, OmniSegWithAmbi());
    }
    template<typename Container, typename SegType>
    void segment(const string& key, Container& out, SegType seg_type)
    {
        typedef typename Container::value_type Ter;
        int len = key.size();
        if (len > kStackAllocMax)
        {
            short * code = new short[len + KEYCNTMAX];
            if (!code)
                return;
            m_seg.segment(key.c_str(), key.length(), out, code, ResultFunc_<Ter > (key), seg_type);
            delete [] code;
        }
        else
        {
            short code[len + KEYCNTMAX];
            m_seg.segment(key.c_str(), key.length(), out, code, ResultFunc_<Ter > (key), seg_type);
        }
    }
    template<typename Container, typename SegType>
    bool segment(const string& key, Container& out, const char* buff, int buffSize, SegType seg_type)
    {
        typedef typename Container::value_type Ter;
        if (buffSize < int((key.size() + KEYCNTMAX) * sizeof (short)))
        {
            return false;
        }
        short *code = (short*) buff;
        m_seg.segment(key.c_str(), key.length(), out, code, ResultFunc_<Ter > (key), seg_type);
        return true;
    }
    template<typename Container, typename SegType>
    bool segment(const char* beg, const char* end, Container& out, const char* buff, int buffSize, SegType seg_type)
    {
        typedef typename Container::value_type Ter;
        if (NULL == beg || NULL == end || end < beg ||
                buffSize < int((end - beg + KEYCNTMAX) * sizeof (short)))
        {
            return false;
        }
        short *code = (short*) buff;
        int len = end - beg;
        m_seg.segment(beg, len, out, code, ResultFunc_<Ter > (string(beg, len)), seg_type);
        return true;
    }
    //-------------------下面是对外的原始接口的提供
    template<typename T>
    bool MaxSegment(const char* beg, const char* end, T& out, const char* buff, int buffSize)
    {
        return segment(beg, end, out, buff, buffSize, MaxSegWithAmbi());
    }
    template<typename T>
    bool OmniSegment(const char* beg, const char* end, T& out, const char* buff, int buffSize)
    {
        return segment(beg, end, out, buff, buffSize, OmniSegWithAmbi());
    }
    template<typename T>
    bool OmniSegment_IK(const char* beg, const char* end, T& out, const char* buff, int buffSize)
    {
        return segment(beg, end, out, buff, buffSize, OmniSegWithAmbiIK());
    }
    template<typename T>
    bool OmniSegment_FullPath(const char* beg, const char* end, T& out, const char* buff, int buffSize)
    {
        return segment(beg, end, out, buff, buffSize, OmniSegWithAmbiFullPath());
    }
    template<typename T>
    bool OmniSegment_Full(const char* beg, const char* end, T& out, const char* buff, int buffSize)
    {
        return segment(beg, end, out, buff, buffSize, OmniSegWithAmbiFull());
    }
    template<typename T>
    bool MaxSegment(const string& key, T& out, const char* buff, int buffSize)
    {
        return segment(key, out, buff, buffSize, MaxSegWithAmbi());
    }
    template<typename T>
    bool OmniSegment(const string& key, T& out, const char* buff, int buffSize)
    {
        return segment(key, out, buff, buffSize, OmniSegWithAmbi());
    }
    template<typename T>
    bool OmniSegment_IK(const string& key, T& out, const char* buff, int buffSize)
    {
        return segment(key, out, buff, buffSize, OmniSegWithAmbiIK());
    }
    template<typename T>
    bool OmniSegment_FullPath(const string& key, T& out, const char* buff, int buffSize)
    {
        return segment(key, out, buff, buffSize, OmniSegWithAmbiFullPath());
    }
    template<typename T>
    bool OmniSegment_Full(const string& key, T& out, const char* buff, int buffSize)
    {
        return segment(key, out, buff, buffSize, OmniSegWithAmbiFull());
    }


#ifdef CHG_DEBUG
    /**
     * 为了debug和展示
     * 展示给定词从首字开始有哪些词在字典中类型是什么，直接存成string, 如果是岐义展示岐义切分
     * 如"中国 : (0,2) : common : value : 切分"
     * 注意默认只支持中文的，如果有英文显示字符会出错
     */
    void searchAll(const string& key, vector<string>& out)
    {
        out.clear();
        vector<DATrie::ResultType> vec;
        typedef DATrie::CodeType CodeType;
        CodeType code;
        m_seg.m_encoder.getKeyCode(key, code);
        m_seg.m_trie.searchAll(code, vec);
        string word, word_type, ambi_seg, final_str;
        for (size_t i = 0; i < vec.size(); i++)
        {
            word = "";
            ambi_seg = "";
            if (vec[i].length * 2 <= key.size())
                word = key.substr(0, vec[i].length * 2);
            if (vec[i].value > KEYTYPEBIT)
            {
                int amb_info = (vec[i].value >> AMBOFFSET);
                if (vec[i].value & KEYTYPEBIT != ambiguity)
                {//即是common也是ambi
                    word_type = "ambi_and_common";
                }
                else
                {//仅仅是ambi
                    word_type = "ambi";
                }
                if (amb_info == DIANYALIGUO)
                {
                    word_type += ",DIANYALIGUO Type";
                }
                if (amb_info != DIANYALIGUO)
                    ambi_seg = ngram::getAmbiString2(word, amb_info, " / ");
            }
            else
            {
                if (vec[i].value < 0 || vec[i].value >= unknown)
                    word_type = LexTypeStr[unknown];
                else
                    word_type = LexTypeStr[vec[i].value];
            }
            final_str = (boost::format("%1% : %|20t|[0,%2%) : %|20t| %3% : %|40t| %4%")
                    % word % vec[i].length % word_type % ambi_seg).str();
            out.push_back(final_str);
        }
    }
#endif
private:
    SegmentorImpl m_seg;
    const static int kStackAllocMax = 1024;
};

//#define SEGMENTOR_TYPE(Name, SegImpl, PuncSeg, ResultFunc)\
//typedef SegmentorT< SegImpl<PuncSeg>, ResultFunc > Name
//
//#define SEG_TYPE(Name, PuncSeg)\
//typedef SegmentorT< SegmentorImpl_Basic<PuncSeg>, ResultFunc > Name
/**
 * SegmentorImpl_Old         采用不支持单双混合词的旧策略，直接首先切分开单双字节串,即走旧的分词主框架流程
 * PuncSegmentor_AlNumNoSeg  表示数字和英文不分开 图书分词测率
 */
//SEG_TYPE(Segmentor, PuncSegmentor_AlNumNoSeg);
//SEG_TYPE(B2CSegmentor, PuncSegmentor_AlNumSeg);
typedef SegmentorT< SegmentorImpl_Basic<PuncSegmentor_AlNumSeg, SegmentorImpl > > B2CSegmentor;
typedef SegmentorT< SegmentorImpl_Basic<PuncSegmentor_AlNumNoSeg, SegmentorImpl > > Segmentor;
typedef SegmentorT< SegmentorImpl_Basic<PuncSegmentor_AlNumSeg, SegmentorProbImpl > > B2CProbSegmentor;
typedef SegmentorT< SegmentorImpl_Basic<PuncSegmentor_AlNumNoSeg, SegmentorProbImpl > > ProbSegmentor;
//下面这个提供概率最大切分和概率全切分
typedef SegmentorT< SegmentorImpl_Basic<PuncSegmentor_AlNumNoSeg, SegmentorProbImpl_withOmni > > PrSegmentor;
} //----end of namespace segment
#endif  //----end of SEGMENTOR_H_
