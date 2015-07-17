/** 
 *  ==============================================================================
 * 
 *          \file   string_help.h
 *
 *        \author   chenghuige 
 *          
 *          \date   2010-03-15 15:45:57.744496
 *  
 *  \Description: 一些GBK格式 string的处理函数，特别为query_extend.h服务
 *
 *                FIXME 下面的遍历都是错误的，应该是 *cur >= 0 是英文 游标+1,
 *                *cur < 0就是双字节了 游标+2 其中再判断是否汉字有意义的，不是的话可以忽略
 *  ==============================================================================
 */

#ifndef STRING_HELP_H_
#define STRING_HELP_H_

#include <string>
#include <iostream>
//#include <boost/lexical_cast.hpp>
//#include <glog/logging.h>
//#include "debug_help.h"

using std::string;

inline bool isGB2312(unsigned char ch1, unsigned char ch2)
{ //already gbk chinese,judge if gb2312 chinese
    return (ch1 >= 176) && (ch1 <= 247) && (ch2 >= 161);
}

inline std::string reverse(const string& s)
{
    if (s.empty())
        return "";
    int len = s.size();
    string r;
    r.resize(len);

    for (int i = 0; i < len; i++)
    {
        r[i] = s[i];
    }

    int j = len;
    for (int i = 0; i < len;)
    {
        if (((unsigned char) s[i]) >= 0x81 && ((unsigned char) s[i]) <= 0xFE && i + 1 < len)
        {
            j -= 2;
            r[j] = s[i];
            r[j + 1] = s[i + 1];
            i += 2;
        }
        else
        {
            j--;
            r[j] = s[i];
            i++;
        }
    }

    return r;
}

//{

/**
 *  对于输入词去掉汉字之间，汉字与英文或者数字之间的空格
 *  英文或者数字之间的空格如果有多个保留1个(这个暂时不处理，假设只会有一个空格)
 *
 *   因为假设调用removeSpace会在调用 filterString之后！
 *   NOTICE!假设空格不会连续！!!!!
 *
 *   NIKE 篮球 科比 ZOOM 4 -> NIKE篮球科比ZOOM 4
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
        //中文情况直接拷贝
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            buf[j++] = phrase[i];
            buf[j++] = phrase[i + 1];
            pre_ch = true;
            i += 2;
        }
        else
        {
            //不是空格直接拷贝  如果是空格，而且前面不是中文，且后面不是中文直接拷贝空格
            if (phrase[i] != ' ' ||
                (!pre_ch && i + 1 < phrase.size() &&
                (((unsigned char) phrase[i + 1]) < 0x81 || ((unsigned char) phrase[i]) > 0xFE)))
            {
                buf[j++] = phrase[i]; //前后都不是中文，需要留下空格的,否则直接略过
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
// *  对于输入词去掉汉字之间，汉字与英文或者数字之间的空格
// *  英文或者数字之间的空格如果有多个保留1个(这个暂时不处理，假设只会有一个空格)
// *
// *   因为假设调用removeSpace会在调用 filterString之后！
// *   NOTICE!假设空格不会连续！!!!!
// *
// *   NIKE 篮球 科比 ZOOM 4 -> NIKE篮球科比ZOOM 4
// */
//inline string removeSpaceCH2(const string& phrase)
//{
//    char *buf = new char[phrase.size() + 1];
//    int j = 0;
//    bool pre_ch = false;
//    for (size_t i = 0; i < phrase.size();)
//    {
//        //中文情况直接拷贝
//        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
//        {
//            buf[j++] = phrase[i];
//            buf[j++] = phrase[i + 1];
//            pre_ch = true;
//            i += 2;
//        }
//        else
//        {
//            //不是空格直接拷贝  如果是空格，而且前面不是中文，且后面不是中文直接拷贝空格
//            if (phrase[i] != ' ' ||
//                    (!pre_ch && i + 1 < phrase.size() &&
//                    (((unsigned char) phrase[i + 1]) < 0x81 || ((unsigned char) phrase[i]) > 0xFE)) )
//            {
//                buf[j++] = phrase[i]; //前后都不是中文，需要留下空格的,否则直接略过
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
 *  假设经过filterString处理
 *  空格不连续的情况下
 *  仅仅去掉中文之间的空格 NIKE 篮球 科比 -> NIKE 篮球科比
 */
