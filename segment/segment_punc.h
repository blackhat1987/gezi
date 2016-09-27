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
 * ����Ӣ�ķֿ���punc segmentor
 */
class PuncSegmentor_AlNumSeg
{
public:
    /**
     *  abc12,3 -> abc 12 , 3 ��Ӣ�ֿ�
     *  �����е�˫�ֽ�����İ����ָ�,SegImpl_Newʹ�� עSegImpl_NewΪʵ�����ʣ���ǰʹ��SegImpl_Basic
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

                if (i > pre) //�洢Ӣ�Ĵ�
                {
                    put(out, length[pre - 1], length[i - 1] - length[pre - 1], level);
                    pre = i;
                }
                while (i < len && code[i] > FRST_OFFSET_CH && isdigit(code[i] - FRST_OFFSET_CH + 31))
                {
                    i++;
                }
                if (i > pre) //�洢���ִ�
                {
                    put(out, length[pre - 1], length[i - 1] - length[pre - 1], level);
                    pre = i;
                }
            }
            //--���Ļ���Ӣ�ı��,�����洢
            if (i < len)
            {
                put(out, length[i - 1], length[i] - length[i - 1], level);
                pre = ++i;
            }
        }
    }

    /**
     * ֻ�е��ֽ�����ķָSegmentImpl_Basicʹ��
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
                if (i > pre) //�洢Ӣ�Ĵ�
                {
                    put(out, offset + pre, i - pre, level);
                    pre = i;
                }
                while (i < len && isdigit(code[i] - FRST_OFFSET_CH + 31))
                { // code[i] > FRST_OFFSET_CH ��ʾ���ֽ��ַ�
                    i++;
                }
                if (i > pre) //�洢���ִ�
                {
                    put(out, offset + pre, i - pre, level);
                    pre = i;
                }

            }
            //--Ӣ�ı��,�����洢
            if (i < len)
            {
                put(out, offset + i, 1, level);
                pre = ++i;
            }
        }
    }
};
/**
 * ����Ӣ�Ĳ��ֿ���punc segmentor
 */
class PuncSegmentor_AlNumNoSeg
{
public:
    /**
     *  abc12,3 -> abc12 , 3 ��Ӣ���ֿ�
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
            if (i > pre) //�洢Ӣ�Ĵ�
            {
                put(out, length[pre - 1], length[i - 1] - length[pre - 1], level);
                pre = i;
            }
            //--���Ļ���Ӣ�ı��,�����洢
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
            if (i > pre) //�洢Ӣ�Ĵ�
            {
                put(out, offset + pre, i - pre, level);
                pre = i;
            }
            //--Ӣ�ı��,�����洢
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
