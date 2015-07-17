/** 
 *  ==============================================================================
 * 
 *          \file   string_help.h
 *
 *        \author   chenghuige 
 *          
 *          \date   2010-03-15 15:45:57.744496
 *  
 *  \Description: һЩGBK��ʽ string�Ĵ��?���ر�Ϊquery_extend.h����
 *
 *                FIXME ����ı����Ǵ���ģ�Ӧ���� *cur >= 0 ��Ӣ�� �α�+1,
 *                *cur < 0����˫�ֽ��� �α�+2 �������ж��Ƿ���������ģ����ǵĻ����Ժ���
 *  ==============================================================================
 */

#ifndef STRING_HELP_H_
#define STRING_HELP_H_

#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <glog/logging.h>
#include "debug_help.h"
using std::string;
inline bool isGB2312(unsigned char ch1, unsigned char ch2)
{ //already gbk chinese,judge if gb2312 chinese
    return (ch1 >= 176) && (ch1 <= 247) && (ch2 >= 161);
}

//{
/**
 *  ���������ȥ������֮�䣬������Ӣ�Ļ�������֮��Ŀո�
 *  Ӣ�Ļ�������֮��Ŀո�����ж������1��(�����ʱ�����?����ֻ����һ���ո�)
 *
 *   ��Ϊ�������removeSpace���ڵ��� filterString֮��
 *   NOTICE!����ո񲻻�����!!!!
 *
 *   NIKE ���� �Ʊ� ZOOM 4 -> NIKE����Ʊ�ZOOM 4
 */
inline string removeSpaceCH(const string& phrase)
{
    if (phrase.empty())
    {
        std::cout << "phrase input for removeSpaceCh is empty" << std::endl;
        throw new int(9);
        return "";
    }
    char *buf = new char[phrase.size() + 1];
    int j = 0;
    bool pre_ch = false;
    for (size_t i = 0; i < phrase.size();)
    {
        //�������ֱ�ӿ���
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            buf[j++] = phrase[i];
            buf[j++] = phrase[i + 1];
            pre_ch = true;
            i += 2;
        }
        else
        {
            //���ǿո�ֱ�ӿ���  ����ǿո񣬶���ǰ�治�����ģ��Һ��治������ֱ�ӿ����ո�
            if (phrase[i] != ' ' ||
                    (!pre_ch && i + 1 < phrase.size() &&
                    (((unsigned char) phrase[i + 1]) < 0x81 || ((unsigned char) phrase[i]) > 0xFE)))
            {
                buf[j++] = phrase[i]; //ǰ�󶼲������ģ���Ҫ���¿ո��,����ֱ���Թ�
            }
            pre_ch = false;
            i++;
        }
    }
    buf[j] = '\0';
    string rs = buf;
    delete [] buf;
    return rs;
}
///**
// *  ���������ȥ������֮�䣬������Ӣ�Ļ�������֮��Ŀո�
// *  Ӣ�Ļ�������֮��Ŀո�����ж������1��(�����ʱ�����?����ֻ����һ���ո�)
// *
// *   ��Ϊ�������removeSpace���ڵ��� filterString֮��
// *   NOTICE!����ո񲻻�����!!!!
// *
// *   NIKE ���� �Ʊ� ZOOM 4 -> NIKE����Ʊ�ZOOM 4
// */
//inline string removeSpaceCH2(const string& phrase)
//{
//    char *buf = new char[phrase.size() + 1];
//    int j = 0;
//    bool pre_ch = false;
//    for (size_t i = 0; i < phrase.size();)
//    {
//        //�������ֱ�ӿ���
//        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
//        {
//            buf[j++] = phrase[i];
//            buf[j++] = phrase[i + 1];
//            pre_ch = true;
//            i += 2;
//        }
//        else
//        {
//            //���ǿո�ֱ�ӿ���  ����ǿո񣬶���ǰ�治�����ģ��Һ��治������ֱ�ӿ����ո�
//            if (phrase[i] != ' ' ||
//                    (!pre_ch && i + 1 < phrase.size() &&
//                    (((unsigned char) phrase[i + 1]) < 0x81 || ((unsigned char) phrase[i]) > 0xFE)) )
//            {
//                buf[j++] = phrase[i]; //ǰ�󶼲������ģ���Ҫ���¿ո��,����ֱ���Թ�
//            }
//            pre_ch = false;
//            i++;
//        }
//    }
//    buf[j] = '\0';
//    string rs = buf;
//    delete [] buf;
//    return rs;
//}
/**
 *  ���辭��filterString����
 *  �ո�����������
 *  ����ȥ������֮��Ŀո� NIKE ���� �Ʊ� -> NIKE ����Ʊ�
 */
