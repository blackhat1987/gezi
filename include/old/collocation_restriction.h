/** 
 *  ==============================================================================
 * 
 *          \file   collocation_restriction.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-20 21:27:51.475051
 *  
 *  \Description:  统计模块中的基于词性的限制
 *  ==============================================================================
 */

#ifndef COLLOCATION_RESTRICTION_H_
#define COLLOCATION_RESTRICTION_H_
#include "scwdef.h"
#include "isegment.h"
#include "ipostag.h"
#include "property.h"
#include "segmentor.h"
namespace semantic {
inline bool is_posttag(const token_t& token, char c)
{
    const char* t = get_pos_str(token.type);
    if (t[0] == c || t[0] == c + 24)
        return true;
    return false;
}
inline bool is_posttag(const char* t, char c)
{
    if (t[0] == c || t[0] == c + 24)
        return true;
    return false;
}
//标记j,i的也视为名次 j简称 “北大"  i 成语 ”掩耳盗铃" b区别词 影视，医用
inline bool is_noun(const token_t& token)
{
    const char* t = get_pos_str(token.type);
    if (is_posttag(t, 'n') || is_posttag(t, 'i') || is_posttag(t, 'j') || is_posttag(t, 'b') || is_posttag(t, 'l')
            || (strcmp(t, "vn") == 0))
        return true;
    return false;
}
////TODO 考虑搭配词性约束
//inline bool add_ok(const token_t& token1, const token_t& token2)
//{
//    if (token1.index == token2.index)
//        return false;
//    //a+n n+v n+n
//    if (is_posttag(token1, 'a') && is_posttag(token2, 'n') ||
//            is_posttag(token1, 'n') && (is_posttag(token2, 'n') || is_posttag(token2, 'v')))
//        return true;
//    return false;
//}
//inline bool add_ok(const token_t& token)
//{
//    if (get_pos_str(token.type) == "w" || strlen(token.buffer) <= 3) //标点不统计  TODO 直接用enum ?
//        return false;
//    return true;
//}
} //----end of namespace semantic

#endif  //----end of COLLOCATION_RESTRICTION_H_
