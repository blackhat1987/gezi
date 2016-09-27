/** 
 *  ==============================================================================
 * 
 *          \file   inverted_default_value.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-16 23:28:11.910177
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef INVERTED_DEFAULT_VALUE_H_
#define INVERTED_DEFAULT_VALUE_H_

namespace inverted {
inline void init_default_null_value(unsigned int& null_value)
{
    null_value = 0;
}
	
inline void init_default_null_value(int& null_value)
{
    null_value = 0;
}
inline void init_default_null_value(float& null_value)
{
    null_value = 0;
}
inline void init_default_null_value(double& null_value)
{
    null_value = 0;
}
inline void init_default_null_value(size_t& null_value)
{
    null_value = 0;
}
inline void init_default_null_value(long long& null_value)
{
    null_value = 0;
}
inline void init_default_null_value(unsigned long long& null_value)
{
    null_value = 0;
}

} //----end of namespace inverted

#endif  //----end of INVERTED_DEFAULT_VALUE_H_
