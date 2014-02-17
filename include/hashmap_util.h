/** 
 *  ==============================================================================
 * 
 *          \file   hashmap_util.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-19 20:08:57.513282
 *  
 *  \Description:   Ϊ�˲�ͬϵͳ�ܹ�����hash_map
 *                  ��ǰ�ҵ�boost �汾��Ϊ�£��Ժ������Ҫ����һ���ɼ��ݵ�ʵ�֣��ӿ�һ�����ɣ�
 *                  ���иĶ�ֻ��Ҫ�޸ı��ļ�
 *  ==============================================================================
 */

#ifndef HASHMAP_UTIL_H_
#define HASHMAP_UTIL_H_

#if __GNUC__ > 3
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
#endif  //----end of HASHMAP_UTIL_H_
