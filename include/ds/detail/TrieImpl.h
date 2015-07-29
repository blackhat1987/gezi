/**
 *  ==============================================================================
 *
 *          \file   detail/TrieImpl.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-07-26 15:04:00.063718
 *
 *  \Description:  模仿std::map std::set接口 但是当前并不提供iterator支持
 *                 另外与map的区别是find返回的iterator 只是mapped的指针，因为内部key,mapped分开存储 没有类似vector<pair<key,mapped> >这样的存储
 *                 trie树的主要功能是前缀查询,特别是查询中间状态的支持
 *                 @TODO 针对中文短串的特定优化 比如第一层hash是否可以直接o(1)索引
 *  ==============================================================================
 */


#include <ds/traits.h> 
#include "map_util.h"
#include "vector_def.h"
#include "common_def.h"
#include "serialize_util.h"
#include "ds/traits.h"

namespace gezi {
#ifdef GEZI_DATA_TRUE_INDICATOR
#define GEZI_TRIE_NAME Trie
#endif

#ifdef GEZI_DATA_FALSE_INDICATOR
#define GEZI_TRIE_NAME TrieSet_
#endif

	template<typename Key,
		typename Mapped,
		template<class _Kty, class _Ty, typename...> class _Map = std::unordered_map>
	class GEZI_TRIE_NAME
	{
	public:
		typedef Key key_type;
		typedef Mapped mapped_type;
		typedef typename key_mapped_traits<Key, Mapped>::value_type value_type;
		typedef typename key_mapped_traits<Key, Mapped>::iterator iterator;
		typedef typename key_mapped_traits<Key, Mapped>::const_iterator const_iterator;

		typedef typename key_type::value_type char_type;
		typedef typename key_mapped_traits<Key, Mapped>::index_type index_type;
		typedef size_t size_type;


		///这里指针没有NULL的情况，利用map.empty()来表示空,使用指针NULL可以节约一点内存，不过利用map empty代码更加方便
		struct Node;
		///这里如果不使用指针map是可以的但是使用unorderd_map gcc4会报错  error: 'std::pair<_T1, _T2>::second' has incomplete type
		typedef _Map<char_type, unique_ptr<Node> > Map;
		//@TODO 先对比下空map和指针大小区别
		//check一下 Map* next的写法 

		enum
		{
#ifdef GEZI_DATA_TRUE_INDICATOR
			null_index = -1,
#else
			null_index = 0,
#endif
		};

		struct Node
		{
			index_type index = null_index;  ///null_index用来表示内部节点
			unique_ptr<Map> next;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & index;
				ar & next;
			}
		};


		pair<iterator, bool> insert(const value_type& value)
		{
			Node* pnode = insert_key(GEZI_V2F(value));
			bool isNewKey = (pnode->index == null_index);
#ifdef  GEZI_DATA_TRUE_INDICATOR
			pnode->index = (index_type)_mappedVec.size();
			_mappedVec.push_back(GEZI_V2S(value));
			return make_pair(&_mappedVec[pnode->index], isNewKey);
#else
			pnode->index = true;
			return make_pair<void*, bool>((void*)NULL, (bool)isNewKey); //@TODO why need... bool again
#endif
		}

#ifdef GEZI_DATA_TRUE_INDICATOR
		/**
		* @brief 只是map使用
		* @param key:
		* @param mapped:
		* @return (pair<iterator, bool>):
		*/
		pair<iterator, bool> insert(const key_type& key, const mapped_type& mapped)
		{
			Node* pnode = insert_key(key);
			if (pnode->index == null_index)
			{
				pnode->index = (index_type)_mappedVec.size();
				_mappedVec.push_back(mapped);
				return make_pair(&_mappedVec[pnode->index], true);
			}
			return make_pair(&_mappedVec[pnode->index], false);
		}

		mapped_type& operator[](const key_type& key)
		{
			Node* pnode = insert_key(key);
			if (pnode->index == null_index)
			{
				pnode->index = (index_type)_mappedVec.size();
				_mappedVec.push_back(mapped_type());
				return _mappedVec.back();
			}
			else
			{
				return _mappedVec[pnode->index];
			}
		}
#endif

		size_type count(const key_type& key) const
		{
			Node* pnode = &_root;
			for (auto& ch : key)
			{
				Map& m = pnode->next;
				auto iter = m.find(ch);
				if (iter == m.end())
				{
					return 0;
				}
				pnode = (iter->second).get();
			}
			return (size_type)(pnode->index != null_index);
		}

