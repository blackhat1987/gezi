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

#include "seralize_boost.h"

#include "conf_util.h"
#include <boost/serialization/nvp.hpp>
#define GEZI_SERIALIZATION_NVP(name)\
	boost::serialization::make_nvp(gezi::conf_trim(#name).c_str(), name)
//namespace serialize = serialize_util;  //����ط����creal��ͻ������ ������������namespace�ͺ��������׻�����ͻ��
//.. / .. / include / cereal / cereal.hpp : 378 : 18 : error : expected primary - expression before '(' token
//serialize(*self, const_cast<T &>(t));
namespace ser = serialize_util

#endif  //----end of SERIALIZE_UTIL_H_
