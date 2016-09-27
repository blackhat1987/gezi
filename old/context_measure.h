/** 
 *  ==============================================================================
 * 
 *          \file   context_measure.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2012-01-19 10:26:31.170211
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef CONTEXT_MEASURE_H_
#define CONTEXT_MEASURE_H_

#include <algorithm>
#include <vector>
#include "common_cmper.h"
#include "vec_calc.h"
#include "sim_calc.h"
#include "debug_help.h"
#include "stl_help.h"
namespace semantic
{

/**
 * 以下都是计算一个词的相关词
 * 记住 first is id , second is weight
 */
template<typename _Invert, typename _Vec>
void cos_sim(size_t id, const _Invert& invert1, const _Invert& invert2, _Vec& result_vec,
             int max_num = std::numeric_limits<int>::max(), float thre = 0, int min_conum = 5)
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

    for (typename vector<size_t>::iterator iter = visit_vec.begin(); iter != visit_vec.end(); ++iter)
    {
        int id2 = *iter;
        double weight = L2NormType(sim_vec[id2]) / L2NormType(invert1.l2norm(id2) * invert1.l2norm(id));
        if (weight > thre && co_vec[id2] >= min_conum) //至少要有5个共用词
            result_vec.push_back(Node_(id2, weight));
        //            result_vec.push_back(Node_( id2, weight * (log(co_vec[id2]) + 1) ) );
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
              int max_num = std::numeric_limits<int>::max(), float beta = 0.6, float thre = 0.15, int min_conum = 5)
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
    for (Iter iter = visit_vec.begin(); iter != visit_vec.end(); ++iter)
    {
        int id2 = *iter;

        //        double weight = pow(10, -beta * pow(10, (sim_vec[id2] + 2 * log(2)) ));
        double weight = pow(10, -beta * (sim_vec[id2] + 2 * log(2)));
        //        double weight = -(sim_vec[id2] + 2 * log(2));

        //        double min_val = pow(10, -beta * 2 * log(2));
        //        weight = norm_val(weight, min_val, 1.0, 0, 0.95);

        if (weight > thre && co_vec[id2] >= min_conum)
            result_vec.push_back(Node_(id2, weight));
        //            result_vec.push_back(Node_( id2, weight * (log(co_vec[id2]) + 1) ));
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
 *
 */
template<typename _Invert, typename _Vec>
void cos_sim(size_t id1, size_t id2, const _Invert& invert1, const _Invert& invert2, _Vec& result_vec,
             int max_num = std::numeric_limits<int>::max(), float thre = 0, int min_conum = 5)
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

    vector<InvertNode_> temp_veca1, temp_vecb1;
    Range rangea1, rangeb1, range2;
    rangea1 = invert1.posting(id1, temp_veca1);
    rangeb1 = invert1.posting(id2, temp_vecb1);
    vector<InvertNode_> vec;
    //    merge2(rangea1.first, rangea1.second, rangeb1.first, rangeb1.second, std2::back_inserter(vec));
    intersect(rangea1.first, rangea1.second, rangeb1.first, rangeb1.second, vec);
    //    intersect(rangea1.first, rangea1.second, rangea1.first, rangea1.second, vec);
    //    Pval(vec.size());
    //    Pvec2(vec);
    typedef typename vector<InvertNode_>::iterator Iter;
    for (Iter iter1 = vec.begin(); iter1 != vec.end(); ++iter1)
    {
        vector<InvertNode_> temp_vec2;
        range2 = invert2.posting(iter1->first, temp_vec2);
        for (RangeIter iter2 = range2.first; iter2 != range2.second; ++iter2)
        {
            if (!sim_vec[iter2->first])
                visit_vec.push_back(iter2->first);
            sim_vec[iter2->first] += iter1->second * iter2->second;
            co_vec[iter2->first] += 1;
        }
    }
    L2NormType l2norm_ = l2norm(vec.begin(), vec.end());
    //    Pval(visit_vec.size());
    for (typename vector<size_t>::iterator iter = visit_vec.begin(); iter != visit_vec.end(); ++iter)
    {
        int id2 = *iter;
        double weight = L2NormType(sim_vec[id2]) / L2NormType(invert1.l2norm(id2) * l2norm_);
        //        Pval(weight);
        //        Pval(co_vec[id2]);
        if (weight > thre && co_vec[id2] >= min_conum) //至少要有5个共用词
            result_vec.push_back(Node_(id2, weight));
        //            result_vec.push_back(Node_( id2, weight * (log(co_vec[id2]) + 1) ) );
    }
    if (result_vec.size() <= max_num)
        std::sort(result_vec.begin(), result_vec.end(), std2::CmpNodeByValue());
    else
    {
        std::partial_sort(result_vec.begin(), result_vec.begin() + max_num, result_vec.end(), std2::CmpNodeByValue());
        _Vec(result_vec.begin(), result_vec.begin() + max_num).swap(result_vec);
    }

}

