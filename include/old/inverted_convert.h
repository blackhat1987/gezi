/** 
 *  ==============================================================================
 * 
 *          \file   inverted_convert.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-18 10:58:41.811781
 *  
 *  \Description:   inverted体系下各种倒排数据数据结构转换
 *  ==============================================================================
 */

#ifndef INVERTED_CONVERT_H_
#define INVERTED_CONVERT_H_
#include <algorithm>
#include <numeric>
#include <vector>
namespace inverted {
/**
 * 通用的普通转换
 * 适合InvertedIndex -> InvertedTable  InvertedIndex -> InvertedMapTable
 * 如果 const _SrcInvert& invert_src 对代码要求更高，比如invert_src.posting(i) 需要const
 *
 * 注意大数据量map hashmap 很占内存 参考map 每个500个数据 58Wpos的时候 就能消耗10G内存了
 */
template<typename _SrcInvert, typename _DestInvert>
void convert(_SrcInvert& invert_src, _DestInvert& invert_dest)
{
    typedef typename _SrcInvert::Node Node;
    typedef typename _SrcInvert::iterator iter;
    typedef typename _SrcInvert::Range Range;
    int row_num = invert_src.size();
    invert_dest.resize(row_num);
    std::vector<Node> vec;
    Range range;
    for (int i = 0; i < row_num; i++)
    {
        vec.clear();
        range = invert_src.posting(i);
        std::copy(range.first, range.second, std::back_inserter(vec));
        invert_dest.add_posting(i, vec);
        invert_dest.index_node(i).l1norm = invert_src.index_node(i).l1norm;
        invert_dest.index_node(i).l2norm = invert_src.index_node(i).l2norm;
    }
}

} //----end of namespace inverted

#endif  //----end of INVERTED_CONVERT_H_
