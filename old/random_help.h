/** 
 *  ==============================================================================
 * 
 *          \file   random_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-06-16 16:41:07.720172
 *  
 *  \Description: test see other/random/random_shuffle_bost.cc
 *  ==============================================================================
 */

#ifndef RANDOM_HELP_H_
#define RANDOM_HELP_H_
#include <ctime>
#include <boost/random.hpp>
template<typename _RandomAccessIterator>
inline void random_sample(_RandomAccessIterator __first, _RandomAccessIterator __last, int __sample_num)
{
    if (__first == __last)
        return;
    _RandomAccessIterator end = std::min(__first + __sample_num, __last);
    for (_RandomAccessIterator __i = __first; __i != end; ++__i)
        std::iter_swap(__i, __i + (std::rand() % (__last - __i)));
}
template<typename _RandomAccessIterator, typename _RandomNumberGenerator>
inline void random_sample(_RandomAccessIterator __first, _RandomAccessIterator __last, int __sample_num, _RandomNumberGenerator& __rand)
{
    if (__first == __last)
        return;
    _RandomAccessIterator end = std::min(__first + __sample_num, __last);
    for (_RandomAccessIterator __i = __first; __i != end; ++__i)
        std::iter_swap(__i, __i + (__rand(__last - __i)));
}
class Random
{
public:
    boost::mt19937 gen;
    boost::uniform_int<int> dst;
    boost::variate_generator< boost::mt19937, boost::uniform_int<int> > rand;
    Random(int N, int min = 0) : // call instance:
    gen(static_cast<unsigned long> (std::time(0))), dst(min, N), rand(gen, dst)
    {
    }
    std::ptrdiff_t operator()(std::ptrdiff_t arg)
    {
        return static_cast<std::ptrdiff_t> (rand(arg));
    }
};

#endif  //----end of RANDOM_HELP_H_
