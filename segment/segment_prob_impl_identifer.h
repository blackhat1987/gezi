/** 
 *  ==============================================================================
 * 
 *          \file   segment_prob_impl_identifer.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-24 15:41:43.672123
 *  
 *  \Description:   �����з֣�������洢Ϊvector<int>����set<int> �ڲ��洢���Ǵʵı��identifer
 *  ==============================================================================
 */

#ifndef SEGMENT_PROB_IMPL_IDENTIFER_H_
#define SEGMENT_PROB_IMPL_IDENTIFER_H_

#include "segment_prob_impl.h"
#include "ngram_model/ngram_types.h"


namespace segment {
class SegmentorProbIdentiferImpl : public SegmentorProbImpl
{
public:
    SegmentorProbIdentiferImpl(const string& dir)
    : SegmentorProbImpl(dir)
    {

    }
    SegmentorProbIdentiferImpl()
    {

    }
        template<typename Container, typename RFunc>
    void segmentCH(Container& out, const short* code, int len, int offset, RFunc put, MaxSegWithIdentifer)
    {
        DATrie::ResultType result;
        ngram::WordID start_id = ngram::kGapID, end_id = ngram::kGapID;
        int i = 0, level = 0;
        while (i < len)
        {
            if (result.length == 0)
            {
                while (i < len && !m_trie.searchLongest(code + i, len - i, result)) //û�гɴ�
                {
                    put(out, ngram::kUnknownID, 0, level);
                    i++;
                    start_id = ngram::kGapID;
                }
            }
            if (i < len) //�гɴʣ���code+iλ�ÿ�ʼ����Ϊresult.length�����ɴ�
            {
                if (isAmbi(result.value))
                {//�ô���Ԥ���������
                    //                    Pval(result.value);
                    //                    Pval(getAmbi(result.value));
                    int ambi_len = addAmbi(out, getAmbi(result.value), offset + i * 2, level, put);
                    start_id = ngram::kGapID; //����зֺ�ǰ���Ǹ��ʲ��õõ���,��ȻҲ���Բ����Ƚ��鷳
                    i += ambi_len;
                    result.length = 0;
                }
                else
                {
                    int length = result.length;
                    //���������С����ô���ܵ����ɴʵĵ���Ҫ���ֵ�����ȥ��
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
                            if (!isAmbi(result.value))
                                end_id = result.value;
                            else
                                end_id = ngram::kGapID;
                        }
                        Lattice lattice;
                        buildLattice(lattice, code + i, length, start_id, end_id);
                        findBestPath(lattice, out, offset + i * 2, put);
                        start_id = end_id;
                    }
                    else
                    {
                        length = ambis_len;
                        put(out, result.value, 0, level);
                        result.length = 0;
                        start_id = result.value;
                    }
                    i += length;
                }
            }
        }
    }
//    template<typename Container, typename RFunc>
//    void segmentCH(Container& out, const short* code, int len, int offset, RFunc put, MaxSegWithIdentifer)
//    {
//        DATrie::ResultType result;
//        ngram::WordID start_id = ngram::kGapID, end_id = ngram::kGapID;
//        int i = 0, level = 0;
//        while (i < len)
//        {
//            if (result.length == 0)
//            {
//                while (i < len && !m_trie.searchLongest(code + i, len - i, result)) //û�гɴ�
//                {
//                    put(out, offset + i * 2, 2, level);
//                    i++;
//                    start_id = ngram::kGapID;
//                }
//            }
//            if (i < len) //�гɴʣ���code+iλ�ÿ�ʼ����Ϊresult.length�����ɴ�
//            {
//                if (isAmbi(result.value))
//                {//�ô���Ԥ���������
//                    //                    Pval(result.value);
//                    //                    Pval(getAmbi(result.value));
//                    int ambi_len = addAmbi(out, getAmbi(result.value), offset + i * 2, level, put);
//                    start_id = ngram::kGapID; //����зֺ�ǰ���Ǹ��ʲ��õõ���,��ȻҲ���Բ����Ƚ��鷳
//                    i += ambi_len;
//                    result.length = 0;
//                }
//                else
//                {
//                    int length = result.length;
//                    //���������С����ô���ܵ����ɴʵĵ���Ҫ���ֵ�����ȥ��
//                    int ambis_len = getAmbiLen(code + i, length, std::min(len - i, kMaxAmbiLen));
//                    if (ambis_len > length)
//                    {
//                        length = ambis_len;
//                        if (i + length == len || !m_trie.searchLongest(code + i + length, len - i - length, result))
//                        {
//                            end_id = ngram::kGapID;
//                        }
//                        else
//                        {
//                            if (!isAmbi(result.value))
//                                end_id = result.value;
//                            else
//                                end_id = ngram::kGapID;
//                        }
//                        Lattice lattice;
//                        buildLattice(lattice, code + i, length, start_id, end_id);
//                        findBestPath(lattice, out, offset + i * 2, put);
//                        start_id = end_id;
//                    }
//                    else
//                    {
//                        length = ambis_len;
//                        put(out, offset + i * 2, length * 2, level);
//                        result.length = 0;
//                        start_id = result.value;
//                    }
//                    i += length;
//                }
//            }
//        }
//    }
    template<typename Container, typename RFunc>
    void findBestPath(const Lattice& lattice, Container& out, int offset, RFunc put)
    {//idx is staring pos at the end, start_idx is the finish����������path
        int level = 0;
        int idx = lattice.size() - 1;
        typedef std::map<State, LatticeStateVal>::const_iterator Iter;
        Iter iter = lattice[idx].begin(); //tail
        //        Pval(iter->second.pr);
        iter = iter->second.pre_state; //</s>
        idx = iter->second.pre_pos;
        int val_vec[iter->second.len];
        int l = 0;
        while (idx > 0)
        {
            //            pos_vec[l++] = idx;
            val_vec[l++] = (iter->first).back();
            iter = iter->second.pre_state; //��post env
            idx = iter->second.pre_pos;
        }
        //        pos_vec[l++] = 0;
        for (int i = l - 1; i >= 0; i--)
        {
            //            put(out, offset + pos_vec[i + 1] * 2, (pos_vec[i] - pos_vec[i + 1])* 2, level); //level is 0
            put(out, val_vec[i], 0, level);
        }
    }
};

} //----end of namespace segment

#endif  //----end of SEGMENT_PROB_IMPL_IDENTIFER_H_
