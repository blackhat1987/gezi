/** 
 *  ==============================================================================
 * 
 *          \file   seg_common.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-06 10:04:47.617791
 *  
 *  \Description: common的seg help函数
 *  ==============================================================================
 */

#ifndef SEG_COMMON_H_
#define SEG_COMMON_H_
#include "seg_type.h"
namespace segment {
inline bool segBoundCheck(short c1, short c2)
{ //检查两个字符编码是否为同一类型[字母/数字/标点]
    if (c1 <= FRST_OFFSET_CH || c2 <= FRST_OFFSET_CH) //如果是中文则可以称为边界
        return true;
    if (c1)
    {
        c1 -= FRST_OFFSET_CH - 31;
    }
    if (c2)
    {
        c2 -= FRST_OFFSET_CH - 31;
    }

    if ((isalpha(c1) && isalpha(c2)) ||
            (isdigit(c1) && isdigit(c2)))
    {
        return false;
    }
    else
    {
        return true;
    }
}
inline bool isNormalAmbiEncode(int encode)
{
    return (encode >> AMBOFFSET) != DIANYALIGUO;
}

} //----end of namespace segment

#endif  //----end of SEG_COMMON_H_
