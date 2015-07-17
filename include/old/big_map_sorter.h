/** 
 *  ==============================================================================
 * 
 *          \file   big_map_sorter.h
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

 *  *
 *                 最终写文件按照二进制的 <key, value>写所有元组，注意key如果里面有string什么的
 *                 可以仿照big vec给出一个可以序列化的。
 *
 *                TODO 对于string作为key的给一个序列话的版本
 *
 *
 *  1.add             往map中写元素，value+ 超过设置大小 写swap文件
 *  2.sort            利用swap文件kmerge排序写sorted文件 //注意这个没有利用map已经排好序的信息 TODO
 *  3.removeDuplicate 读取sorted文件去重合并，写最终sorted文件
 *
 *   可以改进的地方，
 *   1. 利用map已经排好序再进行归并
 *   2. 归并过程中就可以合并相同元素，不需要下一步再操作 从而只需要写一个sorted文件即可
 *
 *   实验表明10K大小的MAP比较合适
 *  ==============================================================================
 */

#ifndef BIG_MAP_SORTER_H_
#define BIG_MAP_SORTER_H_
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
#include "WinnerTree_Linux.h"
template<class _Key, class _Value, class _Cmp = std::less<_Key>, class _CmpNode = std::less<std::pair<_Key, _Value> > >
class BigMapSorter
{
public:
    typedef std::pair<_Key, _Value> Node;
    typedef long long __int64;
    BigMapSorter(int cache_size = 10000, _Cmp cmp = _Cmp())
    : m_maxLen(cache_size / sizeof (std::pair<_Key, _Value>)), m_map(cmp),
    m_bAllMem(true), m_swap(NULL), m_swapFile("big_map_sorter_swap.txt"), m_size(0)
    {
        m_swap = fopen(m_swapFile.c_str(), "wb");
        LOG_IF(FATAL, !m_swap) << "Open failed " << m_swapFile << endl;
    }
    ~BigMapSorter()
    {
        clear();
    }
public:
    //TODO 提供类似map的接口[]
    void add(_Key key, _Value value)
    {
        m_map[key] += value;
        if (m_map.size() > m_maxLen)
        {
            writeMapOut();
            m_bAllMem = false;
        }
    }
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

        if (!m_bAllMem)
        {
            cout << "not all in mem" << endl;
            sort(out_file); //外部排序写结果文件
        }
        else
        {
            cout << "all in mem" << endl;
            if (bf::exists(bf::path(out_file)))
                bf::remove(bf::path(out_file));
            bf::rename(bf::path(m_swapFile), bf::path(out_file)); //临时交换文件内容即为排序好的结果文件
        }
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
        int status = K_MergeFile<Node, _CmpNode > (m_swapFile.c_str(), tmp_sorted_file.c_str(), _CmpNode(), kMergeMem);
        LOG_IF(FATAL, status == -1) << "K_MergeFile failed" << std::endl;
        LOG(INFO) << Pval(boost::filesystem::file_size(out_file));
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
        std::ifstream ifs(tmp_file.c_str());
        std::ofstream ofs(out_file.c_str());
        ifs.read(reinterpret_cast<char*> (&pre_node), sizeof (Node));

        while (true)
        {
            if (!ifs.read(reinterpret_cast<char*> (&node), sizeof (Node)))
                break;
            if (pre_node.first == node.first)
            {
                pre_node.second += node.second;
            }
            else
            {
                ofs.write(reinterpret_cast<char*> (&pre_node), sizeof (Node));
                pre_node = node;
            }
        }
        ofs.write(reinterpret_cast<char*> (&pre_node), sizeof (Node));
    }
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
        typedef typename std::map<_Key, _Value>::iterator MapIter;
        MapIter its = m_map.begin(), ite = m_map.end();
        for (; its != ite; ++its)
        {
            fwrite(&(its->first), sizeof (_Key), 1, m_swap);
            fwrite(&(its->second), sizeof (_Value), 1, m_swap);
        }
        m_map.clear();
    }
private:
    int m_maxLen;
    bool m_bAllMem;

    std::map<_Key, _Value, _Cmp> m_map;
    FILE* m_swap; //内存不能装满则需要写临时交换文件
    string m_swapFile;

    __int64 m_size;
    const static int kMergeMem = 1024 * 1024 * 1024; //实验表明1G比较合理
};

#endif  //----end of BIG_MAP_SORTER_H_
