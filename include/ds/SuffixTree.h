/** 
 *  ==============================================================================
 * 
 *          \file   suffix_tree.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2013-08-15 05:42:41.872766
 *  
 *  \Description:  支持动态添加和删除的后缀树  
 *                 TODO 支持序列化
 *  ==============================================================================
 */

#ifndef SUFFIX_TREE_H_
#define SUFFIX_TREE_H_
#include <string>
#include <map>
#include <deque>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include "hashmap_util.h"
#include "string_util.h"

namespace gezi
{
class SuffixTree
{
public:
	//测试一般用#作为结束便于显示，实际一般选用\n等作为结束符号

	SuffixTree(const wstring& end_mark = L"#")
	: _end_mark(end_mark)
	{
		init();
	}

	virtual ~SuffixTree()
	{
		free();
	}

#ifndef GEZI_SUFFIXTREE_INT_INDEX_TYPE
	///这样线上不断删除 每天按照5kw 也没关系需要太多年，但是int比较危险，不过一般其它应用int足够了,比如离线处理一天的数据,int减小内存占用 @TODO
	typedef unsigned long long index_type;
#else
	typedef int index_type;
#endif

#ifndef GCCXML

	struct Node;
	//typedef std::map<wchar_t, Node*, less<wchar_t> > Edges; //内存占用近似 测试用map 线上可以用hash map提高速度
	typedef std::unordered_map<wchar_t, Node*> Edges;
	typedef Edges::iterator NIter; //typename? ? TODO

	struct Node
	{
		Node()
		{
			init();
			parent = NULL;
			start = 0;
			end = 0;
			length = 0;
			text_id = 0;
		}

		void init()
		{
			next = NULL;
			freq = 0;
			suffix_link = NULL;
		}

		Node(Node* parent_, index_type id_ = 0)
		{
			init();
			parent = parent_;
			text_id = id_;
		}

		Node(Node* parent_, int start_, int end_, int length_, index_type id_ = 0, int freq_ = 0)
		{
			init();
			parent = parent_;
			start = start_;
			end = end_;
			length = length_;
			text_id = id_;
			freq = freq_;
		}

		inline bool is_leaf()
		{
			return next == NULL;
		}

		int length; //从root到当前点的总边长
		int start; //在输入text中的起始位置
		int end; //在输入text中的pass 1 结束位置 end-start表示边的长度
		int freq; //该root到该边对应的串出现频次

		Node* parent; //指向父亲节点 用于统计频次
		Node* suffix_link; // v1 -> v2  v1 a(D)  v2 (D), v1 v2 均为内部节点  事实上叶子结点不需要suffix_link
		Edges* next; //叶子结点next == NULL

		index_type text_id; //node id 指向text所在texts序列中的位置  注意需要是index_type 不是int
	};
#endif //GCCXML
	void init()
	{
		_root = new Node;
		_root->next = new Edges;
		reset_status();
	}

	void reset_status()
	{
		_current_text_id = 0;
		_oldest_text_id = 0;
	}

	//清空一个后缀树保留头节点数据，数据清零，用于多次clear add操作

	void reset()
	{
		clear();
		reset_status();
	}
	//释放后缀树所有空间

	void free()
	{
		clear(_root);
		_root = NULL;
	}

	void clear()
	{
		for (NIter iter = _root->next->begin(); iter != _root->next->end(); ++iter)
		{
			clear(iter->second);
		}
		delete _root->next;
		_root->next = NULL;
	}

	inline wstring& end_mark()
	{
		return _end_mark;
	}

	inline size_t tree_size()
	{
		return _texts.size();
	}

	inline size_t size()
	{
		return _texts.size();
	}

protected:

#ifndef GCCXML
	Node* _root;
	index_type _current_text_id;
	index_type _oldest_text_id;
	std::deque<wstring> _texts;
	std::deque<Node*> _first_leafs;
	wstring _end_mark;
#endif //GCCXML
public:

	void build(const wstring& text)
	{
		wstring s = text + _end_mark;
		boost::replace_all(s, _end_mark, L"");
		_texts.push_back(s);
		build_(s);
		_current_text_id++;
	}

	void add(const wstring& text)
	{
		wstring s = text;
		boost::replace_all(s, _end_mark, L"");
		s = s + _end_mark;
		_texts.push_back(s);
		add_(s);
		_current_text_id++;
	}

	void insert(const wstring& text)
	{
		add(text);
	}