inline string removeSpaceCHOnly(const string & phrase)
{
    char *buf = new char[phrase.size() + 1];
    int j = 0;
    bool pre_ch = false;
    for (size_t i = 0; i < phrase.size();)
    {
        //�������ֱ�ӿ���
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            buf[j++] = phrase[i];
            buf[j++] = phrase[i + 1];
            pre_ch = true;
            i += 2;
        }
        else
        {
            //����ǿո񣬶���ǰ��������,���滹������
            if (
                    (phrase[i] == ' ') && (pre_ch == true)
                    && (i + 2 < phrase.size())
                    && (((unsigned char) phrase[i + 1]) >= 0x81)
                    && (((unsigned char) phrase[i + 1]) <= 0xFE)
                    )
            {
                buf[j++] = phrase[i + 1]; //�Թ�ո�ֱ�ӽ���һ�����Ŀ���
                buf[j++] = phrase[i + 2];
                pre_ch = true;
                i = i + 3;
            }
            else
            {
                buf[j++] = phrase[i++]; //ֱ�ӿ���
                pre_ch = false; //��ʵֻ����pre_ch = true������²���Ҫ��ֵΪfalse
            }
        }
    }
    buf[j] = '\0';
    string rs = buf;
    delete [] buf;
    return rs;
}

//�ǲ��������ַ�
inline bool isGBKCH(unsigned char ch1, unsigned char ch2)
{
    return ( (ch2 >= 64) && (ch2 <= 254) && (ch2 != 127) &&
            ((ch1 >= 129 && ch1 <= 160) || (ch1 >= 170 && ch1 < 254) ||
            (ch1 == 254 && ch2 <= 160)));
}
inline bool isGBKCH(const string& phrase)
{
    if (phrase.size() != 2)
        return false;
    return isGBKCH((unsigned char) phrase[0], (unsigned char) phrase[1]);
}
/**
 *  ȥ��������еķ����֣�Ӣ�ģ����ֵ���������Ķ���
 *  ��������ÿո����,
 *  adrank�������û��Ĳ�ѯ���Ȼᾭ���������
 *  ���ؼ�����û�����ƵĻ���ҲҪ�ȹ���������ٽ���������
 *
 *   TODO ��boost����ֱ��Cд����ʱ����python�ӿ�
 */
inline string filterString(const string & phrase)
{
    using namespace std;
    //return phrase;
    if (phrase.size() == 0)
    {
        cout << "The input is empty string! in filterString2" << std::endl;
        throw new int(9);
        return "";
    }
    char *buf = new char[phrase.size() + 1];
    int j = 0;
    bool pre_space = true; //����һλ�ǿո�ᱻ����
    for (size_t i = 0; i < phrase.size();)
    {
        //���ֻ��ߺ��ֱ���ռ��λ��
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            if (isGBKCH((unsigned char) phrase[i], (unsigned char) phrase[i + 1])) //����Ǻ���ֱ�ӿ���
            {
                buf[j++] = phrase[i];
                buf[j++] = phrase[i + 1];
                pre_space = false;
            }
            else if (!pre_space)
            {
                buf[j++] = ' ';
                pre_space = true;
            }
            i += 2;
        }
        else
        {
            if (std::isalnum(phrase[i])) //��������ֻ���Ӣ����ĸֱ�ӿ�������1
            {
                buf[j++] = phrase[i];
                pre_space = false;
            }
            else if (!pre_space) //���ǵĻ��������ǿո����������Ҫ�Ķ�������һ�γ�����ո��Ժ����Թ�
            {
                buf[j++] = ' ';
                pre_space = true;
            }
            i++;
        }
    }
    if (pre_space && j > 0) //������һ���ǿո����Ƕ���ģ�ȥ����
        j--;
    if (j < 0)
    {
        cout << "j < 0 in filterString2" << endl;
        //throw new int(9);
    }
    if (j >= (phrase.size() + 1))
    {
        cout << phrase << endl;
        cout << "j: " << " " << j << endl;
        cout << "total space: " << phrase.size() + 1 << endl;
        //throw new int(9);
    }
    buf[j] = '\0';
    string rs = buf;
    delete [] buf;
    return rs;
}
inline bool isNum(const string & phrase)
{
    bool is_num = true;
    for (size_t i = 0; i < phrase.size(); i++)
    {
        if (!std::isdigit(phrase[i]))
            is_num = false;
    }
    return is_num;
}
/*
 *  3344-223 ����Ҳȥ��
 */
