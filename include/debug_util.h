/*
 * File:   debug_util.h
 * Author: chenghuige
 *
 * Created on 2010年2月28日, 上午12:53
 */

#ifndef DEBUG_UTIL_H_
#define	DEBUG_UTIL_H_
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>   //for setw format output
#include <iterator>
#ifdef SIMPLE_DEBUG
#define LOG(INFO) cout
#define VLOG(0) cout
#define VLOG(5) cout
#else
#include <glog/logging.h>
#include <gflags/gflags.h>
#endif

using namespace std;

#define VPVAL(s, u)\
	VLOG(u) << #s <<" --- [" << s << "]"

#define PVAL(s)\
	VLOG(4) << #s <<" --- [" << s << "]"

#define PVAL_(s, u)\
	VLOG(4) << u << " " << #s <<" --- [" << s << "]"

#define Pval(s)\
	VLOG(0) << #s <<" --- [" << s << "]"
#define Pval_(s, u)\
	VLOG(0)  << u << " " << #s <<" --- [" << s << "]"

#define PVAL2(a, b)\
	VLOG(4) << #a <<" -- [" << a << "] " << #b <<" -- [" << b << "]"

#define Pval2(a, b)\
	VLOG(0) << #a <<" -- [" << a << "] " << #b <<" -- [" << b << "]"

#define PVAL3(a, b, c)\
	VLOG(4) << #a <<" -- [" << a << "] " << #b <<" -- [" << b << "] "  << #c <<" -- [" << c << "]"

#define Pval3(a, b, c)\
	VLOG(0) << #a <<" -- [" << a << "] " << #b <<" -- [" << b << "] "  << #c <<" -- [" << c << "]"

#define PVAL4(a, b, c, d)\
	VLOG(4) << #a <<" -- [" << a << "] " << #b <<" -- [" << b << "] "  << #c <<" -- [" << c << "] " << #d <<" -- [" << d << "]"

#define Pval4(a, b, c, d)\
	VLOG(0) << #a <<" -- [" << a << "] " << #b <<" -- [" << b << "] "  << #c <<" -- [" << c << "] " << #d <<" -- [" << d << "]"

#define PVAL5(a, b, c, d, e)\
	VLOG(4) << #a <<" -- [" << a << "] " << #b <<" -- [" << b << "] "  << #c <<" -- [" << c << "] " << #d <<" -- [" << d << "] " << #e <<" -- [" << e << "]"

#define Pval5(a, b, c, d, e)\
	VLOG(0) << #a <<" -- [" << a << "] " << #b <<" -- [" << b << "] "  << #c <<" -- [" << c << "] " << #d <<" -- [" << d << "] " << #e <<" -- [" << e << "]"

#define PvalFile(s, ofs)\
	ofs << #s <<" --- " << s << endl

/**
 * TODO FIXME!!! Prange 怎么会丢失没有打印第一个字符？ 见test_prob_seg;
 */
template<typename T>
void Pvec_(const T&vec, std::ostream& out = std::cout, string sep = "\n", string last = "\n")
{
	typedef typename T::value_type VType;
	typedef typename T::const_iterator Iter;
	for (Iter iter = vec.begin(); iter != vec.end(); ++iter)
	{
		out << *iter << sep;
	}
	out << last;
}

template<typename T>
void PrintPairVec(const T&vec, int level = 0, string sep = "\n", string last = "\n")
{
	typedef typename T::value_type VType;
	typedef typename T::const_iterator Iter;
	for (Iter iter = vec.begin(); iter != vec.end(); ++iter)
	{
		VLOG(level) << iter->first << " " << iter->second << sep;
	}
	VLOG(level) << last;
}

template<typename T>
void Pvec2_(const T&vec, std::ostream& out = std::cout, string sep = "\n", string last = "\n")
{
	typedef typename T::value_type VType;
	typedef typename T::const_iterator Iter;
	for (Iter iter = vec.begin(); iter != vec.end(); ++iter)
	{
		out << iter->first << " " << iter->second << sep;
	}
	out << last;
}
//TODO 不好重载。。。

