/**
 *  ==============================================================================
 *
 *          \file   invert_table_creator.h
 *
 *        \author   chenghuige
 *
 *          \date   2010-03-03 17:01:08.065968
 *
 *  \Description:   ��������(�����������P2A)����InvertTable�ṹ
 *                             �����ļ� test_invert_creator.cc
 *
 *                              ���������� fwrite֮��stat �ļ���С��ݲ���ȷ ԭ�� û���� fclose �ļ�
 *                              ���Բ�Ҫ������������ر��ļ���
 *                              ��ofstream ��ȫЩ ����û�йر��� ����statû������
 *
 *                              TODO ����vector ֱ���ö�̬���ٵ�������죿fwrite����Ӧ�ò�ֱ࣬��
 *                              ��������Ļ� freadӦ����
 *
 *             //��ʾ��Ҫ����<<
            //std::copy(m_tripleVec.begin(), m_tripleVec.end(), ostream_iterator<_ST_PidKidInfo>(m_ofs));
            //ostreambuf_iterator<_ST_PidKidInfo> out_it (m_ofs);
            //std::copy(m_tripleVec.begin(), m_tripleVec.end(), out_it);
            //well below is OK :)
            m_ofs.write(reinterpret_cast<char*>(&m_tripleVec[0]), sizeof (_ST_PidKidInfo) * m_tripleVec.size());
 *
 *
 * invert_table Ҫô load ֱ����������Ҫôͨ��InverttableCreator��Ҫ�Լ�ֱ��create,
 * ע�⽨������е�cache��С��invert table ��cahe ��С����һ��
 *
 *  ==============================================================================
 */

#ifndef INVERT_TABLE_CREATOR_H_
#define INVERT_TABLE_CREATOR_H_

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <glog/logging.h>
#include "invert_table.h"
#include "debug_help.h"
#include<stdio.h>
namespace invert_table {
/**
 *   ��������Ԫ����<index_id, invert_id,weight>�������һ�����ű�,�÷��ɲο�adrank.cpp ��load
 *
 *    ��ѡ�����ʲô������򷽷��������Ͻ�Ӧ����ģ�崫�ȽϺ� ���� ����InvertTable�����kmerge��ǰ���õĺ���ָ��TODO
 *    ���Ե�ǰ�������֣�1.����invert_id sort by id 2. ����weight sort by weight
 *
 *    �����Ͽ�ѡ����ȫ�ڻ����ڴ棬�����ڴ�Ų���д�ļ���������������
 *
 *     ע��ģ�����Ҫ�ʹ����InvertTableģ�����һ��
 *
 *  */
template<typename _InvertTable = InvertTable<> >
        class InvertTableCreator
{
public:
    typedef typename _InvertTable::InvertNodeType _InvertNode;
    typedef typename _InvertTable::SortNodeType _ST_PidKidInfo;
    typedef typename _InvertNode::WeightType _WeightType;
    typedef typename _InvertNode::Weight2Type _Weight2Type;
    /**
     *   ���� ���ű? ��ʼ�ļ��� �����ļ��� �����ļ��� �����ļ��� ���򷽷�
     *
     *   ע��Ҳ��������IvertTable��m_cacheSize�趨Ϊ��̬�������Ӷ�����InverTableCreator
     *   ����ͬ��cache�趨
     */
    InvertTableCreator(_InvertTable& invert_table,
            const std::string& inifile, const std::string& sortedfile,
            const std::string& indexfile, const std::string& invertfile,
            SortMethod sort_method = byID, bool persistant = true,
            int CacheSize = 1024 * 1024 * 1024)
    : m_fp(NULL), m_invertTable(&invert_table), m_bAllMem(true), m_dir(""),
    m_inifile(inifile), m_sortedfile(sortedfile), m_indexfile(indexfile), m_invertfile(invertfile),
    m_sortMethod(sort_method), m_bPersitant(persistant), m_maxLen(CacheSize / sizeof (_ST_PidKidInfo))
    {
        init_();
    }
    /*
     * ָֻ���������·��,�ڲ��ļ�Ĭ�ϣ�TODO������ָ���κ��ļ���·�����ܹ�������ȫ�����ڴ�Ĳ�д�ļ��ĵ���
     */
    InvertTableCreator(_InvertTable& invert_table,
            const std::string& dir, SortMethod sort_method = byWeight,
            bool persistant = true, int CacheSize = 1024 * 1024 * 1024)
    : m_fp(NULL), m_invertTable(&invert_table), m_bAllMem(true),
    m_inifile(dir + "/ini.idx"), m_sortedfile(dir + "/sorted.idx"),
    m_indexfile(dir + "/index.idx"), m_invertfile(dir + "/invert.idx"), m_dir(dir),
    m_sortMethod(sort_method), m_bPersitant(persistant), m_maxLen(CacheSize / sizeof (_ST_PidKidInfo))
    {
        init_(dir);
    }
    InvertTableCreator()
    : m_fp(NULL), m_invertTable(NULL), m_bAllMem(true), m_dir(""), m_bPersitant(true)
    {
    }
    ~InvertTableCreator()
    {
        clear();
    }
    void clear()
    {
        LOG(INFO) << "clear " << endl;
        if (m_fp)
        {
            fclose(m_fp);
        }

        if (!m_inifile.empty())
        {
            LOG(INFO) << "delete " << m_inifile << endl;
            bf::remove(bf::path(m_inifile));
        }

        if (!m_sortedfile.empty())
        {
            LOG(INFO) << "delete " << m_sortedfile << endl;
            bf::remove(bf::path(m_sortedfile));
        }
    }
    void init_()
    {
        Pval(m_inifile);
        m_fp = fopen(m_inifile.c_str(), "wb");

        LOG_IF(FATAL, !m_fp) << "Open failed" << m_inifile << endl;
        if (!m_bPersitant)
        {
            //�趨���ű?��ҪӲ�����մ洢
            m_invertTable->setNonPersitant();
        }
    }
    void init_(const std::string& dir)
    {
        namespace bf = boost::filesystem;
        bf::path path(dir); //����������·���ļ���δ�����������Ƚ���������update_data/abc,��Ҫ���Ƚ���abc�ļ���
        if (!bf::exists(path))
        {
            LOG(WARNING) << path << " not exist will create first\n";
            bf::create_directories(path);
        }

    }

