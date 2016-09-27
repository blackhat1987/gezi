/** 
 *  ==============================================================================
 * 
 *          \file   segment_ambi_trainer.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-10 17:54:19.116240
 *  
 *  \Description:  这是一个离线处理歧义串的程序
 *                         只是为了配合 ambi_train.cc 使用 实现以下功能
 *
 *  提取歧义串（要判断内部交叉歧义，所以不能按照mmseg的最大切分歧义判断） 但是保留两个最佳路径
    如果符合 ”手提包“ ”电吹风机”规则 -> 不加入歧义词典
   比较分数 相差超过界限的并且所有title中最佳切分都一致的 -> 歧义词典
   对于分数相差没有超过界限的  -> 提取出来 title 的两种切分  -> 人工标注正确的包括"手提包” 加入add.txt
   对于符合“ 手提包“规则的 需要将 ”手提包“ ”电吹风机"->提取出来 加入到字典中（如果当前未在字典中才加入，
 * 通过查询是否在trie树中即可）
   ”手提包“规则  ”手提“ ”提包“ ”电吹风“ ”吹风机“ 都在ngram模型 unigram中存在 则视为符合规则
   ”长春市长“ ”农民工学“ 不符合，因为”春市长“ ”民工学“不再ungram中

    但是 大卫衣， 花木兰 之类的词呢  可以全切也可以按照概率或者人工标注
 *  当前不用更复杂的算法识别 统一 全切 但是也有人工标注 给在线最大切分用
 *  ==============================================================================
 */

#ifndef SEGMENT_AMBI_TRAINER_H_
#define SEGMENT_AMBI_TRAINER_H_
#include <set>
#include <map>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include <queue>
#include <bitset>
#include <fstream>
#include "seg_type.h"
#include "segment_prob_impl.h"
#include "ngram_model/ambi_encode.h"
#include "file_set.h"
#include "string_help.h"
#include "stl_help.h"
#include "serialize_help.h"
namespace segment
{

class AmbiTrainer
{
private:
    typedef ngram::Model NgramModel;
    typedef vector<short> AmbiInfo;
    typedef string AmbiInfo2;
    typedef std::map<AmbiInfo2, std::set<int> > AmbiInfoMap; //<歧义串，切分形式>
    typedef std::tr1::unordered_set<vector<short>, VecHash<short> > AmbiInfoSet; //为了避免相同有歧义概率低的重复被展示
    typedef std::set<string > AmbiInfoSet2;
    DATrie m_trie; ///词索引
    Encoder m_encoder; ///扩展gb2312词编码
    NgramModel m_model; ///概率模型
    AmbiInfoSet2 m_shoutibaoSet; ///记录提取到的“手提包”"电吹风机" 类型的词
    AmbiInfoMap m_ambiInfoMap; ///记录歧义信息，最后只处理set大小是1的歧义串，另外“手提包”类的词提取判断出来不加入
    AmbiInfoSet m_ambiInfoSet; ///记录已经被访问过的低概率歧义串
    AmbiInfo m_ambiInfo_;
    AmbiInfo2 m_ambiInfo;
    AmbiInfoSet2 m_lowProbAmbiInfoSet;
    //    bool m_smallDiff; ///记录两条最佳路径是否概率差别很小，差别小的外部该title的切分要加入到一个需要人工标注的文本中
    double m_threshold;
    double m_nowMaxDiff;
    double m_nowDiff;
    string m_key; //记录当前要分的句子，因为code转key当前不提供
    StrFileSet m_danziFileSet;
    //    set<string> m_delSet;
    std::tr1::unordered_set<string> m_allAmbiSet;
    //FIXME 需要更多的位置 24比如，然后剩余8位 可以存储其它信息 这样子
    //    const static int kMaxAmbiLen = 15; //当前不允许歧义串>16因为 我们存储的时候只能占据16个位置
public:

    AmbiTrainer(const string& datrie_file, const string& encoder_file, const string& model_file)
    : m_trie(datrie_file), m_encoder(encoder_file), m_model(model_file), m_threshold(threshold)
    {
    }

