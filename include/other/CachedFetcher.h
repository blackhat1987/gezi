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

	template<typename Key, typename Value, 
		template<class _Kty,
	class _Ty,
	class _Pr = less<_Kty>,
	class _Alloc = allocator<pair<const _Kty, _Ty> > > class _Map = std::map>
	class CachedFetcher
	{
	public:
		typedef _Map<Key, Value> Map;
	public:
		
		Value GetValue(const Key& key, std::function<vector<Value>(const vector<Key>&)> func)
		{
			auto iter = _map.find(key);
			if (iter != _map.end())
			{
				return iter->second;
			}
			else
			{//func如果错误需要内部自己抛出异常 不进行后续动作
				Value value = func(key);
				_map[key] = value;
				return value;
			}
		}

		vector<Value> GetValues(const vector<Key>& keys, std::function<vector<Value>(const vector<Key>&)> func)
		{
			vector<Value> values;
			vector<Key> fetchKeys;
			for (const Key& key : keys)
			{
				auto iter = _map.find(key);
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
				for (size_t i = 0; i < tempVec.size(); i++)
				{
					_map[fetchKeys[i]] = tempVec[i];
				}
				merge(values, tempVec);
			}
			return values;
		}

		Map& GetMap()
		{
			return _map;
		}

		void ClearCache()
		{
			_map.clear();
		}

		int CacheSize()
		{
			return _map.size();
		}

	protected:
	private:
		Map _map;
	};

}  //----end of namespace gezi

#endif  //----end of CACHED_FETCHER_H_
