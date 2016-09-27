/** 
 *  ==============================================================================
 * 
 *          \file   big_vec.h
 *
 *        \author   chenghuige 
 *          
 *          \date   2010-07-02 20:48:06.597214
 *  
 *  \Description:   ���vector��װvector,��������ڴ淶Χ��д�ļ���
 *                  �ṩsort�ӿ�һ����������������Զ������ڴ������Ҫ������,
 *                  ��ǰֻ�ṩֻ������������˳����ʵ�������
 *
 *
 *             TODO FIXME
 *             ��ǰֻ����дһ�Σ���һ�ε�֧�֣�δ�����ٴζ�
 *
 *              FIXME BigVec2 ++ ���ǲ���
 *
 *     size()�����ǲ�׼ȷ�ģ���Ϊ����finish֮�����׼ȷ�ģ�����sizeҲû���ã���iterator˳�����
 *    iterator ->begin() ��ʱ���Զ����� finish,
 *
 *     �������Լ�ȷ�����push���� ����һ��finish�ﵽ�ȶ�״̬
 *
 *     �ر�ע�������ֻ��˳�����,��������ֻ��
 *     1. ��ͣ��push_back
 *     2. sort
 *     3. ˳�����
 *
 *     ���� 1,3
 *
 *     ���ǲ�Ҫ��ͼsort֮����push ֮��� TODO,��Ϊ��push��Ҫ����ٴδ�����ļ�,������
 *     sort ���� ֱ��finsh֮�󣬾͹ر��ˡ����� ��push.. ������Ҫ�ټӸ��ⲿǿ�Ƶ��õ�
 *     re_start() ��ʾm_iniFile��Ҫ���򿪣���ָ��ָ�����,
 *     ���߾���ԭ���һֱ���š�������sort֮����Ҫ������ļ�������С���� 
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
 * ��ʵcache_size ������Ϊģ��̶�����
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
    int m_curVecSize; //ֻ������д���ļ���ʱ��
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
        //ɾ���������ļ�
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
            //ֱ���ڴ�����
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
            //������
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
 * �������һ�������������boost ���л��ģ�Ҫ��ʹ���߶�_Node�������л�׼����
 * �������Է��㴦�����string ���͵�_Node
 *
 * ��������Ҫע��m_ofs,m_ifsһ��ʼ m_ofs(infile, std::ios::binary), m_ifs(infile, std::ios::binary)
 * ͬʱ��ʼ�� m_oa(m_ofs, std::ios::binary) ������Ե����� m_ia(m_ifs, std::ios::binary) ���׳��쳣����������
 * ʹ����ָ��
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
        //ɾ���������ļ�, FIXME ��ôbigvec2_ini.txtû�б�ɾ������
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

    //û������Ļ���ҲҪ��finishһ��,Ϊiterator˳�����׼��
    void finish()
    {
        if (m_bAllMem)
        {
            m_ofs.close();
            m_ifs.close();
        }
        else
        {
            if (m_vec.size() > 0) //���û����ǰsort
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
            //ֱ���ڴ�����
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

            //������
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