	//remove the oldest one

	void remove()
	{
		if (_texts.size() == 0)
		{
			return;
		}

		remove_();

		_texts.pop_front();
		_first_leafs.pop_front();

		_oldest_text_id++;
	}

	void remove_newest()
	{

	}

	//删除指定位置的文本 TODO 如果这样 需要将 texts_ first_leafs_存储为 map<int,..>格式方便删除任意位置

	void remove(int id)
	{

	}

#ifndef GCCXML
	void clear(Node* node)
	{
		if (node)
		{
			if (node->next)
			{
				for (NIter iter = node->next->begin(); iter != node->next->end(); ++iter)
				{
					clear(iter->second);
				}
				delete node->next;
			}
			delete node;
		}
	}

	//查找从一个字符串指定位置(start)开始 在后缀树中最长匹配的串

	Node* find_longest_node(const wstring& text, int start = 0)
	{
		int text_length = text.length() - start;
		if (text_length <= 0)
		{
			return _root;
		}

		Node* active_node = _root;
		int cur = start;

		while (cur < text_length)
		{
			NIter iter = active_node->next->find(text[cur]);
			if (iter == active_node->next->end())
			{ //找到不匹配
				return active_node;
			}
			active_node = iter->second;
			int end = cur + (active_node->end - active_node->start);
			int j;
			for (j = cur + 1; j < end && j < text_length; j++)
			{
				if (_texts[active_node->text_id][active_node->start + j] != text[j])
				{//找到不匹配
					return active_node;
				}
			}
			if (j == text_length)
			{ //文本串匹配完
				return active_node;
			}

			if (active_node->is_leaf())
			{//文本串未匹配完 但是已经到叶子节点
				return active_node;
			}

			cur = end;
		}

		return active_node;
	}

#endif //GCCXML

	///返回匹配到的长度
	int find_longest(const wstring& text, int start)
	{
		Node* node = find_longest_node(text, start);
		return node->length;
	}

	int find_longest(const wstring& text, int start, int & freq)
	{
		Node* node = find_longest_node(text, start);
		if (node == _root)
		{ //root_->freq 记录了后缀树一共有多少个叶子节点 = 总文本长度
			freq = 0;
		}
		freq = node->freq;
		return node->length;
	}

	///判断一个字符串是否在后缀树中
	bool find(const wstring& text, int start = 0)
	{
		return find_node(text, start) != NULL;
	}

	int find_freq(const wstring& text, int start = 0)
	{
		Node* node = find_node(text, start);
		if (node)
		{
			return node->freq;
		}
		return 0;
	}

	///----------------------新词识别
	void find_prefix_suffix_freqs(const wstring& text, vector<int>& prefix_freqs, vector<int>& suffix_freqs)
	{
		if (text.length() < 2)
		{
			return;
		}
		Node* node = find_node(text, prefix_freqs);
		prefix_freqs.resize(text.length() - 1);
		suffix_freqs = find_suffix_freqs(node);
	}

	double right_information(const wstring& text)
	{
		double information = 0;
		Node* node = find_node(text);
		if (!node)
		{
			return information;
		}
		Edges* subtree = node->next;
		int total = node->freq;

		if (subtree)
		{
			for (auto item : *subtree)
			{
				double prob = item.second->freq / (double)total;
				information += -prob * log(prob);
			}
		}
		return information;
	}

	set<int> get_text_ids(const wstring& text)
	{
		set<int> tids;
		Node* node = find_node(text);
		if (node)
		{
			tids = get_text_ids(node);
		}
		return tids;
	}

	vector<pair<int, int> > get_texts_id_pos(const wstring& text)
	{
		return get_texts_id_pos(find_node(text));
	}
	///----------------------新词识别 end

#ifndef GCCXML
	///在后缀树中查找一个字符串 并且返回记录频次信息等的Node节点 如果路径中某次查找失败或者走到叶子节点text仍然没有走完 返回root_
	Node* find_node(const wstring& text, int start = 0)
	{
		int text_length = text.length() - start;
		if (text_length <= 0)
		{
			return NULL;
		}

		Node* active_node = _root;
		int cur = start;

		while (cur < text_length)
		{
			NIter iter = active_node->next->find(text[cur]);
			if (iter == active_node->next->end())
			{ //找到不匹配
				return NULL;
			}
			active_node = iter->second;
			int end = cur + (active_node->end - active_node->start);
			int j, idx = 1;
			for (j = cur + 1; j < end && j < text_length; j++, idx++)
			{
				if (_texts[active_node->text_id][active_node->start + idx] != text[j])
				{//找到不匹配
					return NULL;
				}
			}
			if (j == text_length)
			{ //文本串匹配完
				return active_node;
			}

			if (active_node->is_leaf())
			{//文本串未匹配完 但是已经到叶子节点
				return NULL;
			}

			cur = end;
		}

		return active_node;
	}

