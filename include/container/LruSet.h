/**
 *  ==============================================================================
 *
 *          \file   LruSet.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-08-20 15:49:11.636115
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef LRU_SET_H_
#define LRU_SET_H_

#include "common_util.h"

namespace gezi {

//TODO both support set and unoredered_set
template<typename T>
class LruSet 
{
public:
	LruSet(int maxNum)
		:_maxNum(maxNum)
	{

	}

	LruSet()
	{

	}

	void set_capacity(int maxNum)
	{
		_maxNum = maxNum;
	}

	bool empty()
	{
		return _set.empty();
	}

	bool insert(const T& item)
	{ 
		auto iter = _set.find(item);
		if (iter == _set.end())
		{
			if (_set.size() == _maxNum)
			{
				T& oldItem = _queue.front();
				_set.erase(oldItem);
				_queue.pop_front();
			}
			_set.insert(iter, item);
			_queue.push_back(item);
			return true;
		}
		return false;
	}

	bool count(const T& item)
	{
		return _set.count(item);
	}

	int size()
	{
		return _set.size();
	}

	int capacity()
	{
		return _maxNum;
	}

protected:
private:
	unordered_set<T> _set;
	deque<T> _queue; 
	int _maxNum;
};

}  //----end of namespace gezi

#endif  //----end of LRU_SET_H_
