/** 
 *  ==============================================================================
 * 
 *          \file   unordered_set_serialize.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-11-01 16:57:22.715968
 *  
 *  \Description:    暂时不加multi set 似乎load不对 FIXME  暂时不要用
 *  ==============================================================================
 */

#ifndef UNORDERED_SET_SERIALIZE_H_
#define UNORDERED_SET_SERIALIZE_H_
#include "hashmap_util.h"
#include <boost/config.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/hash_collections_save_imp.hpp>
#include <boost/serialization/hash_collections_load_imp.hpp>
//#include <boost/serialization/collections_save_imp.hpp>
//#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost {
namespace serialization {

namespace stl {
template<class Archive, class Container, class InputFunction>
inline void load_hash_collection_unordered_set(Archive & ar, Container &s)
{
    s.clear();
    // retrieve number of elements
    unsigned int count;
    unsigned int item_version(0);
    unsigned int bucket_count;
    ;
    ar >> BOOST_SERIALIZATION_NVP(count);
    if (3 < ar.get_library_version())
    {
        ar >> BOOST_SERIALIZATION_NVP(bucket_count);
        ar >> BOOST_SERIALIZATION_NVP(item_version);
    }
    //    s.resize(bucket_count);
    InputFunction ifunc;
    while (count-- > 0)
    {
        ifunc(ar, s, item_version);
    }
}
}
template<
class Archive,
class Key,
class HashFcn,
class EqualKey,
class Allocator
>
inline void save(
Archive & ar,
const std::unordered_set<
Key, HashFcn, EqualKey, Allocator
> &t,
const unsigned int file_version
)
{
    boost::serialization::stl::save_hash_collection<
            Archive,
            std::unordered_set<
            Key, HashFcn, EqualKey, Allocator
            >
            >(ar, t);
}
template<
class Archive,
class Key,
class HashFcn,
class EqualKey,
class Allocator
>
inline void load(
Archive & ar,
std::unordered_set<
Key, HashFcn, EqualKey, Allocator
> &t,
const unsigned int file_version
)
{
    boost::serialization::stl::load_hash_collection_unordered_set<
            Archive,
            std::unordered_set<
            Key, HashFcn, EqualKey, Allocator
            >,
            boost::serialization::stl::archive_input_set<
            Archive,
            std::unordered_set<
            Key, HashFcn, EqualKey, Allocator
            >
            >
            >(ar, t);
}

// split non-intrusive serialization function member into separate
// non intrusive save/load member functions
template<
class Archive,
class Key,
class HashFcn,
class EqualKey,
class Allocator
>
inline void serialize(
Archive & ar,
std::unordered_set<
Key, HashFcn, EqualKey, Allocator
> &t,
const unsigned int file_version
)
{
    boost::serialization::split_free(ar, t, file_version);
}


} //----end of namespace serialization
} //----end of namespace boost

#endif  //----end of UNORDERED_SET_SERIALIZE_H_
