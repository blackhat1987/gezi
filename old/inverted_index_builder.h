/**
 *  ==============================================================================
 *
 *          \file   inverted_index_builder.h
 *
 *        \author   chenghuige
 *
 *          \date   2010-03-03 17:01:08.065968
 *                  modified 2011-04-11
 *
 *  \Description:   帮助在线建立InvertedIndex结构
 *                              遇到的问题 fwrite之后stat 文件大小数据部正确 原因 没有先 fclose 文件
 *                              所以不要再析构函数里关闭文件了
 *                              用ofstream 安全些 尽管没有关闭流 但是stat没有问题
 *
 *                              TODO 不用vector 直接用动态开辟的数组会更快？fwrite这种应该差不多，直接
 *                              读到缓存的话 fread应该慢
 *
 *             //提示需要定义<<
            //std::copy(m_tripleVec.begin(), m_tripleVec.end(), ostream_iterator<SortNodeType>(m_ofs));
            //ostreambuf_iterator<SortNodeType> out_it (m_ofs);
            //std::copy(m_tripleVec.begin(), m_tripleVec.end(), out_it);
            //well below is OK :)
            m_ofs.write(reinterpret_cast<char*>(&m_tripleVec[0]), sizeof (SortNodeType) * m_tripleVec.size());
 *
 *
 * invert 要么 load 直接载入索引，要么通过InverttableCreator不要自己直接create,
 * 注意建立过程中的cache大小和invert table 的cahe 大小保持一致
 *
 * TODO 当前稳定了不需要变动，如果BigVec稳定的话 可用BigVec替代 使得代码以及inverted_index.h代码简化
 *
 *  InvertedBuilder其实就是为了InvertedIndex提供初始的排序三元组
 *  另外一个生成InvertedIndex的方法 是调用InvertedIndex自身的add_posting参考 test_convert.cc
 *  ==============================================================================
 */

#ifndef INVERTED_INDEX_BUILDER_H_
#define INVERTED_INDEX_BUILDER_H_

