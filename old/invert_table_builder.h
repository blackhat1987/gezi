/** 
 *  ==============================================================================
 * 
 *          \file   invert_table_builder.h
 *
 *        \author   chenghuige 
 *          
 *          \date   2010-07-07 12:43:01.592826
 *  
 *  \Description:   ����BigVecʵ�ֵĵ�����������������
 *  ==============================================================================
 */

#ifndef INVERT_TABLE_BUILDER_H_
#define INVERT_TABLE_BUILDER_H_

#include <boost/filesystem.hpp>
#include <glog/logging.h>
#include "invert_table.h"
#include "debug_help.h"

#include "big_vec.h"
/**
 * ������Ĭ�ϲ���byWeight,���byID,ʹ��CmpSTNodeID
 * ����汾ֻ֧������·��
 */
namespace invert_table
{
template<class _InvertTable = InvertTable<>, class _Cmp = CmpSTNodeWeight,
template<class _Node, class _Cmp> class _Container = BigVec>
class InvertTableBuilder
{
public:
    typedef typename _InvertTable::InvertNodeType _InvertNode;
    typedef typename _InvertTable::SortNodeType _ST_PidKidInfo;
    typedef typename _InvertNode::WeightType _WeightType;

    typedef _Container<_ST_PidKidInfo, _Cmp> _Vector;
    InvertTableBuilder(_InvertTable& invert_table,
                       const std::string& dir, bool persistant = true, int CacheSize = 1024 * 1024 * 1024)
    : m_invertTable(&invert_table), m_dir(dir), m_bPersitant(persistant), m_maxLen(CacheSize / sizeof (_ST_PidKidInfo))
    {
        init();
    }
private:
    void init()
    {
        bf::path path(m_dir); //����������·���ļ���δ�����������Ƚ���������update_data/abc,��Ҫ���Ƚ���abc�ļ���
        if (!bf::exists(path))
        {
            LOG(WARNING) << path << " not exist will create first\n";
            bf::create_directories(path);
        }
        if (!m_bPersitant)
        {
            m_invertTable->setNonPersitant();
        }
        m_vec.set_maxlen(m_maxLen);
    }
public:
    ///����<index_id, invert_id, weight>��Ԫ��  FIXME ���֧��__int64�ĵ���
    inline void addTriple(int index_id, int invert_id, _WeightType weight)
    {
        m_vec.push_back(_ST_PidKidInfo(index_id, invert_id, weight));
    }
    inline void addTriple(int index_id, int invert_id, _WeightType weight, int weight2)
    {
        m_vec.push_back(_ST_PidKidInfo(index_id, invert_id, weight, weight2));
    }
    __int64 create()
    {
        m_vec.sort();
        m_invertTable->create_bigVec(m_vec, m_dir.c_str());
        return m_invertTable->invertSize();
    }
    __int64 fastCreate()
    {
        m_invertTable->create_bigVec(m_vec, m_dir.c_str());
        return m_invertTable->invertSize();
    }
    __int64 build()
    {
        return create();
    }
    __int64 fastBuild()
    {
        return fastCreate();
    }
private:
    _Vector m_vec;

    _InvertTable* m_invertTable;

    std::string m_dir;
    int m_maxLen;
    bool m_bPersitant; ///�Ƿ���Ҫ������������
};
} //--------end of namesapce invert_table
#endif  //----end of INVERT_TABLE_BUILDER_H_
