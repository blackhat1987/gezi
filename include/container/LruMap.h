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

	LruMap()
	{

	}

	void set_capacity(int maxNum)
	{
		_maxNum = maxNum;
	}
	typedef typename unordered_map<T, U>::iterator iterator;
	//@TODO && support ?  不会更新
	pair<iterator,bool> insert(const pair<T,U>& node)
	{
		auto iter = _map.find(node.first);
		if (iter == _map.end())
		{
			//怎么做更快？又一次find... map内部怎么做的？
			_map[node.first] = node.second;
			return make_pair(iter, true);
		}
		else
		{
			return make_pair(iter, false);
		}
	}

	//会更新。。
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

	bool update(const T& item, const U& value)
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
		if (iter->second == value)
		{
			return false;
		}
		else
		{
			iter->second = value;
			return true;
		}
	}

	bool empty()
	{
		return _map.empty();
	}
	
	const U& operator [](const T& item) const
	{
		return _map[item];
	}

	//@TODO better handle this 看一下map的源代码
	U& operator [](const T& key)
	{
		auto iter = _map.find(key);
		if (iter == _map.end())
		{
			if (_map.size() == _maxNum)
			{
				T& oldItem = _queue.front();
				_map.erase(oldItem);
				_queue.pop_front();
			}
			//@FIXME  两次find等于 map源码怎么做的？ 存在返回值 不存在 插入新值 m[key] = value 如何避免两次
			//find？ 
			auto& val = _map[key]; 
			_queue.push_back(key);
			return val;
		}
		else
		{
			return iter->second;
		}
	}
	//理想的做法是提供iterator对外接口 这样最灵活 性能更好 避免二次查询key @TODO
	U& value(const T& key, bool& find)
	{
		auto iter = _map.find(key);
		if (iter == _map.end())
		{
			if (_map.size() == _maxNum)
			{
				T& oldItem = _queue.front();
				_map.erase(oldItem);
				_queue.pop_front();
			}
			auto& val = _map[key]; //@FIXME
			_queue.push_back(key);
			find = false;
			return val;
		}
		else
		{
			find = true;
			return iter->second;
		}
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
	const unordered_map<T, U>& get_map() const
	{
		return _map;
	}

	unordered_map<T, U>& get_map() 
	{
		return _map;
	}


	deque<T>& get_queue() 
	{
		return _queue;
	}

	void clear()
	{
		_map.clear();
		_queue.clear();
	}

protected:
private:
	unordered_map<T, U> _map;
	deque<T> _queue; 
	int _maxNum;
};

}  //----end of namespace gezi

#endif  //----end of LRU_MAP_H_
