/** 
 *  ==============================================================================
 * 
 *          \file   hot_phrase_finder.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2010-12-26 11:36:17.981994
 *  
 *  \Description:  从数据库中查找热门词，即用优先队列维护最热门的N个词及count输出
 *                 从文本中通过分词 统计热门词, ngram已经实现了。。。,如果要统计所有的词包括
 *                 使用数据库作为源头也用那个。
 *
 *  ==============================================================================
 */

#ifndef HOT_PHRASE_FINDER_H_
#define HOT_PHRASE_FINDER_H_
#include <glog/logging.h>
#include <queue>

#include <tr1/unordered_map>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include "config_help.h"
#include "db_reader.h"
#include "KeywordMapID.h"
#include "debug_help.h"
#include "gbk_ch_converter.h"
#include "string_help.h"
#include "file_set.h"

namespace hot_phraer_finder
{

using namespace std;
using boost::property_tree::ptree;

/**config*/
static bool ch_only;
static int max_phrase_num;
static int max_word_len;
static int only_len;
static int min_count; //最少需要的count
static bool care_time;
static int last_days;
static bool write_count;
static bool need_reduce;
static bool need_split;
static string starting_day;

static int show_num;

static bool need_add;

struct Node
{
    string key;
    int count;

    Node()
    {
    }

    Node(const string& key_, int count_)
    : key(key_), count(count_)
    {
    }

    bool operator>(const Node & other) const
    {
        return count > other.count;
    }
};

/**
 * 用来统计热门词的核心部分
 */
struct ReadFunc
{
    typedef std::deque<Node> Deque;
    typedef std::priority_queue<Node, Deque, std::greater<Node> > PQueue;
    typedef std::tr1::unordered_map<string, int> HashMap;
    HashMap hash_map;
    PQueue m_pqueue;
    ch_convert::ChConverter m_converter;
    long long m_keyNum;
    long long m_keyCount;

    template<typename Stream>
            void operator()(Stream & os)
    {
        string key;
        int count;
        int line_num = 0;
        long long key_count = 0;
        boost::array<char, 2 > seperator = {' ', '\t'};

        while (!os.eof())
        {
            os >> key >> count;
            //---规则化处理key
            key = m_converter.Normalize(key);
            if (key.empty())
                continue;
            key = filterString2(key);
            if (key.empty())
                continue;
            //---如果只提取中文串
            if (ch_only && !isChinesePhrase(key))
                continue;

            if (!need_split)
            {
                //---如果只提取特定长度的key
                if (only_len && key.size() != 2 * only_len)
                    continue;
                //---过滤掉超长的串
                if (key.size() > 2 * max_word_len)
                    continue;
                if (!need_add && count >= min_count)
                { //读取all key 不需要再累加统计
                    m_pqueue.push(Node(key, count));
                    if (m_pqueue.size() > max_phrase_num)
                        m_pqueue.pop();
                    key_count += count;
                }
                else
                {
                    hash_map[key] += count;
                }
            }
            else
            {
                boost::trim(key);
                vector<string> vec;
                boost::algorithm::split(vec, key, boost::is_any_of(seperator));
                int count_ = need_reduce ? std::max((int) (count / vec.size()), 1) : count;
                for (size_t i = 0; i < vec.size(); i++)
                { //---如果只提取特定长度的key
                    if (only_len && vec[i].size() != 2 * only_len)
                        continue;
                    //---过滤掉超长的串
                    if (vec[i].size() > 2 * max_word_len)
                        continue;
                    hash_map[vec[i]] += count_;
                }
            }

            if (line_num++ % show_num == 1)
            {
                cerr << "line_num: " << line_num << "\r";
            }
        }
        cerr << "\n";
        if (!m_pqueue.empty())
        {
            LOG(INFO) << "Total key num is " << line_num << endl;
            LOG(INFO) << "Total key count is " << key_count << endl;
            m_keyNum = line_num;
            m_keyCount = key_count;
        }
    }

