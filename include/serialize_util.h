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

//#define  NO_CEREAL  //���ϣ���л�ʹ��BOOST���л� ȡ�����ע��

#ifdef GCCXML //����ʵ����def GCCXML�жϲ����� ����ndef���á����� why�� @TODO
#ifndef NO_CEREAL
#define NO_CEREAL //python��װ��ʱ�����ʹ��CERAL��ΪCERAL�����ݵͰ汾gcc������#include <unordered_map> ������workaround
#endif
#endif

#ifdef NO_CEREAL //use boost serialize

#include "string_util.h"
#include <boost/serialization/nvp.hpp>
#define GEZI_SERIALIZATION_NVP(name)\  //������Ҫ�������
	boost::serialization::make_nvp(gezi::conf_trim(#name).c_str(), name)
//namespace serialize = serialize_util;  //����ط����creal��ͻ������ ������������namespace�ͺ��������׻�����ͻ
//.. / .. / include / cereal / cereal.hpp : 378 : 18 : error : expected primary - expression before '(' token
//serialize(*self, const_cast<T &>(t));

#ifdef BOOST_SERIALIZATION_NVP
#undef BOOST_SERIALIZATION_NVP
#endif
#define BOOST_SERIALIZATION_NVP(name)\ 
	boost::serialization::make_nvp(gezi::conf_trim(#name).c_str(), name)

#ifndef BOOST_SERIALIZATION_BASE_OBJECT 
#define BOOST_SERIALIZATION_BASE_OBJECT(name) \
	boost::serialization::base_object<name>(*this)
#endif

#include "seralize_boost.h"

namespace cereal { using boost::serialization::access; }

#define CEREAL_NVP GEZI_SERIALIZATION_NVP
#define CEREAL_BASE_OBJECT_NVP BOOST_SERIALIZATION_BASE_OBJECT_NVP 
#define  CEREAL_BASE_OBJECT BOOST_SERIALIZATION_BASE_OBJECT

#else  //use ceral  Ŀǰ��ʹ��boost��Ϊʹ��cereal

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

#ifndef CEREAL_BASE_OBJECT
#define  CEREAL_BASE_OBJECT(name) \
	cereal::base_class<name>(this)
#endif // CEREAL_BASE_OBJECT

//@TODO ��ʱ����ǰ���� define����Ϊʹ��cereal
namespace boost { namespace serialization { using cereal::access; } }

#define  GEZI_SERIALIZATION_NVP CEREAL_NVP 
#define  BOOST_SERIALIZATION_NVP CEREAL_NVP 

#define  BOOST_SERIALIZATION_BASE_OBJECT_NVP CEREAL_BASE_OBJECT_NVP

#define  BOOST_SERIALIZATION_BASE_OBJECT CEREAL_BASE_OBJECT

#ifndef NO_BAIDU_DEP 
#define Uint(inp) (unsigned int)(inp) //sb ullog ��Ȼ�궨�������
#endif // NO_BAIDU_DEP

#endif // NO_CEREAL

namespace ser = serialize_util;

#endif  //----end of SERIALIZE_UTIL_H_
