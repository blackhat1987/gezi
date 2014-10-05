/**
 *  ==============================================================================
 *
 *          \file   format.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-10-05 23:01:49.062666
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef FORMAT_H_
#define FORMAT_H_
#define INT INT_CPPFORMAT
#define UINT UINT_CPPFORMAT
#define STRING STRING_CPPFORMAT
#include "cppformat/format.h"
#undef INT 
#undef UINT 
#undef STRING 

#ifndef NO_GEZI_CONVERT
#include "convert_type.h"
#endif

namespace gezi {

}  //----end of namespace gezi

#endif  //----end of FORMAT_H_
