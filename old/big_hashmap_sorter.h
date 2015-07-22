/** 
 *  ==============================================================================
 * 
 *          \file   big_hash_map.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-10-16 19:36:02.372304
 *  
 *  \Description:  一个排序器，对外隐藏外排序过程的的，假定输入有重复元素并进行vlaue加和归并。
 *                 用法
 *                 输入， 不断add(key, value)
 *                 输出， 最后输出到一个排序文件,不管是否在内存中能够完全存放
 *                 Sorter sorter(outfile)
 *                 while
 *                    sorter.add(key, value)
 *                 sorter.sort()
 *
 *                 支持输入文本 <key, value>组合
 *                 输出同上
 Sorter sorter(outfile);
 * sorter.open(infile);
 * sorter.sort();

 * 内部采用hash map去重
 *
 *  FIXME TODO 去掉所有的 += 以方便支持更多的add方式, 默认设置AddFunc =
 * DefualtAddFunc(Val& org, const Val&cur)
 * {
 *      org += cur;
 * }
 *
 *  有没有办法外部定义 += 支持，从而不需要内部AddFunc 比如支持pair +  how to ?
 *  ==============================================================================
 */

#ifndef BIG_HASHMAP_SORTER_H_
#define BIG_HASHMAP_SORTER_H_
#include <boost/filesystem.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <glog/logging.h>
#include <fstream>
#include <map>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "winner_tree.h"
#include <unistd.h>
#include "ul_log_help.h"

struct DefaultAddFunc
{

    template<typename ValType>
            inline void operator()(ValType& org, ValType & cur)
    {
        org += cur;
    }
};

struct DefaultWriteFunc
{

    template<typename NodeType, typename Stream>
            inline void operator()(Stream& ofs, NodeType & node) const
    {
        ofs.write(reinterpret_cast<char*> (&node), sizeof (NodeType));
    }
};
//template<class _Key, class _Value, class _HashMap, class _CmpNode = std::less<std::pair<_Key, _Value> > >

template<class _Key, class _Value, class _HashMap, class _AddFunc = DefaultAddFunc,
class _WriteFunc = DefaultWriteFunc, class _CmpNode = std::less<std::pair<_Key, _Value> > >
class BigHashMapSorter
{
public:
    typedef std::pair<_Key, _Value> Node;
    typedef long long __int64;

    //类似stl容器的写法，可以const _WrtiteFunc& func = _WriteFunc(),另外可以考虑用tr1::function 去掉模板中的_WriteFunc
    //类似函数指针
    BigHashMapSorter(int cache_size = 10000000, long long merge_size = 1024 * 1024 * 1024)
    : m_maxLen(cache_size / sizeof (std::pair<_Key, _Value>)), m_mergeMem(merge_size),
    m_bAllMem(true), m_swap(NULL), m_swapFile("big_hashmap_sorter_swap.txt"), m_size(0),
    m_writeFunc(_WriteFunc())
    {
        LOG(INFO) << Pval(cache_size) << "\n";
        LOG(INFO) << Pval(m_maxLen) << "\n";
        Pval(m_mergeMem);
        m_swapFile = boost::lexical_cast<string>(getpid()) + m_swapFile;
        m_swap = fopen(m_swapFile.c_str(), "wb");
        LOG_IF(FATAL, !m_swap) << "Open failed " << m_swapFile << endl;
    }

    ~BigHashMapSorter()
    {
        clear();
    }
public:
    //TODO 提供类似map的接口[]

    void add(_Key key, _Value value = 1)
    {
        //        m_map[key] += value;
        m_addFunc(m_map[key], value);
        if (m_map.size() > m_maxLen)
        {
            writeMapOut();
            m_bAllMem = false;
        }
    }

    //    template<typename AddFunc>
    //    void add(_Key key, _Value value, AddFunc add_func)
    //    {
    //        add_func(m_map[key], value);
    //        if (m_map.size() > m_maxLen)
    //        {
    //            writeMapOut();
    //            m_bAllMem = false;
    //        }
    //    }
    //提供一个读文本直接内部add的接口

    void open(const string& infile)
    {
        std::ifstream ifs(infile.c_str());
        Node node;
        while (ifs.read(reinterpret_cast<char*> (&node), sizeof (Node)))
        {
            add(node.first, node.second);
        }
    }

    /**
     * sort and save the result to out_file
     */
    void save(const string& out_file)
    {
        namespace bf = boost::filesystem;
        if (m_map.size() > 0)
        {
            writeMapOut();
        }
        if (m_swap)
        {
            fclose(m_swap);
            m_swap = NULL;
        }
        LOG(INFO) << Pval(m_size) << "\n";
        LOG(INFO) << Pval(m_bAllMem) << "\n";

        sort(out_file); //外部排序写结果文件
    }

    template<typename AddFunc>
    void save(const string& out_file, AddFunc)
    {
        namespace bf = boost::filesystem;
        if (m_map.size() > 0)
        {
            writeMapOut();
        }
        if (m_swap)
        {
            fclose(m_swap);
            m_swap = NULL;
        }
        LOG(INFO) << Pval(m_size) << "\n";
        LOG(INFO) << Pval(m_bAllMem) << "\n";

        sort(out_file); //外部排序写结果文件
    }
    //-----------------func

    void set_maxlen(int x)
    {
        m_maxLen = x;
    }

    void set_cacheSize(int x)
    {
        m_maxLen = x / sizeof (Node);
    }

