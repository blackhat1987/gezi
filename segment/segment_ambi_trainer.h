/** 
 *  ==============================================================================
 * 
 *          \file   segment_ambi_trainer.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-10 17:54:19.116240
 *  
 *  \Description:  ����һ�����ߴ������崮�ĳ���
 *                         ֻ��Ϊ����� ambi_train.cc ʹ�� ʵ�����¹���
 *
 *  ��ȡ���崮��Ҫ�ж��ڲ��������壬���Բ��ܰ���mmseg������з������жϣ� ���Ǳ����������·��
    ������� ��������� ���紵��������� -> ����������ʵ�
   �ȽϷ��� �������޵Ĳ�������title������зֶ�һ�µ� -> ����ʵ�
   ���ڷ������û�г������޵�  -> ��ȡ���� title �������з�  -> �˹���ע��ȷ�İ���"������� ����add.txt
   ���ڷ��ϡ� ������������ ��Ҫ�� ��������� ���紵���"->��ȡ���� ���뵽�ֵ��У������ǰδ���ֵ��вż��룬
 * ͨ����ѯ�Ƿ���trie���м��ɣ�
   �������������  �����ᡰ ������� ���紵�硰 ��������� ����ngramģ�� unigram�д��� ����Ϊ���Ϲ���
   �������г��� ��ũ��ѧ�� �����ϣ���Ϊ�����г��� ����ѧ������ungram��

    ���� �����£� ��ľ�� ֮��Ĵ���  ����ȫ��Ҳ���԰��ո��ʻ����˹���ע
 *  ��ǰ���ø����ӵ��㷨ʶ�� ͳһ ȫ�� ����Ҳ���˹���ע ����������з���
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
    typedef std::map<AmbiInfo2, std::set<int> > AmbiInfoMap; //<���崮���з���ʽ>
    typedef std::tr1::unordered_set<vector<short>, VecHash<short> > AmbiInfoSet; //Ϊ�˱�����ͬ��������ʵ͵��ظ���չʾ
    typedef std::set<string > AmbiInfoSet2;
    DATrie m_trie; ///������
    Encoder m_encoder; ///��չgb2312�ʱ���
    NgramModel m_model; ///����ģ��
    AmbiInfoSet2 m_shoutibaoSet; ///��¼��ȡ���ġ��������"�紵���" ���͵Ĵ�
    AmbiInfoMap m_ambiInfoMap; ///��¼������Ϣ�����ֻ����set��С��1�����崮�����⡰���������Ĵ���ȡ�жϳ���������
    AmbiInfoSet m_ambiInfoSet; ///��¼�Ѿ������ʹ��ĵ͸������崮
    AmbiInfo m_ambiInfo_;
    AmbiInfo2 m_ambiInfo;
    AmbiInfoSet2 m_lowProbAmbiInfoSet;
    //    bool m_smallDiff; ///��¼�������·���Ƿ���ʲ���С�����С���ⲿ��title���з�Ҫ���뵽һ����Ҫ�˹���ע���ı���
    double m_threshold;
    double m_nowMaxDiff;
    double m_nowDiff;
    string m_key; //��¼��ǰҪ�ֵľ��ӣ���Ϊcodeתkey��ǰ���ṩ
    StrFileSet m_danziFileSet;
    //    set<string> m_delSet;
    std::tr1::unordered_set<string> m_allAmbiSet;
    //FIXME ��Ҫ�����λ�� 24���磬Ȼ��ʣ��8λ ���Դ洢������Ϣ ������
    //    const static int kMaxAmbiLen = 15; //��ǰ���������崮>16��Ϊ ���Ǵ洢��ʱ��ֻ��ռ��16��λ��
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
                while (i < len && !m_trie.searchLongest(code + i, len - i, result)) //��С�зֿ��� ����Ь   ���� ��Ƭ ��  ���ֲ���
                {
                    put(out, offset + i * 2, 2, level);
                    i++;
                    start_id = ngram::kGapID;
                }
            }
            if (i < len) //�гɴʣ���code+iλ�ÿ�ʼ����Ϊresult.length�����ɴ�
            {
                int length = result.length;
                //���������С����ô���ܵ����ɴʵĵ���Ҫ���ֵ�����ȥ��
                int ambis_len = getAmbiLen(code + i, length, std::min(len - i, kMaxAmbiLen));
                if (ambis_len > length)
                {//������зֽ�������
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
                    m_trie.searchFirstNonSingle(code + i, len - i, result2); //�����ж���С�з�����
                    if (result2.length < length && getAmbiLen2(code + i, result2.length, len - i) == length)
                    {//���ڲ��зֽ�������
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
            if (idx == 0)
                m_trie.searchAll(code + idx, len - idx - 1, vec); //���ﲻҪ��嵥���ɴ�
            else
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
        //��� tail  ��¼���·��
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

        if (!m_ambiInfoSet.insert(ambi).second) //����Ѿ��ҹ����Թ�
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
    {//idx is staring pos at the end, start_idx is the finish����������path
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
            iter = iter->second.pre_state; //��post env
            idx = iter->second.pre_pos;
        }
        pos_vec[l++] = 0;
        for (int i = l - 2; i >= 0; i--)
        {
            put(out, offset + pos_vec[i + 1] * 2, (pos_vec[i] - pos_vec[i + 1])* 2, level); //level is 0
        }

        int code = (int) ambi_encode.to_ulong();
        code <<= AMBOFFSET;
        //        Pval(ngram::getAmbiString("����ѧ", code));
        m_ambiInfo = m_key.substr(offset, pos_vec[0] * 2);
        m_allAmbiSet.insert(m_ambiInfo); //��Ҫ��¼���������е���崮,���Ҽ�¼һ��title ������������ �Ժ����ֹ���,��֮������ǵ͸��ʵģ�Ҳ��¼һ��title Ҳ�ֹ��д�
        if (!isShoutibao(m_ambiInfo_))
        {
            //            Pval(m_nowDiff);
            if (m_nowDiff > m_threshold) //Խ�� ��Խ�ӽ�1 ˵������Խ�ӽ�,�����ǵ͸����¼�
                m_lowProbAmbiInfoSet.insert(m_ambiInfo);
            if (m_lowProbAmbiInfoSet.find(m_ambiInfo) == m_lowProbAmbiInfoSet.end())
                m_ambiInfoMap[m_ambiInfo].insert(code);
        }
        else
        {//��ǰ ��������� ���͵Ķ�����������ʵ�  �ƺ�ֻ��Ҫ�� "��ѹ������ �����Ĵʡ�������Ϊ ����ѹ���� ������ �� ���� û��
            //������������Ҫ���⴦���¡����������������������Ĵ� ������ж���ǰ׺����ѹ�����Ƿ��������ֵ��У��ڵļ��롣����
            //�ر��Ҫ����ﵽ��ȫ�з�һ�£�����Ҫ�ж����б����Ե����崮 �Ƿ����ǰ׺���������ֵ��е����������
            m_shoutibaoSet.insert(m_ambiInfo);
        }
    }

    bool isShoutibao(const AmbiInfo& ambi)
    {//FIXME Ϊʲô��len==2 ?
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
    //    {//��ѹ���������Ĵ����Ҫ���������ֵ�, ���濼�Ǽ������п����зֲ�һ�µĴ�
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
     * ����/��/ȫ��   �˴�/ȫ��   ����ֻҪ����������崮���� ��ȥ��
     */
    void writeAmbi(const string& file, const string& show_file)
    {
        vector<string> all_ambi;
        std::copy(m_allAmbiSet.begin(), m_allAmbiSet.end(), std::back_inserter(all_ambi));
        m_allAmbiSet.clear();
        std::sort(all_ambi.begin(), all_ambi.end());
        LOG(INFO) << "һ�������� " << all_ambi.size() << " �����Ƭ��" << "\n";
        //        addDianyaliguo();
        std::ofstream ofs(file.c_str());
        std::ofstream ofs2(show_file.c_str());
        int num = 0;
        serialize_help::save(all_ambi, "all_ambi.ser");
        serialize_help::save(m_ambiInfoMap, "ambi_map.ser");
        //        int total_num = 0;
        for (AmbiInfoSet2::iterator iter = m_shoutibaoSet.begin(); iter != m_shoutibaoSet.end(); ++iter)
        { //��������͵�ȫ�з���崮ȫ��д��
            m_ambiInfoMap[*iter].clear();
            m_ambiInfoMap[*iter].insert(DIANYALIGUO << AMBOFFSET);
        }
        for (AmbiInfoMap::iterator iter = m_ambiInfoMap.begin(); iter != m_ambiInfoMap.end(); ++iter)
        {
            //            cout << "candiate num: " << total_num++ << endl;
            //            if (iter->second.size() == 1 && m_delSet.find(iter->first) == m_delSet.end())
            if (iter->second.size() == 1) //����ж����зֿ�����ô�����
            { //FIXME Ϊʲôshow file�ļ�д���������ء�����
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

        LOG(INFO) << "����д�� " << num << "��Ԥ������崮" << "\n";
    }

    /**
     * ��������зֵ��жϽ������ĵ�ǰ��崮����
     */
    int getAmbiLen(const short* code, int word_len, int max_len)
    {
        int len = 0;
        for (int i = 1; i < word_len; ++i)
        {
            len = m_trie.matchLongest(code + i, max_len - i); // ��code + iλ�ò���������Ǵ����Ȳ��ᳬ�� max_len - i
            if (word_len < i + len)
            {
                word_len = i + len;
            }
        }
        return word_len;
    }

    /**
     * ������С�з��жϽ�������, ���� ���Ұ�����Ь�� �ܹ��г� ���Ұ� ���� Ь��
     * �ĳɲ�ѵ�����ڲ�������û��ϵ��ȫ���г�
     */
    int getAmbiLen2(const short* code, int word_len, int max_len)
    {
        return word_len; //11.01.18  ��ʱ��Ϊ��ѵ���ڲ����
        for (int i = 1; i < word_len; ++i)
        {
            int len = m_trie.matchFirstNonSingle(code + i, max_len - i); // ��code + iλ�ò���������Ǵ����Ȳ��ᳬ�� max_len - i
            if (word_len < i + len)
                word_len = i + len;
        }
        return word_len;
    }
};
} //----end of namespace segment

#endif  //----end of SEGMENT_AMBI_TRAINER_H_
