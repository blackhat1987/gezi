/** 
 *  ==============================================================================
 * 
 *          \file   segment_result_func.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-10-11 14:28:28.805448
 *  
 *  \Description:   提供结果处理的不同处理函数
 *                  比如将star,len结果按照term 存储
 *                  或者直接存储string
 *  ==============================================================================
 */

#ifndef SEGMENT_RESULT_FUNC_H_
#define SEGMENT_RESULT_FUNC_H_
#include "seg_type.h"
#include <bitset>
#include <vector>
#include <set>
namespace segment
{

template<typename T>
struct ResultFunc
{

    ResultFunc()
    {
    }

    ResultFunc(const string & key)
    {
    }

    void operator()(vector<T>& out, int start, int len, int level) const
    {
        out.push_back(start);
    }

    void operator()(std::set<T>& out, int start, int len, int level) const
    {
        out.insert(start);
    }

};

template<>
struct ResultFunc<Term>
{

    ResultFunc()
    {
    }

    ResultFunc(const string & key)
    {
    }

    void operator()(vector<Term>& out, int start, int len, int level) const
    {
        out.push_back(Term(start, len, level));
    }

};

template<>
struct ResultFunc<std::string>
{
    const string& key_;

    ResultFunc(const string & key)
    : key_(key)
    {
    }

    void operator()(vector<string>& out, int start, int len, int level) const
    {
        string s = key_.substr(start, len);
        // if (!(s.size() == 1 && std::isspace(s[0])))
        if (!(s == " "))
        {
            out.push_back(s);
        }
    }

    void operator()(std::set<string>& out, int start, int len, int level) const
    {
        string s = key_.substr(start, len);
        // if (!(s.size() == 1 && std::isspace(s[0])))
        if (!(s == " "))
        {
            out.insert(s);
        }
    }
};

} //----end of namespace segment

#endif  //----end of SEGMENT_RESULT_FUNC_H_
