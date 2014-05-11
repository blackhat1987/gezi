/**
 *  ==============================================================================
 *
 *          \file   convert_type.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-17 16:47:09.121000
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef CONVERT_TYPE_H_
#define CONVERT_TYPE_H_

#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>

//@TODO 比atoi atof慢 
//#define TO_INT boost::lexical_cast<int>
#define TO_UINT boost::lexical_cast<unsigned int>
#define TO_INT64 boost::lexical_cast<long long>
#define TO_UINT64 boost::lexical_cast<unsigned long long>
#define TO_BOOL boost::lexical_cast<bool>
#define TO_FLOAT boost::lexical_cast<float>
//#define TO_DOUBLE boost::lexical_cast<double>
#undef  TO_STR
#define TO_STR boost::lexical_cast<std::string>
//#define INT boost::lexical_cast<int>
#define UINT boost::lexical_cast<unsigned int>
#define INT64 boost::lexical_cast<long long>
#define UINT64 boost::lexical_cast<unsigned long long>
#define FLOAT_ boost::lexical_cast<Float>
#undef BOOL
#define BOOL boost::lexical_cast<bool>
#undef FLOAT
#define FLOAT boost::lexical_cast<float>
#undef INT
#undef  DOUBLE	
//#define DOUBLE boost::lexical_cast<double>
#undef  STRING
#define STRING boost::lexical_cast<std::string>

#undef  STR
#define STR boost::lexical_cast<std::string>

#define  STR_TO_INT(a) \
atoi(a.c_str())
#define STR_TO_DOUBLE(a) \
atof(a.c_str())

#define  TO_INT(a) \
atoi(a.c_str())
#define TO_DOUBLE(a) \
atof(a.c_str())

#define  ATOI(a) \
atoi(a.c_str())
#define ATOF(a) \
atof(a.c_str())

#define  INT_PARSE(a) \
	atoi(a.c_str())
#define DOUBLE_PARSE(a) \
	atof(a.c_str())

#define  INT(a) \
	atoi(a.c_str())
#define  INT_(a) \
	atoi(a)
#define DOUBLE(a) \
	atof(a.c_str())

//namespace gezi
//{
//	template<typename T, typename U>
//	T lexical_cast(U input)
//	{
//		T result;
//		std::stringstream s;
//		s << input;
//		s >> result;
//		return result;
//	}
//}
//gezi lexical_cast 可以比如 1.0 转成int 1, 包括模板里面可以 string -> string转换 方便模板统一处理
//但是并不安全所以不再提供define 需要直接使用 不安全的情况如 vec[0] --- [Instance] UINT64(vec[0]) --- [18619200]
//#define TO_INT boost::lexical_cast<int>
//#define TO_UINT boost::lexical_cast<unsigned int>
//#define TO_INT64 boost::lexical_cast<long long>
//#define TO_UINT64 boost::lexical_cast<unsigned long long>
//#define TO_BOOL boost::lexical_cast<bool>
//#define TO_FLOAT boost::lexical_cast<float>
//#define TO_DOUBLE boost::lexical_cast<double>
//#define STR boost::lexical_cast<std::string>
//#define INT gezi::lexical_cast<int>
//#define UINT gezi::lexical_cast<unsigned int>
//#define INT64 gezi::lexical_cast<long long>
//#define UINT64 gezi::lexical_cast<unsigned long long>
//#define BOOL gezi::lexical_cast<bool>
//#define FLOAT gezi::lexical_cast<float>
//#define FLOAT_ gezi::lexical_cast<Float>
//#define DOUBLE gezi::lexical_cast<double>
//#define STRING gezi::lexical_cast<std::string>
//#define STR gezi::lexical_cast<std::string>

#endif  //----end of CONVERT_TYPE_H_
