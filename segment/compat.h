/** 
 *  ==============================================================================
 * 
 *          \file   compat.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-11 15:43:44.792275
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef COMPAT_H_
#define COMPAT_H_
#ifdef CHG_DEBUG
#include <glog/logging.h>
#include <boost/format.hpp>
#include "ngram_model/ambi_encode.h"
#else
#include "boost_hack/serialization.hpp"
#include "boost_hack/stack_constructor.hpp"
#include <iostream>
#define LOG(INFO) std::cout
#define LOG(WARNING) std::cout
#define LOG(FATAL) std::cout
#endif

namespace segment {


}  //----end of namespace segment

#endif  //----end of COMPAT_H_
