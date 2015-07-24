/** 
 *  ==============================================================================
 * 
 *          \file   segment_prob_impl.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-05 17:54:19.116240
 *  
 *  \Description:  ����ngramģ�͵���������зִַʣ��ṩ���°汾
 *                         1. ������ȫ�����з�
 *                         2. ��֤�����岿������з֣�ֻ�Կ���������Ĳ��֣�����ǰ���ﾳ�߸���ģ�͸����з֣��ο�sun ƴ��������
 *                        �ԱȽ����Ч��
 *
 *    ���ڵ�����ԭ��
 *    1.����·�����ȶ̵�����
 *    2. ���ʴ������ ����ȡ�� log ������-�� ���Ǵ������ Ҳ���Ǿ���ֵС������ ����1/8-> -3 ���� 1/16->-4
 *    pr *  6M/S  ԭ�����ִ��޸��ʴ��20M/S
 *
 *   2011.01.14   ���Ӹ�������зֻ����ϵ�ȫ�з֣�����ÿһ���� �� ȥ�ڲ�ÿ��λ�� ���ҿ��ܵĴʡ�����
 *   ��Ҫ����һ��������ĵ��֡���֤������ĵ��ֲ��ٱ��г������ٶȿ��ܱȽ�����Ҫ���ԣ����ʹ��Ӧ��û���⡣
 *
 *   �����㷨��Ҫ���Ӷ� Ԥ�������崮��֧��
 *  ==============================================================================
 */

#ifndef SEGMENT_PROB_IMPL_H_
#define SEGMENT_PROB_IMPL_H_
#include <map>
#include "seg_type.h"
#include "seg_common.h"
#include "gbk_encoder.h"
#include "datrie.h"
#include "segment_result_func.h"
#include "ngram_model.h"
#include "ngram_types.h"
//#include "serialize_help.h"
namespace segment
{
//ע���������������ģ������������ڲ�����LatticeStateVal������
typedef vector<ngram::WordID> State; //TODO do not use vector use array instead than NgramModel must be һ��

/* ����ģ�͵�״̬�ڵ㣬����״̬��Ϣ��ÿ��״̬�ڵ�λ��lattice��һ��idx������*/
struct LatticeStateVal
{
    typedef std::map<State, LatticeStateVal>::const_iterator Iter;
    int pre_pos; /**���ĸ�λ����������,������Ҫ��¼�зֵ�λ��*/
    Iter pre_state; /**���ĸ�״̬��ת����*/
    //        State state; /**��ǰ״̬(δ����������) state.back()��Ӧ��ǰwordid,ֻ���Ի�Ҫ��¼�����Ϊ��ͬlatticeλ�õ���ͬstateֻȡһ�����pr*/
    double pr; /**��״̬�ĸ���ֵ*/
    short len; /**���˼��������˼���*/
    short total_len_square; /**ÿ����С��ƽ��֮��*/

    LatticeStateVal()
    : pre_pos(-1), len(0), total_len_square(0)
    {
    }

    LatticeStateVal(int pre_pos_, const Iter& pre_state_, double pr_, short len_ = 0, short len2_ = 0)
    : pre_pos(pre_pos_), pre_state(pre_state_), pr(pr_), len(len_), total_len_square(len2_)
    {
    }

    bool operator>(const LatticeStateVal & other) const
    {
        return len < other.len || (len == other.len && pr > other.pr);
    }
};

struct FinalStateGreater
{