    void finalize()
    {
        if (m_pqueue.empty())
        {
            LOG(INFO) << "Total key num is " << hash_map.size() << endl;
            long long key_count = 0;
            for (HashMap::iterator iter = hash_map.begin(); iter != hash_map.end(); ++iter)
            {
                if (iter->second >= min_count)
                {
                    m_pqueue.push(Node(iter->first, iter->second));
                    if (m_pqueue.size() > max_phrase_num)
                        m_pqueue.pop();
                }
                key_count += iter->second;
            }
            m_keyNum = hash_map.size();
            m_keyCount = key_count;
            hash_map.clear();
            LOG(INFO) << "Total key count is " << key_count << endl;
        }
    }
};

/**
 * 用来对应热搜的词，统计其点击情况，收藏情况，购买情况
 * 它需要一个输入文本 即所有的热门搜索词文本
 */
struct ReadFunc2
{
    typedef CKeyDictionaryMap<string> KDMap;
    KDMap m_key2id;
    vector<int> m_countVec;
    ch_convert::ChConverter m_converter;

    ReadFunc2()
    {
    }

    ReadFunc2(const string & hot_phrase_file)
    {
        parse(hot_phrase_file);
    }

    void parse(const string & file)
    {
        std::ifstream ifs(file.c_str());
        string key;
        string line;
        while (getline(ifs, line))
        {
            key = line.substr(0, line.find("\t"));
            m_key2id.AddKeyID(key);
        }
        m_countVec.resize(m_key2id.size());
        for (size_t i = 0; i < m_key2id.size(); i++)
            m_countVec[i] = 0;
        LOG(INFO) << Pval(m_countVec.size());
    }

    template<typename Stream>
            void operator()(Stream & os)
    {
        int line_num = 0;
        string key;
        int count;
        int id;
        while (!os.eof())
        {
            os >> key >> count;
            //---规则化处理key
            key = m_converter.Normalize(key);
            if (key.empty())
                continue;
            key = filterString2(key);
            if (key.empty())
                continue;
            id = m_key2id.GetIDFromKey(key);
            if (id != KDMap::null_id)
            {
                m_countVec[id] += count;
            }
            if (line_num++ % show_num == 1)
            {
                cerr << "line_num: " << line_num << "\r";
            }
        }
        cerr << "\n";
    }
};

class HotPhraseFinder
{
private:
    ptree pt; ///for read config file
    DBReader m_dbReader;
    string m_configFile;
    vector<Node> m_hotPhraseVec; ///存储最终得到的热门词结果
    long long m_keyNum;
    long long m_keyCount;
public:

    HotPhraseFinder()
    : m_keyNum(0), m_keyCount(0)
    {
    }

    HotPhraseFinder(const string& config_file)
    : m_keyNum(0), m_keyCount(0)
    {
        init(config_file);
    }

    void init(const string& config_file)
    {
        m_configFile = config_file;
        readConfig();
        initDB();
        need_add = (m_dbReader.getTable() != "all_key");
        LOG(INFO) << Pval(need_add);
    }

    void readConfig()
    {
        read_ini(m_configFile, pt); //初始化propetry tree 用于读取配置文件
        ValGet(ch_only, true);
        ValGet(max_phrase_num, 100);
        ValGet(min_count, 30);
        ValGet(max_word_len, 20);
        ValGet(only_len, 2);
        ValGet(care_time, false);
        ValGet(last_days, 10);
        ValGet(write_count, true);
        ValGet(need_reduce, true);
        ValGet(need_split, true);
        ValGet(starting_day, "0");
        ValGet(show_num, 10000); //for process show

        LOG(INFO) << Pval(care_time);
        LOG(INFO) << Pval(max_phrase_num);
        LOG(INFO) << Pval(min_count);
        LOG(INFO) << Pval(ch_only);
        LOG(INFO) << Pval(only_len);
        LOG(INFO) << Pval(max_word_len);
        LOG(INFO) << Pval(need_split);
        LOG(INFO) << Pval(need_reduce);
        LOG(INFO) << Pval(starting_day);
    }

    void initDB()
    {
        string section;
        if (care_time)
        {//读取日表
            section = "db_key_each_day";
        }
        else
        {//读取历史总表
            section = "db_all_key";
        }
        m_dbReader.init(m_configFile, section);
    }

    void run()
    { //normal 情况 热门词统计
        LOG(INFO) << "Normal run" << endl;
        ReadFunc reader;
        run_(reader);
        finalize_(reader);
    }

    void run(const string& hot_phrase_file)
    {// special 情况 已经有热门词 统计这些词的其它情况
        LOG(INFO) << "Special run" << endl;
        ReadFunc2 reader(hot_phrase_file);
        run_(reader);
        finalize2_(reader);
    }

