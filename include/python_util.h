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

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/iterator.hpp>
#include <vector>
#include <string>
#include <map>
#include <set>
//using namespace boost::python; //有问题 /usr/include/bits/fcntl.h:200: error: `ssize_t' does not name a type
namespace bp = boost::python;
//----------------------------------------vector<X> 帮助

inline void IndexError()
{
    PyErr_SetString(PyExc_IndexError, "Index out of range");
}

template<class T>
struct std_item
{
    typedef typename T::value_type V;

    static V & get(T & x, int i)
    {
        if (i < 0) i += x.size();
        if (i >= 0 && i < x.size()) return x[i];
        IndexError();
    }

    static void set(T & x, int i, V const& v)
    {
        if (i < 0) i += x.size();
        if (i >= 0 && i < x.size()) x[i] = v;
        else IndexError();
    }

    static void del(T & x, int i)
    {
        if (i < 0) i += x.size();
        if (i >= 0 && i < x.size()) x.erase(x.begin() + i);
        else IndexError();
    }

    static void add(T & x, V const& v)
    {
        x.push_back(v);
    }
};

//-----------------------helper 宏
//#define UseVec(name)\
// NameVec(name)\
// DefVec(name)

#define NameVec(name)\
    typedef std::vector<name> name##Vec

#define DefVec(MyVec) \
class_<MyVec > (#MyVec) \
.def("__len__", &MyVec::size)\
.def("clear", &MyVec::clear)\
.def("append", &std_item<MyVec>::add,\
     bp::with_custodian_and_ward <1, 2 > ()) \
.def("__getitem__", &std_item<MyVec>::get,  \
     return_value_policy<bp::copy_non_const_reference > ())\
.def("__setitem__", &std_item<MyVec>::set, \
     bp::with_custodian_and_ward<1, 2 >())\
.def("__delitem__", &std_item<MyVec>::del)\
.def("__iter__", bp::iterator<MyVec>())

typedef std::vector<int> IntVec;
typedef std::vector<float> FloatVec;
typedef std::vector<double> DoubleVec;
typedef std::vector<std::string> StringVec;
typedef std::vector<std::string> StrVec;
typedef std::vector<std::pair<std::string, int> > PairSIVec;
typedef std::pair<std::string, int> StrIntPair;
typedef std::map<std::string, std::string> StrStrMap;
typedef std::map<std::string, int> StrIntMap;
typedef std::map<std::string, double> StrDoubleMap;
typedef std::map<std::string, float> StrFloatMap;
typedef std::map<std::string, std::pair<int, int> > StrPairIIMap;
typedef std::set<std::string> StrSet;

using bp::vector_indexing_suite;
using bp::map_indexing_suite;
using bp::class_;
#define UseVec(X) \
  class_<X > (#X)\
.def(vector_indexing_suite<X> ())

#define UseMap(X) \
  class_<X > (#X)\
.def(map_indexing_suite<X > ())

#define UsePair(X) \
    class_<X >(#X)\
        .def_readwrite("first", &X::first)\
        .def_readwrite("second", &X::second)

#define UseStrStrMap \
  class_<StrStrMap > ("StrStrMap")\
.def(map_indexing_suite< StrStrMap > ())

#define UseStrIntMap \
  class_<StrIntMap > ("StrIntMap")\
.def(map_indexing_suite< StrIntMap > ())

#define UseStrDoubleMap \
	class_<StrDoubleMap > ("StrDoubleMap")\
	.def(map_indexing_suite< StrDoubleMap > ())

#define UseStrFloatMap \
	class_<StrFloatMap > ("StrFloatMap")\
	.def(map_indexing_suite< StrFloatMap > ())

#define UseStrPairIIMap \
  class_<StrPairIIMap > ("StrPairIIMap")\
.def(map_indexing_suite< StrPairIIMap > ())

#define UseIntVec \
  class_<IntVec > ("IntVec")\
.def(vector_indexing_suite< IntVec > ())

#define UseFloatVec \
  class_<FloatVec > ("FloatVec")\
.def(vector_indexing_suite< FloatVec > ())

#define UseDoubleVec \
  class_<DoubleVec > ("DoubleVec")\
.def(vector_indexing_suite< DoubleVec > ())

#define UseStringVec\
  class_<StringVec > ("StringVec")\
.def(vector_indexing_suite< StringVec > ())

#define UseStrVec\
	class_<StrVec > ("StrVec")\
	.def(vector_indexing_suite< StrVec > ())

//#define UseStrSet\
//	class_<StrSet > ("StrSet")\
//	.def(bp::map_indexing_suite<StrSet> ())

#endif  //----end of PYTHON_UTIL_H_
