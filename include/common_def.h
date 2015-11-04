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
#ifndef  BOOST_DETAIL_NO_CONTAINER_FWD
#define BOOST_DETAIL_NO_CONTAINER_FWD
#endif

#include "format.h" //放在最前面 有和convert_type.h的宏的冲突处理 

#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>

#include <limits>
#include <cmath>
#if __GNUC__ > 3 || defined(WIN32) 
#include <mutex>
#include <array>
#include <memory>
#include <thread>
#include <omp.h> //openmp for gcc4
//using namespace std::placeholders; //去掉这个一个测试lambda bind的测试会有问题 但是一般ok 使用lambda不用bind 将_1等留给boost也避免冲突
#else
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/ref.hpp>
#include <boost/function.hpp>
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
namespace std {
	using boost::array;
	using boost::ref;
	using boost::shared_ptr;
	using boost::function;
	using boost::thread;
				using boost::bind;
				using boost::cref;
}
#endif

#include "hashmap_util.h"

using std::bind;
using std::function;
using std::shared_ptr;
using std::thread;
using std::ref; 
using std::cref;
#if __GNUC__ > 3 || defined(WIN32)
using std::mutex;
using std::lock_guard;
#endif

#include <iostream>     // std::cout, std::hex, std::endl
#include <iomanip>      // std::setiosflags
#include <fstream>
#include <sstream>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

typedef long long int64;
typedef unsigned int uint;
typedef unsigned long long uint64;
typedef unsigned char uchar;

typedef unsigned int WordIndex;

//typedef float Float;

#ifdef FLOAT32
typedef float Float;
#else
typedef double Float;
#endif // FLOAT

using std::set;
using std::map;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::array;
using std::swap;
using std::pair;
using std::make_pair;
using std::setfill;
using std::endl;
using std::sort;


//-------------folly related
//#ifdef GEZI_USE_FOLLY
#ifndef GEZI_NO_FOLLY   //@FXIME urate中发现ub.h -> ul_log.h 由于定义宏Max。。 会冲突且暂时没有解决
#ifdef MAX           //sb ullog  #define Max(a,b) ((a)>(b)?(a):(b))
#undef  MAX
#endif

#ifdef MIN           //sb ullog  #define Max(a,b) ((a)>(b)?(a):(b))
#undef  MIN
#endif

#ifndef	FOLLY_NO_CONFIG 
#define FOLLY_NO_CONFIG 1
#endif

#ifndef  FOLLY_HAVE_CLOCK_GETTIME
#define FOLLY_HAVE_CLOCK_GETTIME 1
#endif

#ifndef FOLLY_VERSION 
#define FOLLY_VERSION "1"
#endif

#ifndef FOLLY_HAVE_MALLOC_H
#define  FOLLY_HAVE_MALLOC_H 1
#endif

#ifndef GCCXML

#include "folly/Foreach.h"
#include "folly/small_vector.h"
#include "folly/MapUtil.h"
#include "folly/FBVector.h"

//@TODO c++14 里面有了make_unique
#include "folly/Memory.h"

namespace std
{
	using folly::make_unique;
}
using std::make_unique;
//#endif //GEZI_USE_FOLLY 
#endif //GEZI_NO_FOLLY

#endif //GCCXML


#if __GNUC__ > 3 || defined(WIN32)
using std::move;
using std::make_shared;
#endif

//using namespace std;
#include "vector_def.h"
#include "string_def.h"

typedef vector<int> ivec;
typedef shared_ptr<ivec> ivec_ptr;
typedef shared_ptr<ivec> IvecPtr;
typedef vector<int64> lvec;
typedef vector<uint> uvec;
typedef vector<uint64> ulvec;
typedef vector<double> dvec;
typedef vector<float> fvec;
typedef vector<Float> Fvec;
typedef shared_ptr<Fvec> fvec_ptr;
typedef shared_ptr<Fvec> FvecPtr;
typedef vector<string> svec;

