/**
 *  ==============================================================================
 *
 *          \file   vector_def.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-07-20 12:07:59.390678
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef VECTOR_DEF_H_
#define VECTOR_DEF_H_

#ifdef USE_FOLLY_VECTOR_AS_DEFAULT
#include <folly/FBVector.h>
template<class T, typename...> using vector = folly::fbvector < T, std::allocator<T> > ;
//template<class T, std::allocator<T> > using vector = folly::fbvector < T, std::allocator<T> >;
using ::vector;
#else 
#include <vector>
using std::vector;
#endif // USE_FOLLY_VECTOR_AS_DEFAULT

namespace gezi {

}
#endif  //----end of VECTOR_DEF_H_
