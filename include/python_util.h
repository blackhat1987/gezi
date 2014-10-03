/**
 *  ==============================================================================
 *
 *          \file   python_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2010-03-22 16:42:25.635933
 *
 *  \Description: boost.python�İ�������
 *  ==============================================================================
 */

#ifndef PYTHON_UTIL_H_
#define PYTHON_UTIL_H_

#define BOOST_BIND_PLACEHOLDERS_HPP_INCLUDED
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
using namespace boost::lambda;

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/iterator.hpp>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
//#include "hashmap_util.h"
//using namespace boost::python; //������ /usr/include/bits/fcntl.h:200: error: `ssize_t' does not name a type
namespace bp = boost::python;
//----------------------------------------vector<X> ����

inline void IndexError()
{
	PyErr_SetString(PyExc_IndexError, "Index out of range");
}

template<class Vec>
struct std_item
{
	typedef typename Vec::value_type ValueType;

	static size_t size(Vec& vec) 
	{
		return vec.size();
	}

	static void erase(Vec & vec, int i)
	{
		if (i < 0) i += vec.size();
		if (i >= 0 && i < vec.size()) vec.erase(vec.begin() + i);
		else IndexError();
	}

	static void push_back(Vec & vec, const ValueType& val)
	{
		vec.push_back(val);
	}

	static void resize(Vec & vec, int length, const ValueType & val)
	{
		vec.resize(length, val);
	}

	static std::string str(Vec& vec)
	{
		using std::stringstream;
		stringstream ofs;
		ofs << "[";
		if (!vec.empty())
		{
			ofs << vec.front();
		}
		for (size_t i = 1; i < vec.size(); i++)
		{
			ofs << ", " << vec[i];
		}
		ofs << "]";
		return ofs.str();
	}

	//print�������������� l = dvec() l.print() python�в������� ԭ��δ֪ ����Ҫ������ ʹ��print l����
	//static void print(Vec & vec)
	//{
	//	using std::cout;
	//	cout << "[";
	//	if (!vec.empty())
	//	{
	//		cout << vec.front();
	//	}
	//	for (size_t i = 1; i < vec.size(); i++)
	//	{
	//		cout << ", " << vec[i];
	//	}
	//	cout << "]";
	//}

	static void init(Vec& vec, const boost::python::list& list)
	{
		vec.assign(boost::python::stl_input_iterator<ValueType>(list),
			boost::python::stl_input_iterator<ValueType>());
	}

	static boost::python::list tolist(Vec& vec)
	{
		boost::python::list list;
		for (auto& item : vec)
		{
			list.append(item);
		}
		return list;
	}
};

using bp::vector_indexing_suite;
using bp::map_indexing_suite;
using bp::class_;


//-----------------------helper ��

//@TODO ������vector py++�򵥴���ķ�װ����Ϊ�����ķ�װ
#define VEC_METHOD(Vec)\
	.def("__str__", &std_item<Vec>::str)\
	.def("__delitem__", &std_item<Vec>::erase)\
	.def("push_back", &std_item<Vec>::push_back)\
	.def("size", &std_item<Vec>::size)\
	.def("clear", &Vec::clear)\
	.def("erase", &std_item<Vec>::erase)\
	.def("resize", &std_item<Vec>::resize)\
	.def("init", &std_item<Vec>::init)\
	.def("tolist", &std_item<Vec>::tolist)

#define DEF_VEC(Vec) \
	class_<Vec >(#Vec) \
	.def(vector_indexing_suite<Vec, true>())\
	VEC_METHOD(Vec)

#define VEC_METHOD2(Base, Vec)\
	Base.def(vector_indexing_suite<Vec >())\
	.def("__str__", &std_item<Vec>::str)\
	.def("__delitem__", &std_item<Vec>::erase)\
	.def("push_back", &std_item<Vec>::push_back)\ 
	.def("size", &std_item<Vec>::size)\
	.def("clear", &Vec::clear)\
	.def("erase", &std_item<Vec>::erase)\
	.def("resize", &std_item<Vec>::resize)\
	.def("init", &std_item<Vec>::init)\
	.def("tolist", &std_item<Vec>::tolist)

#define DEF_MAP(Map) \
	class_<Map >(#Map)\
	.def(map_indexing_suite<Map >())

#define DEF_PAIR(Pair) \
	class_<Pair >(#Pair)\
	.def_readwrite("first", &Pair::first)\
	.def_readwrite("second", &Pair::second)




#endif  //----end of PYTHON_UTIL_H_
