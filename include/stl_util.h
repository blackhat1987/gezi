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
#include "map_util.h"
#include <boost/lexical_cast.hpp>
#define TO_STRING boost::lexical_cast<std::string>
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
			string kv = (format("\"%1%\":\"%2%\"") % TO_STRING(i) % TO_STRING(vec[i])).str();
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
			string kv = (format("\"%1%\":\"%2%\"") % TO_STRING(i) % TO_STRING(vec[i])).str();
			rvec.push_back(kv);
		}
		return (format("{%1%}") % join(rvec, ",")).str();
	}

	

	inline vector<string> to_vec(const string& input_, const string& sep = ",")
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

	inline vector<string> split(const string& input_, const string& sep = "\t ")
	{
		vector<string> vec;
		string input = boost::trim_copy(input_);
		boost::split(vec, input, is_any_of(sep));

		foreach(string str, vec)
		{
			boost::trim(str);
		}
		return vec;
	}

	//TODO FIXME 貌似比如 "1, 2, 3"这样还是处理不了会抛异常 按说trim了
	template<typename T>
	inline void to_vec(const string& input_, vector<T>& ovec, const string& sep = ",")
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
	
}  //----end of namespace gezi

#undef TO_STRING
#endif  //----end of STL_UTIL_H_
