/** 
 *  ==============================================================================
 * 
 *          \file   common_traits.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-18 16:17:00.683213
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef COMMON_TRAITS_H_
#define COMMON_TRAITS_H_
template<typename T>
struct NormTypeTraits
{ //ע����Щ�Ǽ����ʱ����Ҫ�õ����м����洢����������,�����ս���Ļ���l1norm��ValueType��ͬ
    typedef long double L2NormType;
    typedef double L1NormType;
};
template<>
struct NormTypeTraits<int>
{
    typedef long long L2NormType;
    typedef long long L1NormType;
};
template<>
struct NormTypeTraits<long long>
{
    typedef long long L2NormType;
    typedef long long L1NormType;
};
template<>
struct NormTypeTraits<size_t>
{
    typedef unsigned long long L2NormType;
    typedef unsigned long long L1NormType;
};
template<>
struct NormTypeTraits<unsigned long long>
{
    typedef unsigned long long L2NormType;
    typedef unsigned long long L1NormType;
};
template<typename T>
struct IteratorTraits
{
    typedef typename T::value_type value_type;
};
template<typename T>
struct IteratorTraits<T*>
{
    typedef T value_type;
};
#endif  //----end of COMMON_TRAITS_H_
