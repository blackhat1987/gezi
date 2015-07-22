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
 *  \Description:   �������߽���InvertedIndex�ṹ
 *                              ���������� fwrite֮��stat �ļ���С���ݲ���ȷ ԭ�� û���� fclose �ļ�
 *                              ���Բ�Ҫ������������ر��ļ���
 *                              ��ofstream ��ȫЩ ����û�йر��� ����statû������
 *
 *                              TODO ����vector ֱ���ö�̬���ٵ��������죿fwrite����Ӧ�ò�ֱ࣬��
 *                              ��������Ļ� freadӦ����
 *
 *             //��ʾ��Ҫ����<<
            //std::copy(m_tripleVec.begin(), m_tripleVec.end(), ostream_iterator<SortNodeType>(m_ofs));
            //ostreambuf_iterator<SortNodeType> out_it (m_ofs);
            //std::copy(m_tripleVec.begin(), m_tripleVec.end(), out_it);
            //well below is OK :)
            m_ofs.write(reinterpret_cast<char*>(&m_tripleVec[0]), sizeof (SortNodeType) * m_tripleVec.size());
 *
 *
 * invert Ҫô load ֱ������������Ҫôͨ��InverttableCreator��Ҫ�Լ�ֱ��create,
 * ע�⽨�������е�cache��С��invert table ��cahe ��С����һ��
 *
 * TODO ��ǰ�ȶ��˲���Ҫ�䶯�����BigVec�ȶ��Ļ� ����BigVec��� ʹ�ô����Լ�inverted_index.h�����
 *
 *  InvertedBuilder��ʵ����Ϊ��InvertedIndex�ṩ��ʼ��������Ԫ��
 *  ����һ������InvertedIndex�ķ��� �ǵ���InvertedIndex�����add_posting�ο� test_convert.cc
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
 *   ��������Ԫ����<index_id, invert_id,weight>��������һ�����ű�,�÷��ɲο�adrank.cpp ��load
 *
 *    ��ѡ�����ʲô�������򷽷��������Ͻ�Ӧ����ģ�崫�ȽϺ� ���� ����InvertTable�����kmerge��ǰ���õĺ���ָ��TODO
 *    ���Ե�ǰ�������֣�1.����invert_id sort by id 2. ����weight sort by weight
 *
 *    �����Ͽ�ѡ����ȫ�ڻ����ڴ棬�����ڴ�Ų���д�ļ���������������
 *
 *     ע��ģ�����Ҫ�ʹ����InvertTableģ�����һ��
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
     *   ���� ���ű� ��ʼ�ļ��� �����ļ��� �����ļ��� �����ļ��� ���򷽷�
     *
     *   ע��Ҳ��������IvertTable��m_cacheSize�趨Ϊ��̬�������Ӷ�����InverTableCreator
     *   ����ͬ��cache�趨
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
     * ָֻ����������·��,�ڲ��ļ�Ĭ�ϣ�TODO������ָ���κ��ļ���·�����ܹ�������ȫ�����ڴ�Ĳ�д�ļ��ĵ���
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
            //�趨���ű���ҪӲ�����մ洢
            m_invertedIndex->set_nonpersistant();
        }
    }
    void init_(const std::string& dir)
    {
        namespace bf = boost::filesystem;
        bf::path path(dir); //����������·���ļ���δ�����������Ƚ���������update_data/abc,��Ҫ���Ƚ���abc�ļ���
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
    ///��ȫ����Ԫ�������ϣ��������ű�
    uint64 build_normal()
    {

        if (!m_bAllMem) //������ȫ�����ڴ棬ͨ��������
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

    ///��Ҫ�����Ѿ��ź��������£����ٴ���, ���������m_inifile�����ź�����ļ�sorted!
    uint64 build_nosort()
    {

        if (!m_bAllMem) //������ȫ�����ڴ棬ͨ��������
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
            //���ź�����ļ��д�������
            m_invertedIndex->create(m_inifile.c_str(), m_indexfile.c_str(), m_invertfile.c_str());
        }
        else
        {
            LOG_TRACE("The index is build all in mem");
            write_vec(m_tripleVec, m_dir + std::string(".triple_vec.idx")); //�����ʱ���ĳ�����������Ż᲻�ɹ�дӲ�̣����ô�������why?
            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }
            //���ڴ洴��
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

    bool m_bAllMem; ///�Ƿ����ȫ�����ڴ�
    bool m_bPersitant; ///�Ƿ���Ҫ������������

    std::vector<SortNodeType> m_tripleVec; ///���ݴ��cahe���������ȫ��������������ڴ˴�
    FILE* m_fp; ///ָ��inifile
};

} //----end of namespace inverted

#endif  //----end of INVERT_TABLE_CREATOR_H_
