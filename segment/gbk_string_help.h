/** 
 *  ==============================================================================
 * 
 *          \file   gbkstring_help.h
 *
 *        \author   gezi  
 *          
 *          \date   2010-09-25 15:55:20.892174
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef GBKSTRING_HELP_H_
#define GBKSTRING_HELP_H_
#include <string>
namespace segment
{
inline bool isGB2312(unsigned char ch1, unsigned char ch2)
{ //already gbk chinese,judge if gb2312 chinese
    return (ch1 >= 176) && (ch1 <= 247) && (ch2 >= 161);
}
inline bool isGBKCH(unsigned char ch1, unsigned char ch2)
{ //judge if gbk chinese
    return ( (ch2 >= 64) && (ch2 <= 254) && (ch2 != 127) &&
            ((ch1 >= 129 && ch1 <= 160) || (ch1 >= 170 && ch1 < 254) ||
            (ch1 == 254 && ch2 <= 160)));
}
inline std::string reverse(const std::string& phrase)
{
    int len = phrase.size();
    char out[len + 1];
    out[len] = '\0';
    int i, j;
    for (i = 0, j = len - 1; i < len;)
    {
        //汉字或者汉字标点等占两位的
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < len)
        {
            out[j - 1] = phrase[i];
            out[j] = phrase[i + 1];
            i += 2;
            j -= 2;
        }
        else
        {
            out[j] = phrase[i];
            i++;
            j--;
        }
    }
    return out;
}
inline void reverse(const std::string& phrase, std::string& out)
{
    int len = phrase.size();
    out.resize(len + 1);
    out[len] = '\0';
    int i, j;
    for (i = 0, j = len - 1; i < len;)
    {
        //汉字或者汉字标点等占两位的
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < len)
        {
            out[j - 1] = phrase[i];
            out[j] = phrase[i + 1];
            i += 2;
            j -= 2;
        }
        else
        {
            out[j] = phrase[i];
            i++;
            j--;
        }
    }
}
}

#endif  //----end of GBKSTRING_HELP_H_
