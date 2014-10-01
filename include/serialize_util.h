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

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_oarchive.hpp>

//#include "serialization/shared_ptr.hpp"
//#include "serialization/shared_ptr_helper.hpp"
//#include "serialization/unique_ptr.hpp"

#include <boost/serialization/utility.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include "serialization/unordered_map_serialize.h"
#include "serialization/unordered_set_serialize.h"

#include "conf_util.h"
#include <boost/serialization/nvp.hpp>
#define GEZI_SERIALIZATION_NVP(name)\
	boost::serialization::make_nvp(gezi::conf_trim(#name).c_str(), name)
//namespace serialize = serialize_util;  //这个地方会和creal冲突。。。 尽量不用这种namespace和函数名容易混淆冲突？
//.. / .. / include / cereal / cereal.hpp : 378 : 18 : error : expected primary - expression before '(' token
//serialize(*self, const_cast<T &>(t));

#ifndef USE_CEREAL //use boost serialize
#include "seralize_boost.h"
#else  //use ceral
#include "seralize_cereal.h"
#endif

namespace ser = serialize_util;

#endif  //----end of SERIALIZE_UTIL_H_
