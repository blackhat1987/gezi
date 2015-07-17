/** 
 *  ==============================================================================
 * 
 *          \file   cos_calc.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-25 18:09:19.788365
 *  
 *  \Description:   余弦等向量计算工具，现在反思相关搜索中代码偶合性还是太高，该单独提出的尽量轻量级
 *  ==============================================================================
 */

#ifndef COS_CALC_H_
#define COS_CALC_H_
#include <vector>
//#include <tr1/unordered_map>
namespace cos {
using std::vector;
/**
 * 计算所有某个id 的 所有相关id的相似度，dot not cos 不做归一化
 */
template<typename Invert, typename Hash>
void dot_calc(int id, const Invert& f2s_invert, const Invert& s2f_invert, Hash& hash)
{
    typedef typename Invert::InvertNodeType InvertNode;
    vector<InvertNode> temp_vec; //need this
    InvertNode* start = NULL;
    int hits = 0;
    f2s_invert.getPostList(id, temp_vec, start, hits); //get post list from invert table

    for (int i = 0; i < hits; i++, start++)
    {
        vector<InvertNode> temp_vec2; //need this
        InvertNode* start2 = NULL;
        int hits2 = 0;
        s2f_invert->getPostList(start->m_nID, temp_vec2, start2, hits2);
        for (int j = 0; j < hits2; j++, start2++)
        {
            if (start2->m_nID == id) //not inculde one's self
                continue;
            hash[start2->m_nID] += start->m_nWeight * start2->m_nWeight;
        }
    }
}

} //----end of namespace cos

#endif  //----end of COS_CALC_H_