    AmbiTrainer(const string& dir)
    : m_trie(dir + "/datrie.idx"), m_encoder(dir + "/gbk_encode.idx"), m_model(dir + "/ngram_model.idx"), m_danziFileSet("dict/danzi2.txt"),
    m_threshold(threshold)
    { //only this is suppoted right now

    }

    AmbiTrainer()
    : m_threshold(threshold)
    {

    }

    void init(const string& datrie_file, const string& encoder_file, const string& model_file)
    {
        m_trie.load(datrie_file);
        m_encoder.load(encoder_file);
        m_model.load(model_file);
        assert(m_model.useLogPr());
    }

    void init(const string& dir)
    {
        m_trie.load(dir + "/datrie.idx");
        m_encoder.load(dir + "/gbk_encode.idx");
        m_model.load(dir + "/ngram_model.idx");
        assert(m_model.useLogPr());
    }

    void setKey(const string& key)
    {
        m_key = key;
    }

    void setThreshold(double thre)
    {
        m_threshold = thre;
    }

    bool isConfused()
    {
        return m_nowMaxDiff > m_threshold;
    }
public:

    template<typename Container, typename RFunc>
    void segmentCH(Container& out, const short* code, int len, int offset, RFunc put, MaxSegWithAmbi)
    {
        m_nowDiff = std::numeric_limits<double>::min(); //small enough
        m_nowMaxDiff = std::numeric_limits<double>::min(); //small enough
        DATrie::ResultType result, result2;
        ngram::WordID start_id = ngram::kGapID, end_id = ngram::kGapID;
        int i = 0, level = 0;
        while (i < len)
        {
            if (result.length == 0)
            {
                while (i < len && !m_trie.searchLongest(code + i, len - i, result)) //最小切分可以 篮球，鞋   爱心 卡片 灯  这种不行
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
                {//有最大切分交集歧义
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
                    findBestPath(lattice, out, offset + i * 2, put);
                    start_id = end_id;
                }
                else
                {
                    m_trie.searchFirstNonSingle(code + i, len - i, result2); //尝试判断最小切分歧义
                    if (result2.length < length && getAmbiLen2(code + i, result2.length, len - i) == length)
                    {//有内部切分交集歧义
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
                        findBestPath(lattice, out, offset + i * 2, put);
                        start_id = end_id;
                    }
                    else
                    {
                        put(out, offset + i * 2, length * 2, level);
                        result.length = 0;
                        start_id = result.value;
                    }
                }
                i += length;
            }
        }
    }
private:

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
            if (idx == 0)
                m_trie.searchAll(code + idx, len - idx - 1, vec); //这里不要岐义单独成词
            else
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
                    lattice_state.pre_state = iter; //some will not be needed if not add to map
                    state.push_back(vec[j].value);
                    lattice_state.pr = iter->second.pr + m_model.getPr(&state[0], state.size());
                    lattice_state.len = iter->second.len + 1;
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
            state.push_back(end_id);
            lattice_state.pre_state = iter; //some will not be needed if not add to map
            lattice_state.pr = iter->second.pr + m_model.getPr(&state[0], state.size());
            lattice_state.len = iter->second.len;
            LatticeColumn& lattice_column = lattice[idx + 1];
            LatticeColumn::iterator itn = lattice_column.find(state);
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
        //添加 tail  记录最佳路径
        state.clear();
        lattice_state.pre_pos = idx;
        for (Iter iter = lattice[idx].begin(); iter != lattice[idx].end(); ++iter)
        { //TODO can speed up here a bit?
            LatticeColumn& lattice_column = lattice[idx + 1];
            Iter itn = lattice_column.find(state);
            lattice_state.pre_state = iter;
            lattice_state.pr = iter->second.pr;
            lattice_state.len = iter->second.len;
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

        AmbiInfo ambi;
        ambi.resize(len, 0);
        memcpy(&ambi[0], code, len * sizeof (short));
        m_ambiInfo_ = ambi;
        ambi.push_back(start_id);
        ambi.push_back(end_id);

        if (!m_ambiInfoSet.insert(ambi).second) //如果已经找过了略过
            return;
        typedef std::deque<LatticeStateVal> Deque;
        typedef std::priority_queue<LatticeStateVal, Deque, std::greater<LatticeStateVal> > PQueue;
        PQueue queue_;
        for (Iter iter = lattice[idx].begin(); iter != lattice[idx].end(); ++iter)
        {
            queue_.push(iter->second);
            if (queue_.size() > 2)
                queue_.pop();
        }
        if (queue_.size() == 2)
        {
            double second = queue_.top().pr;
            queue_.pop();
            double first = queue_.top().pr;
            //            Pval(first);
            //            Pval(second);
            m_nowDiff = first / second;
            if (m_nowDiff > m_nowMaxDiff)
                m_nowMaxDiff = m_nowDiff;
        }
    }

