/** 
 *  ==============================================================================
 * 
 *          \file   ghash_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-06 20:13:11.933307
 *  
 *  \Description:   TODO FIXME 为什么const char* 版本 存储会有问题 再打印iter->first显示不对
 *  ==============================================================================
 */

#ifndef GHASH_HELP_H_
#define GHASH_HELP_H_
#include <google/dense_hash_map>
#include <google/sparse_hash_map>
#include <ext/hash_map>
#include <string>
#include "my_hash_map.h"
//struct eqstr {
//
//    bool operator() (const char* s1, const char* s2) const
//    {
//        return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0);
//    }
//};

struct hash_string {
    size_t operator()(const std::string& str) const
    {
        return __gnu_cxx::__stl_hash_string(str.c_str());
    }
};

using google::dense_hash_map;
using __gnu_cxx::hash;
using google::sparse_hash_map;

//typedef dense_hash_map<const char*, int, hash<const char*>, eqstr> DHashMapChar2int;
//typedef sparse_hash_map<const char*, int, hash<const char*>, eqstr> SHashMapChar2int;

typedef sparse_hash_map<std::string, int, hash_string> SHashMapStr2int;
typedef dense_hash_map<std::string, int, hash_string> DHashMapStr2int;

#endif  //----end of GHASH_HELP_H_
