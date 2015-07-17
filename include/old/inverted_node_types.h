/** 
 *  ==============================================================================
 * 
 *          \file   inverted_node_types.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-11 10:33:55.369475
 *  
 *  \Description:  词典要求int 编号不要超过
 *
 *                 如果使用复杂的 value类型 则需要为该类型定义 比较函数 等等,因为InvertedIndex
 *                 绑定了 l1norm l2norm 所以需要 对second的类型 定义 + 等等operator
 *                 或者你定义其它的继承InvertNode增加first second之外的域 比如 data value等等
 *
 * 统一用first标示key 用second 标示value weight
 * 设置类型的时候 尽量不要用unsigned!!
 *  ==============================================================================
 */

#ifndef INVERTED_NODE_TYPES_H_
#define INVERTED_NODE_TYPES_H_
#include "inverted_common.h"
namespace inverted {

///----------------------index node
/**IndexNode可以再配置*/
template<typename _ValueType>
struct IndexNode
{
    typedef DP L2Norm;
    typedef typename NormTypeTraits<_ValueType>::L1NormType L1Norm;
    L2Norm l2norm; //这个设计为了存储sqrt(a1^2 +a2^2...) 为了cos计算准备
    L1Norm l1norm; //存储倒排链中的weight的加和
    int64 addr; // unsigned is dangerous and you can not use -1 as a mark:)
    int count;
    int first; //为了那种不要求编号从0开始顺序记录的，比如直接存储产品id  first 均标示id！
};

//------------invert and sort node
//SortNode 可固定
template<typename _IndexType, typename _KeyType, typename _ValueType>
struct SortNode
{
    _IndexType pid;
    _KeyType kid;
    _ValueType second;
    SortNode()
    {
        pid = 0;
    }
    SortNode(_IndexType pid_, _KeyType kid_, _ValueType second_ = 0)
    : pid(pid_), kid(kid_), second(second_)
    {
    }
    template<typename _Index, typename _Key, typename _Value>
            inline bool operator<(const SortNode<_Index, _Key, _Value> & other) const
    {
        return ((pid < other.pid)
                || ((pid == other.pid) && (kid < other.kid))
                || ((pid == other.pid) && (kid == other.kid) && (second < other.second)));
    }
    inline void setData(_IndexType pid_, _KeyType kid_, _ValueType second_)
    {
        pid = pid_;
        kid = kid_;
        second = second_;
    }
};


//去掉 InvertNode  默认使用 std::pair 但是InvertNode和IndexNode都是可以配置的
template<typename _IndexType, typename _KeyType, typename _ValueType>
inline void copy(const SortNode<_IndexType, _KeyType, _ValueType> & other, std::pair<_KeyType, _ValueType>& node)
{
    node.first = other.kid;
    node.second = other.second;
}

} //----end of namespace inverted

#endif  //----end of INVERTED_NODE_TYPES_H_
