/**
 *  ==============================================================================
 *
 *          \file   CachedFetcher.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-02 11:23:38.764028
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef CACHED_FETCHER_H_
#define CACHED_FETCHER_H_

#include "common_util.h"

namespace gezi {

	template<typename _Key, typename _Value,
		template<class _Kty, class _Ty, typename...> class _Map = std::unordered_map>
	class CachedFetcher
	{
	public:
		typedef _Key Key;
		typedef _Value Value;
		typedef _Map<Key, Value> Map;
		typedef typename Map::iterator iterator;
		typedef typename Map::const_iterator const_iterator;
	public:
		CachedFetcher()
		{

		}

		//普通map不支持设定大小 LruMap才支持设置最大容量
		CachedFetcher(int capacity)
		{
			_map.set_capacity(capacity);
		}

		void set_capacity(int capacity)
		{
			_map.set_capacity(capacity);
		}

		void SetCapacity(int capacity)
		{
			_map.set_capacity(capacity);
		}

		template<typename Func>
		Value GetValue(const Key& key, Func func)
		{
			const_iterator iter = _map.find(key);
			if (iter != _map.end())
			{
				return iter->second;
			}
			else
			{//func如果错误需要内部自己抛出异常 不进行后续动作
				Value value = func(key);
#pragma  omp critical
				{
					_map[key] = value;
				}
				return value;
			}
		}

		//类似sort 采用template写法　template<typename Fun>  Func func 也完全ok似乎 类似sort也可以最后是普通函数
		//@TODO 到底哪种写法更好? 效率一样？ 
		//注意返回结果可能少于keys另外顺序完全不保证
		//vector<Value> GetValues(const vector<Key>& keys, std::function<vector<Value>(const vector<Key>&)> func)
		template<typename Func>
		vector<Value> GetValues(const vector<Key>& keys, Func func)
		{
			vector<Value> values;
			vector<Key> fetchKeys;
			for (const Key& key : keys)
			{
				const_iterator	iter = _map.find(key); //@TODO check if really thread safe for const
				if (iter != _map.end())
				{
					values.push_back(iter->second);
				}
				else
				{
					fetchKeys.push_back(key);
				}
			}
			{ //func需要确保传回value数组temp长度和输入fetchKeys长度相同
				vector<Value> tempVec = func(fetchKeys);
				//func如果错误需要内部自己抛出异常 不进行后续动作
#pragma omp critical 
				{
					for (size_t i = 0; i < tempVec.size(); i++)
					{
						_map[fetchKeys[i]] = tempVec[i];
					}
				}
				merge(values, tempVec);
			}
			return values;
		}

		template<typename Func>
		map<Key, Value> GetValuesMap(const vector<Key>& keys, Func func)
		{
			map<Key, Value> valuesMap;
			vector<Key> fetchKeys;
			for (const Key& key : keys)
			{
				const_iterator iter = _map.find(key); //@TODO check thread safe
				if (iter != _map.end())
				{
					valuesMap[key] = iter->second;
				}
				else
				{
					fetchKeys.push_back(key);
				}
			}
			{ //func需要确保传回value数组temp长度和输入fetchKeys长度相同
				map<Key, Value> tempMap = func(fetchKeys);
				//func如果错误需要内部自己抛出异常 不进行后续动作
#pragma omp critical 
				{
					for (auto& item : tempMap)
					{
						_map[item->first] = tempMap[item->second];
					}
				}
				merge(valuesMap, tempMap);
			}
			return valuesMap;
		}

		Map& GetMap()
		{
			return _map;
		}

		void ClearCache()
		{
			_map.clear();
		}

		int CacheSize() const
		{
			return _map.size();
		}

	protected:
	private:
		Map _map;
	};

}  //----end of namespace gezi

#endif  //----end of CACHED_FETCHER_H_
