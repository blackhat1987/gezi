/**
 *  ==============================================================================
 *
 *          \file   LruMap.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-08-20 15:49:11.636115
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef LRU_MAP_H_
#define LRU_AMP_H_

#include "common_util.h"

namespace gezi {

//TODO both support set and unoredered_set
template<typename T, typename U>
class LruMap
{
public:
	LruMap(int maxNum)
		:_maxNum(maxNum)
	{

	}

	bool insert(const T& item, const U& value)
	{ 
		auto iter = _map.find(item);
		if (iter == _map.end())
		{
			if (_map.size() == _maxNum)
			{
				T& oldItem = _queue.front();
				_map.erase(oldItem);
				_queue.pop_front();
			}
			_map[item] = value;
			_queue.push_back(item);
			return true;
		}
		iter->second = value;
		return false;
	}

	bool empty()
	{
		return _map.empty();
	}
	//@TODO better handle this 看一下map的源代码
	U& operator [](const T& item) 
	{
		auto iter = _map.find(item);
		if (iter == _map.end())
		{
			if (_map.size() == _maxNum)
			{
				T& oldItem = _queue.front();
				_map.erase(oldItem);
				_queue.pop_front();
			}
			_map[item] = 0; //@FIXME
			_queue.push_back(item);
		}
		return _map[item];
	}

	const U& operator [](const T& item) const
	{
		return _map[item];
	}

	bool count(const T& item)
	{
		return _map.count(item);
	}

	int size()
	{
		return _map.size();
	}

	//@FIXME　remove this and add begin end ..
	const map<T, U>& get_map() const
	{
		return _map;
	}

protected:
private:
	map<T, U> _map;
	deque<T> _queue; 
	int _maxNum;
};

}  //----end of namespace gezi

#endif  //----end of LRU_MAP_H_
