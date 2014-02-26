/** 
 *  ==============================================================================
 * 
 *          \file   common_util.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2010-11-15 16:33:52.681821
 *  
 *  \Description:  
 *  ==============================================================================
 */

#ifndef COMMON_UTIL_H_
#define COMMON_UTIL_H_

#include <stdlib.h>
#include <string.h>

#include <gtest/gtest.h> 
#include <glog/logging.h>
#include <gflags/gflags.h>

#include "common_def.h"

#include "hashmap_util.h"
#include "log_util.h"
#include "conf_util.h"
#include "debug_util.h"
#include "string_util.h"
#include "serialize_util.h"
#include "Matrix.h"
#include "sort_util.h"

#include "statistic_util.h"
#include "datetime_util.h"
#include "time_util.h"

#include "file_util.h"
#include "stl_util.h"
#include "linq.h"

#ifndef NO_GEZI_CONVERT
#include "convert_type.h"
#endif

#include "Exception.h"

#include "ProgressBar.h"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&); \
	void operator=(const TypeName&)


#define FREE(ptr) \
  {if (ptr) { delete ptr; ptr = NULL;}}

#define FREE2(ptr) \
  {if (ptr) { delete [] ptr; ptr = NULL;}}


namespace gz = gezi;
#endif  //----end of COMMON_UTIL_H_
