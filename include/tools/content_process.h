/**
 *  ==============================================================================
 *
 *          \file   tools/content_process.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-03-03 09:59:08.057036
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TOOLS_CONTENT_PROCESS_H_
#define TOOLS_CONTENT_PROCESS_H_
#include "string_util.h"
namespace gezi {
	inline string strip_html(string src)
	{
		string pattern = "<a.*class=\"at\">@.{2,20}</a>|(<[^>]*>)|(//[^>]*>)|(&nbsp;)+";
		return reg_remove(src, pattern);
	}
}  //----end of namespace gezi

#endif  //----end of TOOLS_CONTENT_PROCESS_H_