inline string removeSpaceCHOnly(const string & phrase)
{
    char *buf = new char[phrase.size() + 1];
    int j = 0;
    bool pre_ch = false;
    for (size_t i = 0; i < phrase.size();)
    {
        //中文情况直接拷贝
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            buf[j++] = phrase[i];
            buf[j++] = phrase[i + 1];
            pre_ch = true;
            i += 2;
        }
        else
        {
            //如果是空格，而且前面是中文,后面还是中文
            if (
                (phrase[i] == ' ') && (pre_ch == true)
                && (i + 2 < phrase.size())
                && (((unsigned char) phrase[i + 1]) >= 0x81)
                && (((unsigned char) phrase[i + 1]) <= 0xFE)
                )
            {
                buf[j++] = phrase[i + 1]; //略过空格，直接将下一个中文拷贝
                buf[j++] = phrase[i + 2];
                pre_ch = true;
                i = i + 3;
            }
            else
            {
                buf[j++] = phrase[i++]; //直接拷贝
                pre_ch = false; //其实只有在pre_ch = true的情况下才需要赋值为false
            }
        }
    }
    buf[j] = '\0';
    string rs = buf;
    delete [] buf;
    return rs;
}

//是不是中文字符

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
 *  去掉输入词中的非数字，英文，汉字的所有其他的东西
 *  并且最后用空格隔开,
 *  adrank中搜索用户的查询词先会经过这个处理
 *  广告关键词如果没有限制的话，也要先过这个处理再建倒排索引
 *
 *   TODO 用boost或者直接C写，暂时调用python接口
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
    bool pre_space = true; //如果第一位是空格会被忽略
    for (size_t i = 0; i < phrase.size();)
    {
        //汉字或者汉字标点等占两位的
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            if (isGBKCH((unsigned char) phrase[i], (unsigned char) phrase[i + 1])) //如果是汉字直接拷贝
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
            if (std::isalnum(phrase[i])) //如果是数字或者英文字母直接拷贝，增1
            {
                buf[j++] = phrase[i];
                pre_space = false;
            }
            else if (!pre_space) //不是的话，可能是空格或者其它不需要的东西，第一次出现填空格，以后则略过
            {
                buf[j++] = ' ';
                pre_space = true;
            }
            i++;
        }
    }
    if (pre_space && j > 0) //如果最后一个是空格则是多余的，去掉它
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
 *  3344-223 这种也去掉
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
    bool pre_space = true; //如果第一位是空格会被忽略
    for (size_t i = 0; i < phrase.size();)
    {
        //汉字或者汉字标点等占两位的
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            if (isGBKCH((unsigned char) phrase[i], (unsigned char) phrase[i + 1])) //如果是汉字直接拷贝
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
                || phrase[i] == '\'' || phrase[i] == '&') //如果是数字或者英文字母直接拷贝，增1
            {
                buf[j++] = phrase[i];
                pre_space = false;
            }
            else if (!pre_space) //不是的话，可能是空格或者其它不需要的东西，第一次出现填空格，以后则略过
            {
                buf[j++] = ' ';
                pre_space = true;
            }
            i++;
        }
    }
    if (pre_space && j > 0) //如果最后一个是空格则是多余的，去掉它
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
 *  跟上面的类似但是会同时把中文中文，中文数字英文之间的空格去掉
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
        //汉字或者汉字标点等占两位的
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
        //汉字或者汉字标点等占两位的
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

inline bool isDanZi(const std::string& phrase)
{
    if (phrase.size() == 2 && isChinesePhrase(phrase))
        return true;
    return false;
}