    template<typename Container, typename RFunc>
    int findBestPath(const Lattice& lattice, Container& out, int offset, RFunc put)
    {//idx is staring pos at the end, start_idx is the finish倒序找最优path
        int level = 0;
        int idx = lattice.size() - 1;
        typedef std::map<State, LatticeStateVal>::const_iterator Iter;
        std::bitset < 16 > ambi_encode;
        Iter iter = lattice[idx].begin(); //tail
        iter = iter->second.pre_state; //</s>
        idx = iter->second.pre_pos;
        int pos_vec[iter->second.len + 1];
        int l = 0;
        while (idx > 0)
        {
            ambi_encode.set(idx - 1, 1);
            pos_vec[l++] = idx;
            iter = iter->second.pre_state; //到post env
            idx = iter->second.pre_pos;
        }
        pos_vec[l++] = 0;
        for (int i = l - 2; i >= 0; i--)
        {
            put(out, offset + pos_vec[i + 1] * 2, (pos_vec[i] - pos_vec[i + 1])* 2, level); //level is 0
        }

        int code = (int) ambi_encode.to_ulong();
        code <<= AMBOFFSET;
        //        Pval(ngram::getAmbiString("美文学", code));
        m_ambiInfo = m_key.substr(offset, pos_vec[0] * 2);
        m_allAmbiSet.insert(m_ambiInfo); //需要记录标题中所有的岐义串,并且记录一个title 这样的情况输出 以后人手工切,再之后可以是低概率的，也记录一个title 也手工切词
        if (!isShoutibao(m_ambiInfo_))
        {
            //            Pval(m_nowDiff);
            if (m_nowDiff > m_threshold) //越大 即越接近1 说明概率越接近,表明是低概率事件
                m_lowProbAmbiInfoSet.insert(m_ambiInfo);
            if (m_lowProbAmbiInfoSet.find(m_ambiInfo) == m_lowProbAmbiInfoSet.end())
                m_ambiInfoMap[m_ambiInfo].insert(code);
        }
        else
        {//当前 ”手提包“ 类型的都加入了歧义词典  似乎只需要加 "电压力锅“ 这样的词。。。因为 ”电压力“ 有歧义 而 手提 没有
            //但是那样你需要特殊处理下。。。，即对于所有这样的词 最后再判断下前缀”电压力“是否在歧义字典中，在的加入。。。
            //特别的要处理达到完全切分一致，还需要判断所有被忽略的歧义串 是否存在前缀是在歧义字典中的情况。。。
            m_shoutibaoSet.insert(m_ambiInfo);
        }
    }

    bool isShoutibao(const AmbiInfo& ambi)
    {//FIXME 为什么这len==2 ?
        if (!m_danziFileSet.contains(m_ambiInfo.substr(m_ambiInfo.size() - 2, 2)))
            return false;
        DATrie::ResultType result;
        int len = ambi.size() - 1;
        m_trie.searchLongest(&ambi[0], len, result);
        if (result.length != len)
            return false;
        m_trie.searchLongest(&ambi[1], len, result);
        return result.length == len;
    }