	set<int> get_text_ids(Node* node)
	{
		set<int> tids;
		get_text_ids(node, tids);
		return tids;
	}

	void get_text_ids(Node* node, set<int>& tids)
	{
		using namespace std;
		if (node->next == NULL)
		{
			tids.insert(node->text_id - _oldest_text_id);
			return;
		}
		for (NIter iter = node->next->begin(); iter != node->next->end(); ++iter)
		{
			get_text_ids(iter->second, tids);
		}
	}

	void get_text_ids(Node* node, vector<Node*>& tids)
	{
		using namespace std;
		if (node->next == NULL)
		{
			tids.push_back(node);
			return;
		}
		for (NIter iter = node->next->begin(); iter != node->next->end(); ++iter)
		{
			get_text_ids(iter->second, tids);
		}
	}

	vector<pair<int, int> > get_texts_id_pos(Node* node)
	{
		vector<pair<int, int> > results;
		if (!node)
		{
			return results;
		}
		vector<Node*> nodes;
		get_text_ids(node, nodes);
		set<int> tids;
		for (Node* node : nodes)
		{
			int id = node->text_id - _oldest_text_id;
			auto ret = tids.insert(id);
			if (ret.second)
			{//@TODO check 当前返回的其实是end位置 也就是下一个char的位置
				results.emplace_back(id, node->start);
			}
		}
		return results;
	}

	//-------------------------------------新词识别
	/**
	* @brief 为了新词识别，返回text所有前缀的频次 比如abca 返回 a,ab,abc,abca 4个前缀的频次
	* @param text: 
	* @param freqs: 
	* @return (Node*):
	*/
	Node* find_node(const wstring& text, vector<int>& freqs) 
	{
		freqs.resize(text.length(), 0);
		int text_length = text.length();

		Node* active_node = _root;
		int cur = 0;
		while (cur < text_length)
		{
			NIter iter = active_node->next->find(text[cur]);
			if (iter == active_node->next->end())
			{ //找到不匹配
				return NULL;
			}
			
			active_node = iter->second;
			freqs[cur] = active_node->freq;

			int end = cur + (active_node->end - active_node->start);
			int j, idx = 1;
			for (j = cur + 1; j < end && j < text_length; j++, idx++)
			{
				if (_texts[active_node->text_id][active_node->start + idx] != text[j])
				{//找到不匹配
					return NULL;
				}
				freqs[j] = active_node->freq;
			}
			if (j == text_length)
			{ //文本串匹配完
				return active_node;
			}

			if (active_node->is_leaf())
			{//文本串未匹配完 但是已经到叶子节点
				return NULL;
			}

			cur = end;
		}

		return active_node;
	}
	///abca所有后缀的频次记录 bca,ca,a
	vector<int> find_suffix_freqs(Node* node)
	{
		vector<int> freqs;
		node = node->suffix_link;
		int len = node_length(node);
		for (; freqs.size() < len; node = node->suffix_link)
		{
			freqs.push_back(node->freq);
		}
		return freqs;
	}

	static int node_length(const Node* node)
	{
		return node->next == NULL ? node->length - 1 : node->length;
	}

	inline wstring get_str(const Node* node)
	{
		wstring& text = _texts[node->text_id - _oldest_text_id];
		int len = node_length(node);
		return text.substr(node->end - node->length, len);
	}

	///------------------------------新词识别 end

	//输入是一个叶子结点

	void dec_freq(Node* node)
	{
		if (node->freq == 1)
		{ //需要删除叶子
			Node* active_node = node->parent;
			wchar_t key = _texts[node->text_id - _oldest_text_id][node->start];
			delete node;
			active_node->next->erase(key);
			if (active_node != _root && active_node->next->size() == 1) //root_结点不能收缩单边
			{ //收缩单边情况, active_node被删除 up -- active -- low  -> up -- low
				key = _texts[active_node->text_id - _oldest_text_id][active_node->start];
				NIter iter = active_node->next->begin();
				Node* low_node = iter->second;
				Node* up_node = active_node->parent;
				(*(up_node->next))[key] = low_node;
				low_node->parent = up_node;
				int edge_length = active_node->end - active_node->start; //or son_node->length - active_node->length
				low_node->start -= edge_length;

				delete active_node->next;
				delete active_node;
				node = up_node;
			}
			else
			{
				node = active_node;
			}
		}

		//向上直到root 频率减一
		for (; node != NULL; node = node->parent)
		{
			node->freq--;
		}
	}

