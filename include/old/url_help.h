/** 
 *  ==============================================================================
 * 
 *          \file   url_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-01-26 08:00:02.668359
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef URL_HELP_H_
#define URL_HELP_H_
#include <ctype.h>
#include <string.h>
#include <string>
#include "debug_help.h"
//Ϊ����URL������ʱ���ĵ�ת��
inline int h2i(unsigned char *s)
{
    char *digits = "0123456789ABCDEF";
    if (islower(s[0])) s[0] = toupper(s[0]); /* �ж��Ƿ���Сд��ĸ������ת���ɴ�д */
    if (islower(s[1])) s[1] = toupper(s[1]);
    return 16 * (strchr(digits, s[0]) - strchr(digits, '0'))
            + (strchr(digits, s[1]) - strchr(digits, '0')); /* ������Ӧʮ������ */
}

inline void url2char(const char *surl, char *res)
{
    int i, j, nlen;
    unsigned char tmp[3];

    nlen = (int) strlen(surl);

    j = 0;
    for (i = 0; i < nlen;)
    {
        if (surl[i] == '%' && i + 2 < nlen)//��%��ͷ���Ǻ��ֻ������������ַ�
        {
            tmp[0] = surl[i + 1];
            tmp[1] = surl[i + 2];
            tmp[2] = 0;
            i += 3;
            res[j] = h2i(tmp);
        }
        else // Ӣ���ַ���ֱ�ӿ���
        {
            res[j] = surl[i];
            i++;
        }
        j++;
    }
    res[j] ='\0';
}

inline std::string url2str(const std::string& input)
{
    char res[input.size()];
    url2char(input.c_str(), res);
    return std::string(res);
}
#endif  //----end of URL_HELP_H_
