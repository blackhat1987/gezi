/** 
 *  ==============================================================================
 * 
 *          \file   hashmap_util.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-19 20:08:57.513282
 *  
 *  \Description:   为了不同系统能够兼容hash_map
 *                  当前我的boost 版本较为新，以后可能需要引入一个可兼容的实现，接口一样即可，
 *                  所有改动只需要修改本文件
 *  ==============================================================================
 */

#ifndef HASHMAP_UTIL_H_
#define HASHMAP_UTIL_H_

#if __GNUC__ > 3
#include <tr1/unordered_map> 
#include <tr1/unordered_set> 
#else
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
namespace std {
namespace tr1 {
using ::boost::unordered_map;
using ::boost::unordered_set;
}
}
#endif
using std::tr1::unordered_map;
using std::tr1::unordered_set;
#endif  //----end of COMPAT_HASHMAP_H_