#include <boost/dynamic_bitset.hpp>
typedef vector<unsigned> bvec;
//vector<bool>不是线程安全的 包括随机index访问等等 内存不是连续存储的 @NOTICE
//但是貌似下面的其它替代都有序列化问题 所以 还是特别注意吧。。 线程安全等使用bvec
typedef vector<bool> BitArray;
//typedef boost::dynamic_bitset<> BitArray;
//typedef deque<bool> BitArray;

//------------下面主要是python封装的时候使用
typedef std::pair<int, int> ii_pair;
typedef std::pair<std::string, int> si_pair;
typedef std::pair<std::wstring, int> wsi_pair;
typedef std::vector<std::pair<std::string, int> > si_pair_vec;
typedef std::vector<std::pair<std::wstring, int> > wsi_pair_vec;
typedef std::map<std::string, std::string> ss_map;
typedef std::map<std::string, int> si_map;
typedef std::unordered_map<std::string, int> si_hashmap;
typedef std::map<std::string, double> sd_map;
typedef std::map<std::string, float> sf_map;
typedef std::map<int, double> id_map;
typedef std::map<int, float> if_map;
typedef std::map<int, Float> iF_map;
typedef std::map<int64, double> ld_map;
typedef std::map<int64, float> lf_map;
typedef std::map<int64, Float> lF_map;
typedef std::map<uint, double> ud_map;
typedef std::map<uint, float> uf_map;
typedef std::map<uint, Float> uF_map;
typedef std::map<uint64, double> uld_map;
typedef std::map<uint64, float> ulf_map;
typedef std::map<uint64, Float> ulF_map;
typedef std::map<std::string, std::pair<int, int> > str_iipair_map;
typedef std::set<std::string> sset;
typedef std::set<int> iset;
typedef std::set<int64> lset;
typedef std::set<uint64> ulset;

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

//using boost::format; //可能会倾向使用cppformat即 fmt::format 不过暂时很多代码使用boost 并且两者格式不一样
using fmt::format; //@TODO 也许所有using typedef 都应该放到gezi namespace内部

using boost::is_any_of;
#include <boost/any.hpp>   
using boost::any_cast;
using boost::any;
typedef std::map<std::string, boost::any> AnyMap;

//@TODO 确认支持regex的gcc版本
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
using boost::regex;
using boost::algorithm::split_regex;

#define interface class //most for pyplusplus wrapper

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&); \
	void operator=(const TypeName&)

#define FREE(ptr) \
{if (ptr) { delete ptr; ptr = NULL;}}

#define FREE2(ptr) \
{if (ptr) { delete [] ptr; ptr = NULL;}}

#define FREE_ARRAY(ptr) \
{if (ptr) { delete[] ptr; ptr = NULL; }}


#define  EXECUTE(cmd) \
	Pval(cmd);\
	system((cmd).c_str())

#if __GNUC__ > 3 || defined(WIN32)
//for polynomial class
//#define  IS_TYPE_OF(a,A) \
//	(dynamic_cast<A>(a) != nullptr)

#define  IS_POINTER_TYPE_OF(a,A)\
	(dynamic_pointer_cast<A>(a) != nullptr)
#endif


#ifndef VERSION
#define  VERSION "unknown"
#endif

namespace gezi
{
	//use this or just use pair ? first as key second as value//suggested to use pair for generic
	template<typename Key, typename Value>
	struct KeyValuePair
	{
		Key key;
		Value value;

		KeyValuePair(const Key& key_, const Value& value_)
			:key(key_), value(value_)
		{

		}

		bool operator == (const KeyValuePair<Key, Value>& other)
		{
			return key == other.key;
		}

		bool operator < (const KeyValuePair<Key, Value>& other)
		{
			key < other.key;
		}
	};


	inline string get_version()
	{
		return string(VERSION) + " -- " + string(__DATE__) + " -- " + string(__TIME__);
	}
} //-----------end of gezi

#endif  //----end of COMMON_DEF_H_