#include<stdio.h>
#include <boost/filesystem.hpp>
#include "ul_log_help.h"
#include "inverted_index.h"
#include "common_help.h"
namespace inverted {
/**
 *   帮助由三元数组<index_id, invert_id,weight>集合生成一个倒排表,用法可参考adrank.cpp 中load
 *
 *    可选择采用什么样的排序方法，理论上讲应该用模板传比较好 但是 由于InvertTable类包括kmerge当前是用的函数指针TODO
 *    所以当前限制两种，1.按照invert_id sort by id 2. 按照weight sort by weight
 *
 *    理论上可选择完全在基于内存，或者内存放不下写文件，外排序建立两种
 *
 *     注意模板参数要和处理的InvertTable模板参数一致
 *
 *  */
template<typename _InvertedIndex = InvertedIndex<> >
        class InvertedIndexBuilder
{
public:
    typedef typename _InvertedIndex::InvertNodeType InvertNodeType;
    typedef typename _InvertedIndex::SortNodeType SortNodeType;
    typedef typename _InvertedIndex::ValueType ValueType;
    typedef typename _InvertedIndex::IndexType IndexType;
    typedef typename _InvertedIndex::KeyType KeyType;
    /**
     *   输入 到排表， 初始文件， 排序文件， 索引文件， 倒排文件， 排序方法
     *
     *   注，也可以类似IvertTable将m_cacheSize设定为静态变量，从而所有InverTableCreator
     *   有相同的cache设定
     */
    InvertedIndexBuilder(_InvertedIndex& invert,
            const std::string& inifile, const std::string& sortedfile,
            const std::string& indexfile, const std::string& invertfile,
            SortMethod sort_method = BY_ID, int64 CacheSize = 1024 * 1024 * 1024,
            bool persistant = true)
    : m_fp(NULL), m_invertedIndex(&invert), m_bAllMem(true), m_dir(""),
    m_inifile(inifile), m_sortedfile(sortedfile), m_indexfile(indexfile), m_invertfile(invertfile),
    m_sortMethod(sort_method), m_bPersitant(persistant), m_maxLen(CacheSize / sizeof (SortNodeType))
    {
        init_();
    }
    /*
     * 只指定索引生成路径,内部文件默认，TODO，不用指定任何文件和路径，能够建立完全基于内存的不写文件的倒排
     */
    InvertedIndexBuilder(_InvertedIndex& invert,
            const std::string& dir, SortMethod sort_method = BY_VALUE,
            int64 CacheSize = 1024 * 1024 * 1024, bool persistant = true)
    : m_fp(NULL), m_invertedIndex(&invert), m_bAllMem(true),
    m_inifile(dir + "/ini.idx"), m_sortedfile(dir + "/sorted.idx"),
    m_indexfile(dir + "/index.idx"), m_invertfile(dir + "/invert.idx"), m_dir(dir),
    m_sortMethod(sort_method), m_bPersitant(persistant), m_maxLen(CacheSize / sizeof (SortNodeType))
    {
        init_(dir);
    }
    InvertedIndexBuilder()
    : m_fp(NULL), m_invertedIndex(NULL), m_bAllMem(true), m_dir(""), m_bPersitant(true)
    {
    }
    ~InvertedIndexBuilder()
    {
        clear();
    }
    void clear()
    {
        LOG_TRACE("clear");
        if (m_fp)
        {
            fclose(m_fp);
        }
        bf::remove(m_inifile);
    }
    void init_()
    {
        m_fp = fopen(m_inifile.c_str(), "wb");

        if (!m_fp)
        {
            LOG_FATAL("Open failed %s", m_inifile.c_str());
            throw -1;
        }

        if (!m_bPersitant)
        {
            //设定倒排表不需要硬盘最终存储
            m_invertedIndex->set_nonpersistant();
        }
    }
    void init_(const std::string& dir)
    {
        namespace bf = boost::filesystem;
        bf::path path(dir); //如果索引输出路径文件夹未被建立则首先建立，比如update_data/abc,需要首先建立abc文件夹
        if (!bf::exists(path))
        {
            LOG_WARNING("%s not exist, will create first", dir.c_str());
            bf::create_directories(path);
        }
        init_();
    }
    /**
     * depreated
     */
    void init(_InvertedIndex& invert,
            const std::string& inifile, const std::string& sortedfile,
            const std::string& indexfile, const std::string& invertfile,
            int64 CacheSize = 1024 * 1024 * 1024, bool persistant = true,
            SortMethod sort_method = BY_ID)
    {
        m_invertedIndex = &invert;
        m_inifile = inifile;
        m_sortedfile = sortedfile;
        m_indexfile = indexfile;
        m_invertfile = invertfile;
        m_maxLen = CacheSize / sizeof (SortNodeType);
        m_sortMethod = sort_method;
        m_bPersitant = persistant;
        m_dir = "";
    }
    void init(_InvertedIndex& invert,
            const std::string& dir, SortMethod sort_method = BY_ID,
            int64 CacheSize = 1024 * 1024 * 1024, bool persistant = true)
    {
        m_sortMethod = sort_method;
        m_invertedIndex = &invert;
        m_inifile = dir + "/ini.idx";
        m_sortedfile = dir + "/sorted.idx";
        m_indexfile = dir + "/index.idx";
        m_invertfile = dir + "/invert.idx";
        m_maxLen = CacheSize / sizeof (SortNodeType);
        m_dir = dir;
        init_(dir);
    }
    inline void add(IndexType index_id, KeyType invert_id, ValueType weight)
    {
        m_tripleVec.push_back(SortNodeType(index_id, invert_id, weight));
        if (m_tripleVec.size() > m_maxLen)
        {
            fwrite(&m_tripleVec[0], sizeof (SortNodeType), m_tripleVec.size(), m_fp);
            m_tripleVec.clear();
            m_bAllMem = false;
        }
    }
    inline void add(IndexType index_id, KeyType invert_id, ValueType weight, int weight2)
    {
        m_tripleVec.push_back(SortNodeType(index_id, invert_id, weight, weight2));
        if (m_tripleVec.size() > m_maxLen)
        {
            fwrite(&m_tripleVec[0], sizeof (SortNodeType), m_tripleVec.size(), m_fp);
            m_tripleVec.clear();
            m_bAllMem = false;
        }
    }
    float get_mem()
    {
        return m_tripleVec.size() * sizeof (SortNodeType) / float(1024 * 1024 * 1024);
    }
    float get_realmem()
    {
        return m_tripleVec.capacity() * sizeof (SortNodeType) / float(1024 * 1024 * 1024);
    }
    uint64 build(bool need_sort = true)
    {
        if (need_sort)
            return build_normal();
        else
            return build_nosort();
    }
    ///当全部三元组加入完毕，建立倒排表
    uint64 build_normal()
    {

        if (!m_bAllMem) //不能完全放在内存，通过外排序
        {
            LOG_TRACE("The index is build from disk");
            if (m_tripleVec.size() > 0)
            {
                fwrite(&m_tripleVec[0], sizeof (SortNodeType), m_tripleVec.size(), m_fp);
                m_tripleVec.clear();
            }
            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }
            if (m_sortMethod == BY_ID)
            {
                if (m_dir.empty())
                    m_invertedIndex->create(m_inifile.c_str(), m_sortedfile.c_str(), m_indexfile.c_str(), m_invertfile.c_str());
                else
                    m_invertedIndex->create(m_dir.c_str());
                m_invertedIndex->set_sort_method(BY_ID);
            }
            else if (m_sortMethod == BY_VALUE)
            {
                if (m_dir.empty())
                    m_invertedIndex->create(m_inifile.c_str(), m_sortedfile.c_str(), m_indexfile.c_str(),
                        m_invertfile.c_str(), CmpSTNodeWeight(), m_maxLen * sizeof (SortNodeType));
                else
                    m_invertedIndex->create(m_dir.c_str(), CmpSTNodeWeight(), m_maxLen * sizeof (SortNodeType));
                m_invertedIndex->set_sort_method(BY_VALUE);
            }
            else if (m_sortMethod == BY_VALUE_REVERSE)
            {
                if (m_dir.empty())
                    m_invertedIndex->create(m_inifile.c_str(), m_sortedfile.c_str(), m_indexfile.c_str(),
                        m_invertfile.c_str(), CmpSTNodeWeight_Reverse(), m_maxLen * sizeof (SortNodeType));
                else
                    m_invertedIndex->create(m_dir.c_str(), CmpSTNodeWeight_Reverse(), m_maxLen * sizeof (SortNodeType));
                m_invertedIndex->set_sort_method(BY_VALUE_REVERSE);
            }
            else
            {
                if (m_dir.empty())
                    m_invertedIndex->create(m_inifile.c_str(), m_sortedfile.c_str(), m_indexfile.c_str(),
                        m_invertfile.c_str(), CmpSTNodeNoOrder(), m_maxLen * sizeof (SortNodeType));
                else
                    m_invertedIndex->create(m_dir.c_str(), CmpSTNodeNoOrder(), m_maxLen * sizeof (SortNodeType));
                m_invertedIndex->set_sort_method(NO_ORDER);
            }

        }
        else
        {
            LOG_TRACE("The index is build all in mem");
            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }
            if (m_sortMethod == BY_ID)
            {
                LOG_INFO("Sort by id");
                std::sort(m_tripleVec.begin(), m_tripleVec.end());
                m_invertedIndex->set_sort_method(BY_ID);
            }
            else if (m_sortMethod == BY_VALUE)
            {
                LOG_INFO("Sort by weight");
                std::sort(m_tripleVec.begin(), m_tripleVec.end(), CmpSTNodeWeight());
                m_invertedIndex->set_sort_method(BY_VALUE);
            }
            else if (m_sortMethod == BY_VALUE_REVERSE)
            {
                LOG_INFO("Sort by weight");
                std::sort(m_tripleVec.begin(), m_tripleVec.end(), CmpSTNodeWeight_Reverse());
                m_invertedIndex->set_sort_method(BY_VALUE_REVERSE);
            }
            else //no order
            {
                LOG_INFO("Sort no order");
                std::sort(m_tripleVec.begin(), m_tripleVec.end(), CmpSTNodeNoOrder());
                m_invertedIndex->set_sort_method(NO_ORDER);
            }