    bool operator() (const LatticeStateVal& l, const LatticeStateVal & r) const
    {
        //        Pval(l.pr);
        //        Pval(r.pr);
        //        Pval((std::max(l.pr, r.pr) / std::min(l.pr, r.pr)));
        //        Pval(l.len);
        //        Pval(r.len);
        if (l.pr > -0.000000001)
            return true;
        if (r.pr > -0.000000001)
            return false;
        if (l.len < r.len)
            return true;
        else if (l.len == r.len)
        {
            if (std::max(l.pr, r.pr) / std::min(l.pr, r.pr) < threshold)
            {//�����нϴ��� TODO���ʵĲ�� ���ܲ���׼ȷ ����·��Խ�� ������Ҫ�趨��thresholdֵԽ��Щ
                //                Pval(l.pr);
                //                Pval(r.pr);
                //                Pval((std::max(l.pr, r.pr) / std::min(l.pr, r.pr)));
                return l.pr > r.pr;
            }
            else
            {//���ʽӽ�,����ѡ�񷽲�С�� ���Ϻ����г�" > "�Ϻ��У����� ��ΰ������ƥ�䡱��ѹ������">"�磬ѹ����"
                //����ע�ⲻ��ȫ��ͬ���ƥ�䣬��Ϊ�������崮�ɶ���2��·�����ɣ��൱ѡȡ���һ����̵�·��
                return l.total_len_square < r.total_len_square || (l.total_len_square == r.total_len_square &&
                        l.pre_state->second.pre_pos > r.pre_state->second.pre_pos); //��������</s>�����ﾳ
            }
        }
        else
            return false;
        //        return  (l.len < r.len) || ( l.len == r.len && ( (l.pr / r.pr < threshold) ||  )
    }
};
typedef std::map<State, LatticeStateVal> LatticeColumn;
typedef vector<LatticeColumn> Lattice;

class SegmentorProbImpl
{
protected:
    typedef ngram::Model NgramModel;
    DATrie m_trie; ///������
    Encoder m_encoder; ///��չgb2312�ʱ���
    NgramModel m_model; ///����ģ��
    vector<int> m_ambi; ///��¼�����Ϣ
    int m_ambiStartID; ///��忪ʼIDע�����û���κ������Ϣ����Ϊ��󣬱�֤������id�� < �����������id
    bool m_useAmbi; ///�����Ƿ�ʹ�������Ϣ
    //     const static int kMaxAmbiLen = 15; //��ǰ���������崮>=16��Ϊ ���Ǵ洢��ʱ��ֻ��ռ��16��λ��,ע�������ģ�ͱ���һ��
public:

    SegmentorProbImpl(const string& datrie_file, const string& encoder_file, const string& model_file)
    : m_trie(datrie_file), m_encoder(encoder_file), m_model(model_file),
    m_ambiStartID(std::numeric_limits<int>::max()), m_useAmbi(true)
    {
    }

    SegmentorProbImpl(const string& dir)
    :m_ambiStartID(std::numeric_limits<int>::max()), m_useAmbi(true)
    {
        init(dir);
    }

    SegmentorProbImpl()
    : m_ambiStartID(std::numeric_limits<int>::max()), m_useAmbi(true)
    {

    }

    void setNoAmbi()
    {
        m_useAmbi = false;
    }

    bool loadAmbi(const string& file)
    {
        //        return serialize_help::load(m_ambi, file);
        std::ifstream ifs(file.c_str(), std::ios::binary);
        if (!ifs.is_open())
        {
            LOG(WARNING) << "Loading ambi file fail so no amib info " << file << "\n";
            return false;
        }
        int ambi_size;
        ifs.read(reinterpret_cast<char*> (&ambi_size), sizeof (int));
        m_ambi.resize(ambi_size);
        ifs.read(reinterpret_cast<char*> (&m_ambi[0]), sizeof (int) * ambi_size);
        if (m_ambi.size() > 1) //�������Ϣ
        {
            m_ambiStartID = m_ambi.back();
        }
        else
        {
            LOG(WARNING) << "No ambi info in the ami file!" << file << "\n";
            return false;
        }
        LOG(INFO) << "Ambi size is " << m_ambi.size() << "\n";
        return true;
    }

    bool init(const string& datrie_file, const string& encoder_file, const string& model_file)
    {
        LOG(INFO) << "SegmentorProbImpl init---" << "\n";
        LOG(INFO) << "Loading trie" << "\n";
        if (!m_trie.load(datrie_file))
            return false;
        LOG(INFO) << "Loading gbk encoder" << "\n";
        if (!m_encoder.load(encoder_file))
            return false;
        LOG(INFO) << "Loading ngram model" << "\n";
        if (!m_model.load(model_file))
            return false;
        Pval(m_model.useLogPr());
        Pval(m_model.getN());
        assert(m_model.useLogPr());
        return true;
    }

    bool init(const string& datrie_file, const string& encoder_file, const string& model_file, const string& ambi_file)
    {
        if (!init(datrie_file, encoder_file, model_file))
            return false;

        LOG(INFO) << "Loading ambi encode" << "\n";
        return loadAmbi(ambi_file);
    }

    bool init(const string& dir)
    {
        string datrie_file = dir + "/datrie.idx";
        string encode_file = dir + "/gbk_encode.idx";
        string model_file = dir + "/ngram_model.idx";
        if (m_useAmbi)
        {
            string ambi_file = dir + "/ambi_encode.idx";
            return init(datrie_file, encode_file, model_file, ambi_file);
        }
        else
        {
            return init(datrie_file, encode_file, model_file);
        }
    }

public:

    /**
     * �Ƿ������id ,�����ʹ�������Ϣ����ô��Ȼid < m_ambiStartID
     */
    bool isAmbi(int id)
    {
        return id >= m_ambiStartID;
    }