		size_type prefix_count(const key_type& key) const
		{
			const Node* pnode = &_root;
			for (auto& ch : key)
			{
				const Map& m = pnode->next;
				auto iter = m.find(ch);
				if (iter == m.end())
				{
					return 0;
				}
				pnode = (iter->second).get();
			}
			return count(pnode);
		}

		bool empty() const
		{
			return (_root.next).empty();
		}

		bool search(const key_type& key) const
		{
			const Node* pnode = &_root;
			for (auto& ch : key)
			{
				const Map& m = pnode->next;
				auto iter = m.find(ch);
				if (iter == m.end())
				{
					return false;
				}
				pnode = (iter->second).get();
			}
			return pnode->index != null_index;
		}

		bool prefix_search(const key_type& key) const
		{
			const Node* pnode = &_root;
			for (auto& ch : key)
			{
				const Map& m = pnode->next;
				auto iter = m.find(ch);
				if (iter == m.end())
				{
					return false;
				}
				pnode = (iter->second).get();
			}
			return true;
		}


		const Node* root() const 
		{
			return &_root;
		}

		static const Node* find(const Node* pnode, const key_type& key) const
		{
			return NULL;
		}

		iterator end() const
		{
			return NULL;
		}

		iterator find(const key_type& key)
		{
			Node* pnode = &_root;
			for (auto& ch : key)
			{
				Map& m = pnode->next;
				auto iter = m.find(ch);
				if (iter == m.end())
				{
					return NULL;
				}
				pnode = (iter->second).get();
			}

			if (pnode->index != null_index)
			{
#ifdef GEZI_DATA_TRUE_INDICATOR
				return &_mappedVec[pnode->index];
#else 
				return (void*)1;
#endif
			}
			else
			{
				return NULL;
			}
		}

		const_iterator find(const key_type& key) const
		{
			const Node* pnode = &_root;
			for (auto& ch : key)
			{
				const Map& m = pnode->next;
				auto iter = m.find(ch);
				if (iter == m.end())
				{
					return NULL;
				}
				pnode = (iter->second).get();
			}

			if (pnode->index != null_index)
			{
#ifdef GEZI_DATA_TRUE_INDICATOR
				return &_mappedVec[pnode->index];
#else 
				return (void*)1;
#endif
			}
			else
			{
				return NULL;
			}
		}

		/**
		* @brief 计算某个节点下面的子串总数
		*				 注意不检查空,默认没有NULL
		*/
		size_type count(const Node* pnode) const
		{
			const auto& m = pnode->next;
			size_type numStrs = pnode->index != null_index;
			for (auto& item : m)
			{
				numStrs += count((item.second).get());
			}
			return numStrs;
		}

		/**
		* @brief  总的串数目
		*/
		size_type size() const
		{
			const auto& m = _root.next;
			size_type numStrs = 0;
			for (auto& item : m)
			{
				numStrs += count((item.second).get());
			}
			return numStrs;
		}

		void print() const
		{
			key_type key;
			print(&_root, key);
		}

		void print(const Node* pnode, key_type key) const
		{
			if (pnode->index != null_index)
			{
				cout << key << endl;
			}
			for (const auto& item : pnode->next)
			{
				key_type key2 = key;
				key2.push_back(item.first);
				print(item.second.get(), key2);
			}
		}

	protected:
		Node* insert_key(const key_type& key)
		{
			Node* pnode = &_root;
			for (auto& ch : key)
			{
				Map& m = pnode->next;
				auto iter = m.find(ch);
				if (iter == m.end())
				{
					iter = m.insert(iter, make_pair(ch, make_unique<Node>()));
				}
				pnode = (iter->second).get();
			}
			return pnode;
		}

	private:
		Node _root;
#ifdef GEZI_DATA_TRUE_INDICATOR
		vector<mapped_type> _mappedVec;
#endif

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			ar & _root;
#ifdef GEZI_DATA_TRUE_INDICATOR
			ar & _mappedVec;
#endif
		}
	};

#ifdef GEZI_DATA_FALSE_INDICATOR
	template <typename Key,
		typename Mapped = null_type,
		template<class _Kty, class _Ty, typename...> class _Map = std::unordered_map>
	using TrieSet = TrieSet_ < Key, Mapped, _Map > ;
#endif

}  //----end of namespace gezi

//CEREAL_REGISTER_TYPE(gezi::GEZI_TRIE_NAME::Node);
#undef GEZI_TRIE_NAME