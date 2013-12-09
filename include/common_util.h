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
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <sstream>
#include <algorithm>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include "hashmap_util.h"
#include "log_util.h"
#include "conf_util.h"
#include "debug_util.h"
#include "string_util.h"
#include "serialize_util.h"

using namespace std;
typedef long long int64;
typedef unsigned int uint;
typedef unsigned long long uint64;
#include <boost/lexical_cast.hpp>
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
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&); \
	void operator=(const TypeName&)
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH
using boost::format;
using boost::is_any_of;

#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
using boost::regex;
using boost::algorithm::split_regex;

//TODO 如何直接推导ValueType 下面这种不行 得到的是比如const long long &
//template<typename Iter, typename Func>
//std::size_t distinct_count(Iter begin, Iter end, Func func)
//{
//    typedef typename Func::result_type ValueType;
//    std::tr1::unordered_set<ValueType> vset;
//    for(Iter it = begin; it != end; ++it)
//    {
//        vset.insert(func(*it));
//    }
//    return vset.size();
//}
using std::string;
using boost::format;

template<typename T>
std::string join(const std::vector<T>& vec, const std::string& sep = " ")
{
  std::stringstream s;
  size_t i = 0;
  for (; i < (int) vec.size() - 1; i++)
  {
    s << vec[i] << sep;
  }
  s << vec[i];
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

#include <boost/bind.hpp>

template<typename ValueType, typename Iter, typename Func>
std::size_t distinct_count(Iter begin, Iter end, Func func)
{
  std::tr1::unordered_set<ValueType> vset;
  for (Iter it = begin; it != end; ++it)
  {
    vset.insert(func(*it));
  }
  return vset.size();
}

template<typename Iter>
std::size_t distinct_count(Iter begin, Iter end)
{
  typedef typename Iter::value_type ValueType;
  std::tr1::unordered_set<ValueType> vset;
  for (Iter it = begin; it != end; ++it)
  {
    vset.insert(*it);
  }
  return vset.size();
}


#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/progress.hpp>

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


#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

inline void try_create_dir(const string& dir)
{
  if (!bfs::exists(dir))
  {
    LOG_WARNING("%s not exist, will create first", dir.c_str());
    bfs::create_directories(dir);
  }
}

//---------------------------for file save load

inline std::string read_file(const std::string& infile)
{
  std::ifstream ifs(infile.c_str());
  return std::string((std::istreambuf_iterator<char>(ifs)),
          std::istreambuf_iterator<char>());
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
  return true;
}

template<typename Container>
void file_to_set(const std::string& infile, Container& container, int index, const string& sep = "\t ")
{
  typedef typename Container::value_type T;
  std::ifstream ifs(infile.c_str());
  string line;
  while (ifs.getline(line))
  {
    boost::trim(line);
    vector<string> vec;
    boost::split(vec, line, is_any_of(sep));
    container.insert(boost::lexical_cast<T>(vec[index]));
  }
}

template<typename Container>
void file_to_vec(const std::string& infile, Container& container, int index, const string& sep = "\t ")
{
  typedef typename Container::value_type T;
  std::ifstream ifs(infile.c_str());
  string line;
  while (ifs.getline(line))
  {
    boost::trim(line);
    vector<string> vec;
    boost::split(vec, line, is_any_of(sep));
    container.push_back(boost::lexical_cast<T>(vec[index]));
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

namespace gezi
{

template<typename Map, typename T>
void add_one(Map& map, T name)
{
  if (!map.count(name))
  {
    map[name] = 1;
  }
  else
  {
    map[name]++;
  }
}

inline vector<string> to_vec(const string& input, const string& sep = ",")
{
  vector<string> vec;
  boost::split(vec, input, is_any_of(sep));
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  return std::move(vec);
#else
  return vec;
#endif
}
}

#endif  //----end of COMMON_UTIL_H_
