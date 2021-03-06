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
  string join(const vector<T>& vec, const string& sep = " ")
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
  string join(Iter begin, Iter end, const string& sep = " ")
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
  vector<T> join_vec2d(const vector<vector<T> >& input)
  {
    vector<T> result;
    for (auto& vec : input)
    {
      for (auto& item : vec)
      {
        result.push_back(item);
      }
    }
    return result;
  }

  template<typename T>
  string get_json(const vector<T>& vec)
  {
    vector<string> rvec;
    for (int i = 0; i < (int)vec.size(); i++)
    {
      //string kv = (format("\"%1%\":\"%2%\"") % STR(i) % STR(vec[i])).str();
      string kv = format("\"{}\":\"{}\"", i, vec[i]);
      rvec.push_back(kv);
    }
    //return (format("{%1%}") % join(rvec, ",")).str();
    return format("{{{}}}", join(rvec, ","));
  }

  template<typename T>
  string get_json(const vector<T>& vec, int len)
  {
    vector<string> rvec;
    for (int i = 0; i < len; i++)
    {
      //string kv = (format("\"%1%\":\"%2%\"") % STR(i) % STR(vec[i])).str();
      string kv = format("\"{}\":\"{}\"", i, vec[i]);
      rvec.push_back(kv);
    }
    //return (format("{%1%}") % join(rvec, ",")).str();
    return format("{{{}}}", join(rvec, ","));
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
  inline vector<string> split2(string s, const char delimiter)
  {
    size_t start = 0;
    size_t end = s.find_first_of(delimiter);

    vector<string> output;

    while (end <= string::npos)
    {
      output.emplace_back(s.substr(start, end - start));

      if (end == string::npos)
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
    size_t index = input.find(sep);
    if (index == string::npos)
    {
      return false;
    }

    first = input.substr(0, index);
    second = input.substr(index + sep.size());
    return true;
  }

  inline bool split_first_of(string input, string sep, string& first, string& second)
  {
    size_t index = input.find_first_of(sep);
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
    size_t index = input.find_first_of(sep);
    if (index == string::npos)
    {
      return false;
    }
    first = input.substr(0, index);
    second = input.substr(index + 1);
    return true;
  }

  inline bool split(string input, string sep, string& first, string& second, string& third)
  {
    size_t index = input.find(sep);
    if (index == string::npos)
    {
      return false;
    }

    first = input.substr(0, index);

    index += sep.size();
    size_t index2 = input.find(sep, index);
    if (index2 == string::npos)
    {
      return false;
    }

    second = input.substr(index, index2 - index);

    third = input.substr(index2 + sep.size());
    return true;
  }

  inline bool split(string input, const char sep, string& first, string& second, string& third)
  {
    size_t index = input.find_first_of(sep);
    if (index == string::npos)
    {
      return false;
    }

    first = input.substr(0, index);

    index += 1;
    size_t index2 = input.find_first_of(sep, index);
    if (index2 == string::npos)
    {
      return false;
    }

    second = input.substr(index, index2 - index);
    third = input.substr(index2 + 1);
    return true;
  }

  template<typename T>
  bool split(string input, const char sep, int& first, T& second)
  {
    size_t index = input.find(sep);
    if (index == string::npos)
    {
      return false;
    }
    first = INT(input);
    second = DOUBLE_(input.c_str() + index + 1);
    return true;
  }

  //自己确保len不超过input的尾部！ 模仿string.find(char)的风格
  inline size_t find_char(string input, const char mark, int start, int len)
  {
    auto begin = input.begin() + start;
    auto end = begin + len;
    auto it = std::find(begin, end, mark);
    if (it != end)
    {
      return (size_t)(it - input.begin());
    }
    else
    {
      return string::npos;
    }
  }


  inline unsigned int fast_atou(const char* str)
  {
    unsigned int val = 0;
    while (*str) {
      val = (val << 1) + (val << 3) + *(str++) - 48;
    }
    return val;
  }

  inline unsigned int fast_atou(const char* str, const char* end)
  {
    unsigned int val = 0;
    while (str != end) {
      val = (val << 1) + (val << 3) + *(str++) - 48;
    }
    return val;
  }


  inline int fast_atoi(const char *buff)
  {
    int c = 0, sign = 0, x = 0;
    const char *p = buff;

    for (c = *(p++); (c < 48 || c > 57); c = *(p++)) { if (c == 45) { sign = 1; c = *(p++); break; } }; // eat whitespaces and check sign
    for (; c > 47 && c < 58; c = *(p++)) x = (x << 1) + (x << 3) + c - 48;

    return sign ? -x : x;
  }

  //inline int fast_atoi(const char *buff, const char * end)
  //{
  //	int c = 0, sign = 0, x = 0;
  //	const char *p = buff;

  //	for (c = *(p++); (c < 48 || c > 57); c = *(p++)) { if (c == 45) { sign = 1; c = *(p++); break; } }; // eat whitespaces and check sign
  //	for (; c > 47 && c < 58; c = *(p++)) x = (x << 1) + (x << 3) + c - 48;

  //	return sign ? -x : x;
  //}

  //@TODO 这个版本是 uint + double 用于sparse格式的特征文件解析 InstanceParser.h 泛化或者放到其它位置
  template<typename FindFunc, typename UnfindFunc>
  void splits_int_double(string input, const char sep, const char inSep, FindFunc findFunc, UnfindFunc unfindFunc)
  {
    size_t pos = 0;
    size_t pos2 = input.find(sep);
    int i = 0;
    while (pos2 != string::npos)
    {
      int len = pos2 - pos;
      //why find_char so slow.... 
      //size_t inPos = find_char(input, inSep, pos, len);
      size_t inPos = input.find(inSep, pos);
      //if (inPos != string::npos)
      if (inPos < pos2) //这个查找可以优化 但是问题不大。。暂时没找到好的方法 改为find_char速度更慢很多
      {
        //findFunc(atoi(input.c_str() + pos), atof(input.c_str() + inPos + 1));
        findFunc(fast_atou(input.c_str() + pos, input.c_str() + inPos), atof(input.c_str() + inPos + 1));
      }
      else
      {
        unfindFunc(i, input.substr(pos, len));
      }
      pos = pos2 + 1;
      pos2 = input.find(sep, pos);
      i++;
    }
    size_t inPos = input.find(inSep, pos);
    findFunc(atoi(input.c_str() + pos), atof(input.c_str() + inPos + 1));
  }

  template<typename Func>
  int split_enumerate(string input, const char sep, Func func)
  {
    size_t pos = 0;
    size_t pos2 = input.find(sep);
    int i = 0;
    while (pos2 != string::npos)
    {
      func(i, pos, pos2 - pos);
      pos = pos2 + 1;
      pos2 = input.find(sep, pos);
      i++;
    }
    func(i, pos, input.length() - pos);
    return i + 1;
  }
  //@TODO rename
  template<typename FindFunc, typename UnfindFunc>
  void splits_string_double(string input, const char sep, const char inSep, FindFunc findFunc, UnfindFunc unfindFunc)
  {
    size_t pos = 0;
    size_t pos2 = input.find(sep);
    int i = 0;
    while (pos2 != string::npos)
    {
      int len = pos2 - pos;
      //why find_char so slow.... 
      //size_t inPos = find_char(input, inSep, pos, len);
      size_t inPos = input.find(inSep, pos);
      //if (inPos != string::npos)
      if (inPos < pos2) //这个查找可以优化 但是问题不大。。暂时没找到好的方法 改为find_char速度更慢很多
      {
        //findFunc(atoi(input.c_str() + pos), atof(input.c_str() + inPos + 1));
        findFunc(input.substr(pos, inPos - pos), atof(input.c_str() + inPos + 1));
      }
      else
      {
        unfindFunc(i, input.substr(pos, len));
      }
      pos = pos2 + 1;
      pos2 = input.find(sep, pos);
      i++;
    }
    size_t inPos = input.find(inSep, pos);
    findFunc(input.substr(pos, inPos - pos), atof(input.c_str() + inPos + 1));
  }

  //假设都是类似 1:3 2:6 7:9 标准样式的解析
  template<typename FindFunc>
  void splits_int_double(string input, const char sep, const char inSep, FindFunc findFunc)
  {
    size_t pos = 0;
    size_t pos2 = input.find(sep);
    while (pos2 != string::npos)
    {
      int len = pos2 - pos;
      input[pos + len] = '\0';
      size_t inPos = input.find(inSep, pos);
      findFunc(atoi(input.c_str() + pos), atof(input.c_str() + inPos + 1));
      pos = pos2 + 1;
      pos2 = input.find(sep, pos);
    }
    size_t inPos = input.find(inSep, pos);
    findFunc(atoi(input.c_str() + pos), atof(input.c_str() + inPos + 1));
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

  inline vector<double> to_dvec(string input, const char sep)
  {
    vector<double> vec;
    int preIndex = 0, index = 0;
    while (index < input.size())
    {
      index = input.find_first_of(sep, preIndex);
      vec.push_back(atof(input.substr(preIndex, index - preIndex).c_str()));
      preIndex = index + 1;
    }
    vec.push_back(atof(input.substr(preIndex).c_str()));
    return vec;
  }

  template<typename T>
  void covert_append(const vector<string>&ivec, vector<T>& ovec)
  {
    for (string item : ivec)
    {
      ovec.push_back(boost::lexical_cast<T>(item));
    }
  }

  template<typename T>
  void convert(const vector<string>&ivec, vector<T>& ovec)
  {
    ovec.resize(ivec.size());
    for (size_t i = 0; i < ivec.size(); i++)
    {
      ovec[i] = boost::lexical_cast<T>(ivec[i]);
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


  //@TODO maybe shold be append?
  //两个vector合并结果存储到第一个vector,注意第二个数组不再有效 @TODO验证对map正确 注意两个容器需要类型一样 bool int这种不行
  template<typename Container>
  void merge(Container& dest, Container& src)
  {
    dest.insert(
      dest.end(),
      std::make_move_iterator(src.begin()),
      std::make_move_iterator(src.end())
      );
  }

  template<typename Container>
  void append(Container& dest, Container&& src)
  {
    dest.insert(
      dest.end(),
      std::make_move_iterator(src.begin()),
      std::make_move_iterator(src.end())
      );
  }

  template<typename Container>
  void append(Container& dest, Container& src)
  {
    dest.insert(
      dest.end(),
      std::make_move_iterator(src.begin()),
      std::make_move_iterator(src.end())
      );
  }

  template<typename Container>
  void merge(Container& dest, Container&& src)
  {
    dest.insert(
      dest.end(),
      std::make_move_iterator(src.begin()),
      std::make_move_iterator(src.end())
      );
  }

  template<typename Container, typename Container2>
  void merge_map(Container& dest, Container2& src)
  {
    for (auto& item : src)
    {
      dest[item.first] = item.second;
    }
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

    return (*std::max_element(m.begin(), m.end(), [](const ItemType& l, const ItemType& r) { return l.second.size() < r.second.size(); })).second.size();
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

    return (*std::min_element(m.begin(), m.end(), [](const ItemType& l, const ItemType& r) { return l.second.size() < r.second.size(); })).second.size();
  }

  template<typename Container, typename Container2>
  void add_vec(Container& vec1, const Container2& vec2)
  {
    for (size_t i = 0; i < vec1.size(); i++)
    {
      vec1[i] += vec2[i];
    }
  }

  template<typename Container, typename Container2>
  void vec_add(Container& vec1, const Container2& vec2)
  {
    for (size_t i = 0; i < vec1.size(); i++)
    {
      vec1[i] += vec2[i];
    }
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




  //@TODO select_many cpplinq
  //	//@TODO select_many not work as this , how to use?
  //	//auto perInstanceColumns = from(datasetMetrics) >> select_many([](const DatasetMetricsPtr& m) { return m->PerInstanceColumnNames(); }) >>  >> to_vector();
  template<typename T, typename U, typename Func>
  vector<T> join_vec(const vector<U>& input, Func func)
  {
    vector<T> result;
    if (input.empty())
    {
      return result;
    }
    result = func(input[0]);
    for (size_t i = 1; i < input.size(); i++)
    {
      //@TODO can do this?
      merge(result, func(input[i]));
      //vector<T> temp = func(input[i]);
      //merge(result, temp);
    }
    return result;
  }

  template<typename T, typename U>
  void print(const vector<T>& names, const vector<U>& results, string inSep = "\t", string outSep = "\n", int space = 40)
  {
    for (size_t i = 0; i < names.size(); i++)
    {
      std::cerr << std::setiosflags(std::ios::left) << std::setfill(' ') << std::setw(space)
        << names[i] << inSep
        << results[i] << outSep;
    }
  }

  template<typename T, typename U>
  void print_key_value(const T& name, const U& result, string inSep = "", string outSep = "\n", int space = 40)
  {
    std::cerr << std::setiosflags(std::ios::left) << std::setfill(' ') << std::setw(space)
      << name + inSep
      << result << outSep;
  }

  template<typename T, typename U>
  string print2str(const vector<T>& names, const vector<U>& results, string inSep = "", string outSep = "\n", int space = 40)
  {
    std::stringstream ss;
    for (size_t i = 0; i < names.size(); i++)
    {
      ss << std::setiosflags(std::ios::left) << std::setfill(' ') << std::setw(space)
        << STR(names[i]) + inSep
        << results[i] << outSep;
    }
    return ss.str();
  }

  template<typename T, typename U>
  string print2str_row(const vector<T>& names, const vector<U>& results, int space = 40, string inSep = ":", char outSep = ' ')
  {
    std::stringstream ss;
    for (size_t i = 0; i < names.size(); i++)
    {
      ss << names[i] << inSep
        << std::setiosflags(std::ios::left) << std::setfill(outSep) << std::setw(space)
        << results[i]
        << outSep;
    }
    return ss.str();
  }
  //将数组中最大的转为1 其余norm到0-1, 需要输入数组都是正数
  template<typename Vec>
  void normalize_vec(Vec& vec)
  {
    Float maxValue = *(std::max_element(vec.begin(), vec.end()));
    Float normalizingFactor = (maxValue != 0) ? std::sqrt(maxValue) : 1.0;
    for (auto& item : vec)
    {
      item = std::sqrt(item) / normalizingFactor;
    }
  }

  template<typename Vec, typename T>
  void reset_vec(Vec& vec, int len, T value)
  {
    for (auto& item : vec)
    {
      item = value;
    }
    vec.resize(len, value);
  }

  template<typename T>
  inline T* begin_ptr(vector<T>& vec)
  {
    return vec.empty() ? NULL : &vec[0];
  }

  template<typename T>
  inline const T* begin_ptr(const vector<T>& vec)
  {
    return vec.empty() ? NULL : &vec[0];
  }

  inline vector<int> range_vec(size_t length)
  {
    vector<int> indexVec(length);
    for (size_t i = 0; i < length; i++)
    {
      indexVec[i] = i;
    }
    return indexVec;
  }
}  //----end of namespace gezi

#endif  //----end of STL_UTIL_H_