	//去掉最旧的文本，删除过程相对简单因为我们假定删除的文本是以前添加的 所以任何后缀都是在后缀树中存在已经
	//首先找到对应整个文本的叶子结点，对应 active_node - next_node next_node对应叶子结点
	//向上直到root频次-1，然后如果叶子结点频率将为0 删除叶子结点 同时判断active_node是否next map只有1个边
	//如果是则将next_node合并到active_node, active_node成为叶子结点
	//继续active_node = active_node->suffix_link
	//设字符串长度为m 整个过程就是删除m

	void remove_(int idx = 0)
	{
		for (Node* leaf_node = _first_leafs[idx]; leaf_node != NULL; leaf_node = leaf_node->suffix_link)
		{
			dec_freq(leaf_node);
		}
	}

#endif //GCCXML

protected:
#ifndef GCCXML
	//完全按照
	//http://stackoverflow.com/questions/9452701/ukkonens-suffix-tree-algorithm-in-plain-english/9513423#9513423
	//事实上remainder可以去掉得到 形式上更简洁的结果 效率应该一样 但可理解性变差 

	void build_(const wstring& text)
	{
		int text_length = text.length();
		Node* active_node = _root; //active_node记录要考虑插入的节点
		Node* next_node = NULL; //由于没有显示的边数据结构，active_node -> next_node 表示当前active edge
		int active_length = 0; //相对于active_node的length
		int remainder = 1; //需要处理的后缀数目
		//例如输入abcaf
		//依次完成如下子后缀树建立 a, ab, abc, abca ... abcabf
		for (int end_idx = 0; end_idx < text_length; end_idx++, remainder++)
		{
			//建立后缀树 [0, i]
			//循环 remainder 次 (不必考虑[0,end_idx] [1,end_idx] ...[end_idx,end_idx] 
			//只需要考虑[end_idx - remainder + 1, end_idx]..[end_idx,end_idx])
			//remainder >= 1  remainder == 1意味着active_node == root 从头开始插入
			Node* mid_node; //当前指向新建叶子节点的时候 in_node 通过边长为1的边指向该叶子节点 即分裂边上的新生节点  a -- mid_node -- b
			Node* old_node = _root; //记录循环中前一次的in_node位置，第一次设置为root_
			for (; remainder > 0; remainder--)
			{
				int edge_length;
				if (active_length > 0)
				{
					//下面处理使得active_length < edge_len 可能会沿着某个路径多次向下跳动， 
					//但是一个[start_idx, end_idx]这样 remainder次数的循环中，总跳动次数 < actvie_length <= remainder,所以算法依然线性
					int first_char_pos = end_idx - active_length;
					if (next_node == NULL)
					{
						next_node = active_node->next->find(text[first_char_pos])->second;
					}
					while (true)
					{
						edge_length = next_node->end - next_node->start;
						if (active_length >= edge_length)
						{
							active_length -= edge_length;
							active_node = next_node;
							if (active_length == 0)
							{
								next_node = NULL;
								break;
							}
							else
							{
								first_char_pos += (active_node->end - active_node->start);
								next_node = next_node->next->find(text[first_char_pos])->second;
							}
						}
						else
						{
							break;
						}
					}
				}

				if (active_length == 0)
				{
					NIter iter = active_node->next->find(text[end_idx]);
					if (iter != active_node->next->end())
					{ //2. 隐节点(在active_edge边上积累)
						active_length++;
						next_node = iter->second;
						break;
					}
					else
					{//否则1. 第一种叶子节点加入方式，内部节点生成一个新边指向新生成的叶子
						mid_node = active_node;
					}
				}
				else
				{
					int pos = next_node->start + active_length;
					if (text[pos] == text[end_idx])
					{
						active_length++;
						break; //2. 提前结束(early stop)   abc 在后缀树中 那么 bc 必然也已经在
					}
					else
					{ //3. 第二种叶子结点加入方式，内部边分裂，产生一个新的内部节点，并且指向新生成的叶子节点
						int remaining_len = edge_length - active_length;
						mid_node = new Node(active_node, next_node->start, pos,
										next_node->length - remaining_len, _current_text_id, next_node->freq);
						(*(active_node->next))[text[next_node->start]] = mid_node;

						next_node->parent = mid_node;
						next_node->start = pos;
						next_node->length = remaining_len;

						mid_node->next = new Edges;
#if __GNUC__ > 3 || defined(WIN32)
						mid_node->next->emplace(text[pos], next_node);
#else
						mid_node->next->insert(Edges::value_type(text[pos], next_node)); 
#endif
					}
				}
				//生成新叶(内部节点插入,内部边分裂两种情形的生成新叶统一放到这里处理)
				//叶子结点始终是叶子节点结束位置问输入文本结束位置  
				Node* leaf_node = new Node(mid_node, end_idx, text_length, mid_node->length + (text_length - end_idx), _current_text_id, 1);
#if __GNUC__ > 3 || defined(WIN32)
				mid_node->next->emplace(text[end_idx], leaf_node);
#else
				mid_node->next->insert(Edges::value_type(text[end_idx], leaf_node));
#endif
				//对于连续生成新点的情况，创建suffix link
				if (old_node != _root)
				{
					old_node->suffix_link = mid_node;
				}
				old_node = mid_node;

				if (active_node != _root)
				{ //active_node->suffix_link == NULL 即是root
					active_node = active_node->suffix_link;
				}
				else if (active_length > 0)
				{
					active_length--;
				}
				next_node = NULL;
			}

			//最后一个old_node 需要处理suffix_link
			//最后一个old_node如果是最后一次产生的 一定对应old_node == active_node == root_
			//而如果不是那必然最后一次是匹配了然后break 这时候 前一次余下的 old_node需要suffix_link
			//处理完remainder个后缀后 注意最后一个结束有两种可能
			//1.回到原点old_node == root_ active_node == root_  考虑"xtptxy" 插入最后y的时候 xy y  
			//2.最后再某个位置匹配 然后break了  如果是在边中间非第一个位置break 那么 old_node == root_ 不需要处理什么
			//  如果是在边第一个位置break 同时old_node != root_ 也就是说 之前产生了一个新的内部点(old_node)需要一个 suffix_link
			//  比如前面  root -- .... --ab--ce 
			//                                       --d
			//active_node--next_node对应ab位置 之后 active_node = active_node->suffix_link  那么后续会有
			//... --ab -- d  
			//           -- d
			//因为active_length == edge_legnth 所以 active_node会继续向下走到  --d 因此 old_node->suffix_link = active_node 即可
			if (old_node != _root)
			{
				old_node->suffix_link = active_node;
			}
		}
	}

