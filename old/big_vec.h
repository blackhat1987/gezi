/** 
 *  ==============================================================================
 * 
 *          \file   big_vec.h
 *
 *        \author   chenghuige 
 *          
 *          \date   2010-07-02 20:48:06.597214
 *  
 *  \Description:   大的vector包装vector,如果超出内存范围则写文件。
 *                  提供sort接口一个序列排序帮助，自动处理内存或者需要外排序,
 *                  当前只提供只读操作的正向顺序访问迭带器。
 *
 *
 *             TODO FIXME
 *             当前只考虑写一次，读一次的支持，未考虑再次读
 *
 *              FIXME BigVec2 ++ 还是不对
 *
 *     size()函数是不准确的，因为调用finish之后才是准确的，不过size也没有用，用iterator顺序访问
 *    iterator ->begin() 的时候自动调用 finish,
 *
 *     或者你自己确保最后push完了 调用一下finish达到稳定状态
 *
 *     特别注意迭带器只能顺序访问,而且现在只能
 *     1. 不停的push_back
 *     2. sort
 *     3. 顺序访问
 *
 *     或者 1,3
 *
 *     但是不要试图sort之后再push 之类的 TODO,因为再push需要输出再次打开输出文件,而现在
 *     sort 或者 直接finsh之后，就关闭了。。。 再push.. 理论需要再加个外部强制调用的
 *     re_start() 表示m_iniFile需要被打开，且指针指向最后,
 *     或者就让原输出一直开着。。但是sort之后换了要输出的文件。。。小复杂 
 *  ==============================================================================
 */

#ifndef BIG_VEC_H_
#define BIG_VEC_H_

#include <boost/filesystem.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <glog/logging.h>
#include "winner_tree.h"
#include <fstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/scoped_ptr.hpp>


using boost::scoped_ptr;
template<typename _Vec, typename _Node>
class bigvec_iterator
: public boost::iterator_facade<
bigvec_iterator<_Vec, _Node>
, _Node
, boost::forward_traversal_tag
, _Node&
>
{
private:
    _Vec* m_pvec;

public:
    bigvec_iterator()
    : m_pvec(NULL)
    {
    }
    explicit bigvec_iterator(_Vec* pbig_vec)
    : m_pvec(pbig_vec)
    {
        if (!m_pvec->isInited())
        {
            m_pvec->finish();
        }
        if (m_pvec->size() == 0)
            m_pvec = NULL;
    }

private:
    friend class boost::iterator_core_access;
    void increment()
    {
        if (!m_pvec->increment())
        {
            m_pvec = NULL;
        }
    }
    bool equal(bigvec_iterator<_Vec, _Node> const& other) const
    {
        return m_pvec == other.m_pvec;
    }
    _Node& dereference() const
    {
        return m_pvec->current();
    }
};
/**
 *
 * TODO friend for interator and use private for increment()
 * 其实cache_size 可以作为模板固定参数
 */
template<class _Node, class _Cmp = std::less<_Node> >
class BigVec
{
public:
    typedef bigvec_iterator<BigVec<_Node, _Cmp>, _Node> iterator;
public:
    BigVec(int cache_size = 512 * 1024 * 1024, _Cmp cmp = _Cmp(),
           const char* infile = "bigvec_ini.txt",
           const char* sorted_file = "bigvec_sorted.txt")
    : m_maxLen(cache_size / sizeof (_Node)), m_sorter(cmp), m_bAllMem(true), m_fp(NULL),
    m_iniFile(infile), m_sortedFile(sorted_file), m_cur(0), m_size(0), m_end(false), m_bInited(false)
    {
        m_fp = fopen(infile, "wb");
        LOG_IF(ERROR, !m_fp) << "Open failed " << infile << endl;
    }
    ~BigVec()
    {
        clear();
    }
private:
    int m_maxLen;
    _Cmp m_sorter;
    bool m_bAllMem;
    bool m_bInited;

    vector<_Node> m_vec;
    FILE* m_fp;

    string m_iniFile;
    string m_sortedFile;

