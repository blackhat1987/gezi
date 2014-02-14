/** 
 *  ==============================================================================
 * 
 *          \file   common_util.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2010-11-15 16:33:52.681821
 *  
 *  \Description:  FIXME remove stl_help.h
 *  ==============================================================================
 */

#ifndef COMMON_UTIL_H_
#define COMMON_UTIL_H_

#include <stdlib.h>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <gtest/gtest.h> 
#include <glog/logging.h>
#include <gflags/gflags.h>

#include "common_def.h"

#include "hashmap_util.h"
#include "log_util.h"
#include "conf_util.h"
#include "debug_util.h"
#include "string_util.h"
#include "serialize_util.h"
#include "Matrix.h"
#include "sort_util.h"

#include <boost/lexical_cast.hpp>

namespace gezi
{

template<typename T, typename U>
T lexical_cast(U input)
{
  T result;
  stringstream s;
  s << input;
  s >> result;
  return result;
}
}

#define TO_INT boost::lexical_cast<int>
#define TO_UINT boost::lexical_cast<unsigned int>
#define TO_INT64 boost::lexical_cast<long long>
#define TO_UINT64 boost::lexical_cast<unsigned long long>
#define TO_BOOL boost::lexical_cast<bool>
#define TO_FLOAT boost::lexical_cast<float>
#define TO_DOUBLE boost::lexical_cast<double>
#define TO_STRING boost::lexical_cast<std::string>
#define INT boost::lexical_cast<int>
#define UINT boost::lexical_cast<unsigned int>
#define INT64 boost::lexical_cast<long long>
#define UINT64 boost::lexical_cast<unsigned long long>
#define BOOL boost::lexical_cast<bool>
#define FLOAT boost::lexical_cast<float>
#define DOUBLE boost::lexical_cast<double>
#define STRING boost::lexical_cast<std::string>
#define STR boost::lexical_cast<std::string>

//gezi lexical_cast 可以比如 1.0 转成int 1, 包括模板里面可以 string -> string转换 方便模板统一处理
//但是并不安全所以不再提供define 需要直接使用 不安全的情况如 vec[0] --- [Instance] UINT64(vec[0]) --- [18619200]
//#define TO_INT boost::lexical_cast<int>
//#define TO_UINT boost::lexical_cast<unsigned int>
//#define TO_INT64 boost::lexical_cast<long long>
//#define TO_UINT64 boost::lexical_cast<unsigned long long>
//#define TO_BOOL boost::lexical_cast<bool>
//#define TO_FLOAT boost::lexical_cast<float>
//#define TO_DOUBLE boost::lexical_cast<double>
//#define TO_STRING boost::lexical_cast<std::string>
//#define INT gezi::lexical_cast<int>
//#define UINT gezi::lexical_cast<unsigned int>
//#define INT64 gezi::lexical_cast<long long>
//#define UINT64 gezi::lexical_cast<unsigned long long>
//#define BOOL gezi::lexical_cast<bool>
//#define FLOAT gezi::lexical_cast<float>
//#define DOUBLE gezi::lexical_cast<double>
//#define STRING gezi::lexical_cast<std::string>
//#define STR gezi::lexical_cast<std::string>
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&); \
	void operator=(const TypeName&)

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH
using boost::format;
using boost::is_any_of;
#include <boost/any.hpp>   
using boost::any_cast;

#define FREE(ptr) \
  {if (ptr) { delete ptr; ptr = NULL;}}

#define FREE2(ptr) \
  {if (ptr) { delete [] ptr; ptr = NULL;}}
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
using boost::regex;
using boost::algorithm::split_regex;

#include <boost/function.hpp>
using boost::function;


#include "statistic_util.h"
#include "datetime_util.h"

using std::string;
using boost::format;

namespace gezi
{

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
  for (int i = 0; i < (int) vec.size(); i++)
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
}

//boost bind定义了golobal的_1.._9
#define BOOST_BIND_PLACEHOLDERS_HPP_INCLUDED
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
using namespace boost::lambda;
//#include <boost/spirit/include/phoenix_core.hpp>  
//using namespace boost::phoenix;
//using namespace boost::phoenix::arg_names;

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/progress.hpp>

namespace gezi
{

class MicrosecTimer
{
public:

  MicrosecTimer() : _start_time(boost::posix_time::microsec_clock::local_time())
  {
  }

  ~MicrosecTimer()
  {
  }

  void restart()
  {
    _start_time = boost::posix_time::microsec_clock::local_time();
  }

  double elapsed()
  {
    boost::posix_time::time_duration d = boost::posix_time::microsec_clock::local_time() - _start_time;
    double result = d.ticks();
    return result /= d.ticks_per_second();
  }

