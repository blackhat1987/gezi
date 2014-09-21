/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/feature_extractor_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-10 11:33:52.883245
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_FEATURE_EXTRACTOR_UTIL_H_
#define TIEBA_FEATURE_FEATURE_EXTRACTOR_UTIL_H_
#include "common_util.h"
namespace gezi {
namespace tieba {

	inline double simFunc1(string s1, string s2)
	{
		set<char> s1Set;
		set<char> s2Set;
		set<char> uSet;
		//if (s1.size() < 10 || s2.size() < 10)
		if (s1.empty() || s2.empty())
		{
			return 0;
		}
		for (size_t i = 0; i < s1.size() && i < 500; i++)
		{
			s1Set.insert(s1[i]);
		}
		for (size_t j = 0; j < s2.size() && j < 500; j++)
		{
			if (s1Set.count(s2[j]))
			{
				uSet.insert(s2[j]);
			}
			s2Set.insert(s2[j]);
		}
		if (uSet.size() == 0)
		{
			return 0;
		}
		double res = uSet.size()*1.0 / (s1Set.size() + s2Set.size() - uSet.size());
		return res;
	}

	inline double simFunc2(string s1, string s2)
	{
		if (s1.empty() || s2.empty())
		{
			return 0;
		}
		string _s1 = s1 + "--";
		string _s2 = s2 + "--";
		set<string> s1Set;
		set<string> s2Set;
		set<string> uSet;
		for (size_t i = 0; i < _s1.size() - 2; i++)
		{
			string sub1 = _s1.substr(i, 3);
			s1Set.insert(sub1);
		}
		for (size_t j = 0; j < _s2.size() - 2; j++)
		{
			string sub2 = _s2.substr(j, 3);
			if (s1Set.count(sub2))
			{
				uSet.insert(sub2);
			}
			s2Set.insert(sub2);
		}
		double res = uSet.size()*1.0 / (s1Set.size() + s2Set.size() - uSet.size() + 1);
		return res;
	}

	inline bool strComp(const string &a, const string &b)
	{
		if (a.size() > b.size())
		{
			return false;
		}
		else if (b.size() > a.size())
		{
			return true;
		}
		for (size_t i = 0; i < a.size() && i < b.size(); i++)
		{
			if (a[i] > b[i])
			{
				return false;
			}
			else if (b[i] > a[i])
			{
				return true;
			}

		}
		return false;
	}

	inline bool strComp2(const string &a, const string &b)
	{
		for (size_t i = 0; i < a.size() && i < b.size(); i++)
		{
			if (a[i] > b[i])
			{
				return false;
			}
			else if (b[i] > a[i])
			{
				return true;
			}

		}
		if (a.size() > b.size())
		{
			return false;
		}
		else if (b.size() > a.size())
		{
			return true;
		}
		return false;
	}
}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_FEATURE_EXTRACTOR_UTIL_H_
