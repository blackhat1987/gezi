/** 
 *  ==============================================================================
 * 
 *          \file   segment_prob_impl_omni.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-14 12:29:44.301665
 *  
 *  \Description:  增加支持概率全切分
 *
 *   TODO FIXME  由于概率切分增加了预处理岐义 这个全切分需要改正
 *  ==============================================================================
 */

#ifndef SEGMENT_PROB_IMPL_OMNI_H_
#define SEGMENT_PROB_IMPL_OMNI_H_

#include "segment_prob_impl.h"
#include "segment_impl.h"
namespace segment
{

class SegmentorProbImpl_withOmni : public SegmentorProbImpl
{
protected:
    int m_endid; //danzi end id
public:
    using SegmentorProbImpl::segmentCH;
    SegmentorProbImpl_withOmni()
    {

    }

    SegmentorProbImpl_withOmni(const string& dir)
    {
        init(dir);
    }

    bool init(const string& datrie_file, const string& encoder_file, const string& model_file, const string& ambi_file, const string& danzi_encode)
    {
        if (!SegmentorProbImpl::init(datrie_file, encoder_file, model_file, ambi_file))
            return false;
        std::ifstream ifs(danzi_encode.c_str());
        if (!ifs)
            return false;
        ifs >> m_endid;
        return true;
    }

    bool init(const string& dir)
    {
        if (!SegmentorProbImpl::init(dir))
            return false;
        string danzi_encode = dir + "/danzi_encode.log";
        std::ifstream ifs(danzi_encode.c_str());
        if (!ifs)
            return false;
        ifs >> m_endid;
        return true;
    }


    template<typename Container, typename RFunc>
    void segmentCH(Container& out, const short* code, int len, int offset, RFunc put, OmniSegWithAmbi)
    {
        DATrie::ResultType result;
        ngram::WordID start_id = ngram::kGapID, end_id = ngram::kGapID;
        int i = 0, level = 0;
        while (i < len)
        {
            if (result.length == 0)
            {
                while (i < len && !m_trie.searchLongest(code + i, len - i, result)) //没有成词
                {
                    put(out, offset + i * 2, 2, level);
                    i++;
                    start_id = ngram::kGapID;
                }
            }
            if (i < len) //有成词，从code+i位置开始长度为result.length是最大成词
            {
                int length = result.length;
                //如果考虑最小，那么不能单独成词的单字要在字典里面去掉
                int ambis_len = getAmbiLen(code + i, length, std::min(len - i, kMaxAmbiLen));
                if (ambis_len > length)
                {
                    length = ambis_len;
                    if (i + length == len || !m_trie.searchLongest(code + i + length, len - i - length, result))
                    {
                        end_id = ngram::kGapID;
                    }
                    else
                    {
                        end_id = result.value;
                    }
                    Lattice lattice;
                    buildLattice(lattice, code + i, length, start_id, end_id);
                    findBestPath(lattice, code + i, out, offset + i * 2, put);
                    start_id = end_id;
                }
                else
                {
                    if (length == 1)
                    {
                        level = 0;
                        put(out, offset + i * 2, length * 2, level);
                    }
                    else
                    {
                        vector<DATrie::ResultType> result_vec;
                        for (int j = i; j < i + length; j++)
                        {
                            m_trie.searchAll(code + j, i + length - j, result_vec);
                            for (size_t k = 0; k < result_vec.size(); k++)
                            {
                                level = j == i && k == result_vec.size() - 1 ? 0 : 1;
                                if (result_vec[k].length > 1 || result_vec[k].value <= m_endid) //不是单字，或者是有意义单字
                                {
                                    put(out, offset + j * 2, result_vec[k].length * 2, level);
                                }
                            }
                        }
                    }
                    result.length = 0;
                    start_id = result.value;
                }
                i += length;
            }
        }
    }

    template<typename Container, typename RFunc>
    int findBestPath(const Lattice& lattice, const short* code, Container& out, int offset, RFunc put)
    {//idx is staring pos at the end, start_idx is the finish倒序找最优path
        int level = 0;
        int idx = lattice.size() - 1;
        typedef std::map<State, LatticeStateVal>::const_iterator Iter;
        Iter iter = lattice[idx].begin(); //tail
        //        Pval(iter->second.pr);
        iter = iter->second.pre_state; //</s>
        idx = iter->second.pre_pos;
        int pos_vec[iter->second.len + 1];
        int l = 0;
        while (idx > 0)
        {
            pos_vec[l++] = idx;
            iter = iter->second.pre_state; //到post env
            idx = iter->second.pre_pos;
        }
        pos_vec[l++] = 0;
        for (int i = l - 2; i >= 0; i--)
        {
            int s = pos_vec[i + 1];
            int length = pos_vec[i] - pos_vec[i + 1];
            //            Pval(length);
            level = 0;
            if (length == 1)
            {
                put(out, offset + s * 2, length * 2, level); //level is 0
            }
            else
            {
                for (int j = s; j < s + length; j++)
                {
                    vector<DATrie::ResultType> result_vec;
                    m_trie.searchAll(code + j, s + length - j, result_vec);
                    //                    Pval(result_vec.size());
                    for (size_t k = 0; k < result_vec.size(); k++)
                    {
                        level = j == s && k == result_vec.size() - 1 ? 0 : 1;
                        //                        if (result_vec[k].length == 1)
                        //                        {
                        //                            Pval(result_vec[k].value);
                        //                            Pval(m_endid);
                        //                        }
                        if (result_vec[k].length > 1 || result_vec[k].value <= m_endid) //不是单字，或者是有意义单字
                        {
                            put(out, offset + j * 2, result_vec[k].length * 2, level);
                        }
                    }
                }
            }
        }
    }
};

} //----end of namespace segment

#endif  //----end of SEGMENT_PROB_IMPL_OMNI_H_
