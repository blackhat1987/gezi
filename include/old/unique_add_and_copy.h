/** 
 *  ==============================================================================
 * 
 *          \file   unique_add_and_copy.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-10-16 22:20:18.498862
 *  
 *  \Description:   对应下面应用
 *                  如文件或者序列中存储  <key,value> 。。。
 *                  已经按照key排序,但是可能有重复的
 *                  希望去掉重复的同时value加和。
 *
 *                   要求元素序列按照std::pair<key, value>存储
 *                   即按照first判断是否重复，second相加
 *  ==============================================================================
 */

#ifndef UNIQUE_ADD_AND_COPY_H_
#define UNIQUE_ADD_AND_COPY_H_
namespace common_algorithm
{
template<typename _InputIterator, typename _OutputIterator>
inline _OutputIterator
unique_add_copy(_InputIterator __first, _InputIterator __last,
                _OutputIterator __result)
{
    typedef typename iterator_traits<_OutputIterator>::iterator_category
    _IterType;

    if (__first == __last) return __result;
    return __unique_add_copy(__first, __last, __result, _IterType());
}
template<typename _InputIterator, typename _ForwardIterator>
_ForwardIterator
__unique_add_copy(_InputIterator __first, _InputIterator __last,
                  _ForwardIterator __result,
                  forward_iterator_tag)
{
    // concept requirements -- taken care of in dispatching function
    *__result = *__first;
    while (++__first != __last)
    {
        if (__result->first != __first->first)
            *++__result = *__first;
        else
            __result->second += __first->second;
    }
    return ++__result;
}
template<typename _InputIterator, typename _OutputIterator>
_OutputIterator
__unique_add_copy(_InputIterator __first, _InputIterator __last,
                  _OutputIterator __result,
                  output_iterator_tag)
{
    // concept requirements -- taken care of in dispatching function
    typename iterator_traits<_InputIterator>::value_type __value = *__first;
    while (++__first != __last)
    {
        if (__value->first != __first->first)
        {
            *__result = __value;
            ++__result;
            __value = *__first;
        }
        else
        {
            __value->second += __first->second;
        }
    }
    *__result = __value;
    return ++__result;
}
//template<typename _InputIterator, typename _OutputIterator,
//typename _BinaryPredicate>
//inline _OutputIterator
//unique_add_copy(_InputIterator __first, _InputIterator __last,
//                _OutputIterator __result,
//                _BinaryPredicate __binary_pred)
//{
//    typedef typename iterator_traits<_OutputIterator>::iterator_category
//    _IterType;
//
//    if (__first == __last) return __result;
//    return __unique_add_copy(__first, __last, __result,
//                             __binary_pred, _IterType());
//}

//template<typename _InputIterator, typename _OutputIterator,
//typename _BinaryPredicate>
//_OutputIterator
//__unique_add_copy(_InputIterator __first, _InputIterator __last,
//                  _OutputIterator __result,
//                  _BinaryPredicate __binary_pred,
//                  output_iterator_tag)
//{
//    typename iterator_traits<_InputIterator>::value_type __value = *__first;
//    *__result = __value;
//    while (++__first != __last)
//        if (!__binary_pred(__value, *__first))
//        {
//            __value = *__first;
//            *++__result = __value;
//        }
//    return ++__result;
//}

};
#endif  //----end of UNIQUE_ADD_AND_COPY_H_