	//对应generalized suffix tree 构建（输入为多个字符串文本) 框架一样 但是要注意text_id的使用
	//Adding b
	//|-#[0 1:2]  1 0x17d0f30->0
	//|-b#[0 0:2]  1 0x17d0eb0->0
	//Adding bc
	//|-#[0 1:2]  1 0x17d0f30->0
	//|-b[0 0:1]  1 0x17d17c0->0x17cd740
	//   |-#[0 1:2]  1 0x17d0eb0->0
	//   |-c#[1 1:3]  1 0x17d1880->0
	//|-c#[1 1:3]  1 0x17d1900->0
	//Adding bcd
	//|-#[0 1:2]  1 0x17d0f30->0
	//|-b[0 0:1]  1 0x17d17c0->0x17cd740
	//   |-#[0 1:2]  1 0x17d0eb0->0
	//   |-c[1 1:2]  1 0x17d19f0->0x17d1b30
	//      |-#[1 2:3]  1 0x17d1880->0
	//      |-d#[2 2:4]  1 0x17d1ab0->0
	//|-c[1 1:2]  1 0x17d1b30->0x17cd740
	//   |-#[1 2:3]  1 0x17d1900->0
	//   |-d#[2 2:4]  1 0x17d1bf0->0
	//|-d#[2 2:4]  1 0x17d1c70->0
	//另外考虑计数问题 连续两个 b 注意结尾符号都是相同的，如果继续按照普通建树 ab# ab# 匹配到最后就停止了 忽略了后面的b#等
	//其实相当于模拟 ab# ab$ 的输入
	//#  2
	//b# 2

