/** 
 *  ==============================================================================
 * 
 *          \file   segment_impl_new.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2010-12-07 11:13:02.136562
 *  
 *  \Description:   ֧��u����Ĵ� ���� ��󲻿��������з��� Ŀǰ��֧�������㷨
 *  ==============================================================================
 */

#ifndef SEGMENT_IMPL_NEW_H_
#define SEGMENT_IMPL_NEW_H_
#include "segment_impl.h"
namespace segment
{

template<typename PuncSegFunc, typename SegmentorImpl_ = SegmentorImpl>
        class SegmentorImpl_New : private SegmentorImpl_
{
private:
    PuncSegFunc m_puncSegFunc;
public:
    using SegmentorImpl_::m_encoder;
    using SegmentorImpl_::m_trie;
    using SegmentorImpl_::segmentCH;

    SegmentorImpl_New(const string& datrie_file, const string& encoder_file)
    : SegmentorImpl_(datrie_file, encoder_file)
    {
    }

    template<typename Container, typename RFunc, typename SegType>
    void segment(const char* begin_, int len, Container& out, short* code, short* length, RFunc put, SegType seg_type)
    {
        out.clear();
        out.reserve(len);

        typedef const char* Iter;
        Iter cur, pre_cur, begin; //cur key���α�
        cur = pre_cur = begin = begin_;
        Iter end = cur + len;
        int code_cur = 0; //code �α�
        bool only_ch = true;
        int word_len = 0;
        int word_start = 0;
        int offset = 0;
        length[0] = 0;
        while (cur < end)
        {
            pre_cur = cur;
            //---------------------------------��ȡ״̬
            if (*cur >= 0) //���ֽ�
            {
                code[code_cur++] = m_encoder.getENCode(*cur);
                length[code_cur] = length[code_cur - 1] + 1;
                only_ch = false;
                ++cur;
            }
            else if (cur < end - 1) //˫�ֽ�
            {
                code[code_cur++] = m_encoder.getCHCode((unsigned char) *cur, (unsigned char) *(cur + 1));
                length[code_cur] = length[code_cur - 1] + 2;
                cur += 2;
            }
            else //��Ч�ַ�״̬
            {
                code[code_cur++] = 0;
                length[code_cur] = length[code_cur - 1] + 1;
                ++cur;
            }

            if (!code[code_cur - 1]) //��Ч�ַ�
            {
                if (word_len) //����ǰ��ı��봮��ע��û�б���Ϊ0�����
                {
                    if (only_ch) //ֻ�����ĵĴ�
                    {
                        maxSegmentCH(out, &code[code_cur - 1 - word_len], word_len, offset, put); //-1��Ϊ��Ҫ�����Ч�ַ�
                    }
                    else
                    {
                        maxSegmentMix(out, &code[code_cur - 1 - word_len], length + code_cur - word_len,
                                      code + 2 * len + 1, word_len, put);
                    }
                    word_len = 0;
                }
                offset = (int) (cur - begin);
                only_ch = true;
                put(out, (int) (pre_cur - begin), (int) (cur - pre_cur), 0); //�����ֿ�
            }
            else
            {
                word_len++;
            }
        }
        if (word_len) //�������һ�Σ�����еĻ�,˵�������ѭ�����һ������Ч״̬�ַ�������
        {
            if (only_ch) //ֻ�����ĵĴ�
            {
                segmentCH(out, &code[code_cur - word_len], word_len, offset, put, seg_type); //ע����ʼλ��code_cur - word_len
            }
            else
            {
                maxSegmentMix(out, &code[code_cur - word_len], length + code_cur - word_len + 1, code + 2 * len + 1, word_len, put);
            }
        }
    }

    template<typename Container, typename RFunc>
    void maxSegmentMix(Container& out, const short* code, const short* length, short* result, int len, RFunc put)
    {
        int level = 0;
        int i, j, nbeg, nend, kbeg, kend, index;
        int s;
        i = nbeg = nend = 0;
        int result_num = 0;
        while (i < len)
        {
            //���ҿɳɴ���
            while (i < len)
            {
                s = code[i];
                if (m_trie.canSearch(s) && (0 == i ||
                        true == segBoundCheck(code[i], code[i - 1])))
                { //���ܳɴ��ҷ�����߽�
                    break;
                }
                ++i;
            }
            if (i == len)
                break;
            //���ҳɴ�
            result_num = m_trie.searchAll2(code + i, len - i, result, KEYCNTMAX);
            if (result_num)
            {
                for (j = result_num - 1; j >= 0; j--)
                {
                    index = i + result[j];
                    if (index == len || true == segBoundCheck(code[index - 1], code[index]))
                    {
                        break;
                    }
                }
                if (j >= 0)
                {
                    m_puncSegFunc.segByPunc(out, code + nbeg, length + nbeg, i - nbeg, put);
                    put(out, length[i - 1], length[index - 1] - length[i - 1], level); //[nbeg, i , index] [nbeg,i) segByPunc [i,index]key //now index +1
                    nbeg = i = index;
                }
                else
                {
                    i++;
                }
            }
            else
            {
                i++;
            }
        }
        if (i > nbeg)
        {
            m_puncSegFunc.segByPunc(out, code + nbeg, length + nbeg, i - nbeg, put);
        }
    }
};

} //----end of namespace segment

#endif  //----end of SEGMENT_IMPL_NEW_H_
