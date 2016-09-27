/** 
 *  ==============================================================================
 * 
 *          \file   segment_impl_basic_Identifer.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-25 11:12:54.243277
 *  
 *  \Description:  存储编号。。。 其余一样  TODO 怎么解决这种代码重复:)
 *  ==============================================================================
 */

#ifndef SEGMENT_IMPL_BASIC_IDENFIFER_H_
#define SEGMENT_IMPL_BASIC_IDENTIFER_H_

#include "ngram_types.h"

//#include "segment_prob_impl.h"
namespace segment
{
//TODO 这里其实可以考虑 template<typename T, typname Base> class SegmentorImpl_Basic : Base<T> 从而选取不同的base
//避免各种方法的的切分算法堆积到sgement_impl.h 模板参数对应PuncSeg method

template<typename PuncSegFunc, typename SegmentorImpl_ >
class SegmentorImpl_Basic_Identifer : private SegmentorImpl_
{
private:
    PuncSegFunc m_puncSegFunc;
public:
    using SegmentorImpl_::m_encoder;
    using SegmentorImpl_::m_trie;
    using SegmentorImpl_::segmentCH;
    using SegmentorImpl_::init;

    SegmentorImpl_Basic_Identifer(const string& datrie_file, const string& encoder_file)
    : SegmentorImpl_(datrie_file, encoder_file)
    {
    }

    SegmentorImpl_Basic_Identifer(const string& datrie_file, const string& encoder_file, const string& model_file)
    : SegmentorImpl_(datrie_file, encoder_file, model_file)
    {
    }

    SegmentorImpl_Basic_Identifer(const string& dir)
    : SegmentorImpl_(dir)
    {
    }

    SegmentorImpl_Basic_Identifer()
    {

    }

    void init(const string& datrie_file, const string& encoder_file)
    {
        SegmentorImpl_::init(datrie_file, encoder_file);
    }

    void init(const string& datrie_file, const string& encoder_file, const string& model_file)
    {
        SegmentorImpl_::init(datrie_file, encoder_file, model_file);
    }

    void init(const string& dir)
    {
        SegmentorImpl_::init(dir);
    }

    //    template<typename Container, typename RFunc, SegType seg_type>

    template<typename Container, typename RFunc, typename SegType>
    void segment(const char* begin, int len, Container& out, short* code, RFunc put, SegType seg_type)
    {
        out.clear();
        //        out.reserve(len);  //is this matter big to speed?

        typedef const char* Iter;
        Iter cur, pre_cur, beg; //cur key的游标
        cur = beg = begin;
        Iter end = cur + len;
        int code_cur = 0; //code 游标
        int pre_code_cur;
        while (cur < end)
        {
            //----------single byte EN
            pre_cur = cur;
            pre_code_cur = code_cur;
            while (cur < end && *cur >= 0)
            {
                code[code_cur++] = m_encoder.getENCode(*cur);
                ++cur;
            }
            if (cur > pre_cur)
            {
                segmentEN(out, code + pre_code_cur, (int) (code_cur - pre_code_cur),
                          (int) (pre_cur - beg), put, seg_type);
            }
            //---if half word
            if (cur == end - 1)
            {
                put(out, ngram::kUnknownID, 0, 0);
                break;
            }

            pre_cur = cur;
            //------------double byte CH, non-gbk-chinese
            while (cur < end - 1 && *cur < 0 &&
                    !isGBKCH((unsigned char) *cur, (unsigned char) *(cur + 1)))
            {
                put(out, ngram::kUnknownID, 0, 0);
                cur += 2;
            }

            pre_code_cur = code_cur;
            pre_cur = cur;
            //------------double byte chinese
            while (cur < end - 1 && *cur < 0 &&
                    isGBKCH((unsigned char) *cur, (unsigned char) *(cur + 1)))
            {
                code[code_cur++] =
                        m_encoder.getCHCode((unsigned char) *cur, (unsigned char) *(cur + 1));
                cur += 2;
            }
            if (code_cur > pre_code_cur)
            {
                segmentCH(out, code + pre_code_cur, code_cur - pre_code_cur, (int) (pre_cur - beg), put, seg_type);
            }
        }
    }

    template<typename Container, typename RFunc, typename SegType>
    void segmentEN(Container& out, const short* code, int len, int offset, RFunc put, SegType seg_type)
    {
        int level = 0;
        int i, j, nbeg, nend, kbeg, kend, index;
        int s;
        i = nbeg = nend = 0;
        int result_num = 0;
        vector<DATrie::ResultType> result_vec;
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
            result_num = m_trie.searchAll2(code + i, len - i, result_vec); //TODO FIXME 上面冗余 修改流程
            if (result_num)
            {
                for (j = result_num - 1; j >= 0; j--)
                {
                    index = i + result_vec[j].length;
                    if (index == len || true == segBoundCheck(code[index - 1], code[index]))
                    {
                        break;
                    }
                }
                if (j >= 0)
                {
                    m_puncSegFunc.segByPuncEN(out, code + nbeg, i - nbeg, offset + nbeg, put);
                    put(out, result_vec[j].value, 0, level); //[nbeg, i , index] [nbeg,i) segByPunc [i,index]key
                    addSegByPunc(out, code + i, index - i, offset + i, put, 1, seg_type); //level is 1
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
            m_puncSegFunc.segByPuncEN(out, code + nbeg, i - nbeg, offset + nbeg, put);
        }
    }
private:

    template<typename Container, typename RFunc>
    void addSegByPunc(Container& out, const short* code, int len, int offset, RFunc put,
                      int level, MaxSegBase)
    {

    }

    template<typename Container, typename RFunc>
    void addSegByPunc(Container& out, const short* code, int len, int offset, RFunc put,
                      int level, OmniSegBase)
    {
        m_puncSegFunc.segByPuncEN(out, code, len, offset, put, level);
    }
};

} //----end of namespace segment

#endif  //----end of SEGMENT_IMPL_BASIC_IDENTIFER_H_
