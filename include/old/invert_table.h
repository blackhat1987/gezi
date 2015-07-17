/** 
 *  ==============================================================================
 * 
 *          \file      invert_table.h
 *
 *        \author   chenghuige 
 *          
 *          \date     2010-01-31 13:53:58.446039
 *  
 *  \Description: ��GETPID�ļ򵥷�װ,֧�ּ򵥵ĵ��ű?��������ӳ��
 *
 *                         Important!!
 *                         !!!!!!��ǰ�ĵ���֧�ֶ�ȡ������˳���ŵ�������create�����ĵ����ǰ��ձ��˳������
 *                         !!!!!!Ҳ����˵���indexΪ3����û��post list �����ǵ�������Ҳ��ռλ�ģ�ֻ��post list Ϊ�գ�
 *
 *                         sort based, ��ѯʱ��ȥcache,û����ȥ���ļ�
 *                         createInvertTable Ҫ���ȸ��һ��δ�����
 *                         <phrase, ad>
 *                         .....
 *                         ������ļ�
 *                         ������phrase3 -> ad1 -> ad2 ....����ĵ��Žṹ
 *
 *                          ����Ѿ�������������GETPID��ʽ�洢�������ļ��͵����ļ�
 *                          ����������ļ����������ڴ��н���
 *                          ���벿�ֵ��ţ����ڴ�CACHE�У�������õ�buffer�㹻����ȫ�����룩
 *
 *                          ������ڵ���post list��Ԫ������Ӹ����Ϣ����Ҫ����ģ�塣
 *                          �û����ܻ���Ҫ�̳���дMakeC2PInvertTable,�Ѹı�������ݵļ��㷽ʽ��
 *
 *                          �������Կ���ֻ�ǵ�������ST_PidKidInfo��InvertNode���Ա仯����
 *                          IndexNodeд��������������Ӧ�ñ��������޹أ�����ͬ�ӿڣ�����
 *                          д�����鷳��Ĭ�ϱ仯��ST_PidKidInfo��InvertNodeֻ�����ӱ�����
 *                         ���ı����е���ơ�
 *
 *                           TODO ���ĸı�list sort
 *                           getPostList �� iter begin end ?
 *
 *
 *                           TODO WinnerTree_Linux�и�ֵ���������⣿
 *
 *                           ����TODO setֱ�ӽ������ţ������������û��������ݵ��������������ļ��������Ժ�����
 *
 *                            FIXME!!  �������õĻ����С�����ļ����ã�������ã�
 *
 *                             TODO bettern name InvertTable as InvertIndex ?
 *
 *             //ԭ������������������ <1,..>��ͷ�� 3Ԫ�飬��Ȼ����������1��ֻ���䵹��Ϊ��
            //TODO �ܹ��趨���ԣ���������
 *      //TODO FIXME ��ǰ�����������ܹ���ȫ�ŵ��ڴ�ģ�������أ�
 *        //TODO ����Ų�����ȫ��ŵ��ڴ棬��ȡ�ļ�������Ķ�ȡ��B����
 *        //TODO �����õĸ��·���
 *
 *       //TODO ԭ�������Ŵ��ݵ�����ָ�룬�����õ�ģ�庯��������������չ
 *
 *         //TODO���ļ�֮��ĸ����쳣�� the c++ language P325
 *
 *         ��ǰ�����Ƕ�WINDOWS��֧��
 *
 *        //FIXME ������������з����֧��long long
 *
 *        TODO ���ǵ��ű�Ŀ���!����
 *
 *
 *       10.07.06 ����ʱ�û�����ָ���Ƿ���Ҫһ��persistant��index,�������֤������������д�����
 *       ���棬�����������д���̵��������������Ҫд����ʹд�����������ҲclearDiskɾ�����еĶ�����
 *       ����һ��һľ��
 *
 *       ע���������ͳ���˵��ŵĴ�С�����ǵ������С�Ƚ�С��һ��Ҳ��4.6M 29.6W����,
 *       300W Ҳ��50M��
 *  ==============================================================================
 */

#ifndef INVERT_TABLE2_H_
#define INVERT_TABLE2_H_

#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>
#include <cmath>
//#include <glog/loging.h>

#include "WinnerTree_Linux.h"
#include "debug_help.h"

//���л�
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
//#include <boost/filesystem.hpp>
#include<boost/filesystem/operations.hpp>
#include<boost/filesystem/convenience.hpp>
#include <fstream>

using std::cout;
using std::endl;
using std::vector;

namespace invert_table {
namespace bf = boost::filesystem;

enum SortMethod {
    byID, ///post list ���� id ����
    byWeight, ///post list ���� weight����
    noOrder, ///post list �������
    unknownOrder ///��֪����ɶ˳���
};
///�ļ�����������ṹ,ע��������InvertNode��ʹ��

struct ST_PidKidInfo {
    int m_nPid;
    int m_nKid;
    int m_nWeight;

    ST_PidKidInfo()
    {
        m_nPid = 0;
    }

    ST_PidKidInfo(int pid, int kid, int weight = 0)
    : m_nPid(pid), m_nKid(kid), m_nWeight(weight)
    {
    }

    inline bool operator<(const ST_PidKidInfo & other) const
    {
        return ((m_nPid < other.m_nPid)
                || ((m_nPid == other.m_nPid) && (m_nKid < other.m_nKid))
                || ((m_nPid == other.m_nPid) && (m_nKid == other.m_nKid) && (m_nWeight < other.m_nWeight)));
    }

    inline void setData(int pid, int kid, int weight)
    {
        m_nPid = pid;
        m_nKid = kid;
        m_nWeight = weight;
    }
};

///�?�Žṹ

struct InvertNode {
    int m_nID; //��Ʒ/�˿�ID
    int m_nWeight;
    typedef int WeightType;
    typedef int Weight2Type;

    InvertNode()
    {

    }

    InvertNode(int id, int weight)
    : m_nID(id), m_nWeight(weight)
    {
    }

    ///Ĭ�ϰ���weight�Ӵ�С����

    inline bool operator<(const InvertNode & other) const
    {
        return m_nWeight > other.m_nWeight;
    }

    inline void copy(const ST_PidKidInfo & other)
    {
        m_nID = other.m_nKid;
        m_nWeight = other.m_nWeight;
    }

    friend class boost::serialization::access; //for ���л�
    ///-----------------���л�

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_nID;
        ar & m_nWeight;
    }
};

struct InverNodeCmp {

    inline bool operator()(const InvertNode& l, const InvertNode & r) const
    {
        return l.m_nID < r.m_nID;
    }
};
///Ϊ��֧�ֵ����еĴ洢��Ӧ <��棬�ؼ��> -> < bid, ctr>

struct ST_PidKidInfo2 {
    int m_nPid;
    int m_nKid;
    int m_nWeight;
    int m_nWeight2;

    ST_PidKidInfo2()
    {
        m_nPid = 0;
    }

    ST_PidKidInfo2(int pid, int kid, int weight = 0, int weight2 = 0)
    : m_nPid(pid), m_nKid(kid), m_nWeight(weight), m_nWeight2(weight2)
    {
    }

    inline bool operator ==(const ST_PidKidInfo2 & other) const
    {
        return (m_nPid == other.m_nPid) && (m_nKid == other.m_nKid);
    }

    inline bool operator<(const ST_PidKidInfo2 & other) const
    {
        return ((m_nPid < other.m_nPid)
                || ((m_nPid == other.m_nPid) && (m_nKid < other.m_nKid))
                || ((m_nPid == other.m_nPid) && (m_nKid == other.m_nKid) && (m_nWeight < other.m_nWeight)));
    }

    inline void setData(int pid, int kid, int weight, int weight2)
    {
        m_nPid = pid;
        m_nKid = kid;
        m_nWeight = weight;
        m_nWeight2 = weight2;
    }
};

///�?�Žṹ

struct InvertNode2 {
    int m_nID; //��Ʒ/�˿�ID
    int m_nWeight;
    int m_nWeight2;
    typedef int WeightType;
    typedef int Weight2Type;

    InvertNode2()
    {

    }

    InvertNode2(int id, int weight, int weight2)
    : m_nID(id), m_nWeight(weight), m_nWeight2(weight2)
    {
    }

