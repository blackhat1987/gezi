/** 
 *  ==============================================================================
 * 
 *          \file   bit_file_set.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-11 20:48:47.277261
 *  
 *  \Description:   use bitset or vector<bool>
 *   std::bistset is static
 *   vector<bool> and boost::dynamic_bitset is dynamic  boost and vector<bool> seems to have similar implementaion
 *   offer some other bits funcitons like <<
 *   So here we use vector<bool> will be ok
 *   notice 4G max number will use 4G/8 = 512M mem, so be careful for mem capacity, if not ok try use hash // file_set.h
 *  ==============================================================================
 */

#ifndef BIT_FILE_SET_H_
#define BIT_FILE_SET_H_

#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include "ul_log_help.h"
template<typename T = int> //key can only be int size_t long long...
        class BitFileSet
{
private:
    std::vector<bool> _vec;
    T _size;
    T _len;
public:
    BitFileSet()
    {
    };
    bool init(const string& file)
    {
        std::ifstream ifs(file.c_str());
        if (!ifs.is_open())
        {
            LOG_WARNING("Can not open %s", file.c_str());
            return false;
        }

        std::istream_iterator<T> data_begin(ifs);
        std::istream_iterator<T> data_end;
        std::vector<T> vec(data_begin, data_end);
        T max_elem = *(std::max_element(vec.begin(), vec.end()));
        if (max_elem > std::numeric_limits<T>::max() || max_elem < 0)
        {
            LOG_ERROR("max elem wrong as %d", max_elem);
            return false;
        }
        _vec.resize(max_elem + 1, false);
        _len = max_elem + 1;
        _size = vec.size();
        for (size_t i = 0; i < vec.size(); i++)
        {
            if (vec[i] < 0)
            {
                LOG_ERROR("The %d num is negative!", i);
                return false;
            }
            _vec[vec[i]] = true;
        }
        return true;
    }
    size_t size()
    {
        return _size;
    }
    void clear()
    {
        _vec.clear();
    }
    bool empty()
    {
        return _vec.empty();
    }
    T & operator[](T index)
    {
        return _vec[index];
    }
    template<typename _T>
    bool has(_T elem) const
    {
        if (elem < 0 || elem >= _len)
            return false;
        return _vec[elem] == true;
    }
};
#endif  //----end of BIT_FILE_SET_H_
