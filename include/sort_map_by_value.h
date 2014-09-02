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
//#include <boost/bind.hpp>
#include <complex>      // std::complex, std::abs
#include <cmath>
#include "sort_util.h"

namespace gezi {
	/**如果map<string,int>注意使用的时候vector<pair<srring, int>>*/
	template<typename Map, typename Vec>
	void sort_map_by_value(Map& tmap, Vec& tvec)
	{
		tvec.clear();
		typedef typename Vec::value_type ValueType;
		std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
		std::sort(tvec.begin(), tvec.end(),CmpPairBySecond());
	}

	//@TODO 可否利用decltype 自动推导？
	/*template<typename Map, typename Vec>
	Vec void sort_map_by_value(Map& tmap)
	{
		Vec tvec;
		typedef typename Vec::value_type ValueType;
		std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
		std::sort(tvec.begin(), tvec.end(),
			std::bind(&ValueType::second, _1) <
			std::bind(&ValueType::second, _2));
		return tvec;
	}*/
	template<typename Map, typename Vec, typename Func>
	void sort_map_by_value(Map& tmap, Vec& tvec, Func func)
	{
		tvec.clear();
		typedef typename Vec::value_type ValueType;
		std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
		std::sort(tvec.begin(), tvec.end(), func);
	}
	template<typename Map, typename Vec>
	void sort_map_by_key(Map& tmap, Vec& tvec)
	{
		tvec.clear();
		typedef typename Vec::value_type ValueType;
		std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
		std::sort(tvec.begin(), tvec.end(), CmpPairByFirst());
	}

	//template<typename Map, typename Vec, typename Cmp>
	//void sortMapByValue(Map& tmap, Vec& tvec, Cmp cmp)
	//{
	//    typedef typename Vec::value_type ValueType;
	//    std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
	//    std::sort(tvec.begin(), tvec.end(),
	//              cmp(std::bind(&ValueType::second, _1),
	//              std::bind(&ValueType::second, _2)));
	//}
	template<typename Map, typename Vec>
	void sort_map_by_value_reverse(Map& tmap, Vec& tvec)
	{
		tvec.clear();
		typedef typename Vec::value_type ValueType;
		std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
		std::sort(tvec.begin(), tvec.end(), CmpPairBySecondReverse());
	}

	template<typename Map, typename Vec>
	void sort_map_by_absvalue_reverse(Map& tmap, Vec& tvec)
	{
		tvec.clear();
		typedef typename Vec::value_type ValueType;
		std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
		std::sort(tvec.begin(), tvec.end(),
			[](const ValueType& a, const ValueType&b) { return std::abs(a.second) > std::abs(b.second); });
	}

	/*template<typename Map>
	auto sort_map_by_value_reverse(Map& tmap) -> decltype(vector<pair<Map::key_type, Map::value_type> >)
	{
		
		typedef typename Map::value_type ValueType;
		std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
		std::sort(tvec.begin(), tvec.end(),
			std::bind(&ValueType::second, _1) >
			std::bind(&ValueType::second, _2));
		return tvec;
	}*/

	template<typename Map, typename Vec> 
	void patital_sort_map_by_value(Map& tmap, Vec& tvec, int n = 10)
	{
		tvec.clear();
		typedef typename Vec::value_type ValueType;
		std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
		std::partial_sort(tvec.begin(), tvec.begin() + n, tvec.end(), CmpPairBySecond());
	}
	template<typename Map, typename Vec>
	void patital_sort_map_by_value_reverse(Map& tmap, Vec& tvec, int n = 10)
	{
		tvec.clear();
		typedef typename Vec::value_type ValueType;
		std::copy(tmap.begin(), tmap.end(), std::back_inserter(tvec));
		std::partial_sort(tvec.begin(), tvec.begin() + n, tvec.end(), CmpPairBySecondReverse());
	}
} //end of namespace common_algorithm
#endif  //----end of SORT_MAP_BY_VALUE_H_
