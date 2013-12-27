/**
 *  ==============================================================================
 *
 *          \file   RegexSearcher.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-02 19:23:03.429478
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef REGEX_SEARCHER_H_
#define REGEX_SEARCHER_H_
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <boost/regex.hpp>
#include "log_util.h"
#include "string_util.h"
#include "debug_util.h"
namespace gezi
{
using namespace std;

class RegexSearcher
{
public:

  void add(const string& pattern, bool icase = true)
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
      wreg_list_.push_back(boost::wregex(pattern, boost::wregex::icase | boost::wregex::perl));
    }
    else
    {
      wreg_list_.push_back(boost::wregex(pattern, boost::wregex::perl));
    }
  }

  bool init(const char* file, bool icase = true)
  {
    ifstream ifs(file);
    if (!ifs.is_open())
    {
      LOG_WARNING("RegexSearcher init file fail: %s", file);
      return false;
    }
    string line;
    while (getline(ifs, line))
    {
      boost::trim(line);
      if (!line.empty())
      {
        PVAL(line);
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
        PVAL(line);
        add(wline, icase);
      }
    }
    LOG_INFO("Finish init2 for wregex");
    return true;
  }

  bool init(const string& file, bool icase = true)
  {
    return init(file.c_str(), icase);
  }

  bool init2(const string& file, bool icase = true)
  {
    return init2(file.c_str(), icase);
  }

  int count(const string & src)
  {
    int sum = 0;
    for (int i = 0; i < (int) reg_list_.size(); i++)
    {
      if (boost::regex_search(src, reg_list_[i]))
      {
        sum++;
      }
    }
    return sum;
  }

  bool has_match(const string& src)
  {
    for (int i = 0; i < (int) reg_list_.size(); i++)
    {
      if (boost::regex_search(src, reg_list_[i]))
      {
        DLOG(INFO) << (format("%s find with %dth reg %s") % src % i % reg_list_[i].str()).str();
        return true;
      }
    }
    return false;
  }
  
  int count(const wstring & src)
  {
    int sum = 0;
    for (int i = 0; i < (int) wreg_list_.size(); i++)
    {
      if (boost::regex_search(src, wreg_list_[i]))
      {
        sum++;
      }
    }
    return sum;
  }

  bool has_match(const wstring& src)
  {
    for (int i = 0; i < (int) wreg_list_.size(); i++)
    {
      if (boost::regex_search(src, wreg_list_[i]))
      {
        return true;
      }
    }
    return false;
  }

  int sreg_count()
  {
    return (int)reg_list_.size();
  }
  int wreg_count()
  {
    return (int)wreg_list_.size();
  }
  
  int reg_count()
  {
    return (int) (reg_list_.size() + wreg_list_.size());
  }
private:
  vector<boost::regex> reg_list_;
  vector<boost::wregex> wreg_list_;
};

} //----end of namespace gezi

#endif  //----end of REGEX_SEARCHER_H_