template<typename Iter>
void Prange2(Iter begin, Iter end, std::ostream& out = std::cout, string sep = "\n", string last = "\n")
{
	for (; begin != end; ++begin)
	{
		out << begin->first << " " << begin->second << sep;
	}
	out << last;
}

template<typename Iter>
void Prange(Iter begin, Iter end, std::ostream& out = std::cout, string sep = "\n", string last = "\n")
{
	for (; begin != end; ++begin)
	{
		out << *begin << sep;
	}
	out << last;
}

template<typename T>
void PVec(const T&vec, std::ostream& out = std::cout, string sep = "\n", string last = "\n")
{
	typedef typename T::value_type VType;
	typedef typename T::const_iterator Iter;
	for (Iter iter = vec.begin(); iter != vec.end(); ++iter)
	{
		out << *iter << sep;
	}
	out << last;
}

template<typename T>
void LOGPVec(const T&vec, string sep = " ", int level = 5, string last = "\n")
{
	typedef typename T::value_type VType;
	typedef typename T::const_iterator Iter;
	stringstream ss;
	for (Iter iter = vec.begin(); iter != vec.end(); ++iter)
	{
		ss << *iter << sep;
	}
	ss << last;
	VLOG(level) << ss.str();
}

template<typename Iter>
void PRange(Iter begin, Iter end, std::ostream& out = std::cout, string sep = "\n", string last = "\n")
{
	for (; begin != end; ++begin)
	{
		out << *begin << sep;
	}
	out << last;
}

#define PVECTOR(v)\
{\
	stringstream ss;\
	ss << #v << ":";\
	for (size_t i_ = 0; i_ < v.size(); i_++)\
{\
	ss << setiosflags(ios::left) << setfill(' ') << setw(10) << i_ << v[i_];\
}\
	VLOG(5) << ss.str();\
}
	

#define Pvector(v)\
{\
	stringstream ss;\
	ss << #v << ":";\
	for (size_t i_ = 0; i_ < v.size(); i_++)\
{\
	ss << setiosflags(ios::left) << setfill(' ') << setw(10) << i_ << v[i_]; \
}\
	VLOG(0) << ss.str();\
}

#define PVEC(v)\
	VLOG(5) << #v <<" --- " << v.size();\
	for (size_t i_ = 0; i_ < v.size(); i_++)\
{\
	VLOG(5) << setiosflags(ios::left) << setfill(' ') << setw(10) << i_ << v[i_];\
}

#define PVEC_TOPN(v, n)\
	VLOG(5) << #v <<" --- " << v.size();\
	for (size_t i_ = 0; i_ < v.size() && i_ < n; i_++)\
{\
	VLOG(5) << setiosflags(ios::left) << setfill(' ') << setw(10) << i_ << v[i_];\
}

#define Pvec(v)\
	VLOG(0) << #v <<" --- " << v.size();\
	for (size_t i_ = 0; i_ < v.size(); i_++)\
{\
	VLOG(0) << setiosflags(ios::left) << setfill(' ') << setw(10) << i_ << v[i_];\
}


#define PRANGE(s, e)\
	VLOG(5) << #s <<" ---";\
	PRange(s, e)

template<typename T>
void WPvec(const T&vec, std::wostream& out = std::wcout, const wstring& end = L" ", const wstring& last = L"\n")
{
	typedef typename T::value_type VType;
	typedef typename T::const_iterator Iter;
	for (Iter iter = vec.begin(); iter != vec.end(); ++iter)
	{
		out << *iter << end;
	}
	out << last;
}

#define PrintVec(vec, arg1) \
	VLOG(5) << #vec <<" --- " << vec.size();\
	for (size_t i = 0; i < vec.size(); i++) \
{  \
	VLOG(5) << setiosflags(ios::left) << setfill(' ') << setw(4) << i << vec[i].arg1; \
}
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
	VLOG(5) << setiosflags(ios::left) << setfill(' ') << setw(10) << vec[i].arg1; \
}