    int m_cur;
    __int64 m_size;
    bool m_end; //for iterator
    int m_curVecSize; //只当存在写入文件的时候
public:
    //-------------iterator
    iterator begin()
    {
        return bigvec_iterator<BigVec<_Node, _Cmp>, _Node > (this);
    }
    iterator end()
    {
        return bigvec_iterator<BigVec<_Node, _Cmp>, _Node > ();
    }
    //-----------------func
    void set_maxlen(int x)
    {
        m_maxLen = x;
    }
    void set_cacheSize(int x)
    {
        m_maxLen = x / sizeof (_Node);
    }
    void clear()
    {
        namespace bf = boost::filesystem;
        if (m_fp)
        {
            fclose(m_fp);
            m_fp = NULL;
        }
        //删除掉排序文件
        bf::remove(bf::path(m_iniFile));
        bf::remove(bf::path(m_sortedFile));
        m_vec.clear();
    }
    bool isAllInMem()
    {
        return m_bAllMem;
    }
    void push_back(const _Node& node)
    {
        m_vec.push_back(node);
        if (m_vec.size() > m_maxLen)
        {
            m_size += m_vec.size();
            LOG(INFO) << "Mem can not hold the vec, wirte to disk" << endl;
            fwrite(&m_vec[0], sizeof (_Node), m_vec.size(), m_fp);
            m_vec.clear();
            m_bAllMem = false;
        }
    }
    __int64 size()
    {
        if (m_bAllMem)
            return m_vec.size();
        else
            return m_size;
    }
    void sort()
    {
        if (m_bAllMem)
        {
            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }
            //直接内存排序
            std::sort(m_vec.begin(), m_vec.end(), m_sorter);
        }
        else
        {
            if (m_vec.size() > 0)
            {
                m_size += m_vec.size();
                fwrite(&m_vec[0], sizeof (_Node), m_vec.size(), m_fp);
                m_vec.clear();
            }
            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }
            //外排序
            int status = K_MergeFile<_Node, _Cmp > (m_iniFile.c_str(), m_sortedFile.c_str(), m_sorter, m_maxLen * sizeof (_Node));
            LOG_IF(ERROR, status == -1) << "K_MergeFile failed" << std::endl;
            std::swap(m_iniFile, m_sortedFile);
        }
        finish();
    }
    bool isInited()
    {
        return m_bInited;
    }
    void setFinish()
    {
        m_bInited = true;
    }
    void finish()
    {
        if (!m_bAllMem)
        {
            if (m_vec.size() > 0)
            {
                m_size += m_vec.size();
                fwrite(&m_vec[0], sizeof (_Node), m_vec.size(), m_fp);
                m_vec.clear();
            }
            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }
            m_vec.resize(m_maxLen);
            m_fp = fopen(m_iniFile.c_str(), "rb");
            m_curVecSize = fread(&m_vec[0], sizeof (_Node), m_maxLen, m_fp);
        }
        setFinish();
        setCur();
    }

    ///get not advance
    _Node& current()
    {
        return m_vec[m_cur];
    }
    void setCur()
    {
        m_cur = 0;
    }
    bool increment()
    {
        if (m_bAllMem)
        {
            if (m_cur < (m_vec.size() - 1))
            {
                m_cur++;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (m_cur < (m_curVecSize - 1))
            {
                m_cur++;
                return true;
            }
            else
            {
                if (feof(m_fp))
                    return false;
                else
                {
                    m_curVecSize = fread(&m_vec[0], sizeof (_Node), m_maxLen, m_fp);
                    m_cur = 0;
                    return true;
                }
            }
        }
    }

};

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/string.hpp>
/**
 * 和上面的一样但是这个是用boost 序列化的，要求使用者对_Node做好序列化准备，
 * 这样可以方便处理带有string 类型的_Node
 *
 * 这里面需要注意m_ofs,m_ifs一开始 m_ofs(infile, std::ios::binary), m_ifs(infile, std::ios::binary)
 * 同时初始化 m_oa(m_ofs, std::ios::binary) 这个可以但是再 m_ia(m_ifs, std::ios::binary) 会抛出异常，这里最终
 * 使用了指针
 */
template<class _Node, class _Cmp = std::less<_Node> >
class BigVec2
{
public:
    typedef bigvec_iterator<BigVec2<_Node, _Cmp>, _Node> iterator;
public:
    BigVec2(int cache_size = 512 * 1024 * 1024, _Cmp cmp = _Cmp(),
            const char* infile = "bigvec2_ini.txt",
            const char* sorted_file = "bigvec2_sorted.txt")
    : m_maxLen(cache_size / sizeof (_Node)), m_sorter(cmp), m_bAllMem(true),
    m_iniFile(infile), m_sortedFile(sorted_file), m_cur(0), m_size(0), m_end(false), m_writeTimes(0), m_bInited(false),
    m_ofs(infile, std::ios::binary)
    {
        LOG(INFO) << "notice maxlen not correct right now " << m_maxLen << endl; //FIXME
        m_oa.reset(new boost::archive::binary_oarchive(m_ofs, std::ios::binary));
    }
    ~BigVec2()
    {
        clear();
    }
private:
    int m_maxLen;
    _Cmp m_sorter;
    bool m_bAllMem;
    bool m_bInited;

