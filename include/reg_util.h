/**
 *  ==============================================================================
 *
 *          \file   reg_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-12-22 17:10:03.133824
 *
 *  \Description: boost 正则处理中文也是可能有问题的 try to use c++11 @TODO
 *  ==============================================================================
 */

#ifndef REG_UTIL_H_
#define REG_UTIL_H_

#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
using boost::regex;
using boost::algorithm::split_regex;
using std::string;
using std::wstring;
using std::vector;
namespace gezi
{
	//-------------------regex realted
	//由于boost 的接口是 const string& 所以这里都用 const string& 另外 尽管实际效果一样
	//但是string 和 const string& 是两个函数了 可重载 具体匹配如何 @TODO
	//regex_earch接口 寻找满足整个匹配的 放到0位置，然后对应所有()内的内部匹配结果依次向后存储
	//比如
	//content.substr(it - content.begin())-- - [约咆圣网：<a href = "http://nazr.in/Dqi" target = "_blank">http://nazr.in/Dqi</a>]
	// string(item.first, item.second)-- - [<a href = "http://nazr.in/Dqi" target = "_blank">]
	//string(item.first, item.second)-- - [<a href = "http://nazr.in/Dqi" target = "_blank">]
	//string(item.first, item.second)-- - [http://nazr.in/Dqi]
	//正则表达式是(<a.*? href=\"(.+?)\".*?>)  我们关注的是内部那个()抽取url的算是第二个 index 需要2或者去掉最外层()
	inline string reg_search(const string& content, boost::regex& reg, int index = 1)
	{
		boost::smatch m;
		if (boost::regex_search(content, m, reg))
		{
			return string(m[index].first, m[index].second);
		}
		return "";
	}

//#include "debug_util.h"
	inline void reg_search(const string& content, boost::regex& reg, vector<string>& result, int index = 1)
	{
		boost::smatch m;
		string::const_iterator it = content.begin();
		while (boost::regex_search(it, content.end(), m, reg))
		{
			/*		Pval(content);
					Pval(content.substr(it - content.begin()));
					Pval(reg.str());
					for (auto item : m)
					{
					Pval(string(item.first, item.second));
					}*/
			result.push_back(string(m[index].first, m[index].second));
			it = m[0].second;
		}
	}

	inline wstring reg_search(const wstring& content, boost::wregex& reg, int index = 1)
	{
		boost::wsmatch m;
		if (boost::regex_search(content, m, reg))
		{
			return wstring(m[index].first, m[index].second);
		}
		return L"";
	}

	inline void reg_search(const wstring& content, boost::wregex& reg, vector<wstring>& result, int index = 1)
	{
		boost::wsmatch m;
		wstring::const_iterator it = content.begin();
		while (boost::regex_search(it, content.end(), m, reg))
		{
			result.push_back(wstring(m[index].first, m[index].second));
			it = m[0].second;
		}
	}
	inline bool reg_find(const string& content, string pattern)
	{
		boost::regex reg(pattern);
		boost::smatch m;
		return boost::regex_search(content, m, reg);
	}
	inline string reg_search(const string& content, string pattern, int index = 1)
	{
		boost::regex reg(pattern);
		return reg_search(content, reg, index);
	}

	inline void reg_search(const string& content, string pattern, vector<string>& result, int index = 1)
	{
		boost::regex reg(pattern);
		reg_search(content, reg, result, index);
	}

	inline wstring reg_search(const wstring& content, wstring pattern, int index = 1)
	{
		boost::wregex reg(pattern);
		return reg_search(content, reg, index);
	}

	inline void reg_search(const wstring& content, wstring pattern, vector<wstring>& result, int index = 1)
	{
		boost::wregex reg(pattern);
		reg_search(content, reg, result, index);
	}

	inline string reg_replace(const string& input, string pattern, string replacement = "")
	{
		boost::regex reg(pattern);
		return boost::regex_replace(input, reg, replacement);
	}

	inline wstring reg_replace(const wstring& input, wstring pattern, wstring replacement = L"")
	{
		boost::wregex reg(pattern);
		return boost::regex_replace(input, reg, replacement);
	}

	inline string reg_remove(const string& input, string pattern)
	{
		boost::regex reg(pattern);
		return boost::regex_replace(input, reg, "");
	}

	inline wstring reg_remove(const wstring& input, wstring pattern)
	{
		boost::wregex reg(pattern);
		return boost::regex_replace(input, reg, L"");
	}

	//@TODO http://www.boost.org/doc/libs/1_46_1/libs/regex/doc/html/boost_regex/ref/regex_token_iterator.html
	inline vector<string> reg_split(const string& input, string pattern)
	{
		vector<string> vec;
		boost::regex reg(pattern);
		split_regex(vec, input, reg); //@TODO 为什么用iterator不直接用split_regex? 效果一样 速度也差不多 复杂写法
		//更灵活一点 后面不是-1 可以匹配其它的部分 -1 是反向匹配 也就是变成了split 当然连续reg_search也一样
		/*boost::sregex_token_iterator i(input.begin(), input.end(), reg, -1);
		boost::sregex_token_iterator j;
		while (i != j)
		{
			vec.push_back(*i++);
		}*/
		return vec;
	}

	inline vector<wstring> reg_split(const wstring& input, wstring pattern)
	{
		vector<wstring> vec;
		boost::wregex reg(pattern);
		split_regex(vec, input, reg);
		/*boost::wsregex_token_iterator i(input.begin(), input.end(), reg, -1);
		boost::wsregex_token_iterator j;
		while (i != j)
		{
			vec.push_back(*i++);
		}*/
		return vec;
	}

	namespace ufo
	{
		inline vector<string> split_regex(const string& input, string pattern)
		{
			vector<string> vec;
			boost::regex reg(pattern);
			split_regex(vec, input, reg); 
			return vec;
		}

		inline vector<string> reg_search(const string& content, boost::regex& reg, int index = 1)
		{
			vector<string> result;
			gezi::reg_search(content, reg, result, index);
			return result;
		}

		inline vector<string> reg_search(const string& content, string pattern, int index = 1)
		{
			vector<string> result;
			boost::regex reg(pattern);
			gezi::reg_search(content, reg, result, index);
			return result;
		}

		inline vector<wstring> reg_search(const wstring& content, boost::wregex& reg, int index = 1)
		{
			vector<wstring> result;
			gezi::reg_search(content, reg, result, index);
			return result;
		}

		inline vector<wstring> wreg_search(const wstring& content, wstring pattern, int index = 1)
		{
			vector<wstring> result;
			boost::wregex reg(pattern);
			gezi::reg_search(content, reg, result, index);
			return result;
		}

	}
}

#endif  //----end of REG_UTIL_H_
