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
 *                 具体使用的时候参考test_trie.cc  Trie<string, int> 一般意义的支持任意mapped_type的的Trie, TrieSet<string> 一般意义的TrieSet
 *                 TrieDict<string> mapped_type是int 同时index就是表示存储的value,类似 Identifer 适用于Key Id的存储
 *                 相比Trie占用更少内存，但是如果mapped_type是占用更大内存uint64等等，由于内部节点较多可能占用更多内存
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
#ifndef GEZI_TRIE_INDEX_IS_VALUE
#define GEZI_TRIE_NAME Trie
#else 
#define  GEZI_TRIE_NAME TrieDict_
#endif 
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
#ifndef GEZI_TRIE_INDEX_IS_VALUE
		typedef typename key_mapped_traits<Key, Mapped>::index_type index_type;
#else 
		typedef mapped_type index_type;
#endif
		typedef size_t size_type;


		///这里指针没有NULL的情况，利用map.empty()来表示空,使用指针NULL可以节约一点内存，不过利用map empty代码更加方便
		struct Node;
		typedef unique_ptr<Node> NodePtr;
		///这里如果不使用指针map是可以的但是使用unorderd_map gcc4会报错  error: 'std::pair<_T1, _T2>::second' has incomplete type
		//这里为了支持unordered_map至少要有一个指针next 或者 这里的Node,为了使用uniqe ptr方便 这里Node不再使用指针
		//这个写法类似sunpinyin 而在SuffixTree中都使用了指针,使用指针占用的空间会少一点点但是不多 只是少一个index_type的空间，这里不用裸指针，使用unique ptr希望能方便序列化
		//SuffixTree一般没有序列化需求,因此使用裸指针
		//而为了使用unique ptr方便 这里使用Node 而不是指针 否则不太方便，访问也复杂一些
		typedef _Map<char_type, Node > Map;
		typedef unique_ptr<Map> MapPtr;

		enum
		{
#ifdef GEZI_DATA_TRUE_INDICATOR
			null_index = -1,  //@TODO uint32怎么定义null?
#else
			null_index = 0,
#endif
		};

		struct Node
		{
			index_type index = null_index;  ///null_index用来表示内部节点,如果没有用Node* 那么多一个index_type的占用空间 对于叶子节点 @TODO 暂时不考虑这个了
			//MapPtr next = nullptr; //@FIXME this will complie error 
			//.. / .. / .. / .. / .. / .. / .. / app / search / sep / anti - spam / gezi / include / ds / detail / TrieImpl.h: In constructor 'constexpr gezi::Trie<std::basic_string<char>, int>::Node::Node()' :
			//	.. / .. / .. / .. / .. / .. / .. / app / search / sep / anti - spam / gezi / include / ds / detail / TrieImpl.h : 73 : 10 : error : conversion from 'std::nullptr_t' to non - scalar type 'std::unique_ptr<std::unordered_map<char, gezi::Trie<std::basic_string<char>, int>::Node>, std::default_delete<std::unordered_map<char, gezi::Trie<std::basic_string<char>, int>::Node> > >' requested
			//struct Node
			MapPtr next;
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
#ifndef GEZI_TRIE_INDEX_IS_VALUE
			pnode->index = (index_type)_mappedVec.size();
			_mappedVec.push_back(GEZI_V2S(value));
			return make_pair(&_mappedVec[pnode->index], isNewKey);
#else 
			pnode->index = GEZI_V2F(value); //@TODO pnode->id = value ?
			return make_pair(&pnode->index, isNewKey);
#endif
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
#ifndef GEZI_TRIE_INDEX_IS_VALUE
				pnode->index = (index_type)_mappedVec.size();
				_mappedVec.push_back(mapped);
				return make_pair(&_mappedVec[pnode->index], true);
#else 
				pnode->index = mapped;
				return make_pair(&pnode->index, true);
#endif
			}
#ifndef GEZI_TRIE_INDEX_IS_VALUE
			return make_pair(&_mappedVec[pnode->index], false);
#else 
			return make_pair(&pnode->index, false);
#endif
		}

		pair<iterator, bool> insert(const key_type& key, mapped_type&& mapped)
		{
			Node* pnode = insert_key(key);
			if (pnode->index == null_index)
			{
#ifndef GEZI_TRIE_INDEX_IS_VALUE
				pnode->index = (index_type)_mappedVec.size();
				_mappedVec.emplace_back(mapped);
				return make_pair(&_mappedVec[pnode->index], true);
#else 
				pnode->index = mapped;
				return make_pair(&pnode->index, true);
#endif
			}
#ifndef GEZI_TRIE_INDEX_IS_VALUE
			return make_pair(&_mappedVec[pnode->index], false);
#else 
			return make_pair(&pnode->index, false);
#endif
		}

		mapped_type& operator[](const key_type& key)
		{
			Node* pnode = insert_key(key);
			if (pnode->index == null_index)
			{
#ifndef GEZI_TRIE_INDEX_IS_VALUE
				pnode->index = (index_type)_mappedVec.size();
				_mappedVec.push_back(mapped_type());
				return _mappedVec.back();
#else 
				return pnode->index;
#endif
			}
			else
			{
#ifndef GEZI_TRIE_INDEX_IS_VALUE
				return _mappedVec[pnode->index];
#else 
				return pnode->index;
#endif
			}
		}
