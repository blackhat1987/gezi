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
    //���뷱��\���庺�ֶ��ձ�
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

    //������תΪ������
    //ע�⣺ֱ�Ӹı�ԭ���ڴ��е�ֵ ���Ⱥ�ԭ����ͬ
    inline bool Convert_t2s(char* src)
    {
        if (!src || !*src) return true;
        if (m_hashChinese.size() == 0) return false;

        char word[3] = {0};
        while (*src)
        {
            if (*src < 0) //����
            {
                if (!*(src + 1)) //ֻ�а���ַ���ȥ��
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

    //ȫ���ַ�תΪ����ַ�
    // ת����ĳ��ȿ��ܱ�ԭ��С
    // ��->��  a3b0 - a3b9
    inline bool ConvertDigitAlpha(char*src)
    {
        if (!src || !*src) return false;
        char * p = src;
        while (*src)
        {
            if (*src < 0)
            {
                if (*src == '\xa3') //ת��Ӣ�ĵ�ȫ�ǵ����163��ͷ,ע�����ĵľ�š���161��ͷ��Ӣ��ȫ�ǵľ�Ų�ͬ
                {
                    src++;
                    *p++ = *src - 128;
                    src++;
                }
                else if (*src == '\xa1' && *(src + 1) == '\xa1') //ת��ȫ�ǿո�161��ͷ,�����161
                {
                    src++;
                    *p++ = 32; //��ͨ��ǿո�
                    src++;
                }
                else
                {
                    *p++ = *src++;
                    *p++ = *src++;
                }

            }
            else
                *p++ = *src++; //Ӣ��
        }
        *p = '\0';
        return true;
    }
    bool NormalizeString(std::string& str, //����׼����
                         bool ifSimp = true, //�Ƿ���Ҫ���ַ���ת����
                         bool ifHalf = true, //�Ƿ���Ҫ��ǻ�
                         bool ifLower = true) //�Ƿ���ҪСд��
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
    std::string Normalize(const std::string& str, //����׼����
                          bool ifSimp = true, //�Ƿ���Ҫ���ַ���ת����
                          bool ifHalf = true, //�Ƿ���Ҫ��ǻ�
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
     * �����봮���м��廯����ǻ�, Сд������[β�����а������޼���],�����������false
     * �������תСд�Ļ�Ҳ����ת���,�������ȫ�ǵ�A����仯
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
                    //----------------˫�ֽ�(�����ǻ�Сд��)
                    simp_convert = false;
                    if (ifSimp)
                    {
                        memcpy(word, src, 2);
                        CHARACTER_TABLE::const_iterator it;
                        it = m_hashChinese.find(word);
                        if (it != m_hashChinese.end()) //����ת����
                        {
                            strncpy(dest, (*it).second.c_str(), 2);
                            src += 2;
                            dest += 2;
                            simp_convert = true;
                        }
                    }
                    if (!simp_convert)
                    { //----------------Ӣ�ı��ȫ��ת���
                        if (ifHalf)
                        {
                            if (*src == '\xa3') //ת��Ӣ�ĵ�ȫ�ǵ����163��ͷ,ע�����ĵľ�š���161��ͷ��Ӣ��ȫ�ǵľ�Ų�ͬ
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
                            else if (*src == '\xa1' && *(src + 1) == '\xa1') //ת��ȫ�ǿո�161��ͷ,�����161
                            {
                                src++;
                                *dest++ = ' '; //��ͨ��ǿո�
                                src++;
                            }
                            else
                            { //�ޱ䶯
                                *dest++ = *src++;
                                *dest++ = *src++;
                            }
                        }
                        else
                        { //�ޱ䶯
                            *dest++ = *src++;
                            *dest++ = *src++;
                        }
                    }
                }
                else
                { //β��Ϊ�����
                    *dest = '\0';
                    return false;
                }
            }
            else //English
            {
                //---------------���ֽ�(Сд��)
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