    int getAmbi(int id)
    {//����Ƶ�����ò���Խ���ж�
        return m_ambi[id - m_ambiStartID];
    }

    template<typename Container, typename RFunc>
    int addAmbiMax(Container& out, int ambi_info, int pos, int level, RFunc put)
    {
        int start = pos;
        short len = 0;
        while (ambi_info)
        {
            len = 2;
            while ((ambi_info & 1) == 0)
            {
                ambi_info >>= 1;
                len += 2;
            }
            ambi_info >>= 1;
            if (ambi_info)
            { //β��������һ������������� ���� ��ǳ��,�ס� ��ǳ�ư�ɫ�� -> ��ǳ�ƣ���ɫ"
                put(out, pos, len, level);
                pos += len;
            }
        }
        return (pos - start) / 2;
    }

    /**���׼�򵥵�����·��ȥ�������з�*/
    template<typename Container, typename RFunc>
    void segmentCH(Container& out, const short* code, int len, int offset, RFunc put, MaxProbSeg)
    {
        Lattice lattice;
        //��̬�滮����·����������ֵ�洢��tail
        buildLattice(lattice, code, len);
        //��ȡ����·��
        findBestPath(lattice, out, offset, put);
    }

    template<typename Container, typename RFunc>
    void segmentCH(Container& out, const short* code, int len, int offset, RFunc put, MaxSegWithAmbi)
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
                    put(out, offset + i * 2, 2, level);
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
                    int ambi_len = addAmbiMax(out, getAmbi(result.value), offset + i * 2, level, put);
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
                        put(out, offset + i * 2, length * 2, level);
                        result.length = 0;
                        start_id = result.value;
                    }
                    i += length;
                }
            }
        }
    }