  double elapsed_ms()
  {
    return elapsed() * 1000.0;
  }

private:
  boost::posix_time::ptime _start_time;
};

typedef MicrosecTimer Timer;

class AutoTimer
{
public:
  string _prefix;
  MicrosecTimer _timer;

  AutoTimer(const string& prefix)
  : _prefix(prefix)
  {
  }

  ~AutoTimer()
  {
    VLOG(3) << setiosflags(ios::left) << setfill(' ') << setw(40)
            << _prefix << " " << _timer.elapsed_ms() << " ms";
  }
};
}

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;
namespace bf = boost::filesystem;
//---------------------------for file save load
namespace gezi
{

inline void try_create_dir(const string& dir)
{
  if (!bfs::exists(dir))
  {
    LOG_WARNING("%s not exist, will create first", dir.c_str());
    bfs::create_directories(dir);
  }
}

inline std::string read_file(const std::string& infile)
{
  std::ifstream ifs(infile.c_str());
  return boost::trim_copy(std::string((std::istreambuf_iterator<char>(ifs)),
          std::istreambuf_iterator<char>()));
}

inline void write_file(const string& content, const string& outfile)
{
  std::ofstream ofs(outfile.c_str());
  ofs << content;
}

template<typename Container>
bool file_to_set(const std::string& infile, Container& container)
{
  typedef typename Container::value_type T;
  std::ifstream ifs(infile.c_str());
  if (!ifs.is_open())
  {
    return false;
  }
  std::istream_iterator<T> data_begin(ifs);
  std::istream_iterator<T> data_end;
  std::copy(data_begin, data_end, std::inserter(container, container.begin()));
  return true;
}

//适用于单列文本

template<typename Container>
bool file_to_vec(const std::string& infile, Container& container)
{
  typedef typename Container::value_type T;
  std::ifstream ifs(infile.c_str());
  if (!ifs.is_open())
  {
    return false;
  }
  std::istream_iterator<T> data_begin(ifs);
  std::istream_iterator<T> data_end;
  std::copy(data_begin, data_end, std::back_inserter(container));

  foreach(T& value, container)
  {
    boost::trim(value);
  }
  return true;
}

inline vector<string> read_lines(const std::string& infile)
{
  vector<string> vec;
  std::ifstream ifs(infile.c_str());
  string line;
  while (getline(ifs, line))
  {
    boost::trim(line);
    vec.push_back(line);
  }
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  return std::move(vec);
#else
  return vec;
#endif
}

inline void read_lines(string infile, vector<string>& vec)
{
  std::ifstream ifs(infile.c_str());
  string line;
  while (getline(ifs, line))
  {
    boost::trim(line);
    vec.push_back(line);
  }
}

template<typename T>
inline void write_lines(vector<T>& lines, string file)
{
  std::ofstream ofs(file.c_str());

  foreach(T line, lines)
  {
    ofs << line << endl;
  }
}


//单列 file_

template<typename Set>
inline void read_set(string infile, Set& container)
{
  std::ifstream ifs(infile.c_str());
  string line;
  while (getline(ifs, line))
  {
    boost::trim(line);
    container.insert(line);
  }
}

inline set<string> to_set(string infile)
{
  set<string> container;
  std::ifstream ifs(infile.c_str());
  string line;
  while (getline(ifs, line))
  {
    boost::trim(line);
    container.insert(line);
  }
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  return std::move(container);
#else
  return container;
#endif
}

inline unordered_set<string> to_uset(string infile)
{
  unordered_set<string> container;
  std::ifstream ifs(infile.c_str());
  string line;
  while (getline(ifs, line))
  {
    boost::trim(line);
    container.insert(line);
  }
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  return std::move(container);
#else
  return container;
#endif
}

//多列 read_to

inline void read_to_set(const std::string& infile, std::set<std::string>& container,
        int index = 0, const string& sep = "\t ")
{
  std::ifstream ifs(infile.c_str());
  string line;
  while (getline(ifs, line))
  {
    boost::trim(line);
    vector<string> vec;
    boost::split(vec, line, is_any_of(sep));
    container.insert(vec[index]);
  }
}

inline void read_to_set(const std::string& infile, unordered_set<std::string>& container,
        int index = 0, const string& sep = "\t ")
{
  std::ifstream ifs(infile.c_str());
  string line;
  while (getline(ifs, line))
  {
    boost::trim(line);
    vector<string> vec;
    boost::split(vec, line, is_any_of(sep));
    container.insert(vec[index]);
  }
}

template<typename Container>
void read_to_set(const std::string& infile, Container& container, int index = 0, const string& sep = "\t ")
{
  typedef typename Container::value_type T;
  std::ifstream ifs(infile.c_str());
  string line;
  while (getline(ifs, line))
  {
    boost::trim(line);
    vector<string> vec;
    boost::split(vec, line, is_any_of(sep));
    container.insert(boost::lexical_cast<T>(vec[index]));
  }
}

inline void read_to_vec(const std::string& infile, std::vector<std::string>& container,
        int index = 0, const string& sep = "\t ")
{
  std::ifstream ifs(infile.c_str());
  string line;
  while (getline(ifs, line))
  {
    boost::trim(line);
    vector<string> vec;
    boost::split(vec, line, is_any_of(sep));
    container.push_back(vec[index]);
  }
}

template<typename Container>
void read_to_vec(const std::string& infile, Container& container, int index = 0, const string& sep = "\t ")
{
  typedef typename Container::value_type T;
  std::ifstream ifs(infile.c_str());
  string line;
  while (getline(ifs, line))
  {
    boost::trim(line);
    vector<string> vec;
    boost::split(vec, line, is_any_of(sep));
    container.push_back(boost::lexical_cast<T>(vec[index]));
  }
}
//TODO better method...

inline void read_map(const std::string& infile, std::map<std::string, std::string>& container,
        const string& sep = "\t", int key_idx = 0, int value_idx = 1)
{
  std::ifstream ifs(infile.c_str());
  string line;
  while (getline(ifs, line))
  {
    boost::trim(line);
    vector<string> vec;
    boost::split(vec, line, is_any_of(sep));
    container[boost::trim_copy(vec[key_idx])] = boost::trim_copy(vec[value_idx]);
  }
}

inline void read_map(const std::string& infile, unordered_map<std::string, std::string>& container,
        const string& sep = "\t", int key_idx = 0, int value_idx = 1)
{
  std::ifstream ifs(infile.c_str());
  string line;
  while (getline(ifs, line))
  {
    boost::trim(line);
    vector<string> vec;
    boost::split(vec, line, is_any_of(sep));
    container[boost::trim_copy(vec[key_idx])] = boost::trim_copy(vec[value_idx]);
  }
}

template<typename Container>
void read_map(const std::string& infile, Container& container, const string& sep = "\t",
        int key_idx = 0, int value_idx = 1)
{
  //  typedef typename Container::key_type T;
  typedef typename Container::mapped_type U;
  std::ifstream ifs(infile.c_str());
  string line;
  while (getline(ifs, line))
  {
    boost::trim(line);
    vector<string> vec;
    boost::split(vec, line, is_any_of(sep));
    //    container[boost::lexical_cast<T>(vec[key_idx])] = boost::lexical_cast<U>(vec[value_idx]);
    container[boost::trim_copy(vec[key_idx])] = boost::lexical_cast<U>(boost::trim_copy(vec[value_idx]));
  }
}

inline unordered_map<string, int> to_identifer_map(string infile, int start = 0)
{
  unordered_map<string, int> m;
  std::ifstream ifs(infile.c_str());
  string line;
  while (getline(ifs, line))
  {
    boost::trim(line);
    m[line] = start++;
  }
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  return std::move(m);
#else
  return m;
#endif
}

template<typename Map>
void write_map(const Map& m, const std::string& ofile, const std::string& sep = "\t")
{
  ofstream ofs(ofile.c_str());
  typedef typename Map::value_type Pair;

  foreach(Pair& item, m)
  {
    ofs << m.first << sep << m.second << endl;
  }
}

/**
 * 注意 write_ve 与 read_vec配合使用, 只适用于_Node 是简单类型的情况比如int,float struct{int,float}
 */
template<typename _Node>
void write_vec(const std::vector<_Node>& vec, const std::string& file)
{//不输出长度
  std::ofstream ofs(file.c_str(), std::ios::binary);
  ofs.write(reinterpret_cast<const char*> (&vec[0]), sizeof (_Node) * vec.size());
}

template<typename _Node>
bool read_vec(const std::string& file, std::vector<_Node>& vec)
{
  std::ifstream ifs(file.c_str(), std::ios::binary);
  if (!ifs.is_open())
    return false;
  vec.clear();
  ifs.seekg(0, std::ios::end);
  int length = ifs.tellg(); //FIXME big file?
  ifs.seekg(0, std::ios::beg);
  vec.resize(length / sizeof (_Node));
  ifs.read(reinterpret_cast<char*> (&vec[0]), length);
  return true;
}

template<typename T>
void write_elem(const T& elem, const std::string& file)
{
  std::ofstream ofs(file.c_str());
  ofs << elem;
}

template<typename T>
bool read_elem(const std::string& file, T& elem)
{
  std::ifstream ifs(file.c_str());
  if (!ifs.is_open())
    return false;
  ifs >> elem;
  return true;
}

template<typename _Node>
void write_vec2d(const std::vector<std::vector<_Node> >& vec, std::ofstream& ofs)
{
  size_t row_len = vec.size();
  if (!row_len)
    return;
  for (size_t i = 0; i < row_len; i++)
  {
    int len = (int) vec[i].size();
    ofs.write(reinterpret_cast<const char*> (&len), sizeof (len));
    if (!len)
      continue;
    ofs.write(reinterpret_cast<const char*> (&vec[i][0]), sizeof (_Node) * vec[i].size());
  }
}

template<typename _Node>
void write_vec2d(const std::vector<std::vector<_Node> >& vec, const std::string& file)
{
  std::ofstream ofs(file.c_str(), std::ios::binary);
  size_t row_len = vec.size();
  ofs.write(reinterpret_cast<const char*> (&row_len), sizeof (row_len));
  write_vec2d(vec, ofs);
}

template<typename _Node>
bool read_vec2d(const std::string& file, std::vector<std::vector<_Node> >& vec)
{
  std::ifstream ifs(file.c_str(), std::ios::binary);
  if (!ifs.is_open())
    return false;
  vec.clear();
  //size_t total_len;
  int total_len; //TODO check 相关词的时候write 的是int
  ifs.read(reinterpret_cast<char*> (&total_len), sizeof (total_len));
  if (!total_len)
    return false;
  vec.resize(total_len);
  for (int i = 0; i < total_len; i++)
  {
    int len;
    ifs.read(reinterpret_cast<char*> (&len), sizeof (len));
    if (!len)
      continue;
    vec[i].resize(len);
    ifs.read(reinterpret_cast<char*> (&vec[i][0]), sizeof (_Node) * len);
  }
  return true;
}

class Vec2dWriter
{
public:

