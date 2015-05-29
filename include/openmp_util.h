/**
 *  ==============================================================================
 *
 *          \file   openmp_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-05-12 17:29:47.313001
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef OPENMP_UTIL_H_
#define OPENMP_UTIL_H_

//#ifdef _OPENMP 
//#undef _OPENMP
//#endif

#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_num_threads() 1
#define omp_get_num_procs() 1
#define omp_set_num_threads {}
#endif

namespace gezi {

	inline int get_num_threads()
	{
		int numThreads = 1;
#pragma omp parallel
#pragma omp master
		{
			numThreads = omp_get_num_threads();
		} 
		return numThreads;
	}
}  //----end of namespace gezi

#endif  //----end of OPENMP_UTIL_H_