inline bool isNum2(const string & phrase)
{
    bool is_num = true;
    for (size_t i = 0; i < phrase.size(); i++)
    {
        if (!std::isdigit(phrase[i]) && phrase[i] != '-')
            is_num = false;
    }
    return is_num;
}
inline string filterString2(const string & phrase)
{
    using namespace std;
    //return phrase;
    if (phrase.size() == 0)
    {
        LOG(WARNING) << "The input is empty string! in filterString2" << endl;
        return "";
    }

    char *buf = new char[phrase.size() + 1];
    int j = 0;
    bool pre_space = true; //����һλ�ǿո�ᱻ����
    for (size_t i = 0; i < phrase.size();)
    {
        //���ֻ��ߺ��ֱ���ռ��λ��
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            if (isGBKCH((unsigned char) phrase[i], (unsigned char) phrase[i + 1])) //����Ǻ���ֱ�ӿ���
            {
                buf[j++] = phrase[i];
                buf[j++] = phrase[i + 1];
                pre_space = false;
            }
            else if (!pre_space)
            {
                buf[j++] = ' ';
                pre_space = true;
            }
            i += 2;
        }
        else
        {
            if (std::isalnum(phrase[i]) || (phrase[i] == '+' && i > 1 && (phrase[i - 1] == '+' || phrase[i - 1] == 'c')) || phrase[i] == '#'
                    || phrase[i] == '-' || phrase[i] == '.'
                    || phrase[i] == '\'' || phrase[i] == '&') //��������ֻ���Ӣ����ĸֱ�ӿ�������1
            {
                buf[j++] = phrase[i];
                pre_space = false;
            }
            else if (!pre_space) //���ǵĻ��������ǿո����������Ҫ�Ķ�������һ�γ�����ո��Ժ����Թ�
            {
                buf[j++] = ' ';
                pre_space = true;
            }
            i++;
        }
    }
    if (pre_space && j > 0) //������һ���ǿո����Ƕ���ģ�ȥ����
        j--;
    if (j < 0)
    {
        cout << "j < 0 in filterString2" << endl;
        //throw new int(9);
    }
    if (j >= (phrase.size() + 1))
    {
        cout << phrase << endl;
        cout << "j: " << " " << j << endl;
        cout << "total space: " << phrase.size() + 1 << endl;
        //throw new int(9);
    }
    buf[j] = '\0';
    string rs = buf;
    delete [] buf;

    return rs;
}
/**
 *  ����������Ƶ��ǻ�ͬʱ���������ģ���������Ӣ��֮��Ŀո�ȥ��
 */
inline string filterString_adrank(const string & phrase)
{

}
enum string_type
{
    en_string, ch_string, mix_string, bad_string, unknown_string
};
inline string_type getStringType(const string& phrase)
{
    string_type type = bad_string;
    for (size_t i = 0; i < phrase.size();)
    {
        //���ֻ��ߺ��ֱ���ռ��λ��
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            //            if (!isGBKCH((unsigned char) phrase[i], (unsigned char) phrase[i + 1]))
            //            {
            //                return bad_string;
            //            }
            if (type == bad_string)
                type = ch_string;
            else if (type == en_string)
                return mix_string;
            i += 2;
        }
        else
        {
            if (type == bad_string)
                type = en_string;
            else if (type == ch_string)
                return mix_string;
            i++;
        }
    }
    return type;
}
inline bool isChinesePhrase(const std::string& phrase)
{
    for (size_t i = 0; i < phrase.size();)
    {
        //���ֻ��ߺ��ֱ���ռ��λ��
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            if (!isGBKCH((unsigned char) phrase[i], (unsigned char) phrase[i + 1]))
            {
                return false;
            }
            i += 2;
        }
        else
            return false;
    }

    return true;
}
inline bool isEnPhrase(const std::string& phrase)
{
    for (size_t i = 0; i < phrase.size();)
    {
        //���ֻ��ߺ��ֱ���ռ��λ��
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            return false;
        }
        else
            i++;
    }

    return true;
}
inline int chNum(const std::string& phrase)
{
    int num = 0;
    for (size_t i = 0; i < phrase.size();)
    {
        //���ֻ��ߺ��ֱ���ռ��λ��
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            num++;
            i += 2;
        }
        else
        {
            num++;
            i += 1;
        }
    }
    return num;
}
/**
 *
 * @param phrase
 * @return ��Ч����Ŀ
 *
 *  "31���kobe"  -> 4 "31" "kobe" ����һ��word
 *   �ո�������, �����ǰfilterstring2 ���˵���Ч�ַ� 
 *
 *   ��ǰ��Ҫ����ͳ���û�����ʵĳ�����Ϣ��
 */
