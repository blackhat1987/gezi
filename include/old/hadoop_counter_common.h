/** 
 *  ==============================================================================
 * 
 *          \file   hadoop_counter_common.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-09-11 12:13:29.879087
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef HADOOP_COUNTER_COMMON_H_
#define HADOOP_COUNTER_COMMON_H_

namespace semantic {
enum
{
    MAX_TERM_COUNT = 4096
};
//static const char stop1[] = {'.', '?', '!', ','};
//static const char* stop2[] = {"¡£", "£¬", "£¡", "£¿"};
static const char stop1[] = {'.', '?', '!'};
static const char* stop2[] = {"¡£", "£¡", "£¿"};

enum
{
    gram0, gram1, gram2
};
static const char* start[] = {"A ", "B ", "C "};

} //----end of namespace semantic

#endif  //----end of HADOOP_COUNTER_COMMON_H_
