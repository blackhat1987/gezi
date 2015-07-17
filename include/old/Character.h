#ifndef CHARACTER_H_
#define CHARACTER_H_

//#include "common_headers.h"
#include <string>
#include <stdio.h>
#include <string.h> 
#ifdef __GNUC__
#include<tr1/unordered_map>  //chg modified using unordered map
#else
#endif
#ifdef __GNUC__
typedef std::tr1::unordered_map<std::string, std::string> CHARACTER_TABLE;
#else
typedef hash_map<std::string, std::string> CHARACTER_TABLE;
#endif

#include <iostream>
using namespace std;

namespace ch_convert
{
class CharacterConverter
{
public:
    CharacterConverter()
    {
    };
    CharacterConverter(const char* strFile)
    {
        loadChineseTable(strFile);
    }
    ~CharacterConverter()
    {
        m_hashChinese.clear();
    }
public:
    //载入繁体\简体汉字对照表
    inline bool loadChineseTable(const char * strFile)
    {
        FILE * pFile = fopen(strFile, "r");
        if (!pFile) return false;

        char chLine[1024];
        char chSimple[3];
        char chTraditional[3];
        while (fgets(chLine, 1024, pFile))
        {
            sscanf(chLine, "%s	%s	", chTraditional, chSimple);
            if (strlen(chTraditional) != 2 || strlen(chSimple) != 2)
            {
                fclose(pFile);
                return false;
            }
            m_hashChinese[chTraditional] = chSimple;
        }
        fclose(pFile);
        return true;
    }

    //繁体字转为简体字
    //注意：直接改变原有内存中的值 长度和原来相同
    inline bool Convert_t2s(char* src)
    {
        if (!src || !*src) return true;
        if (m_hashChinese.size() == 0) return false;

        char word[3] = {0};
        while (*src)
        {
            if (*src < 0) //中文
            {
                if (!*(src + 1)) //只有半个字符　去掉
                {
                    *src = '\0';
                    return false;
                }
                memcpy(word, src, 2);
                CHARACTER_TABLE::const_iterator it;
                it = m_hashChinese.find(word);
                if (it != m_hashChinese.end())
                {
                    strncpy(src, (*it).second.c_str(), 2);
                }
                src++;
            }
            src++;
        }
        return true;
    }

    //全角字符转为半角字符
    // 转换后的长度可能比原来小
    // ０->９  a3b0 - a3b9
    inline bool ConvertDigitAlpha(char*src)
    {
        if (!src || !*src) return false;
        char * p = src;
        while (*src)
        {
            if (*src < 0)
            {
                if (*src == '\xa3') //转换英文的全角到半角163开头,注意中文的句号。是161开头与英文全角的句号不同
                {
                    src++;
                    *p++ = *src - 128;
                    src++;
                }
                else if (*src == '\xa1' && *(src + 1) == '\xa1') //转换全角空格161开头,后面跟161
                {
                    src++;
                    *p++ = 32; //普通半角空格
                    src++;
                }
                else
                {
                    *p++ = *src++;
                    *p++ = *src++;
                }

            }
            else
                *p++ = *src++; //英文
        }
        *p = '\0';
        return true;
    }
    bool NormalizeString(std::string& str, //待标准化串
                         bool ifSimp = true, //是否需要汉字繁体转简体
                         bool ifHalf = true, //是否需要半角化
                         bool ifLower = true) //是否需要小写化
    {
        char *buf = new char[str.size() + 1];
        memcpy(buf, str.c_str(), str.size());
        buf[str.size()] = '\0';
        if (!NormalizeString(buf, ifSimp, ifHalf, ifLower))
        {
            delete []buf;
            return false;
        }
        else
        {
            str = buf;
            delete []buf;
        }
        return true;
    }
    std::string Normalize(const std::string& str, //待标准化串
                          bool ifSimp = true, //是否需要汉字繁体转简体
                          bool ifHalf = true, //是否需要半角化
                          bool ifLower = true)
    {
        char *buf = new char[str.size() + 1];
        memcpy(buf, str.c_str(), str.size());
        buf[str.size()] = '\0';
        std::string result;
        NormalizeString(buf, ifSimp, ifHalf, ifLower);
        result = buf;
        delete []buf;
        return result;
    }
    /**
     * 将输入串进行简体化，半角化, 小写话处理[尾部若有半字则修剪掉],如果剪掉返回false
     * 建议如果转小写的话也启用转半角,否则比如全角的A不会变化
     **/
    bool NormalizeString(char *src, bool ifSimp = true, bool ifHalf = true, bool ifLower = true)
    {
        if (NULL == src || *src == '\0')
        {
            return true;
        }
        char *dest = src;
        char word[3] = {0};
        bool simp_convert;
        while (*src != '\0')
        {
            if (*src < 0)
            {
                if (*(src + 1) != '\0') //Chinese
                {
                    //----------------双字节(简体半角化小写化)
                    simp_convert = false;
                    if (ifSimp)
                    {
                        memcpy(word, src, 2);
                        CHARACTER_TABLE::const_iterator it;
                        it = m_hashChinese.find(word);
                        if (it != m_hashChinese.end()) //繁体转简体
                        {
                            strncpy(dest, (*it).second.c_str(), 2);
                            src += 2;
                            dest += 2;
                            simp_convert = true;
                        }
                    }
                    if (!simp_convert)
                    { //----------------英文标点全角转半角
                        if (ifHalf)
                        {
                            if (*src == '\xa3') //转换英文的全角到半角163开头,注意中文的句号。是161开头与英文全角的句号不同
                            {
                                src++;
                                //if (ifLower)  //FIXME why this will not work as below?
                                //  *dest = std::tolower(*src++ - 128);
                                //else
                                //  *dest = *src++ - 128;
                                *dest++ = *src++ -128;
                                if (ifLower)
                                    *(dest - 1) = std::tolower(*(dest - 1));
                            }
                            else if (*src == '\xa1' && *(src + 1) == '\xa1') //转换全角空格161开头,后面跟161
                            {
                                src++;
                                *dest++ = ' '; //普通半角空格
                                src++;
                            }
                            else
                            { //无变动
                                *dest++ = *src++;
                                *dest++ = *src++;
                            }
                        }
                        else
                        { //无变动
                            *dest++ = *src++;
                            *dest++ = *src++;
                        }
                    }
                }
                else
                { //尾部为半个字
                    *dest = '\0';
                    return false;
                }
            }
            else //English
            {
                //---------------单字节(小写化)
                if (ifLower)
                    *dest++ = std::tolower(*src++);
                else
                    *dest++ = *src++;
            }
        }
        *dest = '\0';
        return true;
    }

private:
    CHARACTER_TABLE m_hashChinese;
};
} // end of namspace ch_convert

#endif  //end of CHARACTER_H_

