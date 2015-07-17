/** 
 *  ==============================================================================
 * 
 *          \file   big_map_sorter.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-10-16 19:36:02.372304
 *  
 *  \Description:  һ��������������������������̵ĵģ��ٶ��������ظ�Ԫ�ز�����vlaue�Ӻ͹鲢��
 *                 �÷�
 *                 ���룬 ����add(key, value)
 *                 ����� ��������һ�������ļ�,�����Ƿ����ڴ����ܹ���ȫ���
 *                 Sorter sorter(outfile)
 *                 while
 *                    sorter.add(key, value)
 *                 sorter.sort()
 *
 *                 ֧�������ı� <key, value>���
 *                 ���ͬ��
 Sorter sorter(outfile);
 * sorter.open(infile);
 * sorter.sort();

 *  *
 *                 ����д�ļ����ն����Ƶ� <key, value>д����Ԫ�飬ע��key���������stringʲô��
 *                 ���Է���big vec����һ���������л��ġ�
 *
 *                TODO ����string��Ϊkey�ĸ�һ�����л��İ汾
 *
 *
 *  1.add             ��map��дԪ�أ�value+ �������ô�С дswap�ļ�
 *  2.sort            ����swap�ļ�kmerge����дsorted�ļ� //ע�����û������map�Ѿ��ź������Ϣ TODO
 *  3.removeDuplicate ��ȡsorted�ļ�ȥ�غϲ���д����sorted�ļ�
 *
 *   ���ԸĽ��ĵط���
 *   1. ����map�Ѿ��ź����ٽ��й鲢
 *   2. �鲢�����оͿ��Ժϲ���ͬԪ�أ�����Ҫ��һ���ٲ��� �Ӷ�ֻ��Ҫдһ��sorted�ļ�����
 *
 *   ʵ�����10K��С��MAP�ȽϺ���
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
    //TODO �ṩ����map�Ľӿ�[]
    void add(_Key key, _Value value)
    {
        m_map[key] += value;
        if (m_map.size() > m_maxLen)
        {
            writeMapOut();
            m_bAllMem = false;
        }
    }
    //�ṩһ�����ı�ֱ���ڲ�add�Ľӿ�
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
            sort(out_file); //�ⲿ����д����ļ�
        }
        else
        {
            cout << "all in mem" << endl;
            if (bf::exists(bf::path(out_file)))
                bf::remove(bf::path(out_file));
            bf::rename(bf::path(m_swapFile), bf::path(out_file)); //��ʱ�����ļ����ݼ�Ϊ����õĽ���ļ�
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
        //������ ��ʱ���������� ������û�����õ�map�Ѿ��ƺ����ˣ�������������ر����ô��?  TODO FIXME
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
    /**ȥ���ظ�Ԫ�ز��ҼӺ�value��ֵ*/
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
        //ɾ������ʱ�ļ�
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
    FILE* m_swap; //�ڴ治��װ������Ҫд��ʱ�����ļ�
    string m_swapFile;

    __int64 m_size;
    const static int kMergeMem = 1024 * 1024 * 1024; //ʵ�����1G�ȽϺ���
};

#endif  //----end of BIG_MAP_SORTER_H_
