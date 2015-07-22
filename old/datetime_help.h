/** 
 *  ==============================================================================
 * 
 *          \file   datetime_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-29 10:31:24.159056
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef DATETIME_HELP_H_
#define DATETIME_HELP_H_
#include <string>
#include <boost/lexical_cast.hpp>
inline std::string getMounth(int m)
{ //TODO not used here so move to helper file
    using std::string;
    string mounth = boost::lexical_cast<string > (m);
    if (mounth.size() == 1)
    {
        mounth = string("0") + mounth;
    }
    return mounth;
}
#endif  //----end of DATETIME_HELP_H_