    ///Ĭ�ϰ���weight�Ӵ�С

    inline bool operator<(const InvertNode2 & other) const
    {
        return m_nWeight * m_nWeight2 > other.m_nWeight * other.m_nWeight2;
    }

    inline void copy(const ST_PidKidInfo2 & other)
    {
        m_nID = other.m_nKid;
        m_nWeight = other.m_nWeight;
        m_nWeight2 = other.m_nWeight2;
    }

    friend class boost::serialization::access; //for ���л�
    ///-----------------���л�

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_nID;
        ar & m_nWeight;
        ar & m_nWeight2;
    }
};

struct ST_PidKidInfo3 {
    int m_nPid;
    int m_nKid;
    float m_nWeight;
    int m_nWeight2;

    ST_PidKidInfo3()
    {
        m_nPid = 0;
    }

    ST_PidKidInfo3(int pid, int kid, float weight = 0, int weight2 = 0)
    : m_nPid(pid), m_nKid(kid), m_nWeight(weight), m_nWeight2(weight2)
    {
    }

    inline bool operator ==(const ST_PidKidInfo3 & other) const
    {
        return (m_nPid == other.m_nPid) && (m_nKid == other.m_nKid);
    }

    inline bool operator<(const ST_PidKidInfo3 & other) const
    {
        return ((m_nPid < other.m_nPid)
                || ((m_nPid == other.m_nPid) && (m_nKid < other.m_nKid))
                || ((m_nPid == other.m_nPid) && (m_nKid == other.m_nKid) && (m_nWeight < other.m_nWeight)));
    }

    inline void setData(int pid, int kid, float weight, int weight2)
    {
        m_nPid = pid;
        m_nKid = kid;
        m_nWeight = weight;
        m_nWeight2 = weight2;
    }
};

struct InvertNode3 {
    int m_nID; //��Ʒ/�˿�ID
    float m_nWeight;
    int m_nWeight2;
    typedef float WeightType;
    typedef int Weight2Type;

    InvertNode3()
    {

    }

    InvertNode3(int id, float weight, int weight2)
    : m_nID(id), m_nWeight(weight), m_nWeight2(weight2)
    {
    }

    inline bool operator<(const InvertNode3 & other) const
    {
        return m_nWeight > other.m_nWeight;
    }

    inline void copy(const ST_PidKidInfo3 & other)
    {
        m_nID = other.m_nKid;
        m_nWeight = other.m_nWeight;
        m_nWeight2 = other.m_nWeight2;
    }

};


///�ڴ���ӳ��ID��������

struct IndexNode {
    __int64 m_nAddr;
    int m_nCount;
    int m_nTotalWeight;
    int m_nID; //Ϊ�����ֲ�Ҫ���Ŵ�0��ʼ˳���¼�ģ�����ֱ�Ӵ洢��Ʒid

    friend class boost::serialization::access; //for ���л�
    ///-----------------���л�

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_nAddr;
        ar & m_nCount;
        ar & m_nTotalWeight;
        ar & m_nID;
    }
};

///��������

struct IndexNode_Cache {
    int m_nID;
    int m_nAddr;
    int m_nCount;
    int m_nTotalWeight;

    IndexNode_Cache()
    : m_nID(-1), m_nAddr(-1), m_nCount(-1), m_nTotalWeight(-1)
    {
    }
    friend class boost::serialization::access; //for ���л�
    ///-----------------���л�

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_nID;
        ar & m_nAddr;
        ar & m_nCount;
        ar & m_nTotalWeight;
    }
};

struct InvertPidNode_Sim {
    int m_nID;
    int m_nSimi;
};

///��ȡ�����ļ�

template<class IndexType, class InvertType>
inline bool ReadInvert(FILE *fp, IndexType strIndexNode, vector<InvertType>& vecInvert, int nReadSize)
{
    __int64 nAddr = strIndexNode.m_nAddr;
    int nCount = strIndexNode.m_nCount;

    if (fseek(fp, nAddr, 0) == -1) return false;

    int nReadCnt;
    int nSize;
    if (nCount > nReadSize) nSize = nReadSize;
    else nSize = nCount;

    vecInvert.resize(nSize);
    nReadCnt = fread(&vecInvert[0], sizeof (InvertType), nSize, fp);
    if (nReadCnt == -1 || nReadCnt != nSize) return false;

    return true;
}

struct CmpInvertNodeWeight {

    template<typename _InvertNode>
            bool operator() (const _InvertNode& i, const _InvertNode & j)
    {
        return (i.m_nWeight > j.m_nWeight);
    }
};

struct CmpInvertNodePid {

    template<typename _InvertNode>
            bool operator() (const _InvertNode& i, const _InvertNode & j)
    {
        return (i.m_nID < j.m_nID);
    }
};

struct CmpSTNodeID {

    template<typename _STNode>
            bool operator() (const _STNode& i, const _STNode & j)
    {
        return ((i.m_nPid < j.m_nPid)
                || ((i.m_nPid == j.m_nPid) && (i.m_nKid < j.m_nKid)));
    }
};
///weight �Ӵ�С

struct CmpSTNodeWeight {

    template<typename _STNode>
            bool operator() (const _STNode& i, const _STNode & j)
    {
        return ((i.m_nPid < j.m_nPid)
                || ((i.m_nPid == j.m_nPid) && (i.m_nWeight > j.m_nWeight))
                || ((i.m_nPid == j.m_nPid) && (i.m_nWeight == j.m_nWeight) && (i.m_nKid < j.m_nKid)));
    }
};

struct CmpSTNodeNoOrder {

    template<typename _STNode>
            bool operator() (const _STNode& i, const _STNode & j)
    {
        return (i.m_nPid < j.m_nPid);
    }
};

/**
 * ���ű�
 */