    //    void addDianyaliguo()
    //    {//电压力锅这样的词最后要加入歧义字典, 后面考虑加入所有可能切分不一致的词
    //        int not_good_num = 0, not_good_num2 = 0, not_good_num3 = 0;
    //
    //        for (AmbiInfoSet2::iterator iter = m_shoutibaoSet.begin(); iter != m_shoutibaoSet.end(); ++iter)
    //        {
    //            //state:
    //            int len = iter->size();
    //            for (int j = 0; j < len - 6; j++)
    //            {
    //                for (int i = 6; i < len - j; i += 2) //3*2 4*2...
    //                {
    //                    if (m_ambiInfoMap.find((*iter).substr(j, i)) != m_ambiInfoMap.end())
    //                    {
    //                        m_delSet.insert((*iter).substr(j, i));
    //                        Pval(*iter);
    //                        not_good_num++;
    //                        m_ambiInfoMap[*iter].clear();
    //                        m_ambiInfoMap[*iter].insert(DIANYALIGUO << AMBOFFSET);
    //                        //                        ++iter;
    //                        //                        goto state;
    //                    }
    //                }
    //            }
    //        }
    //        Pval(not_good_num);
    //        for (AmbiInfoSet2::iterator iter = m_lowProbAmbiInfoSet.begin(); iter != m_lowProbAmbiInfoSet.end(); ++iter)
    //        {
    //            //state2:
    //            int len = iter->size();
    //            for (int j = 0; j < len - 6; j++)
    //            {
    //                for (int i = 6; i < len - j; i += 2) //3*2 4*2...
    //                {
    //                    if (m_ambiInfoMap.find((*iter).substr(j, i)) != m_ambiInfoMap.end())
    //                    {
    //                        m_delSet.insert((*iter).substr(j, i));
    //                        Pval(*iter);
    //                        not_good_num2++;
    //                        m_ambiInfoMap[*iter].clear();
    //                        m_ambiInfoMap[*iter].insert(DIANYALIGUO << AMBOFFSET);
    //                        //                        ++iter;
    //                        //                        goto state2;
    //                    }
    //                }
    //            }
    //        }
    //        Pval(not_good_num2);
    //        Pval(m_ambiInfo.size());
    //        for (AmbiInfoMap::iterator iter = m_ambiInfoMap.begin(); iter != m_ambiInfoMap.end(); ++iter)
    //        {
    //            //state3: //            Pval(iter->first);
    //            if (iter->second.size() != 1)
    //            {
    //                int len = iter->first.size();
    //                for (int j = 0; j < len - 6; j++)
    //                {
    //                    for (int i = 6; i < len - j; i += 2) //3*2 4*2...
    //                    {
    //                        if (m_ambiInfoMap.find((iter->first).substr(j, i)) != m_ambiInfoMap.end())
    //                        {
    //                            m_delSet.insert((iter->first).substr(j, i));
    //                            Pval(iter->first);
    //                            not_good_num3++;
    //                            m_ambiInfoMap[iter->first].clear();
    //                            m_ambiInfoMap[iter->first].insert(DIANYALIGUO << AMBOFFSET);
    //                            //                            ++iter;
    //                            //                            goto state3;
    //                        }
    //                    }
    //                }
    //            }
    //        }
    //        Pval(not_good_num3);
    //    }

    void writeShoutibao(const string& file, const string& train_file)
    {
        m_model.clear(); //do not need
        m_ambiInfoSet.clear(); //not need any more
        std::ofstream ofs(file.c_str());
        std::ofstream ofs2(train_file.c_str());
        //        std::copy(m_shoutibaoSet.begin(), m_shoutibaoSet.end(), std::ostream_iterator<string > (ofs, "\n"));
        for (AmbiInfoSet2::iterator iter = m_shoutibaoSet.begin(); iter != m_shoutibaoSet.end(); ++iter)
        {
            ofs << *iter << std::endl;
            ofs2 << iter->substr(0, iter->size() - 2) << " " << iter->substr(iter->size() - 2, 2) << std::endl;
        }
        //        m_shoutibaoSet.clear();
    }

