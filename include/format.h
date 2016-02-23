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

#include "common_define.h"
#if defined (IS_HIGH_COMPILER)

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

namespace fmt {

	inline void print_line(StringRef format_str, ArgList args)
	{
		print(format("{}\n", format_str), args);
	}

	inline void print_colored_line(Color c, StringRef format_str, ArgList args)
	{
		print_colored(c, format("{}\n", format_str), args);
	}

	FMT_VARIADIC(void, print_line, StringRef)
	FMT_VARIADIC(void, print_colored_line, Color, StringRef)
}
namespace gezi {

}  //----end of namespace gezi

#endif //IS_HIGH_COMPILER

#endif  //----end of FORMAT_H_
