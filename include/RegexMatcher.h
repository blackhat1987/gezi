/**
 *  ==============================================================================
 *
 *          \file   RegexMatcher.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-02 19:09:53.996281
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef REGEX_MATCHER_H_
#define REGEX_MATCHER_H_
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <boost/regex.hpp>
#include "log_util.h"
namespace gezi
{
using namespace std;

class RegexMatcher
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
  
  bool init(const char* file, bool icase = true)
  {
    ifstream ifs(file);
    if (!ifs.is_open())
    {
      LOG_WARNING("RegexMatcher init file fail: %s", file);
      return false;
    }
    string line;
    while(getline(ifs, line))
    {
      boost::trim(line);
      if (!line.empty())
      {
        add(line, icase);
      }
    }
    return true;
  }
  
  bool init(const string& file, bool icase = true)
  {
    return init(file.c_str(), icase);
  }

  int count(const string & src)
  {
    int sum = 0;
    for (int i = 0; i < (int) reg_list_.size(); i++)
    {
      if (boost::regex_match(src, reg_list_[i]))
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
      if (boost::regex_match(ret, reg_list_[i]))
      {
        DLOG(INFO) << (format("%s find with %dth reg %s")%src%i%reg_list_[i].str()).str();
        return true;
      }
    }
    return false;
  }
  
private:
  vector<boost::regex>  reg_list_;
};

}  //----end of namespace gezi

#endif  //----end of REGEX_MATCHER_H_