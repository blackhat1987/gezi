/** 
 *  ==============================================================================
 * 
 *          \file   python_embed_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2010-12-20 21:19:22.513809
 *  
 *  \Description:  python嵌入C++的帮助函数
 *                         注意可能有更直接更好的方法。。。 比如from_python
 *                         但是不了解  暂时用这种办法hack...
 *  TODO 返回 [ [ ]...[] ] 这样双重的怎么办?
 *
 *  注意 比如你 得到返回的是list 那么每个list元素都是一个PyObject如果你知道它是什么类型 比如string 你需要 extract<>即可！
 *  ==============================================================================
 */

#ifndef PYTHON_EMBED_HELP_H_
#define PYTHON_EMBED_HELP_H_
#include <boost/python.hpp>
#include <vector>
#include <string>

namespace py = boost::python;

#define InitPy(space)\
    Py_Initialize();\
    py::object module = py::import("__main__");\
    py::object space = module.attr("__dict__");

template<typename T>
inline void  list2vec(const boost::python::list& list, std::vector<T>& vec)
{
    int len = boost::python::len(list);
    vec.reserve(len);
    for (int i = 0; i < len; i++)
    {
        vec.push_back(boost::python::extract<T>(list[i]));
    }
}

#endif  //----end of PYTHON_EMBED_HELP_H_