            if (m_dir.empty())
                m_invertedIndex->create(m_tripleVec, m_indexfile.c_str(), m_invertfile.c_str());
            else
                m_invertedIndex->create(m_tripleVec, m_dir.c_str());

            m_tripleVec.clear();

            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }
        }

        return m_invertedIndex->invert_size();
    }

    ///不要排序，已经排好序的情况下，快速创建, 这种情况下m_inifile就是排好序的文件sorted!
    uint64 build_nosort()
    {

        if (!m_bAllMem) //不能完全放在内存，通过外排序
        {
            LOG_TRACE("The index is build from disk");
            if (m_tripleVec.size() > 0)
            {
                fwrite(&m_tripleVec[0], sizeof (SortNodeType), m_tripleVec.size(), m_fp);
                m_tripleVec.clear();
            }
            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }
            //从排好序的文件中创建倒排
            m_invertedIndex->create(m_inifile.c_str(), m_indexfile.c_str(), m_invertfile.c_str());
        }
        else
        {
            LOG_TRACE("The index is build all in mem");
            write_vec(m_tripleVec, m_dir + std::string(".triple_vec.idx")); //好像耗时长的程序最后建立倒排会不成功写硬盘，如果么有这个？why?
            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }
            //从内存创建
            if (m_dir.empty())
                m_invertedIndex->create(m_tripleVec, m_indexfile.c_str(), m_invertfile.c_str());
            else
                m_invertedIndex->create(m_tripleVec, m_dir.c_str());
            m_tripleVec.clear();
        }
        return m_invertedIndex->invert_size();
    }

private:
    _InvertedIndex* m_invertedIndex;
    std::string m_inifile;
    std::string m_sortedfile;
    std::string m_indexfile;
    std::string m_invertfile;
    std::string m_dir;

    int64 m_maxLen;
    SortMethod m_sortMethod;

    bool m_bAllMem; ///是否可以全放在内存
    bool m_bPersitant; ///是否需要保留磁盘内容

    std::vector<SortNodeType> m_tripleVec; ///数据存放cahe如果够大则全部数据完整存放在此处
    FILE* m_fp; ///指向inifile
};

} //----end of namespace inverted

#endif  //----end of INVERT_TABLE_CREATOR_H_
