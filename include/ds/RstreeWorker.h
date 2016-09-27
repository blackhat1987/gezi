/**
 *  ==============================================================================
 *
 *          \file   RstreeWorker.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-04 19:41:36.956520
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef RSTREE_WORKER_H_
#define RSTREE_WORKER_H_
#include "Rstree.h"
//#include "dsuffix_tree.h"
#include "post_process/PostProcessor.h"
//#include "word_seg.h"
#include "Segmentor.h"
#include "all_util.h"
#include "rstree_def.h"
#include "hashmap_util.h"
namespace gezi
{

	class RstreeWorker
	{
	public:

		RstreeWorker()
			: _min_text_length(8),
			_max_text_length(200),
			_max_result_count(5),
			_use_seg(true),
			_simple_sort(false)
		{

		}

	private:
		int _min_text_length;
		int _max_text_length;
		int _max_result_count;
		bool _use_seg;
		bool _simple_sort;
		static const int MAX_SEG_BUFSIZE = 15000;

		Rstree _rstree;
		PostProcessor _post_processor;
		//SegHandle _seg_handle;
		PostAdjustor _post_adjustor;

	public:

		static void init_static()
		{
			SharedConf::init(RSTREE_CONF_DIR, RSTREE_CONF);
			PostProcessor::init_static();

			//string seg_data_dir = "./data/wordseg";
			//string section = "";
			//SCONF(seg_data_dir);
			//seg_init(seg_data_dir);
			Segmentor::Init();
		}

		void init()
		{
			_rstree.init();
			_post_processor.init();
			//_seg_handle.init(MAX_SEG_BUFSIZE); //

			string section = "RstreeWorker";
			SCONF(_min_text_length);
			SCONF(_max_text_length);
			SCONF(_max_result_count);
			SCONF(_use_seg);
			SCONF(_simple_sort);
		}

		/*
		 * @brief: 合并map，将m2中的key-value对合并入m1，当m2中不包含这个key，或者对应的value值比m1中的大时
		 *
		 */
		void merge_map(std::unordered_map<wstring, int> & m1, const std::unordered_map<wstring, int> & m2)
		{
			for (std::unordered_map<wstring, int>::const_iterator iter = m2.begin(); iter != m2.end(); ++iter)
			{
				std::unordered_map<wstring, int>::iterator iter1 = m1.find(iter->first);
				if (iter1 == m1.end() || iter1->second < iter->second)
				{
					m1[iter->first] = iter->second;
				}
			}
		}

		bool get_postype(const SegHandle& handle, int len, vector<int>& vec)
		{
			vec.resize(len, MIDDLE);
			int start = 0;
			for (int i = 0; i < handle.nresult; i++)
			{
				int end = start + wchar_count(handle.tokens[i].buffer, handle.tokens[i].length);
				if (end > len)
				{
					return false;
				}
				if (end - start > 1)
				{
					vec[start] = LEFT;
					vec[end - 1] = RIGHT;
				}
				else
				{
					vec[start] = SINGLE;
				}
				start = end;
			}
			if (start == len)
			{
				return true;
			}
			else
			{
				vec.clear();
				return false;
			}
		}

		bool get_postype(string sub_c, int len, vector<int>& splits)
		{
			bool ret = Segmentor::Segment_(sub_c);
			if (!ret)
			{
				LOG_WARNING("seg fail %s", sub_c.c_str());
				return false;
			}
			//    print_seg_result(_seg_handle);
			ret = get_postype(Segmentor::handle(), len, splits);
			if (!ret)
			{
				LOG_WARNING("getpos fail for [%s] %d", sub_c.c_str(), len);
			}
			return ret;
		}

		struct Cmp
		{

			bool operator() (const ONode& left, const ONode& right)
			{
				return left.str.length() > right.str.length();
			}
		};

		vector<ONode> get_substrs(string content_, int min_freq, int min_len, int max_len)
		{
			_rstree.set_min_frequency(min_freq);
			_rstree.set_min_substr_len(min_len);
			_rstree.set_max_substr_len(max_len);

			string content = boost::trim_copy(content_);
			boost::replace_all(content, "\n", ""); //rstree的默认结尾填充符号是换行
			wstring wc = str_to_wstr(content);
			vector<ONode> result_vec;
			if ((int)wc.size() < _min_text_length)
			{
				return result_vec;
			}

			std::unordered_map<wstring, int> ret_map;
			vector<wstring> svec = cut_wstring(wc, _max_text_length, max_len + 1);

			//    vector<string> subc_vec;  //黑模式区域识别查询频次用 暂时有bug未用 TODO
			//    vector<vector<int> > splits_vec;
			LOG_DEBUG("Cut to %d parts", (int)svec.size());
			//for (auto &sub_wc : svec)
			for (int i = 0; i < (int)svec.size(); i++)
			{
				wstring& sub_wc = svec[i];

				if ((int)sub_wc.size() < _min_text_length)
				{
					break;
				}

				string sub_c = svec.size() == 1 ? content : wstr_to_str(sub_wc);

				if (sub_c.empty())
				{
					continue;
				}

				vector<WPair > rvec;
				vector<int> splits;
				if (_use_seg)
				{
					bool sucess = get_postype(sub_c, sub_wc.size(), splits);
					if (sucess)
					{
						_rstree.add_find(sub_wc, rvec, &splits);
					}
					else
					{
						_rstree.add_find(sub_wc, rvec);
					}
				}
				else
				{
					_rstree.add_find(sub_wc, rvec);
				}
#ifndef NDEBUG

				foreach(WPair& item, rvec)
				{
					wcout << item.first << " " << item.first.size() << L"\n";
				}
#endif
				_post_adjustor.filter(rvec, _rstree.min_substr_len());
				std::unordered_map<wstring, int> t_ret_map(rvec.begin(), rvec.end());
				merge_map(ret_map, t_ret_map);

				//      subc_vec.push_back(sub_c);
				//      splits_vec.push_back(splits);
			}

			//-----------------post deal trim filter
			vector<INode> ivec;
			for (std::unordered_map<wstring, int>::iterator iter = ret_map.begin(); iter != ret_map.end(); ++iter)
			{
				string substr = wstr_to_str(iter->first);
				if (!substr.empty())
				{
					ivec.push_back(INode(substr, iter->first, iter->second));
				}
			}
			PrintVec2(ivec, str, count);
			//-----------------post black white deal filter and sort choose top max_result_count

			if (!_simple_sort)
			{
				_post_processor.process(ivec, result_vec, _max_result_count);
			}
			else
			{
				for (int i = 0; i < (int)ivec.size(); i++)
				{
					result_vec.push_back(ONode(ivec[i].str, ivec[i].count));
				}
				if (result_vec.size() <= _max_result_count)
				{
					std::sort(result_vec.begin(), result_vec.end(), Cmp());
				}
				else
				{
					std::partial_sort(result_vec.begin(), result_vec.begin() + _max_result_count,
						result_vec.end(), Cmp());
					result_vec.resize(_max_result_count);
				}
			}
			PrintVec4(result_vec, str, filtered_str, count, black_count);

			//    //当前采用最简单补充策略 尝试补充一个黑载体匹配的串
			//    //当返回结果为空 或者不为空 但是第一个black_count == 0的时候 
			//    //对整个文本 content 查询黑载体 并且对于第一个匹配位置 前后扩展 凑成一个长度约为max_len的串 
			//    //转成wstring 去后缀树查询频次 如果满足最低频次 就替换掉result_vec最后一个 然后和第一个交换
			//    if (result_vec.size() == 0 || result_vec[0].black_count == 0)
			//      //    if (result_vec.size() == 0 || result_vec[result_vec.size() - 1].black_count == 0)
			//    {
			//      for (int i = 0; i < (int) subc_vec.size(); i++)
			//      {
			//        if (svec[i].length() > max_len)
			//        {
			//          string spam = _post_processor.get_spam(subc_vec[i]);
			//          if (spam.empty())
			//          {
			//            continue;
			//          }
			//          wstring wspam = str_to_wstr(spam);
			//          if (wspam.empty())
			//          {
			//            continue;
			//          }
			//          size_t idx = svec[i].find(wspam);
			//          if (idx == wstring::npos)
			//          {
			//            continue;
			//          }
			//          int start = idx;
			//          if (start >= 4 && wspam.length() + 4 <= max_len)
			//          {
			//            start -= 4;
			//          }
			//          int end = idx + wspam.length();
			//          if (splits_vec[i].size() == svec[i].length())
			//          {
			//            while (start > 0 && splits_vec[i][start] != LEFT && splits_vec[i][start] != SINGLE)
			//            {
			//              start--;
			//            }
			//          }
			//
			//          while (end < svec[i].length() && end - start < max_len)
			//          {
			//            end++;
			//          }
			//
			//          if (splits_vec[i].size() == svec[i].length())
			//          {
			//            while (end > start && splits_vec[i][end - 1] != RIGHT && splits_vec[i][end - 1] != SINGLE)
			//            {
			//              end--;
			//            }
			//          }
			//
			//          int len = end - start;
			//          if (len >= min_len && len <= max_len)
			//          {
			//            wstring spam_phrase = svec[i].substr(start, len);
			//            int freq = _rstree.find_freq(spam_phrase);
			//            if (freq >= min_freq)
			//            {
			//              ONode node;
			//              node.count = freq;
			//              node.wstr = spam_phrase;
			//              node.str = wstr_to_str(spam_phrase);
			//              node.black_count = 1;
			//              if (!node.str.empty())
			//              {
			//                DLOG(INFO) << "Add spam candiate " << node.str;
			//                Pval(content);
			//                ONode temp = result_vec[0];
			//                result_vec[0] = node;
			//                result_vec[result_vec.size() - 1] = temp;
			//                break;
			//              }
			//            }
			//          }
			//        }
			//      }
			//    }


			return result_vec;
		}

		inline int tree_size()
		{
			return _rstree.tree_size();
		}

	};

} //----end of namespace gezi

#endif  //----end of RSTREE_WORKER_H_