template <typename _InvertNode = InvertNode, typename _ST_PidKidInfo = ST_PidKidInfo>
        class InvertTable {
public:
    friend class boost::serialization::access; //for ���л�
    typedef _InvertNode InvertNodeType;
    typedef _ST_PidKidInfo SortNodeType;
public:

    InvertTable()
    : fp_Invert_C2P(NULL), m_nFirstColumnCount(0), m_bAllInMem(false),
    m_sortMethod(unknownOrder), m_bPersitant(true), m_invertSize(0),
    m_infileName(""), m_sortedfileName(""), m_indexfileName(""), m_invertfileName("")
    {
    }

    explicit InvertTable(int entry_num)
    : fp_Invert_C2P(NULL), m_nFirstColumnCount(entry_num), m_bAllInMem(false),
    m_sortMethod(unknownOrder), m_bPersitant(true), m_invertSize(0),
    m_infileName(""), m_sortedfileName(""), m_indexfileName(""), m_invertfileName("")
    {
    }

    ~InvertTable()
    {
        clearAll();
    }

    void setNonPersitant()
    {
        m_bPersitant = false;
    }

    bool isPersistant()
    {
        return m_bPersitant;
    }

    void clearCache()
    {
        if (fp_Invert_C2P) {
            fclose(fp_Invert_C2P);
            fp_Invert_C2P = NULL;
        }
        cls_vecIndex_C2P.clear();
        cls_vecIndex_C2P_Cache.clear();
        cls_vecInvert_C2P_Cache.clear();
        m_nFirstColumnCount = 0;
    }

    void clear()
    {
        clearCache();

        //ɾ����Ҫ���ļ�
        if (!m_infileName.empty()) {
            //LOG(INFO) << "delete " << m_infileName << endl;
            bf::remove(bf::path(m_infileName));
        }
        if (!m_sortedfileName.empty()) {
            //LOG(INFO) << "delte " << m_sortedfileName << endl;
            bf::remove(bf::path(m_sortedfileName));
        }
    }

    void clearAll()
    {
        clear();
        if (!isPersistant())
            clearDisk();
    }

    void clearDisk()
    {
        //LOG(INFO) << "clear disk" << endl;
        if (m_dir.empty()) {
            //LOG(INFO) << "delte " << m_indexfileName << " " << m_invertfileName << endl;
            bf::remove(bf::path(m_indexfileName));
            bf::remove(bf::path(m_invertfileName));
        } else {
            //LOG(INFO) << "Remove idr " << m_dir << endl;
            bf::remove_all(bf::path(m_dir));
        }
    }

    /**�趨���ű�����Ҫ���ļ�����������ģ����������ļ���͵����ļ���*/
    void setFile(const char* index_file, const char* invert_file)
    {
        m_indexfileName = index_file;
        m_invertfileName = invert_file;
    }

    void setEntryNum(int entry_num)
    {
        m_nFirstColumnCount = entry_num;
    }

    /**
     * ��������ļ���Ϊ���룬�������ű?Node��ʾ�ļ�����Ԫ��������
     *<phrase,ad> ����<phrase, phrase , weight>
     *����GETPID������WinnerTree_Linux.h�е�Ҫ����Ҫ�ṩ������Cmp��Node��δ�ṩ
     * ͬʱ�ṩindexfile,invertfile,sorted_file������
     */

    template<class CMP_NODE>
    void create(const char *infile_name, const char * sortedfile_name,
    const char *indexfile_name, const char* invertfile_name,
    CMP_NODE cmp_node,
    int nFreeMemSize = SortCacheSize)
    {
        clear();
        m_infileName = infile_name;
        m_indexfileName = indexfile_name;
        m_invertfileName = invertfile_name;

        if (K_MergeFile<_ST_PidKidInfo, CMP_NODE > (infile_name, sortedfile_name,
                cmp_node, nFreeMemSize) == -1) {
            //LOG(FATAL) << "Sorting file " << infile_name << " FATAL" << endl;
        }
        m_sortedfileName = sortedfile_name;

        createInvertTable();
    }

    /**
     *
     * @param dir    �������·�������ִ���Ĭ������ļ�������
     * @param cmp_node
     * @param nFreeMemSize
     * @return
     */
    template<class CMP_NODE>
    void create(const char *dir, CMP_NODE cmp_node, int nFreeMemSize = SortCacheSize)
    {
        clear();
        m_dir = dir;
        m_infileName = m_dir + "/ini.idx";
        m_indexfileName = m_dir + "/index.idx";
        m_invertfileName = m_dir + "/invert.idx";
        m_sortedfileName = m_dir + "/sorted.idx";

        if (K_MergeFile<_ST_PidKidInfo, CMP_NODE > (m_infileName.c_str(), m_sortedfileName.c_str(),
                cmp_node, nFreeMemSize) == -1) {
            //LOG(FATAL) << "Sorting file " << m_infileName << " FATAL" << endl;
        }

        createInvertTable();
    }
    ///���溯���Ĭ�����򷽷�

    void create(const char *infile_name, const char * sortedfile_name,
            const char *indexfile_name, const char* invertfile_name,
            int nFreeMemSize = SortCacheSize)
    {
        clear();
        m_infileName = infile_name;
        m_indexfileName = indexfile_name;
        m_invertfileName = invertfile_name;

        if (K_MergeFile<_ST_PidKidInfo > (infile_name, sortedfile_name,
                CmpSTNodeID(), nFreeMemSize) == -1) {
            //LOG(FATAL) << "Sorting file " << infile_name << " FATAL" << endl;
        }
        m_sortedfileName = sortedfile_name;

        createInvertTable();
    }

    void create(const char *dir, int nFreeMemSize = SortCacheSize)
    {
        clear();
        m_dir = dir;
        m_infileName = m_dir + "/ini.idx";
        m_indexfileName = m_dir + "/index.idx";
        m_invertfileName = m_dir + "/invert.idx";
        m_sortedfileName = m_dir + "/sorted.idx";
        if (K_MergeFile<_ST_PidKidInfo > (m_infileName.c_str(), m_sortedfileName.c_str(),
                CmpSTNodeID(), nFreeMemSize) == -1) {
            //LOG(FATAL) << "Sorting file " << m_infileName << " FATAL" << endl;
        }

        createInvertTable();
    }

    ///���Ѿ��ź�����ļ��н�����������

    void create(const char * sortedfile_name, const char *indexfile_name, const char* invertfile_name)
    {
        clear();
        m_indexfileName = indexfile_name;
        m_invertfileName = invertfile_name;
        m_sortedfileName = sortedfile_name;

        //do real work here
        createInvertTable();
    }
    ///������Ϊ�˱��� void create(const char *dir, int nFreeMemSize = SortCacheSize) �ظ�

    void create2(const char* dir)
    {
        clear();
        m_dir = dir;
        m_indexfileName = m_dir + "/index.idx";
        m_invertfileName = m_dir + "/invert.idx";
        m_sortedfileName = m_dir + "/sorted.idx";

        createInvertTable();
    }

    ///�����ڴ�ĵ���������

    void create(std::vector<_ST_PidKidInfo>& vec, const char *indexfile_name, const char* invertfile_name)
    {
        setFile(indexfile_name, invertfile_name);
        createInvertTable(vec);
    }

    void create(std::vector<_ST_PidKidInfo>& vec, const char *dir)
    {
        m_dir = dir;
        string indexfile_name = m_dir + "/index.idx";
        string invertfile_name = m_dir + "/invert.idx";
        setFile(indexfile_name.c_str(), invertfile_name.c_str());
        createInvertTable(vec);
    }

    /*
     * FIXME TEMPLY rmove const
     */
    template<typename Vector>
    void create_bigVec(Vector& vec, const char *dir)
    {
        m_dir = dir;
        string indexfile_name = m_dir + "/index.idx";
        string invertfile_name = m_dir + "/invert.idx";
        setFile(indexfile_name.c_str(), invertfile_name.c_str());
        createInvertTable_bigVec(vec);
    }

    /**
     * ����Žṹ�Ѿ������ô洢���ļ������ȡ����͵����ļ�
     * �������ű�
     */
    int load(const char *indexfile_name, const char *invertfile_name, const char *sortedfile_name = "")
    {
        return load<IndexNode_Cache > (indexfile_name, invertfile_name, sortedfile_name);
    }

    int load(const string& dir)
    {
        return load<IndexNode_Cache > (dir);
    }

    template <typename IndexType>
    int load(const string& dir)
    {
        m_dir = dir;
        string indexfile_name = m_dir + "/index.idx";
        string invertfile_name = m_dir + "/invert.idx";
        return load<IndexType > (indexfile_name.c_str(), invertfile_name.c_str());
    }

    template <typename IndexType>
    int load(const char *indexfile_name, const char *invertfile_name, const char *sortedfile_name = "")
    {
        clear();
        m_indexfileName = indexfile_name;
        //LOG_IF(FATAL, !bf::exists(bf::path(m_indexfileName))) << "not exist index file " << m_indexfileName << endl;
        m_invertfileName = invertfile_name;
        //LOG_IF(FATAL, !bf::exists(bf::path(m_invertfileName))) << "not exist index file " << m_invertfileName << endl;
        if (sortedfile_name != "")
            m_sortedfileName = sortedfile_name;

        //�򿪵����ļ�
        if ((fp_Invert_C2P = fopen(m_invertfileName.c_str(), "rb")) == NULL) {
            return false;
        }

        loadC2PinvertTable<IndexType > ();

        //�ڴ��л���cache
        makeC2PInvertCache();
        return 0;
    }

    template <typename IndexType>
    int load_noSequence(const char *indexfile_name, const char *invertfile_name, const char *sortedfile_name = "")
    {
        clear();
        m_indexfileName = indexfile_name;
        m_invertfileName = invertfile_name;
        if (sortedfile_name != "")
            m_sortedfileName = sortedfile_name;

        //�򿪵����ļ�
        if ((fp_Invert_C2P = fopen(m_invertfileName.c_str(), "rb")) == NULL) {
            cout << "open " << m_invertfileName << " failed" << endl;
            return false;
        }

        loadC2PinvertTable_noSequence<IndexType > ();

        //�ڴ��л���cache
        makeC2PInvertCache();
        return 0;
    }

    ///������ṹд���ļ���ע��д�Ľṹ��IndexNode_Cache,����IndexNode

    void writeIndex()
    {
        FILE* fpIndex = fopen(m_indexfileName.c_str(), "wb");
        //д���������ļ� FIXME is this OK for big file?
        fwrite(&cls_vecIndex_C2P_Cache[0], sizeof (IndexNode_Cache), cls_vecIndex_C2P.size(), fpIndex);
        fclose(fpIndex);
        fpIndex = NULL;
    }

    ///���������ٽ�������

    template<class CMP_NODE>
    void reCreate(CMP_NODE cmp_node = CmpInvertNodePid(),
    int nFreeMemSize = SortCacheSize)
    {
        clear();
        std::string tempfileName("temp.idx");
        if (K_MergeFile<_ST_PidKidInfo, CMP_NODE > (m_sortedfileName.c_str(), tempfileName.c_str(),
                cmp_node, SortCacheSize) == -1) {
            //LOG(FATAL) << "Sorting file FATAL" << endl;
        }


        bf::rename(bf::path(tempfileName), bf::path(m_sortedfileName));

        createInvertTable();
    }

    ///���ű�(���ú�)�ж��ٸ���ڣ������ٸ�post list

    int entryNum()
    {
        return cls_vecIndex_C2P.size();
    }

    /**
     * ��ȡĳ�������Ӧ�ĵ��ŵ�begin()
     * ע��Ĭ�����е�������int��ŵģ�ͨ��ӳ��,��0��elem_num -1)
     * �ⲿ��Ҫ�ṩһ����vector,��Ϊ�п��ܵ���list�����ڴ�cache�У���ʱ����Ҫ�������vector��
     * �����ⲿ��Ҫ��ʼ������ʼλ�ú�Ҫ���ĵ���listԪ����Ŀ,�����cache ��start == &(vec[0])
     *
     * usage:
     *  std::vector<_InvertNode> temp_vec;
     *  _InvertNode* post_start = NULL;
     *   int post_num = 0;
     *
     *  getPostList (index, temp_vec, post_start,  post_num);
     *
     *  for ( int i = 0; i < num; i++)
     * {
     *      cout << *(post_start++).m_nId << endl;
     * }
     */
    inline bool getPostList(int index, std::vector<_InvertNode>& temp_vec, _InvertNode*& post_start, int& post_num)
    {
        temp_vec.clear();
        //�������������Ч��
        if (index < 0 || index >= cls_vecIndex_C2P.size()) {
            post_num = 0;
            post_start = NULL;
            return false;
        }

        int nAddr_C2P;
        bool bRt;
        //���һ������Ƿ��иù˿͵Ĺ����б�
        if (cls_vecIndex_C2P_Cache[index].m_nAddr != -1) {
            //cout << "reading from cache" << endl;
            //������Ϣ
            post_num = cls_vecIndex_C2P_Cache[index].m_nCount;
            nAddr_C2P = cls_vecIndex_C2P_Cache[index].m_nAddr;
            post_start = &(cls_vecInvert_C2P_Cache[nAddr_C2P]);
        } else//�Ӵ����ж�ȡ�ù˿͵Ĺ����б�
        {
            temp_vec.clear();
            //            cout << "reading from file" << endl;
            //������Ϣ
            post_num = cls_vecIndex_C2P[index].m_nCount;

            //file read
            bRt = ReadInvert(fp_Invert_C2P, cls_vecIndex_C2P[index], temp_vec, post_num);
            if (!bRt) return false;

            post_start = &(temp_vec[0]);
        }
        return true;
    }

    ///��ʹ������Ϣ���ڴ���Ҳ���Ƶ�result vec

    bool getPostList(int index, std::vector<_InvertNode>& result_vec)
    {
        //Pval(index);
        //�������������Ч
        if (index < 0 || index >= cls_vecIndex_C2P.size())
            return false;

        int post_num, nAddr_C2P;
        bool bRt;
        //Pval(cls_vecIndex_C2P_Cache.size());
        //���һ������Ƿ��иù˿͵Ĺ�����
        if (cls_vecIndex_C2P_Cache[index].m_nAddr != -1) {
            //cout << "reading from cache" << endl;
            //������Ϣ
            post_num = cls_vecIndex_C2P_Cache[index].m_nCount;
            nAddr_C2P = cls_vecIndex_C2P_Cache[index].m_nAddr;

            for (int i = nAddr_C2P; i < nAddr_C2P + post_num; i++) {
                result_vec.push_back(cls_vecInvert_C2P_Cache[i]);
            }
        } else//�Ӵ����ж�ȡ�ù˿͵Ĺ����б�
        {
            //            cout << "reading from file" << endl;
            //������Ϣ
            post_num = cls_vecIndex_C2P[index].m_nCount;
            //file read
            bRt = ReadInvert(fp_Invert_C2P, cls_vecIndex_C2P[index], result_vec, post_num);
            if (!bRt) return false;
        }
        return true;
    }

    inline int getIndexID(int index)
    {
        return cls_vecIndex_C2P[index].m_nID;
    }

    inline int getPostLength(int index)
    {
        //�������������Ч��
        if (index < 0 || index >= m_nFirstColumnCount)
            return 0;

        if (cls_vecIndex_C2P_Cache[index].m_nAddr != -1)
            return cls_vecIndex_C2P_Cache[index].m_nCount;
        else
            return cls_vecIndex_C2P[index].m_nCount;
    }

    ///return |weight|

    inline int getTotalWeight(int index)
    {
        //�������������Ч��
        if (index < 0 || index >= m_nFirstColumnCount)
            return -1;

        if (cls_vecIndex_C2P_Cache[index].m_nAddr != -1)
            return cls_vecIndex_C2P_Cache[index].m_nTotalWeight;
        else
            return cls_vecIndex_C2P[index].m_nTotalWeight;
    }

    std::string getInvertFileName()
    {
        return m_invertfileName;
    }

    /**
     * ���Ӧ�����ڲ����õ�,ֻ�ṩ������sim_calc.h�ã���Ҫ�����������
     * �����¸�addIndex ��Ҫ�����д�뵹���ļ���ַ��addIndex ���漰����make cache.
     *
     * ������ sim_calc.h�У��������ƴʵ���������������ĵ�ÿ���ʵ����ƴʴ���һ�������е�
     * 1. invert_table.setFile(indexfile, invertfile)   //ȷ����������͵����ļ�������
     * 2. File* fp_invert = fopen(invert_table.getInvertFileName(), "wb"))
     *     from = 0;
     * 3  foreach phrase_id
     *           get similar phrase to post_vec
     *           from = invert_table.addIndex(post_vec, phrase_id, from, fp_invert, max_num)  //from�����λ�ã������ļ��е�
     *     fclose(fp_invert)
     * 4. invert_table.writeIndex()  //д�����ļ��������ļ��Ѿ���add_index�����д����
     */
    __int64 addIndex(const std::vector<InvertNode>& post_vec, int index, __int64 from, FILE* fp_invert, size_t max_num = 50)
    {
        IndexNode strIndexNode_C2P; //�ڴ��е�MapID����ڵ�
        IndexNode_Cache strIndexNode_Cache; //��������ڵ�
        _InvertNode str_InvertNode_C2P; //�����¼�ڵ�

        int post_size = std::min(post_vec.size(), max_num);
        int nTotalWeight = 0;

        for (size_t i = 0; i < post_size; i++) {
            nTotalWeight += post_vec[i].m_nWeight * post_vec[i].m_nWeight;
        }
        nTotalWeight = (int) (sqrt(nTotalWeight) * 1000);

        strIndexNode_C2P.m_nAddr = from * sizeof (_InvertNode); //ADDR
        strIndexNode_C2P.m_nCount = post_size; //�������Ʒ����
        strIndexNode_C2P.m_nTotalWeight = nTotalWeight;

        cls_vecIndex_C2P.push_back(strIndexNode_C2P);

        //cache
        strIndexNode_Cache.m_nID = index;
        strIndexNode_Cache.m_nAddr = -1;
        strIndexNode_Cache.m_nCount = strIndexNode_C2P.m_nCount;
        strIndexNode_Cache.m_nTotalWeight = strIndexNode_C2P.m_nTotalWeight;

        cls_vecIndex_C2P_Cache.push_back(strIndexNode_Cache);

        //д�����ļ�
        if (post_size > 0)
            fwrite(&post_vec[0], sizeof (_InvertNode), strIndexNode_C2P.m_nCount, fp_invert);

        from += strIndexNode_C2P.m_nCount;
        return from;
    }

    //    //private:
    //public:
    ///��������,gcc4.1.4����֧��Ĭ�Ϻ���ģ��������֧��template <typename IndexType = IndexNode_Cache>)
    ///����ģ��Ϊ����Ӧ��ĳ���д�õ�������ܲ���˳����߸���ͬ
    ///���Ƕ���m_nID��m_nCount
    ///load֮ǰ��ȷ������ṹ�����ڻ��߱����

    template <typename IndexType>
    bool loadC2PinvertTable()
    {
        //boost::timer timer;
        FILE* fpIndex = fopen(m_indexfileName.c_str(), "rb");

        if (!fpIndex)
            throw new int(3);

        ///TODO make easy if we use the same IndexType write than read?
        //fread(&cls_vecIndex_C2P_Cache[0], sizeof (IndexNode_Cache), cls_vecIndex_C2P.size(), fpIndex);
        cls_vecIndex_C2P.reserve(m_nFirstColumnCount); //ΪC2P��������ڴ�
        cls_vecIndex_C2P_Cache.reserve(m_nFirstColumnCount);
        //Bug ����һ��400 * indexType�Ķ�̬�ڴ棬��ʱ��������ʱû�¡�������
        //A bug why loading c2c index file than new using 4s while loading p2p bigger file than new using 0.2s? FIXME
        //IndexType *tempinfo = new IndexType[cache_size];
        //FIXME mdify load no sequence
        int cache_size = 4 * 1024; //IndexType���16��24B
        IndexType tempinfo[cache_size]; //FIXME temply
        //cout << "new mem using " << timer.elapsed() << " " << cache_size << endl;
        //ʵ����40M����ֱ�Ӷ�ջ����ˣ�ֻ�ܶ�̬���٣�һ�δ��ļ�����������������ı��������
        //vector��ܶ�
        //IndexType tempinfo[cache_size];  //notice for speed may be wrong for big! FIXME
        //std::vector<IndexType> tempinfo;
        //tempinfo.resize(cache_size);
        IndexNode strIndexNode_C2P; //�ڴ��е�MapID����ڵ�
        IndexNode_Cache strIndexNode_Cache; //��������ڵ�

        int num;
        int from = 0;
        int nPid = 0;

        while (!feof(fpIndex)) {
            //num = fread(&tempinfo[0], sizeof (IndexType), cache_size, fpIndex);
            num = fread(tempinfo, sizeof (IndexType), cache_size, fpIndex);

            for (int i = 0; i < num; i++) {
                //������,���Ϊ��
                if (nPid != tempinfo[i].m_nID) {
                    //cout << "This really happens?  no postlist for " << nPid << endl;
                    for (int j = 0; j < tempinfo[i].m_nID - nPid; j++) {
                        strIndexNode_C2P.m_nAddr = from * sizeof (_InvertNode);
                        strIndexNode_C2P.m_nCount = 0;
                        strIndexNode_C2P.m_nTotalWeight = 0;
                        cls_vecIndex_C2P.push_back(strIndexNode_C2P);

                        strIndexNode_Cache.m_nID = nPid + j;
                        strIndexNode_Cache.m_nAddr = -1;
                        strIndexNode_Cache.m_nCount = strIndexNode_C2P.m_nCount;
                        strIndexNode_Cache.m_nTotalWeight = strIndexNode_C2P.m_nTotalWeight;
                        cls_vecIndex_C2P_Cache.push_back(strIndexNode_Cache);
                    }

                }
                nPid = tempinfo[i].m_nID;

                strIndexNode_C2P.m_nAddr = from * sizeof (_InvertNode);
                strIndexNode_C2P.m_nCount = tempinfo[i].m_nCount;
                strIndexNode_C2P.m_nTotalWeight = tempinfo[i].m_nTotalWeight;
                cls_vecIndex_C2P.push_back(strIndexNode_C2P);
                from += strIndexNode_C2P.m_nCount; //from advance

                //cache
                strIndexNode_Cache.m_nID = nPid;
                strIndexNode_Cache.m_nAddr = -1;
                strIndexNode_Cache.m_nCount = strIndexNode_C2P.m_nCount;
                strIndexNode_Cache.m_nTotalWeight = strIndexNode_C2P.m_nTotalWeight;
                cls_vecIndex_C2P_Cache.push_back(strIndexNode_Cache);

                nPid++; //nPid advance
            }
            if (num < cache_size)
                break;

            //do not need this?
            //memset(tempinfo, 0, (sizeof (IndexType)) * cache_size); //����
        }

        m_nFirstColumnCount = cls_vecIndex_C2P.size();

        fclose(fpIndex);
        fpIndex = NULL;

        //delete [] tempinfo; //FIXME
        return true;
    }
    ///��Ҫ�����index��0��ʼ˳����

    template <typename IndexType>
    bool loadC2PinvertTable_noSequence()
    {
        FILE* fpIndex = fopen(m_indexfileName.c_str(), "rb");
        if (!fpIndex) {
            cout << "Open " << m_indexfileName << " failed" << endl;
            throw new int(3);
        }

        ///TODO make easy if we use the same IndexType write than read?
        //fread(&cls_vecIndex_C2P_Cache[0], sizeof (IndexNode_Cache), cls_vecIndex_C2P.size(), fpIndex);

        cls_vecIndex_C2P.reserve(m_nFirstColumnCount); //ΪC2P��������ڴ�
        cls_vecIndex_C2P_Cache.reserve(m_nFirstColumnCount);

        const int cache_size = 4 * 1024;
        IndexType tempinfo[cache_size];
        // IndexType *tempinfo = new IndexType[cache_size];
        IndexNode strIndexNode_C2P; //�ڴ��е�MapID����ڵ�
        IndexNode_Cache strIndexNode_Cache; //��������ڵ�

        int num;
        int from = 0;
        int nPid = 0;

        while (!feof(fpIndex)) {
            num = fread(tempinfo, sizeof (IndexType), cache_size, fpIndex);
            for (int i = 0; i < num; i++) {

                //nPid = tempinfo[i].m_nID;
                strIndexNode_C2P.m_nID = tempinfo[i].m_nID;
                strIndexNode_C2P.m_nAddr = from * sizeof (_InvertNode);
                strIndexNode_C2P.m_nCount = tempinfo[i].m_nCount;
                strIndexNode_C2P.m_nTotalWeight = tempinfo[i].m_nTotalWeight;
                cls_vecIndex_C2P.push_back(strIndexNode_C2P);
                from += strIndexNode_C2P.m_nCount; //from advance

                //cache
                strIndexNode_Cache.m_nID = nPid;
                strIndexNode_Cache.m_nAddr = -1;
                strIndexNode_Cache.m_nCount = strIndexNode_C2P.m_nCount;
                strIndexNode_Cache.m_nTotalWeight = strIndexNode_C2P.m_nTotalWeight;
                cls_vecIndex_C2P_Cache.push_back(strIndexNode_Cache);

                nPid++; //nPid advance
            }

            if (num < cache_size)
                break;

            memset(tempinfo, 0, (sizeof (IndexType)) * cache_size); //����
        }

        m_nFirstColumnCount = cls_vecIndex_C2P.size();

        //delete [] tempinfo;
        fclose(fpIndex);
        fpIndex = NULL;
        return true;
    }

    /**
     * �������������д���ļ�
     *
     */
    bool makeC2PInvertTable()
    {
        cout << "��ɵ�һ��->�ڶ��е��ű������" << endl;
        FILE *fpCP, *fpInvert;
        if ((fpCP = fopen(m_sortedfileName.c_str(), "rb")) == NULL) {
            cout << "open " << m_sortedfileName << " FATAL!" << endl;
            throw new int(3);
            return false;
        }

        if ((fpInvert = fopen(m_invertfileName.c_str(), "wb")) == NULL) {
            cout << "create " << m_invertfileName << " FATAL!" << endl;
            throw new int(3);
            return false;
        }

        const int cache_size = 4 * 1024; //4k *  cache
        _ST_PidKidInfo tempinfo[cache_size];
        cls_vecIndex_C2P.reserve(m_nFirstColumnCount);
        cls_vecIndex_C2P_Cache.reserve(m_nFirstColumnCount);

        IndexNode strIndexNode_C2P;
        IndexNode_Cache strIndexNode_Cache;
        vector<_InvertNode> vecTmpCPList;
        vecTmpCPList.reserve(1024);
        _InvertNode str_InvertNode_C2P;

        int nCustID_old = 0;
        __int64 nTotalWeight = 0;
        int a;
        __int64 from = 0;

        while (!feof(fpCP)) {
            a = fread(&tempinfo[0], sizeof ( _ST_PidKidInfo), cache_size, fpCP);

            int i = 0;
            while (i < a) {
                while (nCustID_old < tempinfo[i].m_nPid) {
                    //��������
                    strIndexNode_C2P.m_nAddr = from * sizeof (_InvertNode);
                    //strIndexNode_C2P.m_nCount = vecTmpCPList.size();
                    strIndexNode_C2P.m_nCount = 0;
                    strIndexNode_C2P.m_nTotalWeight = nTotalWeight;
                    cls_vecIndex_C2P.push_back(strIndexNode_C2P);

                    //cache
                    strIndexNode_Cache.m_nID = nCustID_old;
                    strIndexNode_Cache.m_nAddr = -1;
                    strIndexNode_Cache.m_nCount = strIndexNode_C2P.m_nCount;
                    strIndexNode_Cache.m_nTotalWeight = nTotalWeight;
                    cls_vecIndex_C2P_Cache.push_back(strIndexNode_Cache);

                    nCustID_old++;
                }

                //---------------------------------------------nCustID_old == tempinfo[i].m_nPid
                //��Ӹù˿͵Ĺ����б�
                while (nCustID_old == tempinfo[i].m_nPid && i < a) {
                    str_InvertNode_C2P.copy(tempinfo[i]);
                    nTotalWeight += tempinfo[i].m_nWeight * tempinfo[i].m_nWeight;
                    vecTmpCPList.push_back(str_InvertNode_C2P);
                    i++;
                }
                if (i == a)
                    break;

                if (vecTmpCPList.size() > 0) {
                    strIndexNode_C2P.m_nAddr = from * sizeof (_InvertNode);
                    strIndexNode_C2P.m_nCount = vecTmpCPList.size();
                    strIndexNode_C2P.m_nTotalWeight = (int) (sqrt((float) nTotalWeight) * 1000);

                    cls_vecIndex_C2P.push_back(strIndexNode_C2P);

                    //cache
                    strIndexNode_Cache.m_nID = nCustID_old;
                    strIndexNode_Cache.m_nAddr = -1;
                    strIndexNode_Cache.m_nCount = strIndexNode_C2P.m_nCount;
                    strIndexNode_Cache.m_nTotalWeight = strIndexNode_C2P.m_nTotalWeight;
                    cls_vecIndex_C2P_Cache.push_back(strIndexNode_Cache);

                    //д�����ļ�
                    fwrite(&vecTmpCPList[0], sizeof (_InvertNode), strIndexNode_C2P.m_nCount, fpInvert);
                    vecTmpCPList.clear();
                    nTotalWeight = 0;
                    nCustID_old++;
                    from += strIndexNode_C2P.m_nCount;
                }
            }

            if (a < cache_size) break;
        }

        if (vecTmpCPList.size() > 0) {
            strIndexNode_C2P.m_nAddr = from * sizeof (_InvertNode);
            strIndexNode_C2P.m_nCount = vecTmpCPList.size();
            strIndexNode_C2P.m_nTotalWeight = (int) (sqrt((float) nTotalWeight) * 1000);

            cls_vecIndex_C2P.push_back(strIndexNode_C2P);

            //cache
            strIndexNode_Cache.m_nID = nCustID_old;
            strIndexNode_Cache.m_nAddr = -1;
            strIndexNode_Cache.m_nCount = strIndexNode_C2P.m_nCount;
            strIndexNode_Cache.m_nTotalWeight = strIndexNode_C2P.m_nTotalWeight;
            cls_vecIndex_C2P_Cache.push_back(strIndexNode_Cache);

            //д�����ļ�
            fwrite(&vecTmpCPList[0], sizeof (_InvertNode), strIndexNode_C2P.m_nCount, fpInvert);
            vecTmpCPList.clear();
            nTotalWeight = 0;
            nCustID_old++;
            from += strIndexNode_C2P.m_nCount;
        }

        m_nFirstColumnCount = cls_vecIndex_C2P.size();

        fclose(fpCP);
        fpCP = NULL;
        fclose(fpInvert);
        fpInvert = NULL;
        return true;
    }

    /**
     * ����������ͬ�ϣ������Ǵ��ڴ��е�һ��vector�ж�ȡ��ݣ����Ǵ�sorted file�ж�ȡ
     * ע�����vectorҪ���ǰ���<index_id, invert_id, weight> �ź����
     * TODO ������Ĵ����ظ�~
     * ע��ֻ���������������!isPersitant���ǲŲ�д�ļ� 10/07/06 add ֧��ֱ����ȫ�ڴ治д�ļ�
     */
    void makeC2PInvertTable(const std::vector<_ST_PidKidInfo>& tempinfo)
    {
        //LOG(INFO) << "��ɵ�һ��->�ڶ��е��ű������,��ȫ���ڴ��ж�ȡ��Ϣ" << endl;
        FILE *fpInvert;

        fpInvert = fopen(m_invertfileName.c_str(), "wb");
        //LOG_IF(FATAL, !fpInvert) << "create " << m_invertfileName << " FATAL!" << endl;

        cls_vecIndex_C2P.reserve(m_nFirstColumnCount);
        cls_vecIndex_C2P_Cache.reserve(m_nFirstColumnCount);

        IndexNode strIndexNode_C2P;
        IndexNode_Cache strIndexNode_Cache;
        vector<_InvertNode> vecTmpCPList;
        vector<_InvertNode> vecCPList;
        vecTmpCPList.reserve(1024);
        _InvertNode str_InvertNode_C2P;

        int nCustID_old = 0;
        __int64 nTotalWeight = 0;
        __int64 from = 0;

        size_t i = 0;
        size_t size = tempinfo.size();
        while (i < size) {
            while (nCustID_old < tempinfo[i].m_nPid) {
                //��������
                strIndexNode_C2P.m_nAddr = from * sizeof (_InvertNode);
                strIndexNode_C2P.m_nCount = 0;
                strIndexNode_C2P.m_nTotalWeight = nTotalWeight;
                cls_vecIndex_C2P.push_back(strIndexNode_C2P);

                //cache
                strIndexNode_Cache.m_nID = nCustID_old;
                strIndexNode_Cache.m_nAddr = -1;
                strIndexNode_Cache.m_nCount = strIndexNode_C2P.m_nCount;
                strIndexNode_Cache.m_nTotalWeight = nTotalWeight;
                cls_vecIndex_C2P_Cache.push_back(strIndexNode_Cache);

                nCustID_old++;
            }

            //---------------------------------------------nCustID_old == tempinfo[i].m_nPid
            //��Ӹù˿͵Ĺ����б�
            while (i < size && nCustID_old == tempinfo[i].m_nPid) //id < size must at first 10.05.19
            {
                str_InvertNode_C2P.copy(tempinfo[i]);
                nTotalWeight += tempinfo[i].m_nWeight * tempinfo[i].m_nWeight;
                vecTmpCPList.push_back(str_InvertNode_C2P);
                i++;
            }
            if (vecTmpCPList.size() > 0) {
                strIndexNode_C2P.m_nAddr = from * sizeof (_InvertNode);
                strIndexNode_C2P.m_nCount = vecTmpCPList.size();
                strIndexNode_C2P.m_nTotalWeight = (int) (sqrt((float) nTotalWeight) * 1000);

                cls_vecIndex_C2P.push_back(strIndexNode_C2P);

                //cache
                strIndexNode_Cache.m_nID = nCustID_old;
                strIndexNode_Cache.m_nAddr = -1;
                strIndexNode_Cache.m_nCount = strIndexNode_C2P.m_nCount;
                strIndexNode_Cache.m_nTotalWeight = strIndexNode_C2P.m_nTotalWeight;
                cls_vecIndex_C2P_Cache.push_back(strIndexNode_Cache);

                //д�����ļ�,��Ϊ�����Ѿ�֪���������ڴ��д洢������ֻ����Ҫ��¼��Ӳ�����ǲ�д
                if (isPersistant()) {
                    fwrite(&vecTmpCPList[0], sizeof (_InvertNode), strIndexNode_C2P.m_nCount, fpInvert);
                } else {
                    //�ڴ��б���
                    std::copy(vecTmpCPList.begin(), vecTmpCPList.end(), std::back_inserter(vecCPList));
                }
                vecTmpCPList.clear();
                nTotalWeight = 0;
                nCustID_old++;
                from += strIndexNode_C2P.m_nCount;
            }
        }
        //TODO remove it! Where creating we must tell how many entries are
        m_nFirstColumnCount = cls_vecIndex_C2P.size();
        //clear
        fclose(fpInvert);
        if (!isPersistant()) //�����Ҫ�־û�����ô�����Ѿ����ڴ������˵�����Ϣ
            cls_vecInvert_C2P_Cache.swap(vecCPList);
    }

    /**
     *  Ŀǰ��Ҫ��Ϊ��ʹ��BigVec help implement
     *
     * FIXME Using const Vector& tempinfo; Iter iter = tempinfo.begin(); will cause FATAL
     * 1262: FATAL: passing ��const BigVec<invert_table::ST_PidKidInfo, invert_table::CmpSTNodeWeight>��
     * as ��this�� argument of ��bigvec_iterator<BigVec<_Node, _Cmp>, _Node> BigVec<_Node, _Cmp>::begin()
     *  [with _Node = invert_table::ST_PidKidInfo, _Cmp = invert_table::CmpSTNodeWeight]�� discards qualifiers
     *
     * FIXME temply remove const!!
     */
    template<typename Vector>
    void makeC2PInvertTable_bigVec(Vector& tempinfo)
    {
        //LOG(INFO) << "��ɵ�һ��->�ڶ��е��ű������,��ȫ���ڴ��ж�ȡ��Ϣ" << endl;
        FILE *fpInvert;

        fpInvert = fopen(m_invertfileName.c_str(), "wb");
        //LOG_IF(FATAL, !fpInvert) << "create " << m_invertfileName << " FATAL!" << endl;

        typedef typename Vector::iterator Iter;

        cls_vecIndex_C2P.reserve(m_nFirstColumnCount);
        cls_vecIndex_C2P_Cache.reserve(m_nFirstColumnCount);

        IndexNode strIndexNode_C2P;
        IndexNode_Cache strIndexNode_Cache;
        vector<_InvertNode> vecTmpCPList;
        vector<_InvertNode> vecCPList;
        vecTmpCPList.reserve(1024);
        _InvertNode str_InvertNode_C2P;

        int nCustID_old = 0;
        __int64 nTotalWeight = 0;
        __int64 from = 0;

        Iter iter = tempinfo.begin();
        Iter iter_end = tempinfo.end();
        while (iter != iter_end) {
            while (nCustID_old < iter->m_nPid) {
                //��������
                strIndexNode_C2P.m_nAddr = from * sizeof (_InvertNode);
                strIndexNode_C2P.m_nCount = 0;
                strIndexNode_C2P.m_nTotalWeight = nTotalWeight;
                cls_vecIndex_C2P.push_back(strIndexNode_C2P);

                //cache
                strIndexNode_Cache.m_nID = nCustID_old;
                strIndexNode_Cache.m_nAddr = -1;
                strIndexNode_Cache.m_nCount = strIndexNode_C2P.m_nCount;
                strIndexNode_Cache.m_nTotalWeight = nTotalWeight;
                cls_vecIndex_C2P_Cache.push_back(strIndexNode_Cache);

                nCustID_old++;
            }

            //---------------------------------------------nCustID_old == tempinfo[i].m_nPid
            //��Ӹù˿͵Ĺ����б�
            while (iter != iter_end && nCustID_old == iter->m_nPid) //id < size must at first 10.05.19
            {
                str_InvertNode_C2P.copy(*iter);
                nTotalWeight += iter->m_nWeight * iter->m_nWeight;
                vecTmpCPList.push_back(str_InvertNode_C2P);
                ++iter;
            }
            if (vecTmpCPList.size() > 0) {
                strIndexNode_C2P.m_nAddr = from * sizeof (_InvertNode);
                strIndexNode_C2P.m_nCount = vecTmpCPList.size();
                strIndexNode_C2P.m_nTotalWeight = (int) (sqrt((float) nTotalWeight) * 1000);

                cls_vecIndex_C2P.push_back(strIndexNode_C2P);

                //cache
                strIndexNode_Cache.m_nID = nCustID_old;
                strIndexNode_Cache.m_nAddr = -1;
                strIndexNode_Cache.m_nCount = strIndexNode_C2P.m_nCount;
                strIndexNode_Cache.m_nTotalWeight = strIndexNode_C2P.m_nTotalWeight;
                cls_vecIndex_C2P_Cache.push_back(strIndexNode_Cache);

                if (isPersistant() || !tempinfo.isAllInMem()) {
                    fwrite(&vecTmpCPList[0], sizeof (_InvertNode), strIndexNode_C2P.m_nCount, fpInvert);
                } else {
                    //�ڴ��б���
                    std::copy(vecTmpCPList.begin(), vecTmpCPList.end(), std::back_inserter(vecCPList));
                }
                vecTmpCPList.clear();
                nTotalWeight = 0;
                nCustID_old++;
                from += strIndexNode_C2P.m_nCount;
            }
        }
        //TODO remove it! Where creating we must tell how many entries are
        m_nFirstColumnCount = cls_vecIndex_C2P.size();
        //clear
        fclose(fpInvert);
        if (!isPersistant() && tempinfo.isAllInMem()) //�����Ҫ�־û�����ô�����Ѿ����ڴ������˵�����Ϣ
            cls_vecInvert_C2P_Cache.swap(vecCPList);
    }

    /**
     * �����ڴ��е�����͵���cache
     * ��ǰ���� simple cache
     * �����ṩ����cahe ���� TODO
     *
     */
    void makeC2PInvertCache()
    {
        printf("\n---------------Cache Invert C2P To Memery---------------\n");
        __int64 nCurInvertCacheSize = 0;
        int nFrom = 0;
        bool allInMem = true;
        for (int i = 0; i < m_nFirstColumnCount; i++) {
            //�ж��ڴ�cache��û��ʣ��ռ�
            int nCount_C2P = cls_vecIndex_C2P_Cache[i].m_nCount;
            int nLength_C2P = nCount_C2P * sizeof (_InvertNode);

            if ((nCurInvertCacheSize + nLength_C2P) > InvertCacheSize) //��С����Ԥ���ڴ�����
            {
                allInMem = false;
                break;
            } else {
                cls_vecIndex_C2P_Cache[i].m_nAddr = nFrom;
                nFrom += nCount_C2P;
                nCurInvertCacheSize += nLength_C2P;
            }
        }

        //��������ҪCACHE��������ݶ���CACHE
        //TODO all try c++ style ? copy   TODO ������, ȫ���쳣��
        if (cls_vecInvert_C2P_Cache.empty()) {
            cls_vecInvert_C2P_Cache.resize(nFrom);
            fread(&cls_vecInvert_C2P_Cache[0], sizeof (_InvertNode), nFrom, fp_Invert_C2P);
        } else {
            //LOG(WARNING) << "Not write the invert to the disk for invert is small and we do not need persit" << endl;
        }

        if (allInMem) //���ȫ���ڴ棬���Թرմ򿪵ĵ����ļ�
        {
            m_bAllInMem = true;
            fclose(fp_Invert_C2P);
            fp_Invert_C2P = NULL;
        }
    }

    /**���ź�����ı��ж�ȡ��ݣ�������������*/
    void createInvertTable()
    {
        //������Ҫ��գ�����re sort֮���ٽ�������
        clearCache();

        //�������ű?����post list��д���ļ�
        makeC2PInvertTable();

        //�򿪵����ļ�
        fp_Invert_C2P = fopen(m_invertfileName.c_str(), "rb");
        //LOG_IF(FATAL, !fp_Invert_C2P) << "open " << m_invertfileName << "failed" << endl;

        //�ڴ��л���cache
        makeC2PInvertCache();

        //����ṹ,��д���ļ�
        writeIndex();
    }

    void createInvertTable(std::vector<_ST_PidKidInfo>& vec)
    {
        //������Ҫ��գ�����re sort֮���ٽ�������
        clearCache();

        //�������ű?����post list��д���ļ�
        makeC2PInvertTable(vec);

        //�򿪵����ļ�
        fp_Invert_C2P = fopen(m_invertfileName.c_str(), "rb");
        //LOG_IF(FATAL, !fp_Invert_C2P) << "open " << m_invertfileName << "failed" << endl;

        //�ڴ��л���cache
        makeC2PInvertCache();

        //����ṹ,��д���ļ�
        writeIndex();
    }

    /**
     * FIXME Ϊʲôinvert_table_creator ���õ�ʱ��,m_invertTable->create(m_tripleVec, m_indexfile.c_str(), m_invertfile.c_str());
     * ����Ҳ��ѡ��������ķ�֧����ѡ�������
     */
    template<typename Vector>
    void createInvertTable_bigVec(Vector& vec)
    {
        //������Ҫ��գ�����re sort֮���ٽ�������
        clearCache();

        //�������ű?����post list��д���ļ�
        makeC2PInvertTable_bigVec(vec);

        //�򿪵����ļ�
        fp_Invert_C2P = fopen(m_invertfileName.c_str(), "rb");
        //LOG_IF(FATAL, !fp_Invert_C2P) << "open " << m_invertfileName << "failed" << endl;

        //�ڴ��л���cache
        makeC2PInvertCache();

        //����ṹ,��д���ļ�
        writeIndex();
    }

    //--------------------------helper func for ���л�

    bool isAllInMem()
    {
        return m_bAllInMem;
    }

    bool openInvertFile()
    {
        if ((fp_Invert_C2P = fopen(m_invertfileName.c_str(), "rb")) == NULL) {
            return false;
        }
    }

    void setInvertFile(const char* filename)
    {
        m_invertfileName = filename;
    }

    void setInvertFile(const std::string& filename)
    {
        m_invertfileName = filename;
    }

    static void setCacheSize(int sort_size, int invert_size)
    {
        SortCacheSize = sort_size;
        InvertCacheSize = invert_size;
    }

    void setSortMethod(SortMethod sort_method)
    {
        m_sortMethod = sort_method;
    }

    SortMethod sortMethod()
    {
        return m_sortMethod;
    }

    __int64 invertSize()
    {
        return m_invertSize;
    }

    //private:
public: //FIXME temp
    std::string m_infileName;
    std::string m_sortedfileName;
    std::string m_indexfileName;
    std::string m_invertfileName;
    std::string m_dir;

    ///�ڴ�ӳ���еĵ�������
    vector<IndexNode> cls_vecIndex_C2P;

    ///�ڴ滺����
    vector<IndexNode_Cache> cls_vecIndex_C2P_Cache;
    vector< _InvertNode> cls_vecInvert_C2P_Cache;

    int m_nFirstColumnCount; ///table ��entrie ��Ŀ == clse_vecIndex_C2P.size()

    FILE *fp_Invert_C2P; ///�����ļ�ָ�룬�ڽ����õ�������֮���

    bool m_bAllInMem; ///����Ƿ�ȫ��cache�У�make cache������ñ��λ�����ȫ�ڲ���Ҫ�򿪵����ļ�
    bool m_bPersitant; ///�Ƿ���Ҫ��Ӳ�̱�������

    SortMethod m_sortMethod;

    __int64 m_invertSize;

    //��ʼ���Ļ�������const��ǰ
    //    static int SortCacheSize = 40 * 1024 * 1204;
    //    static int InvertCacheSize = 512 * 1024 * 1024;

    //FIXME ��ǰ�������е�InvertTable���������ͬ��cache���ã�����һЩ
public:
    static int SortCacheSize; ///�ⲿ�鲢ʱ��cache��С
    static int InvertCacheSize; ///������ɵ��ŵ�ʱ�����ڴ��еĵ��ŵ�cache��С

public:
    ///-----------------���л�

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & cls_vecIndex_C2P;
        ar & cls_vecIndex_C2P_Cache;
        ar & cls_vecInvert_C2P_Cache;
        ar & m_nFirstColumnCount;
        ar & m_bAllInMem;

        //this may be useful
        ar & m_indexfileName;
        ar & m_invertfileName;
    }
}; //---end of class InvertTable


