/** 
 *  ==============================================================================
 * 
 *          \file   inverted_node_old_compat.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-18 13:41:44.021959
 *  
 *  \Description:   Ϊ�˼�����ǰ�������������ɵ������������ݵ�����
 *  ==============================================================================
 */

#ifndef INVERTED_NODE_OLD_COMPAT_H_
#define INVERTED_NODE_OLD_COMPAT_H_
#include "inverted_common.h"
namespace inverted {
template<typename T>
struct IndexNode_Old
{
    typedef DP L2Norm;
    typedef float L1Norm;
    DP l2norm; //������Ϊ�˴洢sqrt(a1^2 +a2^2...) Ϊ��cos����׼��
    T l1norm; //�洢�������е�weight�ļӺ�
    int64 addr; //__int64 addr;
    int count;
    int first; //Ϊ�����ֲ�Ҫ���Ŵ�0��ʼ˳���¼�ģ�����ֱ�Ӵ洢��Ʒid  first ����ʾid��
};
/**TODO ��ǰ�ĳ���������⣬��ȥ��IndexNode_Cache*/
template<typename T>
struct IndexNode_Cache
{
    int first;
    int64 addr; //int addr;
    int count;
    DP l2norm;
    T l1norm; //TODO ���InvertNode weight ��float....
    IndexNode_Cache()
    : first(-1), addr(0), count(-1), l2norm(0), l1norm(0)
    {
    }
};

} //----end of namespace inverted

#endif  //----end of INVERTED_NODE_OLD_COMPAT_H_
