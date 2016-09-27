/** 
 *  ==============================================================================
 * 
 *          \file   sim_calc.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-06 13:25:43.635913
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef SIM_CALC_H_
#define SIM_CALC_H_
#include <functional>
#include <numeric>
#include "vec_calc.h"
#include "common_traits.h"
typedef float SIM_TYPE;
template<typename _Iter>
SIM_TYPE l2norm(_Iter b, _Iter e)
{
    typedef typename IteratorTraits<_Iter>::value_type pair_type;
    typedef typename pair_type::second_type value_type;
    typedef typename NormTypeTraits<value_type>::L2NormType L2NormType;
    L2NormType sum = 0;
    for (; b != e; ++b)
    {
        sum += (b->second * b->second);
    }
    return (SIM_TYPE) sqrt(sum);
}
template<typename _Type, typename _Iter>
_Type l1norm(_Iter b, _Iter e)
{
    _Type result = 0;
    for (; b != e; ++b)
    {
        result += b->second;
    }
    return result;
}
/**
 * 要求两个输入的range按照first排序
 */
template<typename _Iter1, typename _Iter2, typename T, typename U>
SIM_TYPE cos(_Iter1 b1, _Iter1 e1, _Iter2 b2, _Iter2 e2, T l2norm1, U l2norm2)
{ //注意就使用Iter1类型来确定了
    typedef typename IteratorTraits<_Iter1>::value_type pair_type;
    typedef typename pair_type::second_type value_type;
    typedef typename NormTypeTraits<value_type>::L2NormType L2NormType;
    L2NormType dot_val = dot<_Iter1, _Iter2, L2NormType > (b1, e1, b2, e2);
    return dot_val / SIM_TYPE(l2norm1 * l2norm2);
}
template<typename _Iter1, typename _Iter2, typename T, typename U>
SIM_TYPE irad(_Iter1 b1, _Iter1 e1, _Iter2 b2, _Iter2 e2, T l1norm1, U l1norm2, float beta = 0.6)
{
    SIM_TYPE score = 0;
    if (b1 == e1 || b2 == e2)
    {
        return 0;
    }
    float p1, p2, p;
    while (b1 != e1 && b2 != e2)
    {
        if (b1->first == b2->first)
        {
            p1 = b1->second / l1norm1;
            p2 = b2->second / l1norm2;
            p = p1 + p2;
            score += p1 * log(p1 / p) + p2 * log(p2 / p);
            ++b1;
            ++b2;
        }
        else if (b1->first < b2->first)
        {
            ++b1;
        }
        else
        {
            ++b2;
        }
    }
    return pow(10, -beta * (score + 2 * log(2)));
}
/**
 * 要求输入按照->first排序，
 * kl_divergence 越小相似度越高
 */
template<typename _Iter1, typename _Iter2>
SIM_TYPE kl(_Iter1 b1, _Iter1 e1, _Iter2 b2, _Iter2 e2)
{
    SIM_TYPE score = 0;
    while (b1 != e1 && b2 != e2)
    {
        if (b1->first == b2->first)
        {
            score += -b1->second * (log(b2->second) - log(b1->second));
            ++b1;
            ++b2;
        }
        else if (b1->first < b2->first)
        {
            ++b1;
        }
        else
        {
            ++b2;
        }
    }
    return score;
}
template<typename _Iter1, typename _Iter2, typename T, typename U>
SIM_TYPE cos(_Iter1 b1, _Iter1 e1, T l2norm1, _Iter2 b2, _Iter2 e2, U l2norm2)
{ //注意就使用Iter1类型来确定了
    if (b1 == e1 || b2 == e2)
    {
        return 0;
    }
    typedef typename IteratorTraits<_Iter1>::value_type pair_type;
    typedef typename pair_type::second_type value_type;
    typedef typename NormTypeTraits<value_type>::L2NormType L2NormType;
    L2NormType dot_val = dot<_Iter1, _Iter2, L2NormType > (b1, e1, b2, e2);
    return dot_val / SIM_TYPE(l2norm1 * l2norm2);
}
template<typename _Iter1, typename _Iter2, typename T, typename U>
SIM_TYPE irad(_Iter1 b1, _Iter1 e1, T l1norm1, _Iter2 b2, _Iter2 e2, U l1norm2, float beta = 0.6)
{
    SIM_TYPE score = 0;
    float p1, p2, p;
    while (b1 != e1 && b2 != e2)
    {
        if (b1->first == b2->first)
        {
            p1 = b1->second / l1norm1;
            p2 = b2->second / l1norm2;
            p = p1 + p2;
            score += p1 * log(p1 / p) + p2 * log(p2 / p);
            ++b1;
            ++b2;
        }
        else if (b1->first < b2->first)
        {
            ++b1;
        }
        else
        {
            ++b2;
        }
    }
    return pow(10, -beta * (score + 2 * log(2)));
}