    //do not use this one
    void init(_InvertTable& invert,
            const std::string& inifile, const std::string& sortedfile,
            const std::string& indexfile, const std::string& invertfile,
            int CacheSize = 1024 * 1024 * 1024, bool persistant = true,
            SortMethod sort_method = byID)
    {
        m_invertTable = &invert;
        m_inifile = inifile;
        m_sortedfile = sortedfile;
        m_indexfile = indexfile;
        m_invertfile = invertfile;
        m_maxLen = CacheSize / sizeof (_ST_PidKidInfo);
        m_sortMethod = sort_method;
        m_bPersitant = persistant;
        m_dir = "";
    }
    void init(_InvertTable& invert,
            const std::string& dir, SortMethod sort_method = byID,
            int CacheSize = 1024 * 1024 * 1024, bool persistant = true)
    {
        init_(dir);
        m_invertTable = &invert;
        m_inifile = dir + "/ini.idx";
        m_sortedfile = dir + "/sorted.idx";
        m_indexfile = dir + "/index.idx";
        m_invertfile = dir + "/invert.idx";
        m_maxLen = CacheSize / sizeof (_ST_PidKidInfo);
        m_sortMethod = sort_method;
        m_bPersitant = persistant;
        m_dir = dir;
        init_();
    }


    ///����<index_id, invert_id, weight>��Ԫ��
    inline void addTriple(int index_id, int invert_id, _WeightType weight)
    {
        m_tripleVec.push_back(_ST_PidKidInfo(index_id, invert_id, weight));
        if (m_tripleVec.size() > m_maxLen)
        {
            fwrite(&m_tripleVec[0], sizeof (_ST_PidKidInfo), m_tripleVec.size(), m_fp);
            m_tripleVec.clear();
            m_bAllMem = false;
        }
    }
    inline void addTriple(int index_id, int invert_id, _WeightType weight, _Weight2Type weight2)
    {
        m_tripleVec.push_back(_ST_PidKidInfo(index_id, invert_id, weight, weight2));
        if (m_tripleVec.size() > m_maxLen)
        {
            fwrite(&m_tripleVec[0], sizeof (_ST_PidKidInfo), m_tripleVec.size(), m_fp);
            m_tripleVec.clear();
            m_bAllMem = false;
        }
    }


