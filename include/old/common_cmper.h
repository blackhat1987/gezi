/** 
 *  ==============================================================================
 * 
 *          \file   common_cmper.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-21 20:16:27.631493
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef COMMON_CMPER_H_
#define COMMON_CMPER_H_

namespace std2 {
/**
 * value从大到小排序  作为默认顺序
 */
struct CmpNodeByValue
{
    template<typename _Node>
            bool operator() (const _Node& i, const _Node & j)
    {
        return (i.second > j.second);
    }
};
struct CmpNodeByValue_Reverse
{
    template<typename _Node>
            bool operator() (const _Node& i, const _Node & j)
    {
        return (i.second < j.second);
    }
};
struct CmpNodeByID
{
    template<typename _Node>
            bool operator() (const _Node& i, const _Node & j)
    {
        return (i.first < j.first);
    }
};
struct EqualNodeByID
{
    template<typename _Node>
            bool operator() (const _Node& i, const _Node & j)
    {
        return (i.first == j.first);
    }
};

} //----end of namespace std2

#endif  //----end of COMMON_CMPER_H_
