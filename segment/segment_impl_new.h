/** 
 *  ==============================================================================
 * 
 *          \file   segment_impl_new.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2010-12-07 11:13:02.136562
 *  
 *  \Description:   支持u盘类的词 除了 最大不考虑岐义的切分外 目前不支持其它算法
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
        Iter cur, pre_cur, begin; //cur key的游标
        cur = pre_cur = begin = begin_;
        Iter end = cur + len;
        int code_cur = 0; //code 游标
        bool only_ch = true;
        int word_len = 0;
        int word_start = 0;
        int offset = 0;
        length[0] = 0;
        while (cur < end)
        {
            pre_cur = cur;
            //---------------------------------获取状态
            if (*cur >= 0) //单字节
            {
                code[code_cur++] = m_encoder.getENCode(*cur);
                length[code_cur] = length[code_cur - 1] + 1;
                only_ch = false;
                ++cur;
            }
            else if (cur < end - 1) //双字节
            {
                code[code_cur++] = m_encoder.getCHCode((unsigned char) *cur, (unsigned char) *(cur + 1));
                length[code_cur] = length[code_cur - 1] + 2;
                cur += 2;
            }
            else //无效字符状态
            {
                code[code_cur++] = 0;
                length[code_cur] = length[code_cur - 1] + 1;
                ++cur;
            }

            if (!code[code_cur - 1]) //无效字符
            {
                if (word_len) //处理前面的编码串，注意没有编码为0的情况
                {
                    if (only_ch) //只有中文的串
                    {
                        maxSegmentCH(out, &code[code_cur - 1 - word_len], word_len, offset, put); //-1因为需要跨过无效字符
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
                put(out, (int) (pre_cur - begin), (int) (cur - pre_cur), 0); //单独分开
            }
            else
            {
                word_len++;
            }
        }
        if (word_len) //处理最后一段，如果有的话,说明上面的循环最后一个是有效状态字符结束的
        {
            if (only_ch) //只有中文的串
            {
                segmentCH(out, &code[code_cur - word_len], word_len, offset, put, seg_type); //注意起始位置code_cur - word_len
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
            //查找可成词首
            while (i < len)
            {
                s = code[i];
                if (m_trie.canSearch(s) && (0 == i ||
                        true == segBoundCheck(code[i], code[i - 1])))
                { //可能成词且符合左边界
                    break;
                }
                ++i;
            }
            if (i == len)
                break;
            //查找成词
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
