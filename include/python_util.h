/**
 *  ==============================================================================
 *
 *          \file   python_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2010-03-22 16:42:25.635933
 *
 *  \Description: boost.python的帮助函数
 *  ==============================================================================
 */

#ifndef PYTHON_UTIL_H_
#define PYTHON_UTIL_H_

#ifndef GCCXML

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
//using namespace boost::python; //有问题 /usr/include/bits/fcntl.h:200: error: `ssize_t' does not name a type
namespace bp = boost::python;
//----------------------------------------vector<X> 帮助

inline void IndexError()
{
	PyErr_SetString(PyExc_IndexError, "Index out of range");
}

template<class Vec>
struct PyVectorUtil
{
	typedef typename Vec::value_type ValueType;

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

	//这个目前如果对方不支持展示的话危险
	static std::string str(Vec& vec)
	{
		using std::stringstream;
		stringstream ofs;
		ofs << "[";
		if (!vec.empty())
		{
			ofs << vec[0];
		}
		for (size_t i = 1; i < vec.size(); i++)
		{
			ofs << ", " << vec[i];
		}
		ofs << "]";
		return ofs.str();
	}

	//print这个函数如果加入 l = dvec() l.print() python中不能运行 原因未知 不需要加入了 使用print l即可
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

	//这个不起作用 不弄了 在python那边写一个帮助函数 dict2map 好了
	static void init(Vec& vec, const boost::python::list& list)
	{
		vec.assign(boost::python::stl_input_iterator<ValueType>(list),
			boost::python::stl_input_iterator<ValueType>());
	}

	static boost::python::list tolist(Vec& vec)
	{
		boost::python::list list;
		for (size_t i = 1; i < vec.size(); i++)
		{
			list.append(vec[i]);
		}
		return list;
	}
};

template<class Map>
struct PyMapUtil
{
	typedef typename std::pair<typename Map::key_type, typename Map::mapped_type> ValueType;
	static void init(Map& m, const boost::python::dict& dict_)
	{
		for (auto iter = boost::python::stl_input_iterator<ValueType>(dict_); iter != boost::python::stl_input_iterator<ValueType>(); ++iter)
		{
			m.insert(*iter);
		}
	}

	static boost::python::dict todict(Map& m)
	{
		boost::python::dict dict_;
		for (auto& item : m)
		{
			dict_[item.first] = item.second;
		}
		return dict_;
	}
};



template <typename SetType>
struct set_wrapper
{
	typedef SetType w_t;
	typedef typename SetType::value_type e_t;

	static void insert_element(w_t& self, e_t const& x) 
	{ 
		self.insert(x);
	}

	static void insert_set(w_t& self, w_t const& other)
	{
		self.insert(other.begin(), other.end());
	}

	static bool contains(w_t const& self, e_t const& x)
	{
		return self.find(x) != self.end();
	}

	//static e_t getitem(w_t const& self, std::size_t i)
	//{
	//	if (i >= self.size()) IndexError();
	//	typename w_t::const_iterator p = self.begin();
	//	while (i > 0) { p++; i--; } //@FIXME size_t > 0
	//	return *p;
	//}

	static boost::python::tuple getinitargs(w_t const& self)
	{
		return boost::python::make_tuple(boost::python::tuple(self));
	}

	static void wrap(std::string const& python_name)
	{
		namespace bp = boost::python;
		bp::class_<w_t, std::auto_ptr<w_t> >(python_name.c_str())
			.def(bp::init<w_t const&>())
			.def("size", &w_t::size)
			.def("__len__", &w_t::size)
			.def("insert", insert_element)
			.def("add", insert_element)
			.def("append", insert_element)
			.def("insert", insert_set)
			.def("add", insert_set)
			.def("extend", insert_set)
			.def("erase", (std::size_t(w_t::*)(e_t const&)) &w_t::erase)
			.def("clear", &w_t::clear)
			.def("__contains__", contains)
			//.def("__getitem__", getitem)
			.enable_pickling()
			.def("__getinitargs__", getinitargs)
			.def("__iter__", bp::iterator<w_t>())
			;
	}
};

using bp::vector_indexing_suite;
using bp::map_indexing_suite;
using bp::class_;

//-----------------------helper 宏
#define VEC_METHOD(Vec)\
	.def("__delitem__", &PyVectorUtil<Vec>::erase)\
	.def("push_back", &PyVectorUtil<Vec>::push_back)\
	.def("size", &Vec::size)\
	.def("clear", &Vec::clear)\
	.def("erase", &PyVectorUtil<Vec>::erase)\
	.def("resize", &PyVectorUtil<Vec>::resize)\
	.def("init", &PyVectorUtil<Vec>::init)\
	.def("tolist", &PyVectorUtil<Vec>::tolist)

#define DEF_VEC(Vec) \
	class_<Vec >(#Vec) \
	.def(vector_indexing_suite<Vec, true>())\ 
VEC_METHOD(Vec)

#define VEC_METHOD2(Base, Vec)\
	Base.def(vector_indexing_suite<Vec >())\
	.def("__delitem__", &PyVectorUtil<Vec>::erase)\
	.def("push_back", &PyVectorUtil<Vec>::push_back)\ 
.def("size", &Vec::size)\
.def("clear", &Vec::clear)\
.def("erase", &PyVectorUtil<Vec>::erase)\
.def("resize", &PyVectorUtil<Vec>::resize)\
.def("init", &PyVectorUtil<Vec>::init)\
.def("tolist", &PyVectorUtil<Vec>::tolist)

#define  MAP_METHOD(Map)\
	.def("clear", &Map::clear)\
	.def("size", &Map::size)\
	.def("init", &PyMapUtil<Map>::init)\
	.def("todict", &PyMapUtil<Map>::todict)

//#define  MAP_METHOD(Map)\
//	.def("clear", &Map::clear)\
//	.def("size", &Map::size)\
//	.def("todict", &PyMapUtil<Map>::todict)

#define DEF_MAP(Map) \
	class_<Map >(#Map)\
	.def(map_indexing_suite<Map,true>())\
	MAP_METHOD(Map)

#define DEF_PAIR(Pair) \
	class_<Pair >(#Pair)\
	.def_readwrite("first", &Pair::first)\
	.def_readwrite("second", &Pair::second)

#define  DEF_SET(Set) \
	set_wrapper<Set>::wrap(#Set)

#ifndef COMMA
#define  COMMA ,
#endif

#endif // !GCCXML

#endif  //----end of PYTHON_UTIL_H_