	//尝试向下移动 返回最终边的长度
	//下面处理使得active_length < edge_len 可能会沿着某个路径多次向下跳动， 
	//但是一个[start_idx, end_idx]这样 remainder次数的循环中，总跳动次数 < actvie_length <= remainder,所以算法依然线性

	int shift_down(const wstring& text, int end_idx, Node*& active_node, Node*& next_node, int & active_length)
	{
		int edge_length;

		int first_char_pos = end_idx - active_length;
		if (next_node == NULL)
		{
			next_node = active_node->next->find(text[first_char_pos])->second;
		}
		edge_length = next_node->end - next_node->start;

		while (active_length >= edge_length)
		{
			active_length -= edge_length;
			active_node = next_node;
			if (active_length > 0)
			{
				first_char_pos += (active_node->end - active_node->start);
				next_node = next_node->next->find(text[first_char_pos])->second;
				edge_length = next_node->end - next_node->start;
			}
		}
		return edge_length;
	}

	//对边进行分裂 返回新生成的中间结点

	Node* split_edge(Node* active_node, Node* next_node, wchar_t first_char, wchar_t test_char,
					int split_pos, int edge_length, int active_length)
	{
		int remaining_len = edge_length - active_length;

		Node* mid_node = new Node(active_node, next_node->start, split_pos,
						next_node->length - remaining_len, next_node->text_id, next_node->freq);

		(*(active_node->next))[first_char] = mid_node;

		next_node->parent = mid_node;
		next_node->start = split_pos;

		mid_node->next = new Edges;
#if __GNUC__ > 3 || defined(WIN32)
		mid_node->next->emplace(test_char, next_node);
#else
		mid_node->next->insert(Edges::value_type(test_char, next_node));
#endif

		return mid_node;
	}

