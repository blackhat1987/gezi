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

#define TO_INT boost::lexical_cast<int>
#define TO_UINT boost::lexical_cast<unsigned int>
#define TO_INT64 boost::lexical_cast<long long>
#define TO_UINT64 boost::lexical_cast<unsigned long long>
#define TO_BOOL boost::lexical_cast<bool>
#define TO_FLOAT boost::lexical_cast<float>
#define TO_DOUBLE boost::lexical_cast<double>
#define TO_STRING boost::lexical_cast<std::string>
#define INT boost::lexical_cast<int>
#define UINT boost::lexical_cast<unsigned int>
#define INT64 boost::lexical_cast<long long>
#define UINT64 boost::lexical_cast<unsigned long long>
#define FLOAT_ boost::lexical_cast<Float>
#undef BOOL
#define BOOL boost::lexical_cast<bool>
#undef FLOAT
#define FLOAT boost::lexical_cast<float>
#undef  DOUBLE	
#define DOUBLE boost::lexical_cast<double>
#undef  STRING
#define STRING boost::lexical_cast<std::string>
#define STR boost::lexical_cast<std::string>

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
//gezi lexical_cast ���Ա��� 1.0 ת��int 1, ����ģ��������� string -> stringת�� ����ģ��ͳһ����
//���ǲ�����ȫ���Բ����ṩdefine ��Ҫֱ��ʹ�� ����ȫ������� vec[0] --- [Instance] UINT64(vec[0]) --- [18619200]
//#define TO_INT boost::lexical_cast<int>
//#define TO_UINT boost::lexical_cast<unsigned int>
//#define TO_INT64 boost::lexical_cast<long long>
//#define TO_UINT64 boost::lexical_cast<unsigned long long>
//#define TO_BOOL boost::lexical_cast<bool>
//#define TO_FLOAT boost::lexical_cast<float>
//#define TO_DOUBLE boost::lexical_cast<double>
//#define TO_STRING boost::lexical_cast<std::string>
//#define INT gezi::lexical_cast<int>
//#define UINT gezi::lexical_cast<unsigned int>
//#define INT64 gezi::lexical_cast<long long>
//#define UINT64 gezi::lexical_cast<unsigned long long>
//#define BOOL gezi::lexical_cast<bool>
//#define FLOAT gezi::lexical_cast<float>
//#define DOUBLE gezi::lexical_cast<double>
//#define STRING gezi::lexical_cast<std::string>
//#define STR gezi::lexical_cast<std::string>

#endif  //----end of CONVERT_TYPE_H_
