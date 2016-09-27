/** 
 *  ==============================================================================
 * 
 *          \file   inverted_convert.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-18 10:58:41.811781
 *  
 *  \Description:   inverted��ϵ�¸��ֵ����������ݽṹת��
 *  ==============================================================================
 */

#ifndef INVERTED_CONVERT_H_
#define INVERTED_CONVERT_H_
#include <algorithm>
#include <numeric>
#include <vector>
namespace inverted {
/**
 * ͨ�õ���ͨת��
 * �ʺ�InvertedIndex -> InvertedTable  InvertedIndex -> InvertedMapTable
 * ��� const _SrcInvert& invert_src �Դ���Ҫ����ߣ�����invert_src.posting(i) ��Ҫconst
 *
 * ע���������map hashmap ��ռ�ڴ� �ο�map ÿ��500������ 58Wpos��ʱ�� ��������10G�ڴ���
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
