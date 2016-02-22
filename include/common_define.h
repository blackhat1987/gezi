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

#ifndef IS_HIGH_COMPILER
//@FIXME warning: macro expansion producing 'defined' has undefined behavior [-Wexpansion-to-defined]
#define IS_HIGH_COMPILER  !defined(GCCXML) && (__GNUC__ > 3 || defined(WIN32))
#endif


#endif  //----end of GEZI_COMMON_DEFINE_H_
