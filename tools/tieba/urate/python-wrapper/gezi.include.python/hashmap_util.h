#ifndef HASHMAP_UTIL_H_
#define HASHMAP_UTIL_H_
#if __GNUC__ > 3 || defined(WIN32)
#include <unordered_map>
#include <unordered_set>
#else
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
namespace std {
using ::boost::unordered_map;
using ::boost::unordered_set;
}
#endif
using std::unordered_map;
using std::unordered_set;
#endif