	void add_(const wstring & text)
	{
		int text_length = text.length();
		Node* active_node = _root; //active_node记录要考虑插入的节点
		Node* next_node = NULL; //由于没有显示的边数据结构，active_node -> next_node 表示当前active edge
		Node* pre_leaf = NULL;
		int active_length = 0; //相对于active_node的length
		int remainder = 1; //需要处理的后缀数目
		//例如输入abcaf
		//依次完成如下子后缀树建立 a, ab, abc, abca ... abcabf
		for (int end_idx = 0; end_idx < text_length; end_idx++, remainder++)
		{
			//建立后缀树 [0, i]
			//循环 remainder 次 (不必考虑[0,end_idx] [1,end_idx] ...[end_idx,end_idx] 
			//只需要考虑[end_idx - remainder + 1, end_idx]..[end_idx,end_idx])
			//remainder >= 1  remainder == 1意味着active_node == root 从头开始插入
			Node* mid_node = NULL; //当前指向新建叶子节点时 in_node 通过边长为1的边指向该叶子节点 即分裂边上的新生节点  a -- mid_node -- b
			Node* old_node = _root; //记录循环中前一次的in_node位置，第一次设置为root_

			for (; remainder > 0; remainder--)
			{
				Node* leaf_node = NULL;

				int edge_length = 0;
				if (active_length > 0)
				{
					edge_length = shift_down(text, end_idx, active_node, next_node, active_length);
				}

				if (active_length == 0)
				{
					NIter iter = active_node->next->find(text[end_idx]);
					if (iter != active_node->next->end())
					{ //2. 隐节点(在active_edge边上积累)
						if (end_idx != text_length - 1)
						{ //最后一位 标记位#
							active_length++;
							next_node = iter->second;
							break;
						}
						else
						{ //如果不是要计数 而是只判断是否出现过 那么可以不需要这种特殊处理结尾相同的情况 那样直接后续串被略过
							leaf_node = iter->second;
						}
					}
					else
					{//否则1. 第一种叶子节点加入方式，内部节点生成一个新边指向新生成的叶子
						mid_node = active_node;
					}
				}
				else
				{
					int test_pos = next_node->start + active_length;

					wchar_t test_char = _texts[next_node->text_id - _oldest_text_id][test_pos]; //边对应的text id由 next node 决定

					if (test_char == text[end_idx])
					{
						if (end_idx != text_length - 1)
						{
							active_length++;
							break; //2. 提前结束(early stop)   abc 在后缀树中 那么 bc 必然也已经在
						}
						else
						{//比如 ab# ab#匹配到# remainder = 3 active_length = 2 end_idx = text_length
							leaf_node = next_node;
						}
					}
					else
					{ //3. 第二种叶子结点加入方式，内部边分裂，产生一个新的内部节点，并且指向新生成的叶子节点
						wchar_t first_char = _texts[next_node->text_id - _oldest_text_id][next_node->start];
						mid_node = split_edge(active_node, next_node, first_char, test_char, test_pos, edge_length, active_length);
					}
				}

				bool is_leaf_match = false;

				if (!leaf_node)
				{
					//生成新叶(内部节点插入,内部边分裂两种情形的生成新叶统一放到这里处理)
					//叶子节点始终会是叶子节点,所以结束位置问输入文本结束位置
					leaf_node = new Node(mid_node, end_idx, text_length, mid_node->length + (text_length - end_idx), _current_text_id, 0);
#if __GNUC__ > 3 || defined(WIN32)
					mid_node->next->emplace(text[end_idx], leaf_node);
#else
					mid_node->next->insert(Edges::value_type(text[end_idx], leaf_node));
#endif
				}
				else
				{
					is_leaf_match = true;
					leaf_node->text_id = _current_text_id; //更新节点信息为最新文本中的位置
					int edge_length = leaf_node->end - leaf_node->start;
					leaf_node->start = text_length - edge_length;
					leaf_node->end = text_length;
				}

				inc_freq(leaf_node);

				if (pre_leaf)
				{
					pre_leaf->suffix_link = leaf_node;
				}
				else
				{
					_first_leafs.push_back(leaf_node);
				}
				pre_leaf = leaf_node;

				//最后更新状态
				//由于是多次插入串 可能存在前面未匹配分裂 之后匹配直到最后叶子
				if (!is_leaf_match)
				{ //注意如果是最后两个不同text 叶子匹配 这种 不要修改影响到正常的suffix link
					//对于连续生成新点的情况，创建suffix link
					if (old_node != _root)
					{
						old_node->suffix_link = mid_node;
					}
					old_node = mid_node;
				}
				else
				{ //如果上次分裂 当前匹配到最后结束符都相同 注意suffix link要连上,再后续循环 必然都完全匹配后缀 suffix link已经配置好
					if (old_node != _root)
					{
						old_node->suffix_link = active_node;
						old_node = _root;
					}
				}

				if (active_node != _root)
				{ //active_node->suffix_link == NULL 即是root
					active_node = active_node->suffix_link;
				}
				else if (active_length > 0)
				{
					active_length--;
				}
				next_node = NULL;
			}
			//最后一个old_node 需要处理suffix_link
			//最后一个old_node如果是最后一次产生的 一定对应old_node == active_node == root_
			//而如果不是那必然最后一次是匹配了然后break 这时候 前一次余下的 old_node需要suffix_link
			//处理完remainder个后缀后 注意最后一个结束有两种可能
			//1.回到原点old_node == root_ active_node == root_  考虑"xtptxy" 插入最后y的时候 xy y  
			//2.最后再某个位置匹配 然后break了  如果是在边中间非第一个位置break 那么 old_node == root_ 不需要处理什么
			//  如果是在边第一个位置break 同时old_node != root_ 也就是说 之前产生了一个新的内部点(old_node)需要一个 suffix_link
			//  比如前面  root -- .... --ab--ce 
			//                                       --d
			//active_node--next_node对应ab位置 之后 active_node = active_node->suffix_link  那么后续会有
			//... --ab -- d  
			//           -- d
			//因为active_length == edge_legnth 所以 active_node会继续向下走到  --d 因此 old_node->suffix_link = active_node 即可
			if (old_node != _root)
			{
				old_node->suffix_link = active_node;
			}
		}
	}

	void calc_freq()
	{
		_root->freq = get_leaf_num(_root);
	}

	int get_leaf_num(Node * node)
	{
		using namespace std;
		if (!node->next)
		{ //叶子节点直接返回
			return node->freq;
		}
		for (NIter iter = node->next->begin(); iter != node->next->end(); ++iter)
		{
			node->freq += get_leaf_num(iter->second);
		}
		return node->freq;
	}

	//从当前叶子节点向上直到root(包括root) 执行freq +1操作
	//包括了更新边信息为最新的文本中的位置 为了后续删除需要
	//TODO 如果一个文本中的重复串按照1 处理？， 增加一个unique freq 位

