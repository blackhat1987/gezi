/**
 *  ==============================================================================
 *
 *          \file   string_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-10-27 15:40:58.907643
 *
 *  \Description:   �������ģ�� string ��gbk���봦��  ��ģ�����wstring
 *  ==============================================================================
 */

#ifndef STRING_UTIL_H_
#define STRING_UTIL_H_
#include <string>
#include <vector>
#include <iconv.h>
#include "log_util.h"
#include "chinese.h"
#include <boost/algorithm/string.hpp>

#include "wstring_util.h"
#include "encoding_convert.h"
#include "common_util.h"

#include "reg_util.h"

namespace gezi
{
using namespace std;

inline bool is_gb2312(unsigned char ch1, unsigned char ch2)
{ //already gbk chinese,judge if gb2312 chinese
  return (ch1 >= 176) && (ch1 <= 247) && (ch2 >= 161);
}

//TODO just use ccode

inline bool is_gbk_ch(unsigned char ch1, unsigned char ch2)
{
  return ( (ch2 >= 64) && (ch2 <= 254) && (ch2 != 127) &&
          ((ch1 >= 129 && ch1 <= 160) || (ch1 >= 170 && ch1 < 254) ||
          (ch1 == 254 && ch2 <= 160)));
}

inline bool is_gbk_ch(const string& phrase)
{
  if (phrase.size() != 2)
    return false;
  return is_gbk_ch((unsigned char) phrase[0], (unsigned char) phrase[1]);
}


//en means single byte

inline bool all_en(const std::string& phrase)
{
  for (size_t i = 0; i < phrase.size(); i++)
  {
    //˫�ֽڽض� ����single
    if (((unsigned char) phrase[i]) >= 0x80)
    {
      return false;
    }
  }

  return true;
}

//�����en��single btye cn �޶�gbk ch

inline bool is_en_dominate(const std::string& phrase, int var = 3)
{
  int cn_count = 0;
  int en_count = 0;
  for (size_t i = 0; i < phrase.size();)
  {
    if (((unsigned char) phrase[i]) >= 0x80 && i + 1 < phrase.size())
    {
      if (is_gbk_ch((unsigned char) phrase[i], (unsigned char) phrase[i + 1]))
      {
        cn_count++;
      }
      else
      {
        en_count++;
      }
      i += 2;
    }
    else
    {
      en_count++;
      i++;
    }
  }

  return en_count > cn_count * var;
}

//��ȡ����

inline string extract_chinese(const string& temp)
{
  vector<char> out(temp.size() + 1, 0);
  int index = 0;
  for (size_t i = 0; i < temp.size(); i++)
  {
    unsigned high = (unsigned) (0xff & temp[i]);
    if (high >= 0x81)
    {
      if ((high > 0xa9 || high <= 0xa0) && i < temp.size() - 1)
      {
        out[index] = temp[i];
        out[index + 1] = temp[i + 1];
        index += 2;
      }
      i++;
    }

  }
  string ret(&out[0]);
  return ret;
}
//��ȡ����

inline string extract_suspect_symb(const string& temp)
{
  //char out[temp.size() + 1];
  vector<char> out(temp.size() + 1, 0);
  int index = 0;
  unsigned lastcode = 0;
  for (size_t i = 0; i < temp.size(); i++)
  {
    unsigned code = (unsigned) (((0xff & temp[i]) << 8)+(0xff & temp[i + 1]));
    if (code >= 0x8100)
    {
      if (code > 0xa100 && code < 0xaa00 &&
              code != 0xa3bf && code != 0xa1a0 &&
              code != 0xa3ac && code != 0xa3a0 &&
              code != 0xa1a3 && code != 0xa3a1 &&
              code != 0xa1a4 && code != 0xa1a2 &&
              code != 0xa3a8 && code != 0xa3a9 &&
              code != 0xa1a2 && code != 0xa1a1 &&
              code != 0xa3ba && code != 0xa3bb &&
              code != 0xa1b0 && code != 0xa1b1 &&
              code != 0xa1ad)
      {
        if (code != lastcode)
        {
          out[index] = temp[ i];
          out[index + 1] = temp[i + 1];
          index += 2;
        }
        lastcode = code;
        char logtmp[3];
        logtmp[0] = temp[i];
        logtmp[1] = temp[i + 1];
        logtmp[2] = 0;
        ul_writelog(UL_LOG_DEBUG, "extract suspect [%s] [%x]", logtmp, code);
      }
      i++;
    }

  }
  string ret(&out[0]);
  return ret;

}

/**
 *brief ���˵������� ���ɼ��ַ�
 */
inline string filter_str(const string& temp)
{
  //char out[temp.size() + 1];
  vector<char> out(temp.size() + 1, 0);
  int index = 0;
  for (size_t i = 0; i < temp.size(); i++)
  {
    if (temp[i] < 0 && i + 1 < temp.size())
    {
      if (is_gbk_ch((unsigned char) temp[i], (unsigned char) temp[i + 1]))
      {
        out[index] = temp[i];
        out[index + 1] = temp[i + 1];
        index += 2;
      }
      i++;
    }
    else if (temp[i] >= '0' && temp[i] <= '9' || temp[i] >= 'A' && temp[i] <= 'Z'
            || temp[i] >= 'a' && temp[i] <= 'z')
    {
      out[index++] = temp[i];
    }
  }
  string ret(&out[0]);
  return ret;
}

inline string extract_chinese(string& temp)
{
  vector<char> out(temp.size() + 1, 0);
  int index = 0;
  for (size_t i = 0; i < temp.size(); i++)
  {
    if (temp[i] < 0 && i + 1 < temp.size())
    {
      if (is_gbk_ch((unsigned char) temp[i], (unsigned char) temp[i + 1]))
      {
        out[index] = temp[i];
        out[index + 1] = temp[i + 1];
        index += 2;
      }
      i++;
    }
  }
  string ret(&out[0]);
  return ret;
}

inline string remove_space_cn(const string& phrase)
{
  if (phrase.empty())
  {
    return phrase;
  }
  char *buf = new char[phrase.size() + 1];
  int j = 0;
  bool pre_ch = false;
  for (size_t i = 0; i < phrase.size();)
  {
    if (((unsigned char) phrase[i]) >= 0x80 && i + 1 < phrase.size())
    {
      buf[j++] = phrase[i];
      buf[j++] = phrase[i + 1];
      pre_ch = true;
      i += 2;
    }
    else
    {
      if (phrase[i] != ' ' ||
              (!pre_ch && i + 1 < phrase.size() &&
              (((unsigned char) phrase[i + 1]) < 0x80)))
      {
        buf[j++] = phrase[i];
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

inline string remove_space_cnonly(const string & phrase)
{
  char *buf = new char[phrase.size() + 1];
  int j = 0;
  bool pre_ch = false;
  for (size_t i = 0; i < phrase.size();)
  {
    if (((unsigned char) phrase[i]) >= 0x80)
    {
      buf[j++] = phrase[i];
      buf[j++] = phrase[i + 1];
      pre_ch = true;
      i += 2;
    }
    else
    {
      if ((phrase[i] == ' ') && (pre_ch == true)
              && (i + 2 < phrase.size())
              && (((unsigned char) phrase[i + 1]) >= 0x80)
              )
      {
        buf[j++] = phrase[i + 1];
        buf[j++] = phrase[i + 2];
        pre_ch = true;
        i = i + 3;
      }
      else
      {
        buf[j++] = phrase[i++];
        pre_ch = false;
      }
    }
  }
  buf[j] = '\0';
  string rs = buf;
  delete [] buf;
  return rs;
}

inline int wchar_count(const char* buf, int len)
{
  int count = 0;
  for (int i = 0; i < len; i++)
  {
    if (buf[i] < 0)
    {
      i++;
    }
    count++;
  }
  return count;
}

inline int word_count(const string& phrase)
{
  int num = 0;
  bool not_ch = false;
  for (size_t i = 0; i < phrase.size();)
  {
    if (((unsigned char) phrase[i]) >= 0x80 && i + 1 < phrase.size())
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

inline string remove_dupspace(const string& input)
{
  if (input.size() == 0)
  {
    return input;
  }

  char* buf = new char[input.size() + 1];
  bool before_is_space = true;
  int j = 0;
  for (int i = 0; i < (int) input.size(); i++)
  {
    if (input[i] == ' ')
    {
      if (!before_is_space)
      { //the first space
        buf[j++] = input[i];
      }
      before_is_space = true;
    }
    else
    {
      buf[j++] = input[i];
      before_is_space = false;
    }
  }
  if (j > 1 && (buf[j - 1] == ' '))
  { //remove the last single space if exists
    j--;
  }
  buf[j] = '\0';

  string rs = buf;
  delete [] buf;
  return rs;
}


//������հ��滻Ϊ�ո�

inline string replace_special_whitespace(const string& s, const char rep = ' ')
{
  vector<char> buf(s.size() + 1, '\0');
  int j = 0;
  for (int i = 0; i < s.size(); i++)
  {
    if (s[i] < 0 && i < s.size() - 1)
    {
      if ((int) s[i] == -95 && (int) s[i + 1] == -95)
      {
        buf[j++] = ' ';
      }
      else
      {
        buf[j++] = s[i];
        buf[j++] = s[i + 1];
      }
      i++;
    }
    else
    {
      buf[j++] = s[i];
    }
  }
  buf[j] = '\0';
  string r(&buf[0]);
  return r;
}

/**
 * @brief: �����ַ���������Ϊ��󳤶�Ϊunit���Ӵ�,����ǰ�󲹳�max_len
 */
template<typename String>
inline vector<String> cut_wstring(const String & s, int unit, int max_len = 0)
{
  vector<String> ret;
  for (int i = 0; i <= (int) s.size() / unit; i++)
  {
    ret.push_back(s.substr(max(0, i * unit - max_len), unit + max_len));
  }
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  return std::move(ret);
#else
  return ret;
#endif
}

/**
 * @brief: �滻�ַ�������
 * @param str: ԭʼ�ַ���
 * @param old_value: ���滻���Ӵ�
 * @param new_value: �µ��Ӵ�
 * @retval: �滻����ַ���
 *
 */
inline string str_replace_all(const string& tstr, const string& old_value, const string& new_value)
{
  string str = tstr;
  while (true)
  {
    string::size_type pos(0);
    if ((pos = str.find(old_value)) != string::npos)
      str.replace(pos, old_value.length(), new_value);
    else break;
  }
  return str;
}

//inline void gbk_mark(const string& src, vector<bool>& vec)
//{
//  vec.resize(src.length(), true);
//  for (int i = 0; i < (int) src.size(); i++)
//  {
//    if (i + 1 < (int) src.size())
//    {
//      vec[++i] = false;
//    }
//    else
//    {
//      vec[i] = false;
//    }
//  }
//}
//
//inline vector<bool> gbk_mark(const string& src)
//{
//  vector<bool> vec(src.length(), false);
//  for (int i = 0; i < (int) src.size(); i++)
//  {
//    if (s[i] < 0)
//    {
//      if (i + 1 < (int) src.size())
//      {
//        vec[++i] = false;
//      }
//      else
//      {
//        vec[i] = false;
//      }
//    }
//  }
//#ifdef __GXX_EXPERIMENTAL_CXX0X__
//  return std::move(vec);
//#else
//  return vec;
//#endif
//}

// like a king

inline bool is_alpha_only(const string& input)
{
  for (int i = 0; i < (int) input.size(); i++)
  {
    if (input[i] < 0)
    {
      return false;
    }
    if (!(input[i] == ' ' || isalpha(input[i])))
    {
      return false;
    }
  }
  return true;
}

inline string gbk_substr(const string& input, int start_, size_t len = string::npos)
{
  if (start_ >= (int) input.length())
  {
    return "";
  }
  if (start_ < 0)
  {
    start_ = 0;
  }
  int start = 0;
  while (start < start_)
  {
    if (input[start] < 0)
    {
      start++;
    }
    start++;
  }

  if (start == (int) input.length())
  {
    return "";
  }

  int end_ = len == string::npos ? input.length() : std::min(start + len, input.length());
  int end = start;
  while (end < end_)
  {
    if (input[end] < 0)
    {
      end++;
    }
    end++;
  }

  if (end > (int) input.length())
  { //half chinese we trim it
    end = input.length() - 1;
  }

  return input.substr(start, end - start);
}

inline bool startswith(string input, string part)
{
  return input.find(part) == 0;
}

inline bool endswith(string input, string part)
{
  return input.rfind(part) == input.length() - part.length();
}

inline bool contains(string input, string part)
{
  return input.find(part) != string::npos;
}

//Ĭ������������

inline vector<string> to_cnvec(string line)
{
  vector<string> vec;
  if (line.size() % 2 != 0)
  {
    return vec;
  }
  for (int i = 0; i < (int) line.size(); i += 2)
  {
    vec.push_back(line.substr(i, 2));
  }
#ifdef __GXX_EXPERIMENTAL_CXX0X__
  return std::move(vec);
#else
  return vec;
#endif
}

}

#endif  //----end of STRING_UTIL_H_