/** 
 *  ==============================================================================
 * 
 *          \file   inverted_table_node_types.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-16 15:08:39.656676
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef INVERTED_TABLE_NODE_TYPES_H_
#define INVERTED_TABLE_NODE_TYPES_H_
#include "inverted_common.h"
namespace inverted {
///----------------------index node
template<typename _ValueType>
struct TableIndexNode
{
    typedef DP L2Norm;
    typedef typename NormTypeTraits<_ValueType>::L1NormType L1Norm;
    L2Norm l2norm; //这个设计为了存储sqrt(a1^2 +a2^2...) 为了cos计算准备
    L1Norm l1norm; //存储倒排链中的weight的加和
    TableIndexNode()
    : l2norm(0), l1norm(0)
    {

    }
    TableIndexNode(DP l2, _ValueType l1)
    : l2norm(l2), l1norm(l1)
    {

    }
};
//template<typename _ValueType>
//struct TableIndexNode_L2
//{
//    typedef DP L2Norm;
//    typedef typename NormTypeTraits<_ValueType>::L1NormType L1Norm;
//    L2Norm l2norm; //这个设计为了存储sqrt(a1^2 +a2^2...) 为了cos计算准备
//    TableIndexNode_L2()
//    {
//
//    }
//    TableIndexNode_L2(DP l2)
//    : l2norm(l2)
//    {
//
//    }
//};

} //----end of namespace inverted

#endif  //----end of INVERTED_TABLE_NODE_TYPES_H_
