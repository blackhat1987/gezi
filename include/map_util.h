/**
 *  ==============================================================================
 *
 *          \file   map_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-17 17:59:30.628000
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef MAP_UTIL_H_
#define MAP_UTIL_H_

#include "common_def.h"
namespace gezi {
	//-----------------map util

	//like map<string, vector<string> >
	//inline bool contains(string input, string part)
	//{
	//	return input.find(part) != string::npos;
	//}
	//@TODO 定义为contains fullposts.cc里面使用gezi::contains("","")仍然没有匹配上面的而是尝试匹配下面这个map的。。比较弱智，所以带模板的function
	//名字命名长一点。。
	//template<typename Map>
	//inline bool contains(Map* history, string name)
	//{
	//	return history && history->count(name) && (*history)[name].size() > 0;
	//}

	//template<typename Map>
	//inline bool contains(Map& history, string name)
	//{
	//	return contains(&history, name);
	//}

	template<typename Map>
	inline bool map_contains(Map* history, string name)
	{
		return history && history->count(name) && ((*history)[name]).size() > 0;
	}

	template<typename Map>
	inline bool map_contains(Map& history, string name)
	{
		return map_contains(&history, name);
	}

	template<typename Map>
	inline int length(Map* history, string name)
	{
		if (!history || !history->count(name))
		{
			return -1;
		}

		return (*history)[name].size();
	}

	template<typename Map>
	inline int length(Map& history, string name)
	{
		return length(&history, name);
	}

	template<typename Map, typename T>
	void add_one(Map& map, T name, int count = 1)
	{
		auto iter = map.find(name);
		if (iter == map.end())
		{
			map[name] = count;
		}
		else
		{
			iter->second += count;
		}
	}

	template<typename Map, typename T, typename U>
	void add_value(Map& map, T name, U value)
	{
		auto iter = map.find(name);
		if (iter == map.end())
		{
			map[name] = value;
		}
		else
		{
			iter->second += value;
		}
	}

	template<typename ValueType, typename KeyType, typename Map>
	ValueType get_value(const Map& m, KeyType key, const ValueType& default_value)
	{
		auto iter = m.find(key);
		if (iter != m.end())
		{
			return iter->second;
		}
		return default_value;
	}

	template<typename ValueType, typename KeyType, typename Map, typename Func>
	ValueType get_value(const Map& m, KeyType key, Func func, const ValueType& default_value)
	{
		auto iter = m.find(key);
		if (iter != m.end())
		{
			return func(iter->second);
		}
		return default_value;
	}

	template<typename ValueType, typename KeyType, typename Map>
	bool try_add(Map& m, KeyType key, ValueType value)
	{
		if (m.find(key) != m.end())
		{
			m[key] = value;
			return true;
		}
		return false;
	}


	template<typename _Map>
	void print_enum_map(const _Map& m)
	{
		for (auto item : m)
		{
			std::cout << setiosflags(ios::left) << setfill(' ') << setw(40)
				<< item.first << " " << (int)item.second << std::endl;
		}
	}
	template<typename _Map>
	void print_map(const _Map& m)
	{
		for (auto item : m)
		{
			std::cout << setiosflags(ios::left) << setfill(' ') << setw(40)
				<< item.first << " " << item.second << std::endl;
		}
	}
}  //----end of namespace gezi

#endif  //----end of MAP_UTIL_H_