#define PrintVec2TopN(vec, arg1, arg2, n) \
	for (size_t i = 0; i < n; i++) \
{  \
	VLOG(5) << setiosflags(ios::left) << setfill(' ') << setw(10) << vec[i].arg1 << " " \
	<< vec[i].arg2; \
}

#define PrintVec2(vec, arg1, arg2) \
	VLOG(5) << #vec <<" --- " << vec.size();\
	for (size_t i = 0; i < vec.size(); i++) \
{  \
	VLOG(5) << setiosflags(ios::left) << setfill(' ') << setw(10) << i << vec[i].arg1 << " " \
	<< vec[i].arg2; \
}

#define PrintVec_(vec, arg1, file) \
	std::ofstream out##file(#file); \
	for (size_t i = 0; i < vec.size(); i++) \
{  \
	out##file << setiosflags(ios::left) << setw(10) << vec[i].arg1; \
	out##file << std::endl; \
}\
	out##file << std::endl; \
	out##file.close()

#define PrintVec2_(vec, arg1, arg2, file) \
	std::ofstream out##file(#file); \
	for (size_t i = 0; i < vec.size(); i++) \
{  \
	out##file << setiosflags(ios::left) << setw(10) << vec[i].arg1 << " " \
	<< vec[i].arg2; \
	out##file << std::endl; \
}\
	out##file << std::endl; \
	out##file.close()

#define PrintVec3(vec, arg1, arg2, arg3) \
	VLOG(5) << #vec <<" --- " << vec.size();\
	for (size_t i = 0; i < vec.size(); i++) \
{  \
	VLOG(5) << setiosflags(ios::left) << setfill(' ') << setw(10) << i << vec[i].arg1 << " " \
	<< vec[i].arg2 << " " << vec[i].arg3; \
}

#define PrintVec4(vec, arg1, arg2, arg3, arg4) \
	VLOG(5) << #vec <<" --- " << vec.size();\
	for (size_t i = 0; i < vec.size(); i++) \
{  \
	VLOG(5) << setiosflags(ios::left) << setfill(' ') << setw(10) << i << vec[i].arg1 << " " \
	<< vec[i].arg2 << " " << vec[i].arg3 << " " << vec[i].arg4; \
}

#define PrintVec3_(vec, arg1, arg2, arg3, file) \
	std::ofstream out##file(#file); \
	for (size_t i = 0; i < vec.size(); i++) \
{  \
	out##file << setiosflags(ios::left) << setw(10) << vec[i].arg1 << " " \
	<< vec[i].arg2 << " " << vec[i].arg3; \
	out##file << std::endl; \
}\
	out##file << std::endl; \
	out##file.close()

#define PrintVecAdd2(vec, arg1, arg2) \
	for (size_t i = 0; i < vec.size(); i++) \
{  \
	out << setiosflags(ios::left) << setw(10) << vec[i].arg1 << " " \
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
	out##file << setiosflags(ios::left) << setw(10) << (*begin).arg1; \
	out##file << std::endl; \
	++begin; \
}\
	out##file << std::endl; \
	out##file.close()

#define PrintRange2(begin, end, arg1, arg2, file) \
	std::ofstream out##file(#file); \
while(begin != end) \
{  \
	out##file << setiosflags(ios::left) << setw(10) << (*begin).arg1 << " " << (*begin).arg2; \
	out##file << std::endl; \
	++begin; \
}\
	out##file << std::endl; \
	out##file.close()

#define printRange2(begin, end, arg1, arg2, file) \
while(begin != end) \
{  \
	out << setiosflags(ios::left) << setw(10) << (*begin).arg1 << " " << (*begin).arg2; \
	out << std::endl; \
	++begin; \
}\
	out << std::endl; \
	out.close()

#define printRangeFunc2(begin, end, arg1, func1, arg2, func2, file) \
while(begin != end) \
{  \
	out << setiosflags(ios::left) << setw(10) << func1((*begin).arg1) << " " << func2((*begin).arg2); \
	out << std::endl; \
	++begin; \
}\
	out << std::endl; \
	out.close()


#endif	/* _DEBUG_HELPER_H */

