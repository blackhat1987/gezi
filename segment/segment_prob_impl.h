/** 
 *  ==============================================================================
 * 
 *          \file   segment_prob_impl.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-05 17:54:19.116240
 *  
 *  \Description:  基于ngram模型的在线最大切分分词，提供以下版本
 *                         1. 整句完全概率切分
 *                         2. 保证无歧义部分最大切分，只对可能有歧义的部分，考虑前后语境走概率模型给出切分，参考sun 拼音的做法
 *                        对比结果和效率
 *
 *    现在的优先原则
 *    1.首先路径长度短的优先
 *    2. 概率大的优先 概率取了 log 所以是-的 还是大的优先 也就是绝对值小的优秀 比如1/8-> -3 优于 1/16->-4
 *    pr *  6M/S  原来最大分词无概率大概20M/S
 *
 *   2011.01.14   增加概率最大切分基础上的全切分，对于每一个词 都 去内部每个位置 查找可能的词。。。
 *   需要增加一个有意义的单字。保证无意义的单字不再被切除来。速度可能比较慢需要测试，广告使用应该没问题。
 *
 *   概率算法需要增加对 预处理歧义串的支持
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
//注意由于下面的类是模板类好像里面内部定义LatticeStateVal有问题
typedef vector<ngram::WordID> State; //TODO do not use vector use array instead than NgramModel must be 一致

/* 语言模型的状态节点，及其状态信息，每个状态节点位于lattice的一个idx坐标下*/
struct LatticeStateVal
{
    typedef std::map<State, LatticeStateVal>::const_iterator Iter;
    int pre_pos; /**从哪个位置跳过来的,最终需要记录切分的位置*/
    Iter pre_state; /**从哪个状态跳转过来*/
    //        State state; /**当前状态(未考虑线索化) state.back()对应当前wordid,只所以还要记录这个因为相同lattice位置的相同state只取一个最大pr*/
    double pr; /**该状态的概率值*/
    short len; /**走了几步，切了几块*/
    short total_len_square; /**每步大小的平方之和*/

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
            {//概率有较大差距 TODO概率的差距 可能并不准确 比如路径越长 可能需要设定的threshold值越大些
                //                Pval(l.pr);
                //                Pval(r.pr);
                //                Pval((std::max(l.pr, r.pr) / std::min(l.pr, r.pr)));
                return l.pr > r.pr;
            }
            else
            {//概率接近,首先选择方差小的 ”上海，市长" > "上海市，长“ 其次按照最大匹配”电压力，锅">"电，压力锅"
                //但是注意不完全等同最大匹配，因为可能歧义串由多于2个路径构成，相当选取最后一步最短的路径
                return l.total_len_square < r.total_len_square || (l.total_len_square == r.total_len_square &&
                        l.pre_state->second.pre_pos > r.pre_state->second.pre_pos); //跳过最后的</s>或者语境
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
    DATrie m_trie; ///词索引
    Encoder m_encoder; ///扩展gb2312词编码
    NgramModel m_model; ///概率模型
    vector<int> m_ambi; ///记录岐义信息
    int m_ambiStartID; ///岐义开始ID注意如果没有任何岐义信息设置为最大，保证见到的id都 < 即都不是岐义id
    bool m_useAmbi; ///设置是否使用岐义信息
    //     const static int kMaxAmbiLen = 15; //当前不允许歧义串>=16因为 我们存储的时候只能占据16个位置,注意和离线模型保持一致
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
        if (m_ambi.size() > 1) //有岐义信息
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
     * 是否是岐义id ,如果不使用岐义信息，那么必然id < m_ambiStartID
     */
    bool isAmbi(int id)
    {
        return id >= m_ambiStartID;
    }

    int getAmbi(int id)
    {//由于频繁调用不做越界判断
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
            { //尾串留给下一个步骤后续处理 比如 ”浅黄,白“ ”浅黄白色“ -> ”浅黄，白色"
                put(out, pos, len, level);
                pos += len;
            }
        }
        return (pos - start) / 2;
    }

