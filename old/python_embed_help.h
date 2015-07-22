/** 
 *  ==============================================================================
 * 
 *          \file   python_embed_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2010-12-20 21:19:22.513809
 *  
 *  \Description:  pythonǶ��C++�İ�������
 *                         ע������и�ֱ�Ӹ��õķ��������� ����from_python
 *                         ���ǲ��˽�  ��ʱ�����ְ취hack...
 *  TODO ���� [ [ ]...[] ] ����˫�ص���ô��?
 *
 *  ע�� ������ �õ����ص���list ��ôÿ��listԪ�ض���һ��PyObject�����֪������ʲô���� ����string ����Ҫ extract<>���ɣ�
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
