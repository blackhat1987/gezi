/**
 *  ==============================================================================
 *
 *          \file   tieba/common_def.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-25 13:46:36.599365
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_COMMON_DEF_H_
#define TIEBA_COMMON_DEF_H_
#include <map>
#include <boost/any.hpp>
#include <string>
#include <vector>
using std::map;
using std::string;
using std::vector;
namespace gezi {
	namespace tieba {
		typedef map<string, vector<string> > VecHistoryType;
		typedef map<string, double> DoubleHistoryType;
		typedef map<string, boost::any> AnyHistoryType;
		typedef VecHistoryType HistoryType;
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_COMMON_DEF_H_
