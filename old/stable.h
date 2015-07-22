/** 
 *  ==============================================================================
 * 
 *          \file   stable.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-09-11 11:05:41.986922
 *  
 *  \Description:   sorted table
 *  ==============================================================================
 */

#ifndef STABLE_H_
#define STABLE_H_
#include "common_help.h"
#include <algorithm>
#include <vector>
#include <string>
template<typename T = int>
class STable
{
public:
    bool load(const std::string& file)
    {
        return read_vec2d(file, _table);
    }
    /**
     * do not check i and j
     */
    bool operator()(int i, T j) const
    {
        return std::binary_search (_table[i].begin(), _table[i].end(), j);
    }
private:
    std::vector<std::vector<T> > _table;
};

#endif  //----end of STABLE_H_
