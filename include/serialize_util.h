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

namespace serialize_util {

}

//#define  NO_CEREAL

#ifdef NO_CEREAL //use boost serialize
#include "seralize_boost.h"
namespace cereal { using boost::serialization::access;  }
#define CEREAL_NVP GEZI_SERIALIZATION_NVP
#define CEREAL_BASE_OBJECT_NVP BOOST_SERIALIZATION_BASE_OBJECT_NVP 
#else  //use ceral  目前从使用boost改为使用cereal

#ifdef Uint //hack for ullog compact
#undef Uint
#endif // Uint

#include "seralize_cereal.h"

#include "string_util.h"
#ifdef CEREAL_NVP
#undef CEREAL_NVP 
#endif // CEREAL_NVP
#define  CEREAL_NVP(name)\
	cereal::make_nvp(gezi::conf_trim(#name).c_str(), name)

#ifndef  CEREAL_BASE_OBJECT_NVP
#define CEREAL_BASE_OBJECT_NVP(name)                  \
	cereal::make_nvp(BOOST_PP_STRINGIZE(name), \
	cereal::base_class<name>(this)\
	)
#endif // CEREAL_BASE_OBJECT_NVP
//@TODO 暂时性向前兼容 define修正为使用cereal
namespace boost { namespace serialization { using cereal::access; } }

#define  GEZI_SERIALIZATION_NVP CEREAL_NVP 
#define  BOOST_SERIALIZATION_NVP CEREAL_NVP 

#define  BOOST_SERIALIZATION_BASE_OBJECT_NVP CEREAL_BASE_OBJECT_NVP

#ifndef NO_BAIDU_DEP 
#define Uint(inp) (unsigned int)(inp) //sb ullog 竟然宏定义的像函数
#endif // NO_BAIDU_DEP

#endif // NO_CEREAL

namespace ser = serialize_util;

#endif  //----end of SERIALIZE_UTIL_H_
