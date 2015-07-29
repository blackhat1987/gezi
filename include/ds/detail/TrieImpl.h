/**
 *  ==============================================================================
 *
 *          \file   detail/TrieImpl.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-07-26 15:04:00.063718
 *
 *  \Description:  ģ��std::map std::set�ӿ� ���ǵ�ǰ�����ṩiterator֧��
 *                 ������map��������find���ص�iterator ֻ��mapped��ָ�룬��Ϊ�ڲ�key,mapped�ֿ��洢 û������vector<pair<key,mapped> >�����Ĵ洢
 *                 trie������Ҫ������ǰ׺��ѯ,�ر��ǲ�ѯ�м�״̬��֧��
 *                 @TODO ������Ķ̴����ض��Ż� �����һ��hash�Ƿ����ֱ��o(1)����
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


		///����ָ��û��NULL�����������map.empty()����ʾ��,ʹ��ָ��NULL���Խ�Լһ���ڴ棬��������map empty������ӷ���
		struct Node;
		typedef unique_ptr<Node> NodePtr;
		///���������ʹ��ָ��map�ǿ��Եĵ���ʹ��unorderd_map gcc4�ᱨ��  error: 'std::pair<_T1, _T2>::second' has incomplete type
		//����Ϊ��֧��unordered_map����Ҫ��һ��ָ��next ���� �����Node,Ϊ��ʹ��uniqe ptr���� ����Node����ʹ��ָ��
		//���д������sunpinyin ����SuffixTree�ж�ʹ����ָ��,ʹ��ָ��ռ�õĿռ����һ��㵫�ǲ��� ֻ����һ��index_type�Ŀռ䣬���ﲻ����ָ�룬ʹ��unique ptrϣ���ܷ������л�
		//SuffixTreeһ��û�����л�����,���ʹ����ָ��
		//��Ϊ��ʹ��unique ptr���� ����ʹ��Node ������ָ�� ����̫���㣬����Ҳ����һЩ
		typedef _Map<char_type, Node > Map;
		typedef unique_ptr<Map> MapPtr;
		//@TODO �ȶԱ��¿�map��ָ���С����
		//checkһ�� Map* next��д�� 

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
			index_type index = null_index;  ///null_index������ʾ�ڲ��ڵ�,���û����Node* ��ô��һ��index_type��ռ�ÿռ� ����Ҷ�ӽڵ� @TODO ��ʱ�����������
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
		* @brief ֻ��mapʹ��
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

		pair<iterator, bool> insert(const key_type& key, mapped_type&& mapped)
		{
			Node* pnode = insert_key(key);
			if (pnode->index == null_index)
			{
				pnode->index = (index_type)_mappedVec.size();
				_mappedVec.emplace_back(mapped);
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
					Map& m = *pnode->next;
					auto iter = m.find(ch);
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
				if (!pnode->next)
				{
					return NULL;
				}
				else
				{
					const Map& m = *pnode->next;
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
		* @brief ����ĳ���ڵ�������Ӵ�����
		*				 ע�ⲻ����,Ĭ��û��NULL
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
		* @brief  �ܵĴ���Ŀ
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