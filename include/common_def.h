/**
 *  ==============================================================================
 *
 *          \file   common_def.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-19 07:01:25.886398
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef COMMON_DEF_H_
#define COMMON_DEF_H_
#include <string>
#include <vector>
#include <map>
#if __GNUC__ > 3
#include <array>
#else
#include <boost/array.hpp>
namespace std {
	using boost::array;
}
#endif
#include <fstream>
#include <sstream>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

#include <google/gflags.h>
#include <glog/logging.h>

typedef long long int64;
typedef unsigned int uint;
typedef unsigned long long uint64;
typedef unsigned char uchar;

typedef double Float;

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH
using boost::format;
using boost::is_any_of;
#include <boost/any.hpp>   
using boost::any_cast;
typedef std::map<std::string, boost::any> AnyMap;

#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
using boost::regex;
using boost::algorithm::split_regex;

#include <boost/function.hpp>
using boost::function;

//boost bind定义了golobal的_1.._9 所以这里通过define去掉,避免和boost::lambda里面的冲突
#define BOOST_BIND_PLACEHOLDERS_HPP_INCLUDED
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
using namespace boost::lambda;
//using boost::bind;
//#include <boost/spirit/include/phoenix_core.hpp>  
//using namespace boost::phoenix;
//using namespace boost::phoenix::arg_names;

#define BOOST_THREAD_DONT_USE_CHRONO
#include <boost/thread.hpp>

//using std::string;
//using std::vector;
//using std::set;
//using std::map;
//using std::ifstream;
//using std::ofstream;
using std::array;
using namespace std;

#endif  //----end of COMMON_DEF_H_
