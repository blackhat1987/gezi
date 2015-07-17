/** 
 *  ==============================================================================
 * 
 *          \file   inverted_node_types.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-11 10:33:55.369475
 *  
 *  \Description:  �ʵ�Ҫ��int ��Ų�Ҫ����
 *
 *                 ���ʹ�ø��ӵ� value���� ����ҪΪ�����Ͷ��� �ȽϺ��� �ȵ�,��ΪInvertedIndex
 *                 ���� l1norm l2norm ������Ҫ ��second������ ���� + �ȵ�operator
 *                 �����㶨�������ļ̳�InvertNode����first second֮����� ���� data value�ȵ�
 *
 * ͳһ��first��ʾkey ��second ��ʾvalue weight
 * �������͵�ʱ�� ������Ҫ��unsigned!!
 *  ==============================================================================
 */

#ifndef INVERTED_NODE_TYPES_H_
#define INVERTED_NODE_TYPES_H_
#include "inverted_common.h"
namespace inverted {

///----------------------index node
/**IndexNode����������*/
template<typename _ValueType>
struct IndexNode
{
    typedef DP L2Norm;
    typedef typename NormTypeTraits<_ValueType>::L1NormType L1Norm;
    L2Norm l2norm; //������Ϊ�˴洢sqrt(a1^2 +a2^2...) Ϊ��cos����׼��
    L1Norm l1norm; //�洢�������е�weight�ļӺ�
    int64 addr; // unsigned is dangerous and you can not use -1 as a mark:)
    int count;
    int first; //Ϊ�����ֲ�Ҫ���Ŵ�0��ʼ˳���¼�ģ�����ֱ�Ӵ洢��Ʒid  first ����ʾid��
};

//------------invert and sort node
//SortNode �ɹ̶�
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


//ȥ�� InvertNode  Ĭ��ʹ�� std::pair ����InvertNode��IndexNode���ǿ������õ�
template<typename _IndexType, typename _KeyType, typename _ValueType>
inline void copy(const SortNode<_IndexType, _KeyType, _ValueType> & other, std::pair<_KeyType, _ValueType>& node)
{
    node.first = other.kid;
    node.second = other.second;
}

} //----end of namespace inverted

#endif  //----end of INVERTED_NODE_TYPES_H_