#endif

		size_type count(const key_type& key) const
		{
			const Node* pnode = &_root;
			for (auto& ch : key)
			{
				if (!pnode->next)
				{
					return 0;
				}
				else
				{
					const Map& m = *pnode->next;
					auto iter = m.find(ch);
					if (iter == m.end())
					{
						return 0;
					}
					pnode = &(iter->second);
				}
			}
			return (size_type)(pnode->index != null_index);
		}

		size_type prefix_count(const key_type& key) const
		{
			const Node* pnode = &_root;
			for (auto& ch : key)
			{
				if (!pnode->next)
				{
					return 0;
				}
				else
				{
					const Map& m = *pnode->next;
					auto iter = m.find(ch);
					if (iter == m.end())
					{
						return 0;
					}
					pnode = &(iter->second);
				}
			}
			return count(pnode);
		}

		bool empty() const
		{
			return !_root.next;
		}

		bool search(const key_type& key) const
		{
			const Node* pnode = &_root;
			for (auto& ch : key)
			{
				if (!pnode->next)
				{
					return false;
				}
				else
				{
					const Map& m = *pnode->next;
					auto iter = m.find(ch);
					if (iter == m.end())
					{
						return false;
					}
					pnode = &(iter->second);
				}
			}
			return pnode->index != null_index;
		}

		bool prefix_search(const key_type& key) const
		{
			const Node* pnode = &_root;
			for (auto& ch : key)
			{
				if (!pnode->next)
				{
					return false;
				}
				else
				{
					const Map& m = *pnode->next;
					auto iter = m.find(ch);
					if (iter == m.end())
					{
						return false;
					}
					pnode = &(iter->second);
				}
			}
			return true;
		}


		const Node* root() const
		{
			return &_root;
		}

		/////@TODO
		static const Node* find(const Node* pnode, const key_type& key)
		{
			for (auto& ch : key)
			{
				if (!pnode->next)
				{
					return NULL;
				}
				else
				{
					const Map& m = *pnode->next;
					const auto iter = m.find(ch);
					if (iter == m.end())
					{
						return NULL;
					}
					pnode = &(iter->second);
				}
			}
			return pnode;
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
				if (!pnode->next)
				{
					return NULL;
				}
				else
				{
					Map& m = *pnode->next;
					auto iter = m.find(ch);
					if (iter == m.end())
					{
						return NULL;
					}
					pnode = &(iter->second);
				}
			}

			if (pnode->index != null_index)
			{
#ifdef GEZI_DATA_TRUE_INDICATOR
#ifndef GEZI_TRIE_INDEX_IS_VALUE
				return &_mappedVec[pnode->index];
#endif
				return &pnode->index;
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
				if (!pnode->next)
				{
					return NULL;
				}
				else
				{
					const Map& m = *pnode->next;
					const auto iter = m.find(ch);
					if (iter == m.end())
					{
						return NULL;
					}
					pnode = &(iter->second);
				}
			}

			if (pnode->index != null_index)
			{
#ifdef GEZI_DATA_TRUE_INDICATOR
#ifndef GEZI_TRIE_INDEX_IS_VALUE
				return &_mappedVec[pnode->index];
#else
				return &pnode->index;
#endif
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
			size_type numStrs = pnode->index != null_index;
			if (pnode->next)
			{
				const auto& m = *pnode->next;
				for (auto& item : m)
				{
					numStrs += count(&item.second);
				}
			}
			return numStrs;
		}

		/**
		* @brief  总的串数目
		*/
		size_type size() const
		{
			size_type numStrs = 0;
			if (_root.next)
			{
				const auto& m = *_root.next;
				for (auto& item : m)
				{
					numStrs += count(&item.second);
				}
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
			if (pnode->next)
			{
				for (const auto& item : *(pnode->next))
				{
					key_type key2 = key;
					key2.push_back(item.first);
					print(&item.second, key2);
				}
			}
		}

	protected:
		Node* insert_key(const key_type& key)
		{
			Node* pnode = &_root;
			for (auto& ch : key)
			{
				//if (!pnode->next)
				//{
				//	//pnode->next = make_unique<Map>({ch, Node()}); //@TDO
				//	pnode->next = make_unique<Map>();
				//	pnode->next->emplace(ch, Node());
				//}
				//else
				//{
				if (!pnode->next)
				{
					pnode->next = make_unique<Map>();
				}
				Map& m = *pnode->next;
				auto iter = m.find(ch);
				if (iter == m.end())
				{
					iter = m.emplace_hint(iter, ch, Node());
				}
				pnode = &(iter->second);
				//}
			}
			return pnode;
		}

	private:
		Node _root;
#ifdef GEZI_DATA_TRUE_INDICATOR
#ifndef GEZI_TRIE_INDEX_IS_VALUE
		vector<mapped_type> _mappedVec;
#endif
#endif

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			ar & _root;
#ifdef GEZI_DATA_TRUE_INDICATOR
#ifndef GEZI_TRIE_INDEX_IS_VALUE
			ar & _mappedVec;
#endif
#endif
		}
	};

#ifdef GEZI_DATA_FALSE_INDICATOR
	template <typename Key,
		template<class _Kty, class _Ty, typename...> class _Map = std::unordered_map>
	using TrieSet = TrieSet_ < Key, null_type, _Map > ;
#endif

#ifdef GEZI_DATA_TRUE_INDICATOR
#ifdef GEZI_TRIE_INDEX_IS_VALUE 
	template <typename Key,
		typename Mapped = int,
		template<class _Kty, class _Ty, typename...> class _Map = std::unordered_map>
	using TrieDict = TrieDict_ < Key, Mapped, _Map > ;
#endif
#endif

}  //----end of namespace gezi

//CEREAL_REGISTER_TYPE(gezi::GEZI_TRIE_NAME::Node);
#undef GEZI_TRIE_NAME