//FIXME �����Ǹ�GCC BUG�� Ϊɶ����InvertTable<>��ʾ��ʼ������ֵ�ֱ���47M��602M��
template <class T, class U>
int InvertTable<T, U>::SortCacheSize = 1024 * 1024 * 1024; //1G

template <class T, class U>
int InvertTable<T, U>::InvertCacheSize = 1024 * 1024 * 1024; //1G

//------------------------------------------------------------------------------InvertTable ���л�������
///���л����벢��ʼ��һ��dic

template<typename T>
void loadInvertTable(T& invert_table, const char* infile)
{
    std::ifstream fin(infile);
    boost::archive::binary_iarchive ia(fin, std::ios::binary); //�ı�������鵵��
    ia >> invert_table; //�ָ���key_map2����
    fin.close();

    //�����ȫ���ڴ棬��Ҫ�򿪵����ļ�����ѯ����
    if (!invert_table.isAllInMem()) {
        invert_table.openInvertFile();
    }
}

template<typename T>
void loadInvertTable(T& invert_table, const std::string& infile)
{
    loadInvertTable(invert_table, infile.c_str());
}
//��ʵ�������л�����Ϊ���InvertTable�Ǽ��������ܷŵ��ڴ�ģ�����Ҫ�����indexfile
//Ϊ����ǰ�����������ṩ

