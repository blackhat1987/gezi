#ifndef GEZI_PYTHON_MAP_UTIL_H_
#define GEZI_PYTHON_MAP_UTIL_H_
#include <map>
#include <string>
namespace gezi {
using std::map;
using std::string;
float get_value(const map<string, float> dict, string key, float default_value=0);
}
#endif
