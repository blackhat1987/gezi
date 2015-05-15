/**
 *  ==============================================================================
 *
 *          \file   ThreadLocalAnyMap.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-10 10:20:29.064430
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef THREAD_LOCAL_ANY_MAP_H_
#define THREAD_LOCAL_ANY_MAP_H_

namespace gezi {

#ifdef __GNUC__   //@TODO VS2015 support thread local

	class ThreadLocalAnyMap
	{
	public:
		static AnyMap& Instance()
		{
			static thread_local AnyMap _map;
			return _map;
		}
	};

	typedef ThreadLocalAnyMap ThreadLocalData;

#endif //-- __GNUC__ 
}  //----end of namespace gezi

#endif  //----end of THREAD_LOCAL_ANY_MAP_H_
