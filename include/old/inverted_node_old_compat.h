/** 
 *  ==============================================================================
 * 
 *          \file   inverted_node_old_compat.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-18 13:41:44.021959
 *  
 *  \Description:   为了兼容以前不合理设置生成的索引倒排数据的载入
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
    DP l2norm; //这个设计为了存储sqrt(a1^2 +a2^2...) 为了cos计算准备
    T l1norm; //存储倒排链中的weight的加和
    int64 addr; //__int64 addr;
    int count;
    int first; //为了那种不要求编号从0开始顺序记录的，比如直接存储产品id  first 均标示id！
};
/**TODO 以前的程序设计问题，逐步去掉IndexNode_Cache*/
template<typename T>
struct IndexNode_Cache
{
    int first;
    int64 addr; //int addr;
    int count;
    DP l2norm;
    T l1norm; //TODO 如果InvertNode weight 是float....
    IndexNode_Cache()
    : first(-1), addr(0), count(-1), l2norm(0), l1norm(0)
    {
    }
};

} //----end of namespace inverted

#endif  //----end of INVERTED_NODE_OLD_COMPAT_H_