inline bool isEnPhrase(const std::string& phrase)
{
    for (size_t i = 0; i < phrase.size();)
    {
        //汉字或者汉字标点等占两位的
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
        //汉字或者汉字标点等占两位的
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
 * @return 有效词数目
 *
 *  "31岁的kobe"  -> 4 "31" "kobe" 各算一个word
 *   空格不算字数, 最好用前filterstring2 过滤掉无效字符 
 *
 *   当前主要用来统计用户输入词的长度信息量
 */
inline int wordNum(const string& phrase)
{
    int num = 0;
    bool not_ch = false;
    for (size_t i = 0; i < phrase.size();)
    {
        //汉字或者汉字标点等占两位的
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

//将中英文之间用空格隔开

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
            if (!(phrase[i] >= '0' && phrase[i] <= '9')) //数字不分开
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
 *  是否lphrase 广义包含 rphrase
 *
 *  如 "把吃出来的病吃回去" -> "把吃出的病吃回去"
 *
 *  FIXME "adidas背包" 不包含 "adidas 包"  空格影响
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
 *  精确包含，TODO 更好的字符串匹配算法? KMP others？ 有现成的实现boost ? 正则速度怎么样?
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

inline bool starts_with(const string& lphrase, const string& rphrase)
{
    int rlen = rphrase.size();
    int llen = lphrase.size();
    if (rlen > llen)
        return false;
    if (lphrase.substr(0, rlen) == rphrase)
        return true;
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

inline bool is_in(const char stop[], int num, char a)
{
    for (int i = 0; i < num; i++)
    {
        if (a == stop[i])
            return true;
    }
    return false;
}

inline bool is_in(const char* stop[], int num, char a, char b)
{
    for (int i = 0; i < num; i++)
    {
        if (stop[i][0] == a && stop[i][1] == b)
            return true;
    }
    return false;
}

/**
 * 注意这个split是需求相关的，这里3.45 2,ab 都不会分开的要求后面有空格
 */
inline void split(const std::string& phrase, const char stop1[], int num1, const char* stop2[], int num2, std::vector<std::string>& result)
{
    char buf[phrase.size() * 2 + 1];
    buf[0] = '\0';
    int start = 0;
    for (size_t i = 0; i < phrase.size();)
    {
        //汉字或者汉字标点等占两位的
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            if (is_in(stop2, num2, phrase[i], phrase[i + 1]))
            {
                if (start)
                {
                    buf[start] = '\0';
                    result.push_back(std::string(buf));
                    start = -2;
                }
            }
            else
            {
                buf[start] = phrase[i];
                buf[start + 1] = phrase[i + 1];
            }
            start += 2;
            i += 2;
        }
        else
        {
            if (is_in(stop1, num1, phrase[i]) && (i + 1 == phrase.size() || phrase[i + 1] == ' '))
            {
                if (start)
                {
                    buf[start] = '\0';
                    result.push_back(std::string(buf));
                    start = -1;
                }
            }
            else
            {
                buf[start] = phrase[i];
            }
            start += 1;
            i += 1;
        }
    }
    if (start)
    {
        buf[start] = '\0';
        result.push_back(std::string(buf));
        start = -1;
    }
}

inline void split(const std::string& phrase, const char stop1[], int num1, std::vector<std::string>& result)
{
    char buf[phrase.size() * 2 + 1];
    buf[0] = '\0';
    int start = 0;
    for (size_t i = 0; i < phrase.size();)
    {
        //汉字或者汉字标点等占两位的
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            {
                buf[start] = phrase[i];
                buf[start + 1] = phrase[i + 1];
            }
            start += 2;
            i += 2;
        }
        else
        {
            if (is_in(stop1, num1, phrase[i]) && (i + 1 == phrase.size() || phrase[i + 1] == ' '))
            {
                if (start)
                {
                    buf[start] = '\0';
                    result.push_back(std::string(buf));
                    start = -1;
                }
            }
            else
            {
                buf[start] = phrase[i];
            }
            start += 1;
            i += 1;
        }
    }
    if (start)
    {
        buf[start] = '\0';
        result.push_back(std::string(buf));
        start = -1;
    }
}

inline std::string split_first(const std::string& phrase, const char stop1[], int num1)
{
    char buf[phrase.size() * 2 + 1];
    buf[0] = '\0';
    int start = 0;
    for (size_t i = 0; i < phrase.size();)
    {
        //汉字或者汉字标点等占两位的
        if (((unsigned char) phrase[i]) >= 0x81 && ((unsigned char) phrase[i]) <= 0xFE && i + 1 < phrase.size())
        {
            {
                buf[start] = phrase[i];
                buf[start + 1] = phrase[i + 1];
            }
            start += 2;
            i += 2;
        }
        else
        {
            //            if (is_in(stop1, num1, phrase[i]) && (i + 1 == phrase.size() || phrase[i + 1] == ' '))
            if (is_in(stop1, num1, phrase[i]))
            {
                if (start)
                {
                    buf[start] = '\0';
                    return std::string(buf);
                    start = -1;
                }
            }
            else
            {
                buf[start] = phrase[i];
            }
            start += 1;
            i += 1;
        }
    }
    if (start)
    {
        buf[start] = '\0';
        return std::string(buf);
        start = -1;
    }
}
////判断一个切词单元是否为标点
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