    /**最标准简单的整条路径去最大概率切分*/
    template<typename Container, typename RFunc>
    void segmentCH(Container& out, const short* code, int len, int offset, RFunc put, MaxProbSeg)
    {
        Lattice lattice;
        //动态规划各种路径最终最优值存储到tail
        buildLattice(lattice, code, len);
        //提取最优路径
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
                while (i < len && !m_trie.searchLongest(code + i, len - i, result)) //没有成词
                {
                    put(out, offset + i * 2, 2, level);
                    i++;
                    start_id = ngram::kGapID;
                }
            }
            if (i < len) //有成词，从code+i位置开始长度为result.length是最大成词
            {
                if (isAmbi(result.value))
                {//该词是预处理的岐义词
                    //                    Pval(result.value);
                    //                    Pval(getAmbi(result.value));
                    int ambi_len = addAmbiMax(out, getAmbi(result.value), offset + i * 2, level, put);
                    start_id = ngram::kGapID; //岐义切分后前面那个词不好得到了,当然也可以不过比较麻烦
                    i += ambi_len;
                    result.length = 0;
                }
                else
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

    /**动态规划全切分最佳路径*/
    void buildLattice(Lattice& lattice, const short* code, int len, ngram::WordID start_id = ngram::kGapID, ngram::WordID end_id = ngram::kGapID)
    {//TODO 是否还是可以优化？ 比如sun 拼音的状态转移线索化 现在虽然首字查找快了
        lattice.resize(len + 3);
        //------开始是head <s>
        int idx = 0;
        typedef LatticeColumn::const_iterator Iter;
        State state(1, start_id);
        typedef std::pair<State, LatticeStateVal> Pair;

        double pr = 0.0;
        if (start_id != ngram::kGapID)
            pr = m_model.getPr(&state[0], state.size());
        LatticeStateVal lattice_state(-1, std::map<State, LatticeStateVal>::const_iterator(), pr); //<s>概率取1即可
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
                state.clear(); //this is safe  TODO state 用vaarry, 然后利用shift 操作? 但是如何表示size?,空位标识符？
                state_len = (iter->first).size();
                for (size_t k = std::max((int) state_len - 2, 0); k < state_len; k++)
                {
                    state.push_back((iter->first)[k]);
                }
                for (size_t j = 0; j < vec.size(); j++)
                {
                    if (isAmbi(vec[j].value)) //忽略岐义,"人大全集“
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
        //        lattice_state.pre_state = best_iter; //注意没有记录最佳概率值
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
            put(out, offset + pos_vec[i + 1] * 2, (pos_vec[i] - pos_vec[i + 1])* 2, level); //level is 0
        }
    }
    /**
     * 按照最大切分的判断交集岐义的当前岐义串长度
     * 这个是不忽略内部预处理歧义的，注意要和离线全切分算法保持一致
     */
    //    int getAmbiLen(const short* code, int word_len, int max_len)
    //    {
    //        DATrie::ResultType result;
    //        for (int i = 1; i < word_len; ++i)
    //        {
    //            m_trie.searchLongest(code + i, max_len - i, result);
    //            if (isAmbi(result.value)) //净白面膜 净白  白面膜 是歧义串 那么 前面就按照最大切分走
    //                return i; //提单肩包包， 手提单肩包包  “单肩包包” 是预处理的歧义串 按理说不应该有这样的。。
    //            else if (word_len < i + result.length)
    //            {
    //                word_len = i + result.length;
    //            }
    //        }
    //        return word_len;
    //    }

    /**
     * 按照最大切分的判断交集岐义的当前岐义串长度
     * 这个是忽略内部预处理歧义的
     */
    int getAmbiLen(const short* code, int word_len, int max_len)
    {
        int len = 0;
        for (int i = 1; i < word_len; ++i)
        {
            len = m_trie.matchLongest(code + i, max_len - i); // 从code + i位置查找最长串但是串长度不会超过 max_len - i
            if (word_len < i + len)
                word_len = i + len;
        }
        return word_len;
    }
};
//typedef SegmentorProbImplT<ngram::Model> SegmentorProbImpl; //remove template right now
} //----end of namespace segment

#endif  //----end of SEGMENT_PROB_IMPL_H_