    bool isAllInMem()
    {
        return m_bAllMem;
    }

    __int64 size()
    {
        if (m_bAllMem)
            return m_map.size();
        else
            return m_size;
    }
private:

    void sort(const string& out_file)
    {
        namespace bf = boost::filesystem;
        //外排序 暂时这样。。。 这样就没有利用到map已经牌好序了，但是如果段数特别多怎么办?  TODO FIXME
        LOG(INFO) << "k_merge begin" << endl;
        LOG(INFO) << Pval(boost::filesystem::file_size(m_swapFile));
        string tmp_sorted_file = boost::lexical_cast<string > (time(NULL));
        Pval(m_mergeMem);
        int status = k_merge_file<Node, _CmpNode > (m_swapFile.c_str(), tmp_sorted_file.c_str(), _CmpNode(), m_mergeMem);
        if (status == -1)
        {
            LOG_WARNING("fail to merge");
            return;
        }
        LOG(INFO) << Pval(boost::filesystem::file_size(tmp_sorted_file));
        LOG(INFO) << "k merge end" << endl;
        uniqueAddCopy(tmp_sorted_file, out_file);
        bf::remove(bf::path(tmp_sorted_file));
    }

    /**去掉重复元素并且加和value的值*/
    void uniqueAddCopy(const string& tmp_file, const string& out_file)
    {
        LOG(INFO) << "remvoe duplicate" << endl;
        Node pre_node;
        Node node;
        std::ifstream ifs(tmp_file.c_str(), std::ios::binary);
        std::ofstream ofs(out_file.c_str(), std::ios::binary);
//        std::ofstream ofs(out_file.c_str()); //写不写binary好像都一样啊
        bool contain_node = false;
        contain_node = ifs.read(reinterpret_cast<char*> (&pre_node), sizeof (Node));

        uint num = 0;
        while (true)
        {
            if (!ifs.read(reinterpret_cast<char*> (&node), sizeof (Node)))
                break;
            if (pre_node.first == node.first)
            {
                //                pre_node.second += node.second; //如何外部需要支持+= 不加functor?
                m_addFunc(pre_node.second, node.second);
            }
            else
            {
                //                ofs.write(reinterpret_cast<char*> (&pre_node), sizeof (Node));
                m_writeFunc(ofs, pre_node);
                pre_node = node;
                num++;
            }
        }
        if (contain_node)
            m_writeFunc(ofs, pre_node);
        //            ofs.write(reinterpret_cast<char*> (&pre_node), sizeof (Node));
        num++;
        LOG(INFO) << "The final write node num is " << num << "\n";
        LOG(INFO) << Pval(sizeof (Node)) << "\n";
    }

    //    template<typename AddFunc>
    //     void uniqueAddCopy(const string& tmp_file, const string& out_file, AddFunc add_func)
    //    {
    //        LOG(INFO) << "remvoe duplicate" << endl;
    //        Node pre_node;
    //        Node node;
    //        std::ifstream ifs(tmp_file.c_str(), std::ios::binary);
    //        std::ofstream ofs(out_file.c_str(), std::ios::binary);
    //        bool contain_node = false;
    //        contain_node = ifs.read(reinterpret_cast<char*> (&pre_node), sizeof (Node));
    //
    //        uint num = 0;
    //        while (true)
    //        {
    //            if (!ifs.read(reinterpret_cast<char*> (&node), sizeof (Node)))
    //                break;
    //            if (pre_node.first == node.first)
    //            {
    //                //pre_node.second += node.second; //还是需要支持+= 否则还需要一个functor
    //                add_func(pre_node.second, node.second);
    //            }
    //            else
    //            {
    //                ofs.write(reinterpret_cast<char*> (&pre_node), sizeof (Node));
    //                pre_node = node;
    //                num++;
    //            }
    //        }
    //        if (contain_node)
    //            ofs.write(reinterpret_cast<char*> (&pre_node), sizeof (Node));
    //        num++;
    //        LOG(INFO) << "The final write node num is " << num << "\n";
    //        LOG(INFO) << Pval(sizeof (Node)) << "\n";
    //    }

    void clear()
    {
        namespace bf = boost::filesystem;
        if (m_swap)
        {
            fclose(m_swap);
            m_swap = NULL;
        }
        //删除掉临时文件
        bf::remove(bf::path(m_swapFile));
        m_map.clear();
    }

    void writeMapOut()
    {
        m_size += m_map.size();
        typedef typename _HashMap::iterator MapIter;
        MapIter its = m_map.begin(), ite = m_map.end();
        for (; its != ite; ++its)
        {
            //            fwrite(&(its->first), sizeof (_Key), 1, m_swap);
            //            fwrite(&(its->second), sizeof (_Value), 1, m_swap); //这样写可能会存在对齐问题，写的<Node的大小
            Node node(its->first, its->second); //TODO better?
            fwrite(&(node), sizeof (Node), 1, m_swap);
        }
        m_map.clear();
    }
private:
    int m_maxLen;
    bool m_bAllMem;

    _HashMap m_map;
    FILE* m_swap; //内存不能装满则需要写临时交换文件
    string m_swapFile;

    __int64 m_size;
    long long m_mergeMem; //实验表明1G比较合理
    _AddFunc m_addFunc;
public:
    _WriteFunc m_writeFunc;
};


#endif  //----end of BIG_HASHMAP_SORTER_H_