    vector<_Node> m_vec;
    std::ofstream m_ofs;
    std::ifstream m_ifs;
    scoped_ptr<boost::archive::binary_oarchive> m_oa;
    scoped_ptr<boost::archive::binary_iarchive> m_ia;
    string m_iniFile;
    string m_sortedFile;

    int m_cur;
    __int64 m_size;
    int m_writeTimes;
    bool m_end; //for iterator
public:
    //-------------iterator
    iterator begin()
    {
        return bigvec_iterator<BigVec2<_Node, _Cmp>, _Node > (this);
    }
    iterator end()
    {
        return bigvec_iterator<BigVec2<_Node, _Cmp>, _Node > ();
    }
    //-----------------func
    void set_maxlen(int x)
    {
        m_maxLen = x;
    }
    void set_cacheSize(int x)
    {
        m_maxLen = x / sizeof (_Node);
    }
    void clear()
    {
        namespace bf = boost::filesystem;
        if (!m_bAllMem)
        {
            m_ifs.close();
        }
        //删除掉排序文件, FIXME 怎么bigvec2_ini.txt没有被删除掉？
        bf::remove(bf::path(m_iniFile));
        bf::remove(bf::path(m_sortedFile));
        m_vec.clear();
    }
    bool isAllInMem()
    {
        return m_bAllMem;
    }
    void push_back(const _Node& node)
    {
        m_vec.push_back(node);
        if (m_vec.size() > m_maxLen)
        {
            m_size += m_vec.size();
            LOG(INFO) << "Mem can not hold the vec, wirte to disk" << endl;
            *m_oa << m_vec; //save
            m_writeTimes++;
            m_vec.clear();
            m_bAllMem = false;
        }
    }
    void setCur()
    {
        m_cur = 0;
    }
    __int64 size()
    {
        if (m_bAllMem)
            return m_vec.size();
        else
            return m_size;
    }
    bool isInited()
    {
        return m_bInited;
    }
    void setFinish()
    {
        m_bInited = true;
    }

    //没有排序的话，也要先finish一下,为iterator顺序访问准备
    void finish()
    {
        if (m_bAllMem)
        {
            m_ofs.close();
            m_ifs.close();
        }
        else
        {
            if (m_vec.size() > 0) //如果没有提前sort
            {
                m_size += m_vec.size();
                LOG(INFO) << "Mem can not hold the vec, wirte to disk" << endl;
                *m_oa << m_vec; //save
                m_writeTimes++;
                m_vec.clear();
            }
            m_ofs.close();
            m_ifs.open(m_iniFile.c_str(), std::ios::binary);
            m_ia.reset(new boost::archive::binary_iarchive(m_ifs, std::ios::binary));
            m_vec.clear();
            *m_ia >> m_vec;
            m_writeTimes--;
        }
        setFinish();
        setCur();
    }
    void sort()
    {
        if (m_bAllMem)
        {
            m_ofs.close();
            m_ifs.close();
            //直接内存排序
            std::sort(m_vec.begin(), m_vec.end(), m_sorter);
        }
        else
        {
            if (m_vec.size() > 0)
            {
                m_size += m_vec.size();
                LOG(INFO) << "Mem can not hold the vec, wirte to disk" << endl;
                *m_oa << m_vec; //save
                m_writeTimes++;
                m_vec.clear();
            }

            m_ofs.close();

            //外排序
            int status = K_MergeFile<_Node, _Cmp > (m_iniFile.c_str(), m_sortedFile.c_str(), m_sorter, m_maxLen * sizeof (_Node));
            LOG_IF(ERROR, status == -1) << "K_MergeFile failed" << std::endl;
            std::swap(m_iniFile, m_sortedFile);
        }
        finish();
    }

    ///get not advance
    _Node& current()
    {
        return m_vec[m_cur];
    }
    bool increment()
    {
        if (m_bAllMem)
        {
            if (m_cur < (m_vec.size() - 1))
            {
                m_cur++;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (m_cur < (m_vec.size() - 1))
            {
                m_cur++;
                return true;
            }
            else
            {
                if (m_writeTimes == 0)
                    return false;
                else
                {
                    m_vec.clear();
                    *m_ia >> m_vec;
                    m_writeTimes--;
                    m_cur = 0;
                    return true;
                }
            }
        }
    }

};

#endif  //----end of BIG_VEC_H_