inline int wordNum(const string& phrase)
{
    int num = 0;
    bool not_ch = false;
    for (size_t i = 0; i < phrase.size();)
    {
        //���ֻ��ߺ��ֱ���ռ��λ��
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            if (not_ch)
            {
                num++;
                not_ch = false;
            }
            num++;
            i += 2;
        }
        else
        {
            if (phrase[i] != ' ')
                not_ch = true;
            else if (not_ch)
            {
                num++;
                not_ch = false;
            }
            i += 1;
        }
    }

    if (not_ch)
        num++;

    return num;
}
inline string removeAllSpace(const std::string& phrase)
{
    char buf[phrase.size() + 1];
    int j = 0;
    for (size_t i = 0; i < phrase.size(); i++)
    {
        if (phrase[i] != ' ')
            buf[j++] = phrase[i];
    }
    buf[j] = '\0';
    return buf;
}
inline string removeAllSpace2(const std::string& phrase, std::vector<std::string>& vec)
{
    vec.clear();
    vec.push_back("");
    char buf[phrase.size() + 1];
    char buf2[phrase.size() + 1];
    int k = 0, j = 0;
    for (size_t i = 0; i < phrase.size(); i++)
    {
        if (phrase[i] != ' ')
        {
            buf[j++] = phrase[i];
            buf2[k++] = phrase[i];
        }
        else
        {
            buf2[k] = '\0';
            k = 0;
            vec.push_back(buf2);
        }
    }
    buf2[k] = '\0';
    vec.push_back(buf2);

    buf[j] = '\0';
    return buf;
}

//����Ӣ��֮���ÿո����
inline string seperateEnCh(const string& phrase, char space = ' ')
{
    char buf[phrase.size() * 2];
    int pre_ch = -1;
    int j = 0;
    for (size_t i = 0; i < phrase.size();)
    {

        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            if (isGBKCH((unsigned char) phrase[i], (unsigned char) phrase[i + 1]))
            {
                if (pre_ch != 1)
                    buf[j++] = space;

                buf[j++] = phrase[i];
                buf[j++] = phrase[i + 1];

                pre_ch = 1;
            }
            i += 2;
        }
        else
        {
            if (!(phrase[i] >= '0' && phrase[i] <= '9')) //���ֲ��ֿ�
            {
                if (pre_ch == 1)
                    buf[j++] = space;
                pre_ch = 0;
            }

            buf[j++] = phrase[i];
            i++;
        }
    }

    buf[j] = '\0';
    return buf;
}
//} //----end of namespace adrank
/**
 *  lphrase, rphrase,
 *  �Ƿ�lphrase ����� rphrase
 *
 *  �� "�ѳԳ����Ĳ��Ի�ȥ" -> "�ѳԳ��Ĳ��Ի�ȥ"
 *
 *  FIXME "adidas����" ���� "adidas ��"  �ո�Ӱ��
 */

inline bool contains(const string& lphrase, const string& rphrase)
{
    if (rphrase.size() > lphrase.size())
        return false;

    size_t j = 0;
    for (size_t i = 0; i < rphrase.size(); i++)
    {
        while (lphrase[j] != rphrase[i] && j < lphrase.size())
            j++;
        if (j == lphrase.size())
            return false;
    }
    return true;
}
/**
 *  ��ȷ��TODO ��õ��ַ�ƥ���㷨? KMP others�� ���ֳɵ�ʵ��boost ? �����ٶ���ô��?
 */
inline bool exact_contains(const string& lphrase, const string& rphrase)
{
    int rlen = rphrase.size();
    int llen = lphrase.size();
    if (rlen > llen)
        return false;

    for (size_t i = 0; i < llen - rlen; i++)
    {
        if (lphrase.substr(i, rlen) == rphrase)
            return true;
    }
    return false;
}
inline bool has_space(const string& phrase)
{
    bool has_space = false;
    for (size_t i = 0; i < phrase.size();)
    {

        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            i += 2;
        }
        else
        {
            if (std::isspace(phrase[i]))
                has_space = true;
            i++;
        }
    }
    return has_space;
}

inline bool is_in(char stop[], int num, char a)
{
    for (int i = 0; i < num; i++)
    {
        if (a == stop[i])
            return true;
    }
    return false;
}
inline bool is_in(char* stop[], int num, char a, char b)
{
    for (int i = 0; i < num; i++)
    {
        if (stop[i][0] == a && stop[i][1] == b)
            return true;
    }
    return false;
}
inline void split(const string& phrase, char stop1[], int num1, char* stop2[], int num2)
{

}

////�ж�һ���дʵ�Ԫ�Ƿ�Ϊ���
//inline bool isPunct(const string& str)
//{
//    if (str.empty() || str.size() > 2)
//    {
//        return false;
//    }
//    if (1 == str.size() && str[0] >= 0 && !isalnum(str[0]))
//    {
//        return true;
//    }
//    if (2 == str.size() && str[0] < 0 && false == isGBKCH(unsigned char(str[0]), unsigned char(str[1])))
//    {
//        return true;
//    }
//    return false;
//}


#endif  //----end of STRING_HELP_H_
