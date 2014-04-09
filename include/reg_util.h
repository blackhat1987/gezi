/**
 *  ==============================================================================
 *
 *          \file   reg_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-12-22 17:10:03.133824
 *
 *  \Description:
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

inline string reg_search(string content, boost::regex& reg, int index = 1)
{
  boost::smatch m;
  if (boost::regex_search(content, m, reg))
  {
    return string(m[index].first, m[index].second);
  }
  return "";
}

inline void reg_search(string content, boost::regex& reg, vector<string>& result, int index = 1)
{
  boost::smatch m;
  string::const_iterator it = content.begin();
  while (boost::regex_search(it, content.end(), m, reg))
  {
    result.push_back(string(m[index].first, m[index].second));
    it = m[0].second;
  }
}

inline wstring reg_search(wstring content, boost::wregex& reg, int index = 1)
{
  boost::wsmatch m;
  if (boost::regex_search(content, m, reg))
  {
    return wstring(m[index].first, m[index].second);
  }
  return L"";
}

inline void reg_search(wstring content, boost::wregex& reg, vector<wstring>& result, int index = 1)
{
  boost::wsmatch m;
  wstring::const_iterator it = content.begin();
  while (boost::regex_search(it, content.end(), m, reg))
  {
    result.push_back(wstring(m[index].first, m[index].second));
    it = m[0].second;
  }
}
inline bool reg_find(string content, string pattern)
{
	boost::regex reg(pattern);
	boost::smatch m;
	return boost::regex_search(content, m, reg);
}
inline string reg_search(string content, string pattern, int index = 1)
{
  boost::regex reg(pattern);
  return reg_search(content, reg, index);
}

inline void reg_search(string content, string pattern, vector<string>& result, int index = 1)
{
  boost::regex reg(pattern);
  reg_search(content, reg, result, index);
}

inline wstring reg_search(wstring content, wstring pattern, int index = 1)
{
  boost::wregex reg(pattern);
  return reg_search(content, reg, index);
}

inline void reg_search(wstring content, wstring pattern, vector<wstring>& result, int index = 1)
{
  boost::wregex reg(pattern);
  reg_search(content, reg, result, index);
}

inline string reg_replace(string input, string pattern, string replacement = "")
{
  boost::regex reg(pattern);
  return boost::regex_replace(input, reg, replacement);
}

inline wstring reg_replace(wstring input, wstring pattern, wstring replacement = L"")
{
  boost::wregex reg(pattern);
  return boost::regex_replace(input, reg, replacement);
}

inline string reg_remove(string input, string pattern)
{
  boost::regex reg(pattern);
  return boost::regex_replace(input, reg, "");
}

inline wstring reg_remove(wstring input, wstring pattern)
{
  boost::wregex reg(pattern);
  return boost::regex_replace(input, reg, L"");
}

inline vector<string> reg_split(string input, string pattern)
{
  vector<string> vec;
  boost::regex reg(pattern);
  split_regex(vec, input, reg);
  return vec;
}

inline vector<wstring> reg_split(wstring input, wstring pattern)
{
  vector<wstring> vec;
  boost::wregex reg(pattern);
  boost::split_regex(vec, input, reg);
  return vec;
}

namespace ufo
{

inline vector<string> reg_search(string content, boost::regex& reg, int index = 1)
{
  vector<string> result;
  gezi::reg_search(content, reg, result, index);
  return result;
}

inline vector<string> reg_search(string content, string pattern, int index = 1)
{
  vector<string> result;
  boost::regex reg(pattern);
  gezi::reg_search(content, reg, result, index);
  return result;
}

inline vector<wstring> reg_search(wstring content, boost::wregex& reg, int index = 1)
{
  vector<wstring> result;
  gezi::reg_search(content, reg, result, index);
  return result;
}

inline vector<wstring> wreg_search(wstring content, wstring pattern, int index = 1)
{
  vector<wstring> result;
  boost::wregex reg(pattern);
  gezi::reg_search(content, reg, result, index);
  return result;
}

}
}

#endif  //----end of REG_UTIL_H_
