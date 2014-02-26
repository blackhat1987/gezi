/** 
 *  ==============================================================================
 * 
 *          \file   sort_map_by_value.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-10-16 21:56:30.175069
 *  
 *  \Description:   对map用一个vector接过来按照值排序
 *  ==============================================================================
 */

#ifndef SORT_MAP_BY_VALUE_H_
#define SORT_MAP_BY_VALUE_H_
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <boost/bind.hpp>
namespace std2 {
/**如果map<string,int>注意使用的时候vector<pair<srring, int>>*/
template<typename Map, typename Vec>
void sortMapByValue(Map& tmap, Vec& tvec)
{
    tvec.clear();
    typedef typename Vec::value_type ValueType;
    std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
    std::sort(tvec.begin(), tvec.end(),
            boost::bind(&ValueType::second, _1) <
            boost::bind(&ValueType::second, _2));
}
template<typename Map, typename Vec, typename Func>
void sortMapByValue(Map& tmap, Vec& tvec, Func func)
{
    tvec.clear();
    typedef typename Vec::value_type ValueType;
    std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
    std::sort(tvec.begin(), tvec.end(), func);
}
template<typename Map, typename Vec>
void sortMapByID(Map& tmap, Vec& tvec)
{
    tvec.clear();
    typedef typename Vec::value_type ValueType;
    std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
    std::sort(tvec.begin(), tvec.end(),
            boost::bind(&ValueType::first, _1) <
            boost::bind(&ValueType::first, _2));
}

//template<typename Map, typename Vec, typename Cmp>
//void sortMapByValue(Map& tmap, Vec& tvec, Cmp cmp)
//{
//    typedef typename Vec::value_type ValueType;
//    std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
//    std::sort(tvec.begin(), tvec.end(),
//              cmp(boost::bind(&ValueType::second, _1),
//              boost::bind(&ValueType::second, _2)));
//}
template<typename Map, typename Vec>
void sortMapByValue_reverse(Map& tmap, Vec& tvec)
{
    tvec.clear();
    typedef typename Vec::value_type ValueType;
    std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
    std::sort(tvec.begin(), tvec.end(),
            boost::bind(&ValueType::second, _1) >
            boost::bind(&ValueType::second, _2));
}
template<typename Map, typename Vec>
void patitalSortMapByValue(Map& tmap, Vec& tvec, int n = 10)
{
    tvec.clear();
    typedef typename Vec::value_type ValueType;
    std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
    std::partial_sort(tvec.begin(), tvec.begin() + n, tvec.end(),
            boost::bind(&ValueType::second, _1) <
            boost::bind(&ValueType::second, _2));
}
template<typename Map, typename Vec>
void patitalSortMapByValue_reverse(Map& tmap, Vec& tvec, int n = 10)
{
    tvec.clear();
    typedef typename Vec::value_type ValueType;
    std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
    std::partial_sort(tvec.begin(), tvec.begin() + n, tvec.end(),
            boost::bind(&ValueType::second, _1) >
            boost::bind(&ValueType::second, _2));
}
} //end of namespace common_algorithm
#endif  //----end of SORT_MAP_BY_VALUE_H_