  Vec2dWriter(const std::string& file)
  : _ofs(file.c_str(), std::ios::binary)
  {
  }

  template<typename _Node>
  void write(const std::vector<_Node>& vec)
  {
    int len = (int) vec.size();
    _ofs.write(reinterpret_cast<const char*> (&len), sizeof (len));
    if (!len)
      return;
    _ofs.write(reinterpret_cast<const char*> (&vec[0]), sizeof (_Node) * len);
  }

  template<typename _Iter>
  void write(_Iter begin, _Iter end)
  {
    typedef typename _Iter::value_type value_type;
    int len = std::distance(begin, end);
    _ofs.write(reinterpret_cast<const char*> (&len), sizeof (len));
    if (!len)
      return;
    while (begin != end)
    {
      _ofs.write(reinterpret_cast<const char*> (&(*begin)), sizeof (value_type));
    }
  }

  void close()
  {
    _ofs.close();
  }
private:
  std::ofstream _ofs;
};

class VecWriter
{
public:

  VecWriter(const std::string& file)
  : _ofs(file.c_str(), std::ios::binary)
  {
  }

  template<typename _Node>
  void write(const std::vector<_Node>& vec)
  {
    int len = (int) vec.size();
    _ofs.write(reinterpret_cast<const char*> (&vec[0]), sizeof (_Node) * len);
  }