template<typename T>
void loadInvertTable(T& invert_table, const char* infile, const char* indexfile, const char* invertfile)
{
    std::ifstream fin(infile);
    boost::archive::binary_iarchive ia(fin, std::ios::binary); //�ı�������鵵��
    ia >> invert_table; //�ָ���key_map2����
    fin.close();

    //�趨indexfile, invertfile name
    invert_table.setFile(indexfile, invertfile);

    //�����ȫ���ڴ棬��Ҫ�򿪵����ļ�����ѯ����
    if (!invert_table.isAllInMem()) {
        invert_table.openInvertFile();
    }
}

template<typename T>
void loadInvertTable(T& invert_table, const std::string& infile,
        const std::string& indexfile, const std::string inverfile)
{
    loadInvertTable(invert_table, infile.c_str(), indexfile.c_str(), inverfile.c_str());
}

template<typename T>
void loadInvertTable(T& invert_table, const char* infile, const char* invertfile)
{
    std::ifstream fin(infile);
    boost::archive::binary_iarchive ia(fin, std::ios::binary); //�ı�������鵵��
    ia >> invert_table; //�ָ���key_map2����
    fin.close();

    //�趨invertfile name
    invert_table.setInvertFile(invertfile);

    //�����ȫ���ڴ棬��Ҫ�򿪵����ļ�����ѯ����
    if (!invert_table.isAllInMem()) {
        invert_table.openInvertFile();
    }
}

template<typename T>
void loadInvertTable(T& invert_table, const std::string& infile,
        const std::string inverfile)
{
    loadInvertTable(invert_table, infile.c_str(), inverfile.c_str());
}
///���л����

template<typename T>
void saveInvertTable(T& invert_table, const char* outfile)
{
    std::ofstream fout(outfile);
    boost::archive::binary_oarchive oa(fout, std::ios::binary); //�ı�������鵵�࣬ʹ��һ��ostream������
    oa << invert_table; //����dic
    fout.close();
}

template<typename T>
void saveKeyDic(T& invert_table, const std::string& infile)
{
    saveInvertTable(invert_table, infile.c_str());
}

} //-------------end of namespace invert_table
#endif  //----end of INVERT_TABLE_H_
