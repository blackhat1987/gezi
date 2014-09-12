/**
 *  ==============================================================================
 *
 *          \file   SharedAnyMap.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-11 14:31:34.250510
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef SHARED_ANY_MAP_H_
#define SHARED_ANY_MAP_H_
#include "common_util.h"
namespace gezi {

class SharedAnyMap 
{
public:

	static AnyMap& Instance()
	{
		static AnyMap _map;
		return _map;
	}
};

typedef SharedAnyMap SharedData;

}  //----end of namespace gezi

#endif  //----end of SHARED_ANY_MAP_H_
