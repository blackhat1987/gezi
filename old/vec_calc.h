/** 
 *  ==============================================================================
 * 
 *          \file   vec_calc.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-06 13:18:00.608147
 *  
 *  \Description:   一些用vector表示的向量的计算
 *                  默认采用Node{id; weight;} 而不是val, value
 *  ==============================================================================
 */

#ifndef VEC_CALC_H_
#define VEC_CALC_H_
#include <vector>
#include <boost/tuple/tuple.hpp>
//---------------------range
template<typename _Iter1, typename _Iter2, typename _Type>
_Type dot(_Iter1 iter1, _Iter1 iter1_e, _Iter2 iter2, _Iter2 iter2_e)
{
    _Type result = 0;
    while (iter1 != iter1_e && iter2 != iter2_e)
    {
        if (iter1->first == iter2->first)
        {
            result += iter1->second * iter2->second;
            ++iter1;
            ++iter2;
        }
        else if (iter1->first < iter2->first)
        {
            ++iter1;
        }
        else
        {
            ++iter2;
        }
    }
    return result;
}
template<typename _Iter1, typename _Iter2, typename _Type>
_Type dot(_Iter1 iter1, _Iter1 iter1_e, _Iter2 iter2, _Iter2 iter2_e, _Type init)
{
    _Type result = init;
    while (iter1 != iter1_e && iter2 != iter2_e)
    {
        if (iter1->first == iter2->first)
        {
            result += iter1->second * iter2->second;
            ++iter1;
            ++iter2;
        }
        else if (iter1->first < iter2->first)
        {
            ++iter1;
        }
        else
        {
            ++iter2;
        }
    }
    return result;
}
template<typename _Iter, typename _Type>
_Type accumulate2(_Iter iter, _Iter iter_e, _Type init)
{
    for (; iter != iter_e; ++iter)
    {
        init += iter->second;
    }
    return init;
}
template<typename _Iter1, typename _Iter2, typename _Type>
_Type dot2(_Iter1 iter1, _Iter1 iter1_e, _Iter2 iter2, _Iter2 iter2_e, _Type init)
{
    _Type result = init;
    for (; iter1 != iter1_e && iter2 != iter2_e; ++iter1, ++iter2)
    {
        result += (*iter1) * (*iter2);
    }
    return result;
}
template<typename _Iter1, typename _Iter2>
int intersect_num(_Iter1 b1, _Iter1 e1, _Iter2 b2, _Iter2 e2)
{
    int num = 0;
    while (b1 != e1 && b2 != e2)
    {
        if (b1->first == b2->first)
        {
            num++;
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
    return num;
}
template<typename _Iter1, typename _Iter2, typename _OIter>
void add(_Iter1 b1, _Iter1 e1, _Iter2 b2, _Iter2 e2, _OIter result)
{
    typedef typename std::iterator_traits<_OIter>::value_type value_type;
    while (b1 != e1 && b2 != e2)
    {
        if (b1->first == b2->first)
        {
            *result++ = value_type(b1->first, b1->second + b2->second);
            ++b1;
            ++b2;
        }
        else if (b1->first < b2->first)
        {
            *result++ = *b1++;
        }
        else
        {
            *result++ = *b2++;
        }
    }
    while (b1 != e1)
    {
        *result++ = *b1++;
    }
    while (b2 != e2)
    {
        *result++ = *b2++;
    }
}
template<typename _Iter1, typename _Iter2, typename _OIter>
void merge(_Iter1 b1, _Iter1 e1, _Iter2 b2, _Iter2 e2, _OIter result, float beta = 0.5)
{
    typedef typename std::iterator_traits<_OIter>::value_type value_type;
    while (b1 != e1 && b2 != e2)
    {
        if (b1->first == b2->first)
        {
            *result++ = value_type(b1->first, b1->second * beta + b2->second * (1 - beta));
            ++b1;
            ++b2;
        }
        else if (b1->first < b2->first)
        {
            //            *result++ = *b1++;
            *result++ = value_type(b1->first, b1->second * beta);
            b1++;
        }
        else
        {
            //            *result++ = *b2++;
            *result++ = value_type(b2->first, b2->second * (1 - beta));
            b2++;
        }
    }
    while (b1 != e1)
    {
        //        *result++ = *b1++;
        *result++ = value_type(b1->first, b1->second * beta);
        b1++;
    }
    while (b2 != e2)
    {
        //        *result++ = *b2++;
        *result++ = value_type(b2->first, b2->second * (1 - beta));
        b2++;
    }
}

template<typename _Iter1, typename _Iter2, typename _OIter>
void merge2(_Iter1 b1, _Iter1 e1, _Iter2 b2, _Iter2 e2, _OIter result, float beta = 0.5)
{
    typedef typename std::iterator_traits<_OIter>::value_type value_type;
    while (b1 != e1 && b2 != e2)
    {
        if (b1->first == b2->first)
        {
            *result++ = value_type(b1->first, b1->second * beta + b2->second * (1 - beta));
            ++b1;
            ++b2;
        }
        else if (b1->first < b2->first)
        {
            //            *result++ = *b1++;
            *result++ = value_type(b1->first, b1->second * beta);
            b1++;
        }
        else
        {
            //            *result++ = *b2++;
            *result++ = value_type(b2->first, b2->second * (1 - beta));
            b2++;
        }
    }
    while (b1 != e1)
    {
        //        *result++ = *b1++;
        *result++ = value_type(b1->first, b1->second * beta);
        b1++;
    }
    while (b2 != e2)
    {
        //        *result++ = *b2++;
        *result++ = value_type(b2->first, b2->second * (1 - beta));
        b2++;
    }
}


template<typename _Iter, typename _OIter>
void divide(_Iter b, _Iter e, int divisor, _OIter result)
{
    typedef typename std::iterator_traits<_OIter>::value_type value_type;
    for (; b != e; ++b)
    {
        *result++ = value_type(b->first, b->second / divisor);
    }
}

//----------------------vec
/**
 * 注意都需要保证按照id排序
 */
template<typename _Type, typename _Vec>
_Type dot(const _Vec& vec1, const _Vec& vec2)
{
    _Type result = 0;
    for (size_t i = 0, j = 0; i < vec1.size() && j < vec2.size();)
    {
        if (vec1[i].first == vec2[j].first)
        {
            result += vec1[i].second * vec2[j].second;
            i++;
            j++;
        }
        else if (vec1[i].first < vec2[j].first)
        {
            i++;
        }
        else
        {
            j++;
        }
    }
    return result;
}
template<typename _Vec>
int intersect_num(const _Vec& vec1, const _Vec& vec2)
{
    int num = 0;
    for (size_t i = 0, j = 0; i < vec1.size() && j < vec2.size();)
    {
        if (vec1[i].first == vec2[j].first)
        {
            num++;
            i++;
            j++;
        }
        else if (vec1[i].first < vec2[j].first)
        {
            i++;
        }
        else
        {
            j++;
        }
    }
    return num;
}
template<typename _Vec>
int intersect(const _Vec& vec1, const _Vec& vec2, std::vector<int>& vec)
{
    vec.clear();
    for (size_t i = 0, j = 0; i < vec1.size() && j < vec2.size();)
    {
        if (vec1[i].first == vec2[j].first)
        {
            vec.push_back(vec1[i].first);
            i++;
            j++;
        }
        else if (vec1[i].first < vec2[j].first)
        {
            i++;
        }
        else
        {
            j++;
        }
    }
    return vec.size();
}
template<typename _Vec>
int intersect(const _Vec& vec1, const _Vec& vec2, std::vector<boost::tuple<int, float, float> >& vec)
{
    vec.clear();
    int num = 0;
    for (size_t i = 0, j = 0; i < vec1.size() && j < vec2.size();)
    {
        if (vec1[i].first == vec2[j].first)
        {
            num++;
            vec.push_back(boost::make_tuple(vec1[i].first, vec1[i].second, vec2[j].second));
            i++;
            j++;
        }
        else if (vec1[i].first < vec2[j].first)
        {
            i++;
        }
        else
        {
            j++;
        }
    }
    return num;
}

template<typename _Iter1, typename _Iter2>
int intersect(_Iter1 iter1, _Iter1 iter1_e, _Iter2 iter2, _Iter2 iter2_e, std::vector<int>& vec)
{
    while (iter1 != iter1_e && iter2 != iter2_e)
    {
        if (iter1->first == iter2->first)
        {
            vec.push_back(iter1->first);
            ++iter1;
            ++iter2;
        }
        else if (iter1->first < iter2->first)
        {
            ++iter1;
        }
        else
        {
            ++iter2;
        }
    }
    return vec.size();
}
template<typename _Iter1, typename _Iter2, typename _DP>
int intersect(_Iter1 iter1, _Iter1 iter1_e, _Iter2 iter2, _Iter2 iter2_e, std::vector<std::pair<int, _DP> >& vec)
{
    while (iter1 != iter1_e && iter2 != iter2_e)
    {
        if (iter1->first == iter2->first)
        {
            vec.push_back(std::make_pair(iter1->first, (iter1->second + iter2->second) / 2.0));
            ++iter1;
            ++iter2;
        }
        else if (iter1->first < iter2->first)
        {
            ++iter1;
        }
        else
        {
            ++iter2;
        }
    }
    return vec.size();
}

#endif  //----end of VEC_CALC_H_
