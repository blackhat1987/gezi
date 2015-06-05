/**
 *  ==============================================================================
 *
 *          \file   rabit_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-06-05 21:56:12.572037
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef RABIT_UTIL_H_
#define RABIT_UTIL_H_

#include "raibt.h"

namespace gezi
{
	struct Rabit
	{
		Rabit(int argc, char *argv[])
		{
			rabit::Init(argc, argv);
		}
		~Rabit()
		{
			rabit::Finalize();
		}
	};
}
#endif  //----end of RABIT_UTIL_H_