  template<typename _Iter>
  void write(_Iter begin, _Iter end)
  {
    typedef typename _Iter::value_type value_type;
    while (begin != end)
    {
      _ofs.write(reinterpret_cast<const char*> (&(*begin)), sizeof (value_type));
    }
  }

  void close()
  {
    _ofs.close();
  }
private:
  std::ofstream _ofs;
};
//namespace ufo
//{
//
//inline vector<string> split(string line, string pattern = "\t ")
//{
//  vector<string> vec;
//  boost::split(vec, line, is_any_of(pattern));
//#ifdef __GXX_EXPERIMENTAL_CXX0X__
//  return std::move(vec);
//#else
//  return vec;
//#endif
//}
//}

template<typename Map, typename T>
void add_one(Map& map, T name, int count = 1)
{
  if (!map.count(name))
  {
    map[name] = count;
  }
  else
  {
    map[name] += count;
  }
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
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  return std::move(vec);
#else
  return vec;
#endif
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
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  return std::move(vec);
#else
  return vec;
#endif
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
    PVAL(item);
    ovec.push_back(boost::lexical_cast<T>(item));
  }
}

inline bool contains(map<string, vector<string> > * history, string name)
{
  return history && history->count(name) && (*history)[name].size() > 0;
}

inline int length(map<string, vector<string> > * history, string name)
{
  if (!history || !history->count(name))
  {
    return -1;
  }

  return (*history)[name].size();
}

static const int kOneDay = 86400; //24 * 60 * 60
static const int kOneHour = 3600;
static const int kOneMinute = 60;

//TODO 看上去只输出第一句 没有输出后面的stack 信息

inline void write_failure(const char* data, int size)
{
  string s(data, size);
  LOG(FATAL) << s;
}
}

#define BOOST_THREAD_DONT_USE_CHRONO
#include <boost/thread.hpp>

namespace gz = gezi;
#endif  //----end of COMMON_UTIL_H_
