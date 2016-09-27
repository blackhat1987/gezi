/**
 *  ==============================================================================
 *
 *          \file   RegexReplaceProcessor.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-10-29 15:33:29.884527
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef REGEXREPLACEPROCESSOR_H_
#define REGEXREPLACEPROCESSOR_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <boost/regex.hpp>
#include "IProcessor.h"
#include "log_util.h"
#include "string_util.h"
namespace gezi
{
using namespace std;

class RegexReplaceProcessor : public IStringProcessor
{
public:

  RegexReplaceProcessor()
  : replacer_(""), wreplacer_(L"")
  {

  }

  virtual ~RegexReplaceProcessor()
  {

  }

  void add(string pattern, bool icase = true)
  {
    if (icase)
    {
      reg_list_.push_back(boost::regex(pattern, boost::regex::icase | boost::regex::perl));
    }
    else
    {
      reg_list_.push_back(boost::regex(pattern, boost::regex::perl));
    }
  }
  
  void add(const wstring& pattern, bool icase = true)
  {
    if (icase)
    {
      wreg_list_.push_back(boost::wregex(pattern, boost::regex::icase | boost::regex::perl));
    }
    else
    {
      wreg_list_.push_back(boost::wregex(pattern, boost::regex::perl));
    }
  }

  bool init(const char* file, bool icase = true)
  {
    ifstream ifs(file);
    if (!ifs.is_open())
    {
      LOG_WARNING("RegexReplaceProcessor init file fail: %s", file);
      return false;
    }
    string line;
    while (getline(ifs, line))
    {
      boost::trim(line);
      if (!line.empty())
      {
        add(line, icase);
      }
    }
    return true;
  }

  bool init2(const char* file, bool icase = true)
  {
    ifstream ifs(file);
    if (!ifs.is_open())
    {
      LOG_WARNING("RegexSearcher init wstring file fail: %s", file);
      return false;
    }
    string line;
    while (getline(ifs, line))
    {
      boost::trim(line);
      wstring wline = str_to_wstr(line);
      if (!wline.empty())
      {
        add(wline, icase);
      }
    }
    return true;
  }

  bool init(string file, bool icase = true)
  {
    return init(file.c_str(), icase);
  }

  bool init2(string file, bool icase = true)
  {
    return init2(file.c_str(), icase);
  }

  virtual string process(const string & src)
  {
    string ret = src;

    for (int i = 0; i < (int) reg_list_.size(); i++)
    {
      ret = boost::regex_replace(ret, reg_list_[i], replacer_);
    }
    return ret;
  }
  
  wstring process(const wstring & src)
  {
    wstring ret = src;

    for (int i = 0; i < (int) wreg_list_.size(); i++)
    {
      ret = boost::regex_replace(ret, wreg_list_[i], wreplacer_);
    }
    return ret;
  }

  void set_replacer(string replacer)
  {
    replacer_ = replacer;
  }
  
  void set_replacer(const wstring& wreplacer)
  {
    wreplacer_ = wreplacer;
  }

private:
  string replacer_;
  wstring wreplacer_;
  vector<boost::regex> reg_list_;
  vector<boost::wregex> wreg_list_;
};

} //----end of namespace gezi

#endif  //----end of REGEXREPLACEPROCESSOR_H_