///下面是内部自己计算l1nomr,l2nomr的
template<typename _Iter1, typename _Iter2>
SIM_TYPE cos(_Iter1 b1, _Iter1 e1, _Iter2 b2, _Iter2 e2)
{ //注意就使用Iter1类型来确定了
    typedef typename IteratorTraits<_Iter1>::value_type pair_type;
    typedef typename pair_type::second_type value_type;
    typedef typename NormTypeTraits<value_type>::L2NormType L2NormType;
    double l2norm1 = l2norm(b1, e1);
    double l2norm2 = l2norm(b2, e2);
    L2NormType dot_val = dot<_Iter1, _Iter2, L2NormType > (b1, e1, b2, e2);
    return dot_val / SIM_TYPE(l2norm1 * l2norm2);
}
template<typename _Iter1, typename _Iter2>
SIM_TYPE irad(_Iter1 b1, _Iter1 e1, _Iter2 b2, _Iter2 e2, float beta = 0.6)
{
    typedef typename IteratorTraits<_Iter1>::value_type pair_type;
    typedef typename pair_type::second_type L1Norm;

    L1Norm l1norm1 = l1norm<L1Norm > (b1, e1);
    L1Norm l1norm2 = l1norm<L1Norm > (b2, e2);
    SIM_TYPE score = 0;
    float p1, p2, p;
    while (b1 != e1 && b2 != e2)
    {
        if (b1->first == b2->first)
        {
            p1 = b1->second / l1norm1;
            p2 = b2->second / l1norm2;
            p = p1 + p2;
            score += p1 * log(p1 / p) + p2 * log(p2 / p);
            ++b1;
            ++b2;
        }
        else if (b1->first < b2->first)
        {
            ++b1;
        }
        else
        {
            ++b2;
        }
    }
    return pow(10, -beta * (score + 2 * log(2)));
}
template<typename _Iter1, typename _Iter2>
SIM_TYPE cos_(_Iter1 b1, _Iter1 e1, _Iter2 b2, _Iter2 e2)
{
    SIM_TYPE score = 0;
    SIM_TYPE t1 = 0;
    SIM_TYPE t2 = 0;
    while (b1 != e1 && b2 != e2)
    {
        t1 += (*b1) * (*b1);
        t2 += (*b2) * (*b2);
        score += (*b1) * (*b2);
        ++b1;
        ++b2;
    }
    return score / (sqrt(t1) * sqrt(t2));
}
template<typename _Invert, typename _Iter>
SIM_TYPE l2norm(_Iter b, _Iter e, _Invert& invert)
{
    typedef typename IteratorTraits<_Iter>::value_type pair_type;
    typedef typename pair_type::second_type value_type;
    typedef typename NormTypeTraits<value_type>::L2NormType L2NormType;
    L2NormType sum = 0;

    for (_Iter it1 = b; it1 != e; ++it1)
    {
        for (_Iter it2 = b; it2 != e; ++it2)
        {
            float score = (it1->first == it2->first) ? 1 : std::max(invert(it1->first, it2->first), invert(it2->first, it1->first));
            sum += score * (it1->second * it2->second);
        }
    }
    return (SIM_TYPE) sqrt(sum);
}
template<typename _Invert, typename _Iter1, typename _Iter2>
SIM_TYPE cos(_Iter1 b1, _Iter1 e1, _Iter2 b2, _Iter2 e2, _Invert& invert)
{ //注意就使用Iter1类型来确定了
    typedef typename IteratorTraits<_Iter1>::value_type pair_type;
    typedef typename pair_type::second_type value_type;
    typedef typename NormTypeTraits<value_type>::L2NormType L2NormType;
    double l2norm1 = l2norm(b1, e1, invert);
    double l2norm2 = l2norm(b2, e2, invert);
    Pval(l2norm1);
    Pval(l2norm2);
    L2NormType dot_val = 0.0;
    for (_Iter1 it1 = b1; it1 != e1; ++it1)
    {
        for (_Iter2 it2 = b2; it2 != e2; ++it2)
        {
            float score = (it1->first == it2->first) ? 1 : std::max(invert(it1->first, it2->first), invert(it2->first, it1->first));
            dot_val += score * (it1->second * it2->second);
        }
    }
    Pval(dot_val);
    return dot_val / SIM_TYPE(l2norm1 * l2norm2);
}
template<typename _Worker, typename _Iter>
SIM_TYPE l2norm_calc(_Iter b, _Iter e, _Worker& worker)
{
    typedef typename IteratorTraits<_Iter>::value_type pair_type;
    typedef typename pair_type::second_type value_type;
    typedef typename NormTypeTraits<value_type>::L2NormType L2NormType;
    L2NormType sum = 0;

    for (_Iter it1 = b; it1 != e; ++it1)
    {
        for (_Iter it2 = b; it2 != e; ++it2)
        {
            float score = (it1->first == it2->first) ? 1 : std::max(worker.sim(it1->first, it2->first), worker.sim(it2->first, it1->first));
            sum += score * (it1->second * it2->second);
        }
    }
    return (SIM_TYPE) sqrt(sum);
}
template<typename _Worker, typename _Iter1, typename _Iter2>
SIM_TYPE cos_calc(_Iter1 b1, _Iter1 e1, _Iter2 b2, _Iter2 e2, _Worker& worker)
{ //注意就使用Iter1类型来确定了
    typedef typename IteratorTraits<_Iter1>::value_type pair_type;
    typedef typename pair_type::second_type value_type;
    typedef typename NormTypeTraits<value_type>::L2NormType L2NormType;
    double l2norm1 = l2norm_calc(b1, e1, worker);
    double l2norm2 = l2norm_calc(b2, e2, worker);
    Pval(l2norm1);
    Pval(l2norm2);
    L2NormType dot_val = 0.0;
    for (_Iter1 it1 = b1; it1 != e1; ++it1)
    {
        for (_Iter2 it2 = b2; it2 != e2; ++it2)
        {
            float score = (it1->first == it2->first) ? 1 : std::max(worker.sim(it1->first, it2->first), worker.sim(it2->first, it1->first));
            dot_val += score * (it1->second * it2->second);
        }
    }
    Pval(dot_val);
    return dot_val / SIM_TYPE(l2norm1 * l2norm2);
}

#endif  //----end of SIM_CALC_H_
