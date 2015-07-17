/** 
 *  ==============================================================================
 * 
 *          \file   context_measure2.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-19 20:18:10.345646
 *  
 *  \Description:   类似 context_measure2 但是加强限制
 *                  考虑一个词A和它的最相关词B
 *                     coocur(A,B) = M
 *                     sim(A,B) = N
 *                  那么过滤掉coocur(A,C) < 0.4* M, sim(A,C) < 0.3 N 的词C
 *                                        ratio_co            ratio_sim
 *  ==============================================================================
 */

#ifndef CONTEXT_MEASURE2_H_
#define CONTEXT_MEASURE2_H_

#include <algorithm>
#include <vector>
#include "common_cmper.h"
#include "common_help.h"
namespace semantic {


/**
 * 以下都是计算一个词的相关词
 * 记住 first is id , second is weight
 */
template<typename _Invert, typename _Vec>
void cos_sim(int id, const _Invert& invert1, const _Invert& invert2, _Vec& result_vec,
        int max_num = std::numeric_limits<int>::max(), float ratio_co = 0.1, float ratio_sim = 0.2, float thre = 0, int min_conum = 5)
{
    using std::vector;
    result_vec.clear();
    typedef typename _Invert::Range Range;
    typedef typename _Invert::iterator RangeIter;
    typedef typename _Invert::L2NormType L2NormType;
    typedef typename _Invert::InvertNodeType InvertNode_;
    typedef typename _Vec::value_type Node_;

    vector<L2NormType> sim_vec(invert1.size(), 0);
    vector<size_t> co_vec(invert1.size(), 0);
    vector<size_t> visit_vec;

    vector<InvertNode_> temp_vec;
    Range range1, range2;
    range1 = invert1.posting(id, temp_vec);
    for (RangeIter iter1 = range1.first; iter1 != range1.second; ++iter1)
    {
        vector<InvertNode_> temp_vec2;
        range2 = invert2.posting(iter1->first, temp_vec2);
        for (RangeIter iter2 = range2.first; iter2 != range2.second; ++iter2)
        {
            if (iter2->first == id)
                continue;
            if (!sim_vec[iter2->first])
                visit_vec.push_back(iter2->first);
            sim_vec[iter2->first] += iter1->second * iter2->second;
            co_vec[iter2->first] += 1;
        }
    }
    //store id, weight, coocur
    typedef boost::tuple<int, double, int> TNode;
    typedef std::vector<TNode> TNodeVec;
    TNodeVec vec;
    double max_weight = 0.0;
    int max_co = 0;
    for (typename vector<size_t>::iterator iter = visit_vec.begin(); iter != visit_vec.end(); ++iter)
    {
        int id2 = *iter;
        double weight = L2NormType(sim_vec[id2]) / L2NormType(invert1.l2norm(id2) * invert1.l2norm(id));
        if (weight > thre && co_vec[id2] >= min_conum)
        {
            if (weight > max_weight)
                max_weight = weight;
            if (co_vec[id2] > max_co)
                max_co = co_vec[id2];
            vec.push_back(TNode(id2, weight, co_vec[id2]));
        }
    }

    int len = vec.size();
//    Pval( ratio_co );
//    Pval( (ratio_sim * max_weight) );
//    Pval( (ratio_co * max_co) );
    for (int i = 0; i < len; i++)
    {
//        if (vec[i].get < 0 >() == 964298)
//        {
//            Pval(vec[i].get < 1 > ());
//            Pval(vec[i].get < 2 > ());
//        }
        if (vec[i].get < 1 > () > ratio_sim * max_weight && vec[i].get < 2 > () > ratio_co * max_co)
        {
            result_vec.push_back(Node_(vec[i].get < 0 > (), vec[i].get < 1 > ()));
        }
    }

    if (result_vec.size() <= max_num)
        std::sort(result_vec.begin(), result_vec.end(), std2::CmpNodeByValue());
    else
    {
        std::partial_sort(result_vec.begin(), result_vec.begin() + max_num, result_vec.end(), std2::CmpNodeByValue());
        _Vec(result_vec.begin(), result_vec.begin() + max_num).swap(result_vec);
    }

}
/**
 * 这个需要跑一遍整体数据 出现的irad最大值比如0.41 映射到0.95 最小值 映射到0.3 比如 使得分值有一定的区分性
 */
inline double norm_val(double val, double omin, double omax, double nmin, double nmax)
{
    if (val <= omin)
        return nmin;
    if (val > omax)
        return nmax;
    return (int) ((val - omin)*1.0 / (omax - omin))*(nmax - nmin) + nmin;
}
template<typename _Invert, typename _Vec>
void irad_sim(size_t id, const _Invert& invert1, const _Invert& invert2, _Vec& result_vec,
        int max_num = std::numeric_limits<int>::max(),  float ratio_co = 0.1, float ratio_sim = 0.2,
        float beta = 0.6, float thre = 0.155, int min_conum = 5)
{
    using std::vector;
    result_vec.clear();
    typedef vector<size_t>::const_iterator Iter;
    typedef typename _Invert::InvertNodeType InvertNode_;
    typedef typename _Invert::L1NormType L1NormType_;
    typedef typename _Vec::value_type Node_;
    typedef typename _Invert::Range Range;
    typedef typename _Invert::iterator RangeIter;

    vector<double> sim_vec(invert1.size(), 0);
    vector<size_t> co_vec(invert1.size(), 0);
    vector<size_t> visit_vec;

    vector<InvertNode_> temp_vec;
    Range range1, range2;
    range1 = invert1.posting(id, temp_vec);
    L1NormType_ l1norm1 = invert1.l1norm(id);
    for (RangeIter iter1 = range1.first; iter1 != range1.second; ++iter1)
    {
        vector<InvertNode_> temp_vec2;
        range2 = invert2.posting(iter1->first, temp_vec2);
        float p1 = float(iter1->second) / l1norm1;
        for (RangeIter iter2 = range2.first; iter2 != range2.second; ++iter2)
        {
            if (iter2->first == id)
                continue;

            float p2 = float(iter2->second) / invert1.l1norm(iter2->first);
            float p = p1 + p2;
            float weight = p1 * log(p1 / p) + p2 * log(p2 / p);

            if (!sim_vec[iter2->first])
                visit_vec.push_back(iter2->first);
            sim_vec[iter2->first] += (double) weight;
            co_vec[iter2->first] += 1;
        }
    }

    double base = 2 * log(2);
    //store id, weight, kl, coocur
    typedef boost::tuple<int, double, double, int> TNode;
    typedef std::vector<TNode> TNodeVec;
    TNodeVec vec;
    double min_weight = std::numeric_limits<double>::max();
    int max_co = 0;
    //debug
        int min_weight_co, min_weight_id;
        double max_weight;
    for (typename vector<size_t>::iterator iter = visit_vec.begin(); iter != visit_vec.end(); ++iter)
    {
        int id2 = *iter;

        double weight = pow(10, -beta * (sim_vec[id2] + base));
        if (weight > thre && co_vec[id2] >= min_conum)
        {
            //if (weight > max_weight)
            //    max_weight = weight;
            if (base + sim_vec[id2] < min_weight)
            {
                min_weight = base + sim_vec[id2];
                min_weight_co = co_vec[id2];
                min_weight_id = id2;
                max_weight = weight;
            }
            if (co_vec[id2] > max_co)
                max_co = co_vec[id2];
            //            Pval(-sim_vec[id2]);
            vec.push_back(TNode(id2, weight, base + sim_vec[id2], co_vec[id2]));
        }
    }

//    Pval(min_weight);
//    Pval(min_weight_co);
//    Pval(min_weight_id);
//    Pval(max_weight);
//    Pval(max_co);
//    Pval((min_weight / ratio_sim));
    int len = vec.size();
    for (int i = 0; i < len; i++)
    {
        //        if (vec[i].get < 0 > () == 1320131)
        //        {
        //            Pval(vec[i].get < 0 > ());
        //            Pval(vec[i].get < 1 > ());
        //            Pval(vec[i].get < 2 > ());
        //            Pval(vec[i].get < 3 > ());
        //        }
        //        if (vec[i].get < 1 > () > ratio_sim * max_weight && vec[i].get < 2 > () > ratio_co * max_co)
        if (vec[i].get < 2 > () < min_weight / ratio_sim && vec[i].get < 3 > () > ratio_co * max_co)
        {
            result_vec.push_back(Node_(vec[i].get < 0 > (), vec[i].get < 1 > ()));
        }
    }

    if (result_vec.size() <= max_num)
        std::sort(result_vec.begin(), result_vec.end(), std2::CmpNodeByValue());
    else
    {
        std::partial_sort(result_vec.begin(), result_vec.begin() + max_num, result_vec.end(), std2::CmpNodeByValue());
        _Vec(result_vec.begin(), result_vec.begin() + max_num).swap(result_vec);
    }

}
} //----end of namespace semantic

#endif  //----end of CONTEXT_MEASURE_H_