	void inc_freq(Node * node)
	{
		Node* pre_node = node;
		for (; node != NULL; node = node->parent)
		{
			node->freq++;
			if (node->text_id != _current_text_id)
			{ //更新边信息为新文本的索引位置
				int edge_length = node->end - node->start;
				node->text_id = _current_text_id;
				node->end = pre_node->start;
				node->start = node->end - edge_length;
			}
			pre_node = node;
		}
	}
#endif //GCCXML
public:
	//假设使用map作为边 顺序输出遍历的各个节点 (text_id, start point, end point, edge length node freq, node depth)
	//输出到文本 方便对比测试是否结果正确

	void write_result(const string & file)
	{
		wofstream ofs(file.c_str());
		write_result(_root, 0, ofs);
		wcout << "Writed result" << endl;
	}

	void print()
	{
		wcout << "The string is: " << _texts[_texts.size() - 1] << endl;
		wcout << "Current text id: " << _current_text_id << "  Oldest text id: " << _oldest_text_id << " texts_.size: " << _texts.size() << endl;
		wcout << L"root_ " << _root << endl;
		int leaf_freq = 0;
		print(_root, 0, leaf_freq);

		//        wcout << "The string length is " << texts_[0].length() << endl;
		wcout << "The total leaf freq is " << leaf_freq << endl;
	}

	/**
	* @brief 
	* @param id:  相对id 0 开始
	*/
	wstring text(int id) const
	{
		return _texts[id];
	}

	index_type min_text_id() const
	{
		return _oldest_text_id;
	}

	index_type max_text_id() const
	{
		return _current_text_id;
	}

	/**
	* @brief 获取绝对id 包含被remove的累加起来
	* @param id: 
	* @return (gezi::SuffixTree::index_type):
	*/
	index_type text_id(int id) const
	{
		return id + _oldest_text_id;
	}
#ifndef GCCXML
	void write_result(Node* node, int depth, wofstream & ofs)
	{
		using namespace std;
		if (!node || !node->next)
		{
			return;
		}

		for (NIter iter = node->next->begin(); iter != node->next->end(); ++iter)
		{
			//iter->second->freq = 0;
			wstring edge = this->_texts[iter->second->text_id - _oldest_text_id].
				substr(iter->second->start, iter->second->end - iter->second->start);
			ofs << iter->second->text_id << " " << iter->second->start << " " << iter->second->end << " " << edge << " "
				<< (!iter->second->next) << " " << iter->second->freq << "  " << depth << endl;

			//             wcout << iter->second->text_id << " " << iter->second->start << " " << iter->second->end << " " << edge << " "
			//                    << (!iter->second->next) << " " << iter->second->freq << "  " << depth << endl;

			write_result(iter->second, depth + 1, ofs);
		}
	}
	//input from root , input is not NULL

	void print(Node* node, int depth, int & leaf_freq)
	{
		using namespace std;
		if (!node->next)
		{
			return;
		}

		for (NIter iter = node->next->begin(); iter != node->next->end(); ++iter)
		{
			for (int i = 0; i < depth; i++)
			{
				wcout << "   ";
			}

			//TODO why wrong
			//wstring span = boost::wformat(L"[%X %X]") % iter->second->start %iter->second->end;

			if (!iter->second->next)
			{
				leaf_freq += iter->second->freq;
			}

			//            wcout << iter->second->text_id << " " << oldest_text_id_ << endl;
			//                wcout << texts_[iter->second->text_id - oldest_text_id_] << endl;
			//                wcout << iter->second->start << endl;
			//                wcout << (iter->second->end - iter->second->start) << endl;
			//                wcout << iter ->first << endl;
			wstring edge = this->_texts[iter->second->text_id - _oldest_text_id].
							substr(iter->second->start, iter->second->end - iter->second->start);
			wcout << "|-" << edge << "[" << iter->second->text_id << " " << iter->second->start << ":"
							<< iter->second->end << "] " << " (" << iter->second->freq << " " << iter->second->length << ") "
							<< iter->second << "->" << iter->second->suffix_link
							//                    << " " << (iter->second->next == NULL) 
							<< endl;

			//              wcout << "|-"  << " "<< "[" << iter->second->id << " " << iter->second->start << ":"
			//                    << iter->second->end << "] " << iter->second << "->" << iter->second->suffix_link
			//                    << " " << (iter->second->next==NULL) << endl;
			print(iter->second, depth + 1, leaf_freq);
		}
	}
#endif //GCCXML

};
}
#endif  //----end of SUFFIX_TREE_H_