template<typename _Invert, typename _Vec>
void irad_sim(size_t id1, size_t id2, const _Invert& invert1, const _Invert& invert2, _Vec& result_vec,
              int max_num = std::numeric_limits<int>::max(), float beta = 0.6, float thre = 0.15, int min_conum = 5)
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


    vector<InvertNode_> temp_veca1, temp_vecb1;
    Range rangea1, rangeb1, range2;
    rangea1 = invert1.posting(id1, temp_veca1);
    rangeb1 = invert1.posting(id2, temp_vecb1);
    vector<InvertNode_> vec;
    intersect(rangea1.first, rangea1.second, rangeb1.first, rangeb1.second, vec);
    typedef typename vector<InvertNode_>::iterator Iter1;
    L1NormType_ l1norm1 = l1norm<L1NormType_ > (vec.begin(), vec.end());
    for (Iter1 iter1 = vec.begin(); iter1 != vec.end(); ++iter1)
    {
        vector<InvertNode_> temp_vec2;
        range2 = invert2.posting(iter1->first, temp_vec2);
        float p1 = float(iter1->second) / l1norm1;
        for (RangeIter iter2 = range2.first; iter2 != range2.second; ++iter2)
        {
            float p2 = float(iter2->second) / invert1.l1norm(iter2->first);
            float p = p1 + p2;
            float weight = p1 * log(p1 / p) + p2 * log(p2 / p);

            if (!sim_vec[iter2->first])
                visit_vec.push_back(iter2->first);
            sim_vec[iter2->first] += (double) weight;
            co_vec[iter2->first] += 1;
        }
    }
    for (Iter iter = visit_vec.begin(); iter != visit_vec.end(); ++iter)
    {
        int id2 = *iter;

        //        double weight = pow(10, -beta * pow(10, (sim_vec[id2] + 2 * log(2)) ));
        double weight = pow(10, -beta * (sim_vec[id2] + 2 * log(2)));
        //        double weight = -(sim_vec[id2] + 2 * log(2));

        //        double min_val = pow(10, -beta * 2 * log(2));
        //        weight = norm_val(weight, min_val, 1.0, 0, 0.95);

        if (weight > thre && co_vec[id2] >= min_conum)
            result_vec.push_back(Node_(id2, weight));
        //            result_vec.push_back(Node_( id2, weight * (log(co_vec[id2]) + 1) ));
    }
    if (result_vec.size() <= max_num)
        std::sort(result_vec.begin(), result_vec.end(), std2::CmpNodeByValue());
    else
    {
        std::partial_sort(result_vec.begin(), result_vec.begin() + max_num, result_vec.end(), std2::CmpNodeByValue());
        _Vec(result_vec.begin(), result_vec.begin() + max_num).swap(result_vec);
    }
}

//bayesian sets 计算的相似度,给定一系列id,给出最相关id

template<typename _Invert, typename _Vec, typename _IDVec, typename _ParamVec>
void bsets_sim(_IDVec& id_vec, _ParamVec& alpha_vec, _ParamVec& beta_vec,
               const _Invert& invert1, const _Invert& invert2, _Vec& result_vec,
               int max_num = std::numeric_limits<int>::max())
{
    using std::vector;
    typedef typename _Invert::Range Range;
    typedef typename _Invert::InvertNodeType InvertNode_;
    typedef typename _Vec::value_type Node_;
    typedef typename _Invert::iterator RangeIter;
    typedef typename _Invert::L2NormType L2NormType;

    //-------- 参数计算
    _ParamVec w_vec;
    int len = alpha_vec.size();
    w_vec.resize(len, 0);
    vector<int> visit_vec, visit_vec2;
    Range range;
    int nid = id_vec.size();
    for (int i = 0; i < nid; i++)
    {
        int id = id_vec[i];
        vector<InvertNode_> tvec;
        range = invert1.range(id, tvec);
        for (; range.first != range.second; ++range.first)
        {
            if (!w_vec[range.first->first])
                visit_vec.push_back(range.first->first);
            w_vec[range.first->first] += 1.0;
        }
    }

    for (int i = 0; i < len; i++)
    {

        //        Pval(alpha_vec[i]);
        //        Pval(beta_vec[i]);
        //        Pval((w_vec[i] / alpha_vec[i]));
        //        Pval(w_vec[i]);
        //        Pval((len - w_vec[i]));
        //        Pval(((len - w_vec[i]) / beta_vec[i]));
        w_vec[i] = log(1 + w_vec[i] / alpha_vec[i]) - log(1 + (nid - w_vec[i]) / beta_vec[i]);

        //        Pval(w_vec[i]);
    }

    vector<L2NormType> sim_vec(len, 0);

    int vnum = visit_vec.size();

    for (int i = 0; i < vnum; i++)
    {
        int co_id = visit_vec[i];
        vector<InvertNode_> tvec;
        range = invert2.range(co_id, tvec);
        for (RangeIter iter = range.first; iter != range.second; ++iter)
        {
            if (!sim_vec[iter->first])
                visit_vec2.push_back(iter->first);
            sim_vec[iter->first] += w_vec[co_id];
        }
    }
    for (typename vector<int>::iterator iter = visit_vec.begin(); iter != visit_vec.end(); ++iter)
    {
        int id2 = *iter;
        result_vec.push_back(Node_(id2, sim_vec[id2]));
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
