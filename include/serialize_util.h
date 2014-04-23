/** 
 *  ==============================================================================
 * 
 *          \file   serialize_util.h
 *
 *        \author   chenghuige 
 *          
 *          \date   2010-05-16 20:49:43.294749
 *  
 *  \Description:   
 *  ==============================================================================
 */

#ifndef SERIALIZE_UTIL_H_
#define SERIALIZE_UTIL_H_

#include <fstream>
#include <iostream>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_oarchive.hpp>

//#include "serialization/shared_ptr.hpp"
//#include "serialization/shared_ptr_helper.hpp"
//#include "serialization/unique_ptr.hpp"

#include <boost/serialization/utility.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include "serialization/unordered_map_serialize.h"
#include "serialization/unordered_set_serialize.h"



namespace serialize_util {
using std::string;
/**将data序列化输出到file*/
template<class T>
void save(const T& data, string file)
{
    std::ofstream ofs(file.c_str());
    boost::archive::binary_oarchive oa(ofs, std::ios::binary); //文本的输出归档类，使用一个ostream来构造
    oa << data;
}
/**序列化从file中file中读出data*/
template<class T>
bool load(string file, T& data)
{
    std::ifstream ifs(file.c_str());
    if (!ifs.is_open())
    {
        //        LOG(INFO) << "open " << file << " error" << std::endl;
        //        throw new int(10);
        return false;
    }
    try
    {
        boost::archive::binary_iarchive ia(ifs, std::ios::binary); //文本的输出归档类，使用一个ostream来构造
        ia >> data;
    }
    catch (...)
    {
        return false;
    }
    return true;
}
/**序列化从file中file中读出data*/
template<class T>
bool load(T& data, string file)
{
    return load(file, data);
}

}
namespace serialize = serialize_util;
namespace ser = serialize_util;
#endif  //----end of SERIALIZE_UTIL_H_
