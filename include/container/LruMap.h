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

	//@TODO 其实目前不是Lru(最近最少使用) 是简单的淘汰最老的(最先进入的key) Lru算法需要在查询或更新key的时候
	//在queue里面找到这个key并且将它放置到队尾它后面的key位置都前移。 对于Lru的需求queue不是很合适 适合使用list map同时需要记录key->List pos or pointer  考虑如何泛化支持多种淘汰机制
	//这里的Lru表示泛化的淘汰吧 @TODO 可能命名为 FixedSizeMap 更合适
	template<typename _Key, typename _Value,
		template<class _Kty, class _Ty, typename...> class _Map = std::map>
	class LruMap
	{
	public:
		typedef _Key Key;
		typedef _Value Value;
		typedef _Map<Key, Value> Map;
		typedef deque<Key> Deque;
		typedef typename Map::iterator iterator;
		typedef typename Map::const_iterator const_iterator;

		LruMap()
		{

		}

		LruMap(size_t capacity)
			:_capacity(capacity)
		{
			if (_capacity < 1)
			{
				THROW("Capacity should not less than 1");
			}
		}

		LruMap(Map&& m, size_t capacity = 1024)
			:_capacity(capacity), _map(m)
		{
			for (auto& item : _map)
			{
				_queue.push_back(item.first);
			}

			if (_capacity < 1)
			{
				THROW("Capacity should not less than 1");
			}
		}

		void set_capacity(size_t capacity)
		{
			_capacity = capacity;
			if (_capacity < 1)
			{
				THROW("Capacity should not less than 1");
			}
		}

		//@TODO && support ?  不会更新
		pair<iterator, bool> insert(const pair<Key, Value>& node)
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
		bool insert(const Key& item, const Value& value)
		{
			auto iter = _map.find(item);
			if (iter == _map.end())
			{
				if (_map.size() == _capacity)
				{
					Key& oldestKey = _queue.front();
					_map.erase(oldestKey);
					_queue.pop_front();
				}
				_map[item] = value;
				_queue.push_back(item);
				return true;
			}
			iter->second = value;
			return false;
		}

		bool update(const Key& item, const Value& value)
		{
			auto iter = _map.find(item);
			if (iter == _map.end())
			{
				if (_map.size() == _capacity)
				{
					Key& oldestKey = _queue.front();
					_map.erase(oldestKey);
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

		const Value& operator [](const Key& item) const
		{
			return _map[item];
		}

		//@TODO better handle this 看一下map的源代码
		Value& operator [](const Key& key)
		{
			auto iter = _map.find(key);
			if (iter == _map.end())
			{
				if (_map.size() == _capacity)
				{
					Key& oldestKey = _queue.front();
					_map.erase(oldestKey);
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

		iterator find(const Key& key)
		{
			return _map.find(key);
		}

		const_iterator find(const Key& key) const
		{
			return _map.find(key);
		}

		//理想的做法是提供iterator对外接口 这样最灵活 性能更好 避免二次查询key @TODO
		Value& value(const Key& key, bool& find)
		{
			auto iter = _map.find(key);
			if (iter == _map.end())
			{
				if (_map.size() == _capacity)
				{
					Key& oldestKey = _queue.front();
					_map.erase(oldestKey);
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

		bool count(const Key& item)
		{
			return _map.count(item);
		}

		size_t size()
		{
			return _map.size();
		}

		//@FIXME　remove this and add begin end ..
		const Map& get_map() const
		{
			return _map;
		}

		Map& get_map()
		{
			return _map;
		}

		Deque& get_queue()
		{
			return _queue;
		}

		void clear()
		{
			_map.clear();
			_queue.clear();
		}

		iterator begin()
		{
			return _map.begin();
		}

		iterator end()
		{
			return _map.end();
		}

	protected:
	private:
		Map _map;
		Deque _queue;
		size_t _capacity = 1024;
	};


	template <typename Key, typename Value, typename...>
		using LruHashMap = LruMap<Key, Value, std::unordered_map>;

}  //----end of namespace gezi

#endif  //----end of LRU_MAP_H_
