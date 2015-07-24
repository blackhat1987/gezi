/** 
 *  ==============================================================================
 * 
 *          \file   segment_punc.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-10-10 15:39:20.806752
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef SEGMENT_PUNC_H_
#define SEGMENT_PUNC_H_
#include "seg_type.h"
#include "gbk_encoder.h"
#include "segment_result_func.h"
namespace segment
{
/**
 * 数字英文分开的punc segmentor
 */
class PuncSegmentor_AlNumSeg
{
public:
    /**
     *  abc12,3 -> abc 12 , 3 中英分开
     *  考虑有单双字节情况的案标点分割,SegImpl_New使用 注SegImpl_New为实验性质，当前使用SegImpl_Basic
     * No use right now
     */
    template<typename Container, typename RFunc>
    void segByPunc(Container& out, const short* code, const short* length, int len, RFunc put,
            int level = 0)
    {
        int i = 0;
        int pre = 0;
        while (i < len)
        {
            while (i < len && code[i] > FRST_OFFSET_CH && isalnum(code[i] - FRST_OFFSET_CH + 31))
            {
                while (i < len && code[i] > FRST_OFFSET_CH && isalpha(code[i] - FRST_OFFSET_CH + 31))
                {
                    i++;
                }

                if (i > pre) //存储英文串
                {
                    put(out, length[pre - 1], length[i - 1] - length[pre - 1], level);
                    pre = i;
                }
                while (i < len && code[i] > FRST_OFFSET_CH && isdigit(code[i] - FRST_OFFSET_CH + 31))
                {
                    i++;
                }
                if (i > pre) //存储数字串
                {
                    put(out, length[pre - 1], length[i - 1] - length[pre - 1], level);
                    pre = i;
                }
            }
            //--中文或者英文标点,单个存储
            if (i < len)
            {
                put(out, length[i - 1], length[i] - length[i - 1], level);
                pre = ++i;
            }
        }
    }

    /**
     * 只有单字节情况的分割，SegmentImpl_Basic使用
     * This is used right now
     */
    template<typename Container, typename RFunc>
    void segByPuncEN(Container& out, const short* code, int len, int offset, RFunc put, int level = 0)
    {
        int i = 0;
        int pre = 0;
        while (i < len)
        {
            while (i < len && code[i] && isalnum(code[i] - FRST_OFFSET_CH + 31))
            {
                while (i < len && isalpha(code[i] - FRST_OFFSET_CH + 31))
                {
                    i++;
                }
                if (i > pre) //存储英文串
                {
                    put(out, offset + pre, i - pre, level);
                    pre = i;
                }
                while (i < len && isdigit(code[i] - FRST_OFFSET_CH + 31))
                { // code[i] > FRST_OFFSET_CH 表示单字节字符
                    i++;
                }
                if (i > pre) //存储数字串
                {
                    put(out, offset + pre, i - pre, level);
                    pre = i;
                }

            }
            //--英文标点,单个存储
            if (i < len)
            {
                put(out, offset + i, 1, level);
                pre = ++i;
            }
        }
    }
};
/**
 * 数字英文不分开的punc segmentor
 */
class PuncSegmentor_AlNumNoSeg
{
public:
    /**
     *  abc12,3 -> abc12 , 3 中英不分开
     */
    template<typename Container, typename RFunc>
    void segByPunc(Container& out, const short* code, const short* length, int len, RFunc put,
            int level = 0)
    {
        int i = 0;
        int pre = 0;
        while (i < len)
        {
            while (i < len && code[i] > FRST_OFFSET_CH && isalnum(code[i] - FRST_OFFSET_CH + 31))
            {
                i++;
            }
            if (i > pre) //存储英文串
            {
                put(out, length[pre - 1], length[i - 1] - length[pre - 1], level);
                pre = i;
            }
            //--中文或者英文标点,单个存储
            if (i < len)
            {
                put(out, length[i - 1], length[i] - length[i - 1], level);
                pre = ++i;
            }
        }
    }
    template<typename Container, typename RFunc>
    void segByPuncEN(Container& out, const short* code, int len, int offset, RFunc put, int level = 0)
    {
        int i = 0;
        int pre = 0;
        while (i < len)
        {
            while (i < len && code[i] && isalnum(code[i] - FRST_OFFSET_CH + 31))
            {
                i++;
            }
            if (i > pre) //存储英文串
            {
                put(out, offset + pre, i - pre, level);
                pre = i;
            }
            //--英文标点,单个存储
            if (i < len)
            {
                put(out, offset + i, 1, level);
                pre = ++i;
            }
        }
    }
};

} //----end of namespace segment

#endif  //----end of SEGMENT_PUNC_H_
