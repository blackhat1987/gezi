/* 
 * File:   unordered_map_serialize.h
 * Author: chenghuige
 *
 * Created on 2010年3月4日, 下午9:19
 *
 *   FIXME 这个序列话 是否存在一定的风险呢？ 内存占用大小等等 会带来内存泄漏吗？
 *  有时间深入研究下stl hash map的实现
 */

#ifndef _UNORDERD_MAP_SERIALIZE_H
#define	_UNORDERD_MAP_SERIALIZE_H

#include "hashmap_util.h"
#include <boost/config.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/collections_save_imp.hpp>  //FIXME shoulde be hash_save ?
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>
namespace boost {
namespace serialization { 
template<class Archive, class Type, class Key, class Hash, class
Compare, class Allocator >
inline void save(
   Archive & ar,
   const std::tr1::unordered_map<Key, Type, Hash, Compare, Allocator> &t,
   const unsigned int /* file_version */
){
   boost::serialization::stl::save_collection<
       Archive,
       std::tr1::unordered_map<Key, Type, Hash, Compare, Allocator>
>(ar, t);
}
template<class Archive, class Type, class Key, class Hash, class
Compare, class Allocator >
inline void load(
   Archive & ar,
   std::tr1::unordered_map<Key, Type, Hash, Compare, Allocator> &t,
   const unsigned int /* file_version */
){
   boost::serialization::stl::load_collection<
       Archive,
       std::tr1::unordered_map<Key, Type, Hash, Compare, Allocator>,
       //boost::serialization::stl::archive_input_unique<
         boost::serialization::stl::archive_input_map <     //chg modified
           Archive, std::tr1::unordered_map<Key, Type, Hash, Compare,
Allocator> >,

boost::serialization::stl::no_reserve_imp<std::tr1::unordered_map<
               Key, Type, Hash, Compare, Allocator
>
>
>(ar, t);
}
// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<class Archive, class Type, class Key, class Hash, class
Compare, class Allocator >
inline void serialize(
   Archive & ar,
   std::tr1::unordered_map<Key, Type, Hash, Compare, Allocator> &t,
   const unsigned int file_version
){
   boost::serialization::split_free(ar, t, file_version);
}
//// unordered_multimap
//template<class Archive, class Type, class Key, class Hash, class
//Compare, class Allocator >
//inline void save(
//   Archive & ar,
//   const std::tr1::unordered_multimap<Key, Type, Hash, Compare,
//Allocator> &t,
//   const unsigned int /* file_version */
//){
//   boost::serialization::stl::save_collection<
//       Archive,
//       std::tr1::unordered_multimap<Key, Type, Hash, Compare, Allocator>
//>(ar, t);
//}
//template<class Archive, class Type, class Key, class Hash, class
//Compare, class Allocator >
//inline void load(
//   Archive & ar,
//   std::tr1::unordered_multimap<Key, Type, Hash, Compare, Allocator> &t,
//   const unsigned int /* file_version */
//){
//   boost::serialization::stl::load_collection<
//       Archive,
//       std::tr1::unordered_multimap<Key, Type, Hash, Compare, Allocator>,
//       boost::serialization::stl::archive_input_multi<
//           Archive, std::tr1::unordered_multimap<Key, Type, Hash,
//Compare, Allocator>
//>,
//       boost::serialization::stl::no_reserve_imp<
//           std::tr1::unordered_multimap<Key, Type, Hash, Compare,
//Allocator>
//>
//>(ar, t);
//}
//// split non-intrusive serialization function member into separate
//// non intrusive save/load member functions
//template<class Archive, class Type, class Key, class Hash, class
//Compare, class Allocator >
//inline void serialize(
//   Archive & ar,
//   std::tr1::unordered_multimap<Key, Type, Hash, Compare, Allocator> &t,
//   const unsigned int file_version
//){
//   boost::serialization::split_free(ar, t, file_version);
//}
} // serialization
} // namespace boost

#endif	/* _UNORDERD_MAP_SERIALIZE_H */

