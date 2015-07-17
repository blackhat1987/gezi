/** 
 *  ==============================================================================
 * 
 *          \file   big_hash_map.h
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

 * �ڲ�����hash mapȥ��
 *
 *  FIXME TODO ȥ�����е� += �Է���֧�ָ����add��ʽ, Ĭ������AddFunc =
 * DefualtAddFunc(Val& org, const Val&cur)
 * {
 *      org += cur;
 * }
 *
 *  ��û�а취�ⲿ���� += ֧�֣��Ӷ�����Ҫ�ڲ�AddFunc ����֧��pair +  how to ?
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

    //����stl������д��������const _WrtiteFunc& func = _WriteFunc(),������Կ�����tr1::function ȥ��ģ���е�_WriteFunc
    //���ƺ���ָ��
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
    //TODO �ṩ����map�Ľӿ�[]

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
        LOG(INFO) << Pval(m_bAllMem) << "\n";

        sort(out_file); //�ⲿ����д����ļ�
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

        sort(out_file); //�ⲿ����д����ļ�
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

    /**ȥ���ظ�Ԫ�ز��ҼӺ�value��ֵ*/
    void uniqueAddCopy(const string& tmp_file, const string& out_file)
    {
        LOG(INFO) << "remvoe duplicate" << endl;
        Node pre_node;
        Node node;
        std::ifstream ifs(tmp_file.c_str(), std::ios::binary);
        std::ofstream ofs(out_file.c_str(), std::ios::binary);
//        std::ofstream ofs(out_file.c_str()); //д��дbinary����һ����
        bool contain_node = false;
        contain_node = ifs.read(reinterpret_cast<char*> (&pre_node), sizeof (Node));

        uint num = 0;
        while (true)
        {
            if (!ifs.read(reinterpret_cast<char*> (&node), sizeof (Node)))
                break;
            if (pre_node.first == node.first)
            {
                //                pre_node.second += node.second; //����ⲿ��Ҫ֧��+= ����functor?
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
    //                //pre_node.second += node.second; //������Ҫ֧��+= ������Ҫһ��functor
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
        //ɾ������ʱ�ļ�
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
            //            fwrite(&(its->second), sizeof (_Value), 1, m_swap); //����д���ܻ���ڶ������⣬д��<Node�Ĵ�С
            Node node(its->first, its->second); //TODO better?
            fwrite(&(node), sizeof (Node), 1, m_swap);
        }
        m_map.clear();
    }
private:
    int m_maxLen;
    bool m_bAllMem;

    _HashMap m_map;
    FILE* m_swap; //�ڴ治��װ������Ҫд��ʱ�����ļ�
    string m_swapFile;

    __int64 m_size;
    long long m_mergeMem; //ʵ�����1G�ȽϺ���
    _AddFunc m_addFunc;
public:
    _WriteFunc m_writeFunc;
};


#endif  //----end of BIG_HASHMAP_SORTER_H_
