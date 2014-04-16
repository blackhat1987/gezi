/**
 *  ==============================================================================
 *
 *          \file   stl_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-17 16:42:05.935579
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef STL_UTIL_H_
#define STL_UTIL_H_

#include "common_def.h"
#include "convert_type.h"
#include "map_util.h"
#include <boost/lexical_cast.hpp>
namespace gezi {
	template<typename T>
	std::string join(const std::vector<T>& vec, const std::string& sep = " ")
	{
		if (vec.empty())
		{
			return "";
		}
		std::stringstream s;
		size_t i = 0;
		for (; i < vec.size() - 1; i++)
		{
			s << vec[i] << sep;
		}
		s << vec[i];
		return s.str();
	}

	template<typename Iter>
	std::string join(Iter begin, Iter end, const std::string& sep = " ")
	{
		if (begin == end)
		{
			return "";
		}
		std::stringstream s;
		Iter it = begin;
		s << *it++;
		for (; it != end; ++it)
		{
			s << sep << *it;
		}
		return s.str();
	}

	template<typename T>
	std::string get_jason(const std::vector<T>& vec)
	{
		std::vector<string> rvec;
		for (int i = 0; i < (int)vec.size(); i++)
		{
			string kv = (format("\"%1%\":\"%2%\"") % STR(i) % STR(vec[i])).str();
			rvec.push_back(kv);
		}
		return (format("{%1%}") % join(rvec, ",")).str();
	}

	template<typename T>
	std::string get_jason(const std::vector<T>& vec, int len)
	{
		std::vector<string> rvec;
		for (int i = 0; i < len; i++)
		{
			string kv = (format("\"%1%\":\"%2%\"") % STR(i) % STR(vec[i])).str();
			rvec.push_back(kv);
		}
		return (format("{%1%}") % join(rvec, ",")).str();
	}

	

	inline vector<string> to_vec(string input_, string sep = ",")
	{
		vector<string> vec;
		string input = boost::trim_copy(input_);
		boost::split(vec, input, is_any_of(sep));

		foreach(string& str, vec)
		{
			boost::trim(str);
		}
		return vec;
	}

	//@TODO trim好像很慢 回头把依赖 需要trim的代码 改为使用 split_safe
	/*inline vector<string> split(string input_, string sep = "\t ")
	{
		vector<string> vec;
		string input = boost::trim_copy(input_);
		boost::split(vec, input, is_any_of(sep));

		foreach(string str, vec)
		{
			boost::trim(str);
		}
		return vec;
	}*/

	//this one is speed similar to boost::split(container, str, std::bind1st(std::equal_to<char>(), ','));
	inline std::vector<std::string> split2(std::string s, const char delimiter)
	{
		size_t start = 0;
		size_t end = s.find_first_of(delimiter);

		std::vector<std::string> output;

		while (end <= std::string::npos)
		{
			output.emplace_back(s.substr(start, end - start));

			if (end == std::string::npos)
				break;

			start = end + 1;
			end = s.find_first_of(delimiter, start);
		}

		return output;
	}

	inline vector<string> split(string input, char sep)
	{
		vector<string> vec;
		boost::split(vec, input, std::bind1st(std::equal_to<char>(), sep));
		return vec;
	}

	inline vector<string> split(string input, string sep = "\t ")
	{
		vector<string> vec;
		if (sep.size() == 1)
		{
			boost::split(vec, input, std::bind1st(std::equal_to<char>(), sep[0]));
		}
		else
		{
			boost::split(vec, input, is_any_of(sep));
		}
		return vec;
	}

	inline bool split(string input, string sep, string& first, string& second)
	{
		int index = sep.size() == 1 ? input.find(sep[0]) : input.find(sep);
		if (index == string::npos)
		{
			return false;
		}
		
		first = input.substr(0, index);
		second = input.substr(index + sep.size());
		return true;
	}

	inline bool split(string input, const char sep, string& first, string& second)
	{
		int index = input.find(sep);
		if (index == string::npos)
		{
			return false;
		}
		first = input.substr(0, index);
		second = input.substr(index + 1);
		return true;
	}

	//@TODO 去掉trim 带trim的统一后缀 _safe
	//TODO FIXME 貌似比如 "1, 2, 3"这样还是处理不了会抛异常 按说trim了
	template<typename T>
	inline void to_vec(string input_, vector<T>& ovec, string sep = ",")
	{
		vector<string> vec;
		string input = boost::trim_copy(input_);
		boost::split(vec, input, is_any_of(sep));

		foreach(string str, vec)
		{
			boost::trim(str);
			ovec.push_back(boost::lexical_cast<T>(str));
		}
	}

	template<typename T>
	void convert(const vector<string>&ivec, vector<T>& ovec)
	{
		foreach(const string item, ivec)
		{
			ovec.push_back(boost::lexical_cast<T>(item));
		}
	}
	
	template<typename T>
	int compare(T a, T b)
	{
		if (a == b)
		{
			return 0;
		}
		else if (a < b)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}

	template<typename Vec>
	void free_memory(Vec& vec)
	{
		vec.clear();
		vec.shrink_to_fit();
	}

	template<typename Map>
	void free_map(Map& m)
	{
		m.clear();
		Map().swap(m);
	}

	//广义相同 即完全内存位置一样的两个vector 或者 两个空vector 
	//类似C# both null or point to the same a.indices == b.indices
	template<typename Vec>
	bool generalized_same(const Vec& l, const Vec& r)
	{
		return &l == &r || l.empty() && r.empty();
	}
}  //----end of namespace gezi

#endif  //----end of STL_UTIL_H_
