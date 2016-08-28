/**
 *  ==============================================================================
 *
 *          \file   common_define.h
 *
 *        \author   chenghuige
 *
 *          \date   2016-02-16 12:32:36.615535
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef GEZI_COMMON_DEFINE_H_
#define GEZI_COMMON_DEFINE_H_

//#ifndef IS_HIGH_COMPILER
////@FIXME warning: macro expansion producing 'defined' has undefined behavior [-Wexpansion-to-defined]
//#define IS_HIGH_COMPILER  (!defined(GCCXML) && (__GNUC__ > 3 || defined(WIN32)))
//#endif    

#if (!defined(GCCXML) && (__GNUC__ > 3 || defined(WIN32)))
//--@TDOO finally should be below and IS_HIGH_COMPILER_  IS_HIGH_COMPILER_NOGCCXML will be depreciated, as GCCXML will use clang as high compiler
//#if ((__GNUC__ > 3 || defined(WIN32)))
#define IS_HIGH_COMPILER 1
#else
#define IS_HIGH_COMPILER 0
#endif

#if (!defined(GCCXML) && (__GNUC__ > 3 || defined(WIN32)))
#define IS_HIGH_COMPILER_NOGCCXML 1
#else
#define IS_HIGH_COMPILER_NOGCCXML 0
#endif

#if ((__GNUC__ > 3 || defined(WIN32)))
#define IS_HIGH_COMPILER_ 1
#else
#define IS_HIGH_COMPILER_ 0
#endif

#endif  //----end of GEZI_COMMON_DEFINE_H_
