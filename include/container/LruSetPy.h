/**
 *  ==============================================================================
 *
 *          \file   container/LruSetPy.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-12-17 19:15:03.314264
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef GEZI_CONTAINER__LRU_SET_PY_H_
#define GEZI_CONTAINER__LRU_SET_PY_H_

#ifdef GCCXML
#include <set>
#else
#include "container/LruSet.h"
#endif // GCCXML

namespace gezi {
#ifdef GCCXML
	typedef std::set<unsigned long long> LruHashSet_uint64;
	typedef std::set<int> LruHashSet_int;
#else
	typedef LruHashSet<unsigned long long> LruHashSet_uint64;
	typedef LruHashSet<int> LruHashSet_int;
#endif // GCCXML

	struct PyHack_LruHashSet_uint64 : public LruHashSet_uint64
	{
	};
	struct PyHack_LruHashSet_int : public LruHashSet_int
	{
	};
}  //----end of namespace gezi

#endif  //----end of GEZI_CONTAINER__LRU_SET_PY_H_
