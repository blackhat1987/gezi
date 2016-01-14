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
#define omp_get_thread_num() 0
#define omp_get_num_threads() 1
#define omp_get_num_procs() 1
#define omp_set_num_threads {}
#endif

#include <algorithm>

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

	inline int set_num_threads(int numThreads = 0, int reduce = 2)
	{
		if (numThreads)
		{
			omp_set_num_threads(numThreads);
			return numThreads;
		}
		else
		{ //@TODO openmp设置线程数目很微妙。。 如果有其它程序在跑12核 设置12 很慢 11，13 等都比12快很多。。
			int numProcs = omp_get_num_procs();
			numProcs = std::max(1, numProcs - reduce);
			omp_set_num_threads(numProcs);
			return numProcs;
		}
	}
}  //----end of namespace gezi

#endif  //----end of OPENMP_UTIL_H_
