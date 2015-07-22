/** 
 *  ==============================================================================
 * 
 *          \file   contanier_convert.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-06 20:46:35.701265
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef CONTANIER_CONVERT_H_
#define CONTANIER_CONVERT_H_
#include <vector>
template<typename _Vec>
void convert(const _Vec& vec, std::vector<int>& rvec)
{
    rvec.resize(vec.size());
    for (size_t i = 0; i < vec.size(); i++)
    {
        rvec[i] = vec[i].id;
    }
}

#endif  //----end of CONTANIER_CONVERT_H_
