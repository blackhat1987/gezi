/**
 *  ==============================================================================
 *
 *          \file   tools/contents_process.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-11 18:02:05.886212
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TOOLS_CONTENTS_PROCESS_H_
#define TOOLS_CONTENTS_PROCESS_H_

#include "tools/content_process.h"
namespace gezi {

	inline vector<svec> get_pics(const svec& contents)
	{
		vector<svec> resultVec;
		for (auto& content : contents)
		{
			svec vec = get_pics(content);
			resultVec.emplace_back(vec);
		}
		return resultVec;
	}
}  //----end of namespace gezi

#endif  //----end of TOOLS_CONTENTS_PROCESS_H_
