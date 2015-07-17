/** 
 *  ==============================================================================
 * 
 *          \file   invert_table_builder.h
 *
 *        \author   chenghuige 
 *          
 *          \date   2010-07-07 12:43:01.592826
 *  
 *  \Description:   采用BigVec实现的倒排索引帮助建立类
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
 * 编译期默认采用byWeight,如果byID,使用CmpSTNodeID
 * 这个版本只支持索引路径
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
        bf::path path(m_dir); //如果索引输出路径文件夹未被建立则首先建立，比如update_data/abc,需要首先建立abc文件夹
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
    ///加入<index_id, invert_id, weight>三元组  FIXME 如何支持__int64的倒排
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
    bool m_bPersitant; ///是否需要保留磁盘内容
};
} //--------end of namesapce invert_table
#endif  //----end of INVERT_TABLE_BUILDER_H_