    /**
     * 狂人/大/全集   人大/全集   现在只要被更长的岐义串包含 就去掉
     */
    void writeAmbi(const string& file, const string& show_file)
    {
        vector<string> all_ambi;
        std::copy(m_allAmbiSet.begin(), m_allAmbiSet.end(), std::back_inserter(all_ambi));
        m_allAmbiSet.clear();
        std::sort(all_ambi.begin(), all_ambi.end());
        LOG(INFO) << "一共发现了 " << all_ambi.size() << " 个岐义片断" << "\n";
        //        addDianyaliguo();
        std::ofstream ofs(file.c_str());
        std::ofstream ofs2(show_file.c_str());
        int num = 0;
        serialize_help::save(all_ambi, "all_ambi.ser");
        serialize_help::save(m_ambiInfoMap, "ambi_map.ser");
        //        int total_num = 0;
        for (AmbiInfoSet2::iterator iter = m_shoutibaoSet.begin(); iter != m_shoutibaoSet.end(); ++iter)
        { //手提包类型的全切分岐义串全部写入
            m_ambiInfoMap[*iter].clear();
            m_ambiInfoMap[*iter].insert(DIANYALIGUO << AMBOFFSET);
        }
        for (AmbiInfoMap::iterator iter = m_ambiInfoMap.begin(); iter != m_ambiInfoMap.end(); ++iter)
        {
            //            cout << "candiate num: " << total_num++ << endl;
            //            if (iter->second.size() == 1 && m_delSet.find(iter->first) == m_delSet.end())
            if (iter->second.size() == 1) //如果有多种切分可能那么不输出
            { //FIXME 为什么show file文件写的内容少呢。。。
                //                bool can_write = true;
                //                for (size_t i = 0; i < all_ambi.size(); i++)
                //                {
                //                    if (iter->first != all_ambi[i] && exact_contains(all_ambi[i], iter->first))
                //                    {
                //                        can_write = false;
                //                        break;
                //                    }
                //                }
                //                if (!can_write)
                //                    continue;
                //                num++;
                //                if (num % 100 == 0)
                //                {
                //                    cout << "num: " << num << "\r";
                //                }
                num++;
                ofs << iter->first << " " << *(iter->second.begin()) << std::endl;
                ofs2 << iter->first << " " << ngram::getAmbiString(iter->first, *(iter->second.begin())) << std::endl;
            }
        }

        LOG(INFO) << "最终写了 " << num << "个预处理岐义串" << "\n";
    }

    /**
     * 按照最大切分的判断交集岐义的当前岐义串长度
     */
    int getAmbiLen(const short* code, int word_len, int max_len)
    {
        int len = 0;
        for (int i = 1; i < word_len; ++i)
        {
            len = m_trie.matchLongest(code + i, max_len - i); // 从code + i位置查找最长串但是串长度不会超过 max_len - i
            if (word_len < i + len)
            {
                word_len = i + len;
            }
        }
        return word_len;
    }

    /**
     * 按照最小切分判断交集歧义, 这样 “我爱篮球鞋” 能够切成 “我爱 篮球 鞋”
     * 改成不训练，内部有歧义没关系，全部切出
     */
    int getAmbiLen2(const short* code, int word_len, int max_len)
    {
        return word_len; //11.01.18  暂时改为不训练内部岐义
        for (int i = 1; i < word_len; ++i)
        {
            int len = m_trie.matchFirstNonSingle(code + i, max_len - i); // 从code + i位置查找最长串但是串长度不会超过 max_len - i
            if (word_len < i + len)
                word_len = i + len;
        }
        return word_len;
    }
};
} //----end of namespace segment

#endif  //----end of SEGMENT_AMBI_TRAINER_H_