    template<typename Func>
    void run_(Func& reader)
    {
        if (!care_time)
        { //读取all_key 或者 all_pid_key
            m_dbReader.process(reader);
        }
        else
        { //读取最近n天的日表
            using namespace boost::gregorian;
            days diff(1);
            date day_;
            string table_pri = m_dbReader.getTable();
            string date_str;
            LOG(INFO) << Pval(table_pri);
            if (starting_day == "0")
            { //从昨天开始向前统计last_days
                day_ = day_clock::local_day();
                day_ -= diff; //只能统计昨天及之前的
                date_str = to_iso_string(day_);
                for (int i = 0; i < last_days; i++)
                {//统计last_days的日表
                    m_dbReader.setTable(table_pri + date_str);
                    m_dbReader.process(reader);
                    day_ -= diff;
                    date_str = to_iso_string(day_);
                }
            }
            else
            { //从starting_day开始向后统计last_days
                try
                {
                    day_ = from_undelimited_string(starting_day);
                }
                catch (...)
                {
                    LOG(FATAL) << starting_day << " you set as starting day is not a valid date" << endl;
                }
                days diff_all(last_days - 1);
                date end_day = day_ + diff_all;
                LOG(INFO) << Pval(to_iso_string(end_day));
                LOG(INFO) << Pval(to_iso_string(day_clock::local_day()));
                if (to_iso_string(end_day) >= to_iso_string(day_clock::local_day()))
                {
                    LOG(FATAL) << "The lasting days is to many exceed as starting day + last days " << endl;
                }
                date_str = starting_day;
                for (int i = 0; i < last_days; i++)
                {
                    m_dbReader.setTable(table_pri + date_str);
                    m_dbReader.process(reader);
                    day_ += diff;
                    date_str = to_iso_string(day_);
                }
            }
        }
    }

    template<typename Func>
    void finalize_(Func& reader)
    {
        reader.finalize();
        m_keyNum = reader.m_keyNum;
        m_keyCount = reader.m_keyCount;
        int len = reader.m_pqueue.size();
        LOG(INFO) << Pval(reader.m_pqueue.size());
        m_hotPhraseVec.resize(len);
        while (!reader.m_pqueue.empty())
        {
            m_hotPhraseVec[--len] = reader.m_pqueue.top();
            reader.m_pqueue.pop();
        }
    }

    template<typename Func>
    void finalize2_(Func& reader)
    {
        m_hotPhraseVec.reserve(reader.m_countVec.size());
        for (size_t i = 0; i < reader.m_countVec.size(); i++)
        {
            m_hotPhraseVec.push_back(
                                     Node(reader.m_key2id.GetKeyFromID(i), reader.m_countVec[i]));
        }
    }

    void save(const string& file)
    {
        LOG(INFO) << "Saving to file " << file << endl;
        std::ofstream ofs(file.c_str());

        for (size_t i = 0; i < m_hotPhraseVec.size(); i++)
        {
            if (write_count)
                ofs << setiosflags(ios::left) << m_hotPhraseVec[i].key << "\t" << m_hotPhraseVec[i].count << endl;
            else
                ofs << setiosflags(ios::left) << m_hotPhraseVec[i].key << endl;
        }
    }

    template<typename WriteFunc>
    void save_(WriteFunc& write_func)
    {//FIXME 如果用save上面的重载会有问题。。。 save("a.txt")还会调用到这里。。
        for (size_t i = 0; i < m_hotPhraseVec.size(); i++)
        {
            write_func(m_hotPhraseVec[i].key, m_hotPhraseVec[i].count);
        }
    }

    void showResult()
    {
        LOG(INFO) << "show Result: " << endl;
        for (size_t i = 0; i < m_hotPhraseVec.size() && i < 10; i++)
        {
            cout << setiosflags(ios::left) << m_hotPhraseVec[i].key << " " << m_hotPhraseVec[i].count << endl;
        }

        cout << "key_num " << m_keyNum << endl;
        cout << "key_count " << m_keyCount << endl;
        long long top_key_count = 0;
        for (size_t i = 0; i < m_hotPhraseVec.size(); i++)
        {
            top_key_count += m_hotPhraseVec[i].count;
        }
        cout << "top_key_count " << top_key_count << endl;
    }
};

} //----end of namespace hot_phraer_finder

#endif  //----end of HOT_PHRASE_FINDER_H_
