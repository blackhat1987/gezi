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

#ifdef NO_CEREAL
#include "seralize_boost.h"
#include <boost/serialization/nvp.hpp>
#include "conf_util.h"
#define GEZI_SERIALIZATION_NVP(name)\
	boost::serialization::make_nvp(gezi::conf_trim(#name).c_str(), name)
//namespace serialize = serialize_util;  //这个地方会和creal冲突。。。 尽量不用这种namespace和函数名容易混淆冲突？
//.. / .. / include / cereal / cereal.hpp : 378 : 18 : error : expected primary - expression before '(' token
//serialize(*self, const_cast<T &>(t));
#else 
#endif
namespace ser = serialize_util;

#endif  //----end of SERIALIZE_UTIL_H_
