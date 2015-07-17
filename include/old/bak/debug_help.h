/* 
 * File:   debug_help.h
 * Author: chenghuige
 *
 * Created on 2010年2月28日, 上午12:53
 */

#ifndef _DEBUG_HELPER_H
#define	_DEBUG_HELPER_H
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>   //for setw format output
#include <iterator>
//namespace debug_help
//{
using namespace std;

#define Pval(s)\
    cout << #s <<" ------- " << s << endl
#define PvalFile(s, ofs)\
     ofs << #s <<" ------- " << s << endl
template<typename T>
void Prange(const T&vec, std::ostream& out = std::cout, const string& end = " ", const string& last = "\n")
{
    typedef typename T::value_type VType;
    std::copy(vec.begin(), vec.end(), ostream_iterator<VType > (out, end.c_str()));
    //    for (size_t i = 0; i < vec.size(); i++)
    //    {
    ////        out << setiosflags(ios::left) << setw(4) << vec[i] << " ";
    //         out << setiosflags(ios::left) << vec[i] << end;
    //    }
    out << last;
}


//#define Pinfo(s)\
//    LOG(INFO) <<  #s <<" " << s << endl
/**
 * 该函数可以打印数据类型为简单类型
 * (int,long,long long,float,double,char,unsigned char, __int64, unsigned int, char*)struct的数组
 *  i   l     m        f     d       c          C          j         I            s
 *  FIXME 这个实现会存在对齐问题吗，尝试用va_list未遂
 *  FIXME __64 显示不正确 
 **/
#define PrintVecTopN(vec, arg1, n) \
    for (size_t i = 0; i < n; i++) \
    {  \
        std::cout << setiosflags(ios::left) << setw(20) << vec[i].arg1; \
        std::cout << std::endl; \
    }\
    std::cout << std::endl

#define PrintVec2TopN(vec, arg1, arg2, n) \
    for (size_t i = 0; i < n; i++) \
    {  \
        std::cout << << setiosflags(ios::left) << setw(20) << vec[i].arg1 << " " \
                << vec[i].arg2; \
        std::cout << std::endl; \
    }\
    std::cout << std::endl

#define PrintVec(vec, arg1) \
    for (size_t i = 0; i < vec.size(); i++) \
    {  \
        std::cout << setiosflags(ios::left) << setw(4) << vec[i].arg1 << " "; \
    }\
    cout << std::endl

#define PrintVec2(vec, arg1, arg2) \
    for (size_t i = 0; i < vec.size(); i++) \
    {  \
        cout << setiosflags(ios::left) << setw(20) << vec[i].arg1 << " " \
                << vec[i].arg2; \
        cout << std::endl; \
    }\
    cout << std::endl

#define PrintVec_(vec, arg1, file) \
    std::ofstream out##file(#file); \
    for (size_t i = 0; i < vec.size(); i++) \
    {  \
        out##file << setiosflags(ios::left) << setw(20) << vec[i].arg1; \
        out##file << std::endl; \
    }\
    out##file << std::endl; \
    out##file.close()

#define PrintVec2_(vec, arg1, arg2, file) \
    std::ofstream out##file(#file); \
    for (size_t i = 0; i < vec.size(); i++) \
    {  \
        out##file << setiosflags(ios::left) << setw(20) << vec[i].arg1 << " " \
                << vec[i].arg2; \
        out##file << std::endl; \
    }\
    out##file << std::endl; \
    out##file.close()

#define PrintVec3(vec, arg1, arg2, arg3) \
    for (size_t i = 0; i < vec.size(); i++) \
    {  \
        cout << setiosflags(ios::left) << setw(5) << vec[i].arg1 << " " \
                << vec[i].arg2 << " " << vec[i].arg3; \
        cout << std::endl; \
    }

#define PrintVec3_(vec, arg1, arg2, arg3, file) \
    std::ofstream out##file(#file); \
    for (size_t i = 0; i < vec.size(); i++) \
    {  \
        out##file << setiosflags(ios::left) << setw(20) << vec[i].arg1 << " " \
                << vec[i].arg2 << " " << vec[i].arg3; \
        out##file << std::endl; \
    }\
    out##file << std::endl; \
    out##file.close()

#define PrintVecAdd2(vec, arg1, arg2) \
    for (size_t i = 0; i < vec.size(); i++) \
    {  \
        out << setiosflags(ios::left) << setw(20) << vec[i].arg1 << " " \
                << vec[i].arg2; \
        out << std::endl; \
    }


#define PrintVecFunc(vec, arg1, func1, file) \
    std::ofstream out##file(#file); \
    for (size_t i = 0; i < vec.size(); i++) \
    {  \
        out##file << setiosflags(ios::left) << setw(40) << func1(vec[i].arg1); \
        out##file << std::endl; \
    }\
    out##file << std::endl; \
    out##file.close()

#define PrintVecFunc2(vec, arg1, func1, arg2, func2, file) \
    std::ofstream out##file(#file); \
    for (size_t i = 0; i < vec.size(); i++) \
    {  \
        out##file << setiosflags(ios::left) << setw(40) << func1(vec[i].arg1) << " " << func2(vec[i].arg2); \
        out##file << std::endl; \
    }\
    out##file << std::endl; \
    out##file.close()


#define PrintRange(begin, end, arg1, file) \
    std::ofstream out##file(#file); \
    while(begin != end) \
    {  \
        out##file << setiosflags(ios::left) << setw(20) << (*begin).arg1; \
        out##file << std::endl; \
        ++begin; \
    }\
    out##file << std::endl; \
    out##file.close()

#define PrintRange2(begin, end, arg1, arg2, file) \
    std::ofstream out##file(#file); \
    while(begin != end) \
    {  \
        out##file << setiosflags(ios::left) << setw(20) << (*begin).arg1 << " " << (*begin).arg2; \
        out##file << std::endl; \
        ++begin; \
    }\
    out##file << std::endl; \
    out##file.close()

#define printRange2(begin, end, arg1, arg2, file) \
    while(begin != end) \
    {  \
        out << setiosflags(ios::left) << setw(20) << (*begin).arg1 << " " << (*begin).arg2; \
        out << std::endl; \
        ++begin; \
    }\
    out << std::endl; \
    out.close()

#define printRangeFunc2(begin, end, arg1, func1, arg2, func2, file) \
    while(begin != end) \
    {  \
        out << setiosflags(ios::left) << setw(20) << func1((*begin).arg1) << " " << func2((*begin).arg2); \
        out << std::endl; \
        ++begin; \
    }\
    out << std::endl; \
    out.close()


//} //end of namesapce debug_help

//using namespace debug_help;
#endif	/* _DEBUG_HELPER_H */

