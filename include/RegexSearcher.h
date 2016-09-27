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
namespace gezi
{
using namespace std;

class RegexSearcher
{
public:

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

	template<typename Vec>
	void add(const Vec& patterns, bool icase = true)
	{
		foreach(auto pattern, patterns)
		{
			add(pattern, icase);
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
			LOG(WARNING) << "RegexSearcher init file fail: " << file;
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
			LOG(WARNING) << "RegexSearcher init wstring file fail: " << file;
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

	bool Load(string file, bool icase = true)
	{
		return init2(file, icase);
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

	bool has_match(string src)
	{
		for (int i = 0; i < (int) reg_list_.size(); i++)
		{
			if (boost::regex_search(src, reg_list_[i]))
			{
				//VLOG(4) << (format("%s find with %dth reg %s") % src % i % reg_list_[i].str()).str();
				VLOG(4) << format("{} find with {}th reg {}", src, i, reg_list_[i]);
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
