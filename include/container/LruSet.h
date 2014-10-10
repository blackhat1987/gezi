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

	template<typename Key, template<class _Kty, typename...> class _Set = std::set>
	class LruSet
	{
	public:
		typedef _Set<Key> Set;
		LruSet(int maxNum)
			:_capacity(maxNum)
		{

		}

		LruSet()
		{

		}

		void set_capacity(int maxNum)
		{
			_capacity = maxNum;
		}

		bool empty() const
		{
			return _set.empty();
		}

		bool insert(const Key& item)
		{
			auto iter = _set.find(item);
			if (iter == _set.end())
			{
				if (_set.size() == _capacity)
				{
					Key& oldItem = _queue.front();
					_set.erase(oldItem);
					_queue.pop_front();
				}
				_set.insert(iter, item);
				_queue.push_back(item);
				return true;
			}
			return false;
		}

		bool count(const Key& item) const
		{
			return _set.count(item);
		}

		int size() const
		{
			return _set.size();
		}

		int capacity() const
		{
			return _capacity;
		}

	protected:
	private:
		Set _set;
		deque<Key> _queue;
		int _capacity;
	};
	template <typename Key, typename...>
	using LruHashSet = LruSet<Key, std::unordered_set>;
}  //----end of namespace gezi

#endif  //----end of LRU_SET_H_