protected:

    /**��̬�滮ȫ�з����·��*/
    void buildLattice(Lattice& lattice, const short* code, int len, ngram::WordID start_id = ngram::kGapID, ngram::WordID end_id = ngram::kGapID)
    {//TODO �Ƿ��ǿ����Ż��� ����sun ƴ����״̬ת�������� ������Ȼ���ֲ��ҿ���
        lattice.resize(len + 3);
        //------��ʼ��head <s>
        int idx = 0;
        typedef LatticeColumn::const_iterator Iter;
        State state(1, start_id);
        typedef std::pair<State, LatticeStateVal> Pair;

        double pr = 0.0;
        if (start_id != ngram::kGapID)
            pr = m_model.getPr(&state[0], state.size());
        LatticeStateVal lattice_state(-1, std::map<State, LatticeStateVal>::const_iterator(), pr); //<s>����ȡ1����
        Iter iter = lattice[idx].insert(Pair(state, lattice_state)).first;

        //        int N = m_model.getN();
        vector<DATrie::ResultType> vec;
        size_t state_len;
        for (idx = 0; idx < len; idx++)
        {
            m_trie.searchAll(code + idx, len - idx, vec);
            if (vec.size() == 0)
                vec.push_back(DATrie::ResultType(ngram::kUnknownID, 1));
            lattice_state.pre_pos = idx;
            for (Iter iter = lattice[idx].begin(); iter != lattice[idx].end(); ++iter)
            {
                state.clear(); //this is safe  TODO state ��vaarry, Ȼ������shift ����? ������α�ʾsize?,��λ��ʶ����
                state_len = (iter->first).size();
                for (size_t k = std::max((int) state_len - 2, 0); k < state_len; k++)
                {
                    state.push_back((iter->first)[k]);
                }
                for (size_t j = 0; j < vec.size(); j++)
                {
                    if (isAmbi(vec[j].value)) //�������,"�˴�ȫ����
                        continue;
                    lattice_state.pre_state = iter; //some will not be needed if not add to map
                    state.push_back(vec[j].value);
                    lattice_state.pr = iter->second.pr + m_model.getPr(&state[0], state.size());
                    lattice_state.len = iter->second.len + 1;
                    lattice_state.total_len_square += vec[j].length * vec[j].length;
                    LatticeColumn& lattice_column = lattice[idx + vec[j].length];
                    LatticeColumn::iterator itn = lattice_column.find(state);
                    if (itn == lattice_column.end())
                    {//insert
                        lattice_column[state] = lattice_state;
                    }
                    else
                    {//try to update
                        if (lattice_state > itn->second)
                        {//update
                            lattice_column[state] = lattice_state;
                        }
                    }
                    state.pop_back(); //you need to pop the last!
                }
            }
        }

        //add the </s>
        lattice_state.pre_pos = idx;
        for (Iter iter = lattice[idx].begin(); iter != lattice[idx].end(); ++iter)
        {
            state.clear();
            int state_len = (iter->first).size();
            for (size_t k = std::max((int) state_len - 2, 0); k < state_len; k++)
            {
                state.push_back((iter->first)[k]);
            }
            //debug
            if (isAmbi(end_id))
            {
                LOG(FATAL) << "ambi id " << end_id << endl;
            }
            state.push_back(end_id);
            lattice_state.pre_state = iter; //some will not be needed if not add to map
            lattice_state.pr = iter->second.pr + m_model.getPr(&state[0], state.size());
            lattice_state.len = iter->second.len;
            lattice_state.total_len_square = iter->second.total_len_square;
            LatticeColumn& lattice_column = lattice[idx + 1];
            Iter itn = lattice_column.find(state);
            if (itn == lattice_column.end())
            {
                lattice_column[state] = lattice_state;
            }
            else
            {
                if (lattice_state > itn->second)
                {
                    lattice_column[state] = lattice_state;
                }
            }
        }

        idx++;

        //        state.lear();
        //        LatticeStateVal best = lattice[idx].begin()->second;
        //        Iter best_iter = lattice[idx].begin();
        //        lattice_state.pre_pos = idx;
        //        FinalStateGreater greater_cmp;
        //        for (Iter iter = lattice[idx].begin(); iter != lattice[idx].end(); ++iter)
        //        {
        //            LatticeColumn& lattice_column = lattice[idx + 1];
        //            if (greater_cmp(iter->second, best))
        //            {
        //                best = iter->second;
        //                best_iter = iter;
        //            }
        //        }
        //        lattice_state.pre_state = best_iter; //ע��û�м�¼��Ѹ���ֵ
        //        lattice[idx + 1][state] = lattice_state;

        state.clear();
        lattice_state.pre_pos = idx;
        FinalStateGreater greater_cmp;
        for (Iter iter = lattice[idx].begin(); iter != lattice[idx].end(); ++iter)
        {
            LatticeColumn& lattice_column = lattice[idx + 1];
            LatticeColumn::iterator itn = lattice_column.find(state);
            lattice_state.pre_state = iter;
            lattice_state.pr = iter->second.pr;
            lattice_state.len = iter->second.len;
            lattice_state.total_len_square = iter->second.total_len_square;
            if (itn == lattice_column.end())
            {
                lattice_column[state] = lattice_state;
            }
            else
            {
                if (greater_cmp(lattice_state, itn->second))
                    //                if (lattice_state > itn->second)
                {
                    lattice_column[state] = lattice_state;
                }
            }
        }
    }

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
        int pos_vec[iter->second.len + 1];
        int l = 0;
        while (idx > 0)
        {
            pos_vec[l++] = idx;
            iter = iter->second.pre_state; //��post env
            idx = iter->second.pre_pos;
        }
        pos_vec[l++] = 0;
        for (int i = l - 2; i >= 0; i--)
        {
            put(out, offset + pos_vec[i + 1] * 2, (pos_vec[i] - pos_vec[i + 1])* 2, level); //level is 0
        }
    }
    /**
     * ��������зֵ��жϽ������ĵ�ǰ��崮����
     * ����ǲ������ڲ�Ԥ��������ģ�ע��Ҫ������ȫ�з��㷨����һ��
     */
    //    int getAmbiLen(const short* code, int word_len, int max_len)
    //    {
    //        DATrie::ResultType result;
    //        for (int i = 1; i < word_len; ++i)
    //        {
    //            m_trie.searchLongest(code + i, max_len - i, result);
    //            if (isAmbi(result.value)) //������Ĥ ����  ����Ĥ �����崮 ��ô ǰ��Ͱ�������з���
    //                return i; //�ᵥ������� ���ᵥ�����  ����������� ��Ԥ��������崮 ����˵��Ӧ���������ġ���
    //            else if (word_len < i + result.length)
    //            {
    //                word_len = i + result.length;
    //            }
    //        }
    //        return word_len;
    //    }

    /**
     * ��������зֵ��жϽ������ĵ�ǰ��崮����
     * ����Ǻ����ڲ�Ԥ���������
     */
    int getAmbiLen(const short* code, int word_len, int max_len)
    {
        int len = 0;
        for (int i = 1; i < word_len; ++i)
        {
            len = m_trie.matchLongest(code + i, max_len - i); // ��code + iλ�ò���������Ǵ����Ȳ��ᳬ�� max_len - i
            if (word_len < i + len)
                word_len = i + len;
        }
        return word_len;
    }
};
//typedef SegmentorProbImplT<ngram::Model> SegmentorProbImpl; //remove template right now
} //----end of namespace segment

#endif  //----end of SEGMENT_PROB_IMPL_H_
