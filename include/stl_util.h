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

	template<typename Vec>
	inline vector<Vec> split(const Vec& input, int length)
	{
		vector<Vec> result;
		Vec temp;
		for (int i = 0; i < input.size(); i++)
		{
			if (i % length == 0 && i)
			{
				result.push_back(temp);
				temp.clear();
			}
			temp.push_back(input[i]);
		}
		if (!temp.empty())
		{
			result.push_back(temp);
		}
		return result;
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

	inline vector<string> splits(string s, string delim, bool keep_empty = true)
	{
		vector<string> result;
		string::iterator substart = s.begin(), subend;
		while (true) {
			subend = search(substart, s.end(), delim.begin(), delim.end());
			string temp(substart, subend);
			if (keep_empty || !temp.empty()) {
				result.push_back(temp);
			}
			if (subend == s.end()) {
				break;
			}
			substart = subend + delim.size();
		}
		return result;
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
	vector<string> convert(const vector<T>& ivec)
	{
		vector<string> resultVec(ivec.size());
		for (size_t i = 0; i < ivec.size(); i++)
		{
			resultVec[i] = STR(ivec[i]);
		}
		return resultVec;
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
		return ((&l == &r) || (l.empty() && r.empty()));
	}

	//两个vector合并结果存储到第一个vector,注意第二个数组不再有效 @TODO验证对map正确
	template<typename Container>
	void merge(Container& dest, Container& src)
	{
		dest.insert(
			dest.end(),
			std::make_move_iterator(src.begin()),
			std::make_move_iterator(src.end())
			);
	}

	template<typename Vec>
	int non_empty_count(const Vec& vecs)
	{
		int count = 0;
		for (auto& vec : vecs)
		{
			if (!vec.empty())
			{
				count++;
			}
		}
		return count;
	}

	//类似vector<vector<>>遍历计数
	template<typename Vec>
	int distinct_count_vec2d(const Vec& vecs)
	{
		typedef typename Vec::value_type::value_type Value;
		set<Value> set_;
		for (const auto& vec : vecs)
		{
			for (const auto& item : vec)
			{
				set_.insert(item);
			}
		}
		return set_.size();
	}


	template<typename Vec, typename Func>
	void process_adjacent(Vec& vec, Func func)
	{
		for (size_t i = 1; i < vec.size(); i++)
		{
			func(vec[i - 1], vec[i]);
		}
	}

	template<typename Vec1, typename Vec2, typename Func>
	void process_adjacent_when_unequal(Vec1& vec, const Vec2& conditons, Func func)
	{
		for (size_t i = 1; i < conditons.size(); i++)
		{
			if (conditons[i] != conditons[i - 1])
			{
				func(vec[i - 1], vec[i]);
			}
		}
	}

	template<typename Vec1, typename Vec2, typename Func>
	Vec1 filter_adjacent_when_unequal(const Vec1& vec, const Vec2& conditons, Func func)
	{
		Vec1 results;
		for (size_t i = 1; i < conditons.size(); i++)
		{
			if (conditons[i] == conditons[i - 1])
			{
				results.push_back(func(vec[i - 1], vec[i]));
			}
		}
		return results;
	}

	template<typename Vec1, typename Vec2, typename Func>
	void process_adjacent_when_equal(Vec1& vec, const Vec2& conditons, Func func)
	{
		for (size_t i = 1; i < conditons.size(); i++)
		{
			if (conditons[i] == conditons[i - 1])
			{
				func(vec[i - 1], vec[i]);
			}
		}
	}

	template<typename Vec1, typename Vec2, typename Func>
	Vec1 filter_adjacent_when_equal(const Vec1& vec, const Vec2& conditons, Func func)
	{
		Vec1 results;
		for (size_t i = 1; i < conditons.size(); i++)
		{
			if (conditons[i] != conditons[i - 1])
			{
				results.push_back(func(vec[i - 1], vec[i]));
			}
		}
		return results;
	}

	template<typename Vec>
	Vec to_delta_vec(const Vec& vec)
	{
		Vec deltaVec;
		for (size_t i = 1; i < vec.size(); i++)
		{
			deltaVec.push_back(vec[i] - vec[i - 1]);
		}
		return deltaVec;
	}

	template<typename Vec, typename Vec2>
	Vec to_delta_vec_when_unequal(const Vec& vec, const Vec2& vec2)
	{
		Vec deltaVec;
		for (size_t i = 1; i < vec2.size(); i++)
		{
			if (vec2[i - 1] != vec2[i])
			{
				deltaVec.push_back(vec[i] - vec[i - 1]);
			}
		}
		return deltaVec;
	}

	template<typename Vec>
	Vec to_delta_rvec(const Vec& vec)
	{
		Vec deltaVec;
		for (size_t i = 1; i < vec.size(); i++)
		{
			deltaVec.push_back(vec[i - 1] - vec[i]);
		}
		return deltaVec;
	}

	template<typename Vec, typename Vec2>
	Vec to_delta_rvec_when_unequal(const Vec& vec, const Vec2& vec2)
	{
		Vec deltaVec;
		for (size_t i = 1; i < vec2.size(); i++)
		{
			if (vec2[i - 1] != vec2[i])
			{
				deltaVec.push_back(vec[i - 1] - vec[i]);
			}
		}
		return deltaVec;
	}

	template<typename Vec, typename Func>
	Vec to_delta_vec(const Vec& vec, Func func)
	{
		Vec deltaVec;
		for (size_t i = 1; i < vec.size(); i++)
		{
			deltaVec.push_back(func(vec[i - 1], vec[i]));
		}
		return deltaVec;
	}

	//例如一组数据中对应uid最多的ip的uid数目
	template<typename DestVec, typename RefVec>
	int max_count_by(const DestVec& uids, const RefVec& ips)
	{
		typedef typename RefVec::value_type KeyType;
		typedef typename DestVec::value_type ValueType;
		map<KeyType, set<ValueType> > m;
		typedef typename map<KeyType, set<ValueType> >::value_type ItemType;
		int len = std::min(uids.size(), ips.size());
		for (int i = 0; i < len; i++)
		{
			m[ips[i]].insert(uids[i]);
		}

		return (*max_element(m.begin(), m.end(), [](const ItemType& l, const ItemType& r) { return l.second.size() < r.second.size(); })).second.size();
	}

	template<typename DestVec, typename RefVec>
	int min_count_by(const DestVec& uids, const RefVec& ips)
	{
		typedef typename RefVec::value_type KeyType;
		typedef typename DestVec::value_type ValueType;
		map<KeyType, set<ValueType> > m;
		typedef typename map<KeyType, set<ValueType> >::value_type ItemType;
		int len = std::min(uids.size(), ips.size());
		for (int i = 0; i < len; i++)
		{
			m[ips[i]].insert(uids[i]);
		}

		return (*min_element(m.begin(), m.end(), [](const ItemType& l, const ItemType& r) { return l.second.size() < r.second.size(); })).second.size();
	}

	namespace ufo
	{
		template<typename Container>
		vector<typename Container::value_type> set_symmetric_difference(const Container& l, const Container& r)
		{
			vector<typename Container::value_type> results;
			std::set_symmetric_difference(l.begin(), l.end(), r.begin(), r.end(), std::back_inserter(results));
			return results;
		}

		template<typename Container>
		vector<typename Container::value_type> set_difference(const Container& l, const Container& r)
		{
			vector<typename Container::value_type> results;
			std::set_difference(l.begin(), l.end(), r.begin(), r.end(), std::back_inserter(results));
			return results;
		}

		template<typename Container, typename T>
		void erase(Container& vec, const T& value)
		{
			vec.erase(std::remove(vec.begin(), vec.end(), value),
				vec.end());
		}

		template<typename Container, typename Func>
		void erase_if(Container& vec, Func func)
		{
			vec.erase(std::remove_if(vec.begin(), vec.end(), func),
				vec.end());
		}
	}//---- end of namespace ufo

	
}  //----end of namespace gezi

#endif  //----end of STL_UTIL_H_
