/**
 *  ==============================================================================
 *
 *          \file   python/map_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2016-11-08 21:44:39.069205
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef GEZI_PYTHON_MAP_UTIL_H_
#define GEZI_PYTHON_MAP_UTIL_H_

#include <map>
#include <string>
namespace gezi {
    using std::map;
    using std::string;

    float get_value(const map<string, float> dict, string key, float default_value=0)
    {
      auto iter = dict.find(key);
      if (iter != dict.end())
      {
        return iter->second;
      }
      return default_value;
    }

}  //----end of namespace gezi

#endif  //----end of GEZI_PYTHON_MAP_UTIL_H_