    ///��ȫ����Ԫ�������ϣ��������ű�
    __int64 create()
    {
        LOG(INFO) << Pval(m_bAllMem);
        if (!m_bAllMem) //������ȫ�����ڴ棬ͨ��������
        {
            if (m_tripleVec.size() > 0)
            {
                fwrite(&m_tripleVec[0], sizeof (_ST_PidKidInfo), m_tripleVec.size(), m_fp);
                m_tripleVec.clear();
            }
            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }
            if (m_sortMethod == byID)
            {
                if (m_dir.empty())
                    m_invertTable->create(m_inifile.c_str(), m_sortedfile.c_str(), m_indexfile.c_str(), m_invertfile.c_str());
                else
                    m_invertTable->create(m_dir.c_str());
                m_invertTable->setSortMethod(byID);
            }
            else
            {
                if (m_dir.empty())
                    m_invertTable->create(m_inifile.c_str(), m_sortedfile.c_str(), m_indexfile.c_str(),
                        m_invertfile.c_str(), CmpSTNodeWeight()); //FIXME here not correct?
                else
                    m_invertTable->create(m_dir.c_str(), CmpInvertNodeWeight());
                m_invertTable->setSortMethod(byWeight);
            }

        }
        else
        {
            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }
            if (m_sortMethod == byID)
            {
                std::sort(m_tripleVec.begin(), m_tripleVec.end());
                m_invertTable->setSortMethod(byID);
            }
            else if (m_sortMethod == byWeight)
            {
                std::sort(m_tripleVec.begin(), m_tripleVec.end(), CmpSTNodeWeight());
                m_invertTable->setSortMethod(byWeight);
            }
            else //no order
            {
                std::sort(m_tripleVec.begin(), m_tripleVec.end(), CmpSTNodeNoOrder());
                m_invertTable->setSortMethod(noOrder);
            }

            if (m_dir.empty())
                m_invertTable->create(m_tripleVec, m_indexfile.c_str(), m_invertfile.c_str());
            else
                m_invertTable->create(m_tripleVec, m_dir.c_str());

            m_tripleVec.clear();

            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }
        }

        return m_invertTable->invertSize();
    }

    ///��Ҫ�����Ѿ��ź��������£����ٴ���, ���������m_inifile�����ź�����ļ�sorted!
    __int64 fastCreate()
    {
        Pval(m_bAllMem);
        if (!m_bAllMem) //������ȫ�����ڴ棬ͨ��������
        {
            if (m_tripleVec.size() > 0)
            {
                fwrite(&m_tripleVec[0], sizeof (_ST_PidKidInfo), m_tripleVec.size(), m_fp);
                m_tripleVec.clear();
            }
            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }
            //���ź�����ļ��д�������
            m_invertTable->create(m_inifile.c_str(), m_indexfile.c_str(), m_invertfile.c_str());
        }
        else
        {
            if (m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
            }
            //���ڴ洴��
            if (m_dir.empty())
                m_invertTable->create(m_tripleVec, m_indexfile.c_str(), m_invertfile.c_str());
            else
                m_invertTable->create(m_tripleVec, m_dir.c_str());
            m_tripleVec.clear();
        }
        return m_invertTable->invertSize();
    }

private:
    _InvertTable* m_invertTable;
    std::string m_inifile;
    std::string m_sortedfile;
    std::string m_indexfile;
    std::string m_invertfile;
    std::string m_dir;

    int m_maxLen;
    SortMethod m_sortMethod;

    bool m_bAllMem; ///�Ƿ����ȫ�����ڴ�
    bool m_bPersitant; ///�Ƿ���Ҫ������������

    std::vector<_ST_PidKidInfo> m_tripleVec; ///��ݴ��cahe������ȫ������������ڴ˴�
    FILE* m_fp; ///ָ��inifile
    std::ofstream m_ofs;
};

} //----end of namespace invert_table

#endif  //----end of INVERT_TABLE_CREATOR_H_
