/** 
 *  ==============================================================================
 * 
 *          \file   segmentor.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-09-28 20:53:10.658920
 *  
 *  \Description:   ����з�����
 *                  1. �ⲿ��֤��������string����normalize
 *                  2. ��������û�б���ķ��� �����ɴ� ����, ȫ��, ����Ψһ��Ԥ�����з�
 *                     ע������ǿո������Ŀո���һ��
 * 
 *                     ֮���������ȫ���� ��ȫ���Ĵ���
 *                     �����ȫ������ �� ������Ϊһ��term
 *                     �������Ӣ�Ļ�� �����������
 *                     adidas�й� -> adidas �й�
 *                     u�� -> u�� //�ɴ���Ӣ�� ���ֿ�
 *                     ����A��   //�ɴ���Ӣ�� ���ֿ�
 *                     adidasab�й� -> adidasab �й� Ӣ�Ĵʼ�ʹ�������ֵ���Ĵ�Ҳ���ֿ�
 *                     ?�Ƿ��ֵ����治��������Ӣ�Ĵ�
 *
 *                     �����߼�������
 *                     �����Ӣ�Ŀ�ʼ��  �ж�����ѯ
 *                     1. u�� �з��ؽ�� ���ҽ��ĩβ�Ǻ��ֵ� ����
 *                     2. adidasab�й� �з��ؽ����β�ǷǺ��ֵĳ����̲������Ӣ�ĺ�����
 *                     maxSegment�ṩ�������ܣ�
 *                     MaxSegment�ṩԭ�з�����ֱ�ӵ��ֽ�˫�ֽ����п���
 *
 *
 *      Ŀ�� ���û����� ȷ��ʹ�ò�ͬ��segmentor,������ͬ��segmentor���ò�ͬ�Ĳ��Բ���
 *      ������ͬ�ķִʽӿڣ�ֻ��4��
 *      1.����з�
 *      2.��С�з�
 *      3.ȫ�з�
 *      4.�����з�
 *
 *      �ṩ���²���
 *      1.�Ƿ���ƥ��
 *      2.�Ƿ�����Ӣ���зֿ�
 *      3.�Ƿ�����˫�ֽڻ�ϵĴ� u��
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
#include "segment_impl_basic.h" //��ʱֻʹ��
#include "segment_prob_impl.h" //���ʷִ�
#include "segment_punc.h"
#include "segment_result_func.h"
#include "segment_prob_impl_omni.h"

namespace segment {
template<typename SegmentorImpl, template<typename Ter> class ResultFunc_ = ResultFunc>
class SegmentorT
{ //��ǰֻ������ģ�������������ˣ����Կ��Ƕ�һ����Ӳ�дStrategy����
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
     * ���ʷִ������������ò�ʹ�������Ϣ
     */
    void setNoAmbi()
    {
        m_seg.setNoAmbi();
    }
    /**
     * Ĭ���з�
     */
    template<typename T>
    void segment(const string& key, T& out)
    {
        segment(key, out, MaxSegWithAmbi());
    }
    /**
     * �зִ洢���identifer
     */
    template<typename T>
    void segment_(const string& key, T& out)
    {
        segment(key, out, MaxSegWithIdentifer());
    }
    /**
     * ����з֣��������������
     */
    template<typename T>
    void maxSegment_withoutAmbi(const string& key, T& out)
    {
        segment(key, out, MaxSegType()); //before we use MaxSeg
    }
    /**
     * ����з֣������������
     */
    template<typename T>
    void maxSegment(const string& key, T& out)
    {
        segment(key, out, MaxSegWithAmbi());
    }
    /**
     * ���º�����������������壬��ʵ��ֻҪ���������ʵ� ���൱��ȥ�����������
     * ȫ�з�������,�����������,�������ǲ���֤��ȫ·��
     */
    template<typename T>
    void omniSegment_fullAmbi(const string& key, T& out)
    {
        segment(key, out, OmniSegWithAmbiFull());
    }
    /**
     * ģ��IK��ȫ�з�,��������������嵥��
     */
    template<typename T>
    void omniSegment_IKAmbi(const string& key, T& out)
    {
        segment(key, out, OmniSegWithAmbiIK());
    }
    /**
     * ȫ�зֲ�����ȫ��ȫ·��
     */
    template<typename T>
    void omniSegment_fullAmbiPath(const string& key, T& out)
    {
        segment(key, out, OmniSegWithAmbiFullPath());
    }
    /**
     * ȫ�з֣�ֻ�������+��С�зֲ���),�����������
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
    //-------------------�����Ƕ����ԭʼ�ӿڵ��ṩ
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
     * Ϊ��debug��չʾ
     * չʾ�����ʴ����ֿ�ʼ����Щ�����ֵ���������ʲô��ֱ�Ӵ��string, ��������չʾ����з�
     * ��"�й� : (0,2) : common : value : �з�"
     * ע��Ĭ��ֻ֧�����ĵģ������Ӣ����ʾ�ַ������
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
                {//����commonҲ��ambi
                    word_type = "ambi_and_common";
                }
                else
                {//������ambi
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
 * SegmentorImpl_Old         ���ò�֧�ֵ�˫��ϴʵľɲ��ԣ�ֱ�������зֿ���˫�ֽڴ�,���߾ɵķִ����������
 * PuncSegmentor_AlNumNoSeg  ��ʾ���ֺ�Ӣ�Ĳ��ֿ� ͼ��ִʲ���
 */
//SEG_TYPE(Segmentor, PuncSegmentor_AlNumNoSeg);
//SEG_TYPE(B2CSegmentor, PuncSegmentor_AlNumSeg);
typedef SegmentorT< SegmentorImpl_Basic<PuncSegmentor_AlNumSeg, SegmentorImpl > > B2CSegmentor;
typedef SegmentorT< SegmentorImpl_Basic<PuncSegmentor_AlNumNoSeg, SegmentorImpl > > Segmentor;
typedef SegmentorT< SegmentorImpl_Basic<PuncSegmentor_AlNumSeg, SegmentorProbImpl > > B2CProbSegmentor;
typedef SegmentorT< SegmentorImpl_Basic<PuncSegmentor_AlNumNoSeg, SegmentorProbImpl > > ProbSegmentor;
//��������ṩ��������зֺ͸���ȫ�з�
typedef SegmentorT< SegmentorImpl_Basic<PuncSegmentor_AlNumNoSeg, SegmentorProbImpl_withOmni > > PrSegmentor;
} //----end of namespace segment
#endif  //----end of SEGMENTOR_H_
