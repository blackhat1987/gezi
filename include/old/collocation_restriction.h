/** 
 *  ==============================================================================
 * 
 *          \file   collocation_restriction.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-20 21:27:51.475051
 *  
 *  \Description:  ͳ��ģ���еĻ��ڴ��Ե�����
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
//���j,i��Ҳ��Ϊ���� j��� ������"  i ���� ���ڶ�����" b����� Ӱ�ӣ�ҽ��
inline bool is_noun(const token_t& token)
{
    const char* t = get_pos_str(token.type);
    if (is_posttag(t, 'n') || is_posttag(t, 'i') || is_posttag(t, 'j') || is_posttag(t, 'b') || is_posttag(t, 'l')
            || (strcmp(t, "vn") == 0))
        return true;
    return false;
}
////TODO ���Ǵ������Լ��
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
//    if (get_pos_str(token.type) == "w" || strlen(token.buffer) <= 3) //��㲻ͳ��  TODO ֱ����enum ?
//        return false;
//    return true;
//}
} //----end of namespace semantic

#endif  //----end of COLLOCATION_RESTRICTION_H_
