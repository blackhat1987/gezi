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

	//@TODO ��ʵĿǰ����Lru(�������ʹ��) �Ǽ򵥵���̭���ϵ�(���Ƚ����key) Lru�㷨��Ҫ�ڲ�ѯ�����key��ʱ��
	//��queue�����ҵ����key���ҽ������õ���β�������keyλ�ö�ǰ�ơ� ����Lru������queue���Ǻܺ��� �ʺ�ʹ��list mapͬʱ��Ҫ��¼key->List pos or pointer  ������η���֧�ֶ�����̭����
	//�����Lru��ʾ��������̭�� @TODO ��������Ϊ FixedSizeMap ������
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

		//@TODO && support ?  �������
		pair<iterator, bool> insert(const pair<Key, Value>& node)
		{
			auto iter = _map.find(node.first);
			if (iter == _map.end())
			{
				//��ô�����죿��һ��find... map�ڲ���ô���ģ�
				_map[node.first] = node.second;
				return make_pair(iter, true);
			}
			else
			{
				return make_pair(iter, false);
			}
		}

		//����¡���
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

		//@TODO better handle this ��һ��map��Դ����
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
				//@FIXME  ����find���� mapԴ����ô���ģ� ���ڷ���ֵ ������ ������ֵ m[key] = value ��α�������
				//find�� 
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

		//������������ṩiterator����ӿ� ��������� ���ܸ��� ������β�ѯkey @TODO
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

		//@FIXME��remove this and add begin end ..
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
