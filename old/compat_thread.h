/** 
 *  ==============================================================================
 * 
 *          \file   compat_thread.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-19 20:08:57.513282
 *  
 *  \Description:   为了不同系统能够兼容thread
 *  ==============================================================================
 */

#ifndef COMPAT_THREAD_H_
#define COMPAT_THREAD_H_

#if __GNUC__ > 3
#include<thread>  //chg modified using unordered map
#else
#include <boost/thread.hpp>
namespace std {
using ::boost::thread;
}
#endif

#endif  //----end of COMPAT_THREAD_H_
