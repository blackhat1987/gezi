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
#include <boost/range/algorithm/remove_if.hpp>

#include "wstring_util.h"
#include "encoding_convert.h"
#include "common_def.h"
#include "reg_util.h"
#include "stl_util.h"

namespace gezi {
	using namespace std;

	//already gbk chinese,judge if gb2312 chinese
	inline bool is_gb2312(unsigned char ch1, unsigned char ch2)
	{
		return (ch1 >= 176) && (ch1 <= 247) && (ch2 >= 161);
	}

	//TODO just use ccode
	inline bool is_gbk_ch(unsigned char ch1, unsigned char ch2)
	{
		return ((ch2 >= 64) && (ch2 <= 254) && (ch2 != 127) &&
			((ch1 >= 129 && ch1 <= 160) || (ch1 >= 170 && ch1 < 254) ||
			(ch1 == 254 && ch2 <= 160)));
	}

	inline bool is_gbk_ch(string phrase)
	{
		if (phrase.size() != 2)
			return false;
		return is_gbk_ch((unsigned char)phrase[0], (unsigned char)phrase[1]);
	}


	//en means single byte
	inline bool all_en(string phrase)
	{
		for (size_t i = 0; i < phrase.size(); i++)
		{
			//˫�ֽڽض� ����single
			if (((unsigned char)phrase[i]) >= 0x80)
			{
				return false;
			}
		}

		return true;
	}

	//�����en��single btye cn �޶�gbk ch
	inline bool is_en_dominate(string phrase, int var = 3)
	{
		int cn_count = 0;
		int en_count = 0;
		for (size_t i = 0; i < phrase.size();)
		{
			if (((unsigned char)phrase[i]) >= 0x80 && i + 1 < phrase.size())
			{
				if (is_gbk_ch((unsigned char)phrase[i], (unsigned char)phrase[i + 1]))
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

	//��ȡ high>0x81 ����
	inline string extract_gbk_dual(string temp)
	{
		vector<char> out(temp.size() + 1, 0);
		int index = 0;
		for (size_t i = 0; i < temp.size(); i++)
		{
			unsigned high = (unsigned)(0xff & temp[i]);
			if (high >= 0x81)
			{
				out[index] = temp[i];
				out[index + 1] = temp[i + 1];
				index += 2;
				i++;
			}

		}
		string ret(&out[0]);
		return ret;
	}
	//��ȡ����
	inline string extract_suspect_symb(string temp)
	{
		//char out[temp.size() + 1];
		vector<char> out(temp.size() + 1, 0);
		int index = 0;
		unsigned lastcode = 0;
		for (size_t i = 0; i < temp.size(); i++)
		{
			unsigned code = (unsigned)(((0xff & temp[i]) << 8) + (0xff & temp[i + 1]));
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
						out[index] = temp[i];
						out[index + 1] = temp[i + 1];
						index += 2;
					}
					lastcode = code;
					char logtmp[3];
					logtmp[0] = temp[i];
					logtmp[1] = temp[i + 1];
					logtmp[2] = 0;
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
	inline string filter_str(string temp)
	{
		vector<char> out(temp.size() + 1, 0);
		int index = 0;
		for (size_t i = 0; i < temp.size(); i++)
		{
			if (temp[i] < 0 && i + 1 < temp.size())
			{
				if (is_gbk_ch((unsigned char)temp[i], (unsigned char)temp[i + 1]))
				{
					out[index] = temp[i];
					out[index + 1] = temp[i + 1];
					index += 2;
				}
				i++;
			}
			else if ((temp[i] >= '0' && temp[i] <= '9') || (temp[i] >= 'A' && temp[i] <= 'Z')
				|| (temp[i] >= 'a' && temp[i] <= 'z'))
			{
				out[index++] = temp[i];
			}
		}
		string ret(&out[0]);
		return ret;
	}

	//������������ת�� ȫ�ǰ��
	inline string normalize_str(string input)
	{
		return boost::to_lower_copy(filter_str(input));
	}

	inline string extract_chinese(string temp)
	{
		vector<char> out(temp.size() + 1, 0);
		int index = 0;
		for (size_t i = 0; i < temp.size(); i++)
		{
			if (temp[i] < 0 && i + 1 < temp.size())
			{
				if (is_gbk_ch((unsigned char)temp[i], (unsigned char)temp[i + 1]))
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

	inline string remove_space_cn(string phrase)
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
			if (((unsigned char)phrase[i]) >= 0x80 && i + 1 < phrase.size())
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
					(((unsigned char)phrase[i + 1]) < 0x80)))
				{
					buf[j++] = phrase[i];
				}
				pre_ch = false;
				i++;
			}
		}
		buf[j] = '\0';
		string rs = buf;
		delete[] buf;
		return rs;
	}

	inline string remove_space_cnonly(string phrase)
	{
		char *buf = new char[phrase.size() + 1];
		int j = 0;
		bool pre_ch = false;
		for (size_t i = 0; i < phrase.size();)
		{
			if (((unsigned char)phrase[i]) >= 0x80)
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
					&& (((unsigned char)phrase[i + 1]) >= 0x80)
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
		delete[] buf;
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

	inline int word_count(string phrase)
	{
		int num = 0;
		bool not_ch = false;
		for (size_t i = 0; i < phrase.size();)
		{
			if (((unsigned char)phrase[i]) >= 0x80 && i + 1 < phrase.size())
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

	inline string remove_dupspace(string input)
	{
		if (input.size() == 0)
		{
			return input;
		}

		char* buf = new char[input.size() + 1];
		bool before_is_space = true;
		int j = 0;
		for (int i = 0; i < (int)input.size(); i++)
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
		delete[] buf;
		return rs;
	}


	//������հ��滻Ϊ�ո�
	inline string replace_special_whitespace(string s, const char rep = ' ')
	{
		vector<char> buf(s.size() + 1, '\0');
		int j = 0;
		for (int i = 0; i < (int)s.size(); i++)
		{
			if (s[i] < 0 && i < (int)s.size() - 1)
			{
				if ((int)s[i] == -95 && (int)s[i + 1] == -95)
				{
					buf[j++] = rep;
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
		for (int i = 0; i <= (int)s.size() / unit; i++)
		{
			ret.push_back(s.substr(max(0, i * unit - max_len), unit + max_len));
		}
		return ret;
	}

	/**
	 * @brief: �滻�ַ�������
	 * @param str: ԭʼ�ַ���
	 * @param old_value: ���滻���Ӵ�
	 * @param new_value: �µ��Ӵ�
	 * @retval: �滻����ַ���
	 *
	 */
	inline string str_replace_all(string tstr, string old_value, string new_value)
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

	inline string replace(string input, char a, char b)
	{
		std::replace(input.begin(), input.end(), a, b);
		return input;
	}

	//inline void gbk_mark(string src, vector<bool>& vec)
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
	//inline vector<bool> gbk_mark(string src)
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
	//  return vec;
	//}

	// like a king

	inline bool is_alpha_only(string input)
	{
		for (int i = 0; i < (int)input.size(); i++)
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

	inline string gbk_substr(string input, int start_, size_t len = string::npos)
	{
		if (start_ >= (int)input.length())
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

		if (start == (int)input.length())
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

		if (end > (int)input.length())
		{ //half chinese we trim it
			end = input.length() - 1;
		}

		return input.substr(start, end - start);
	}

	inline bool startswith(string input, string part)
	{
		return input.find(part) == 0;
	}

	inline bool startswith(string input, char part)
	{
		return input.find(part) == 0;
	}

	inline bool endswith(string input, string part)
	{
		return input.rfind(part) == input.length() - part.length();
	}

	inline bool contains(string input, char part)
	{
		return input.find(part) != string::npos;
	}

	inline bool contains(string input, string part)
	{
		return input.find(part) != string::npos;
	}

	inline string max(string input, int length)
	{
		return input.length() <= length ? input : input.substr(0, length);
	}

	inline string first(string input, int length)
	{
		return input.length() <= length ? input : input.substr(0, length);
	}

	inline string last(string input, int length)
	{
		return input.length() <= length ? input : input.substr(input.length() - length, length);
	}

	//ȥ��һЩ�ض���char �����ӵı���ȥ�����string ʹ��reg_remove
	inline string erase(string content, string chars)
	{
		content.erase(boost::remove_if(content, boost::is_any_of(chars)), content.end());
		return content;
	}

	//find part and erase from that pos
	inline string erase_from(string content, string part)
	{
		return content.substr(0, content.find(part));
	}

	//Ĭ������������
	inline vector<string> to_cnvec(string line)
	{
		vector<string> vec;
		if (line.size() % 2 != 0)
		{
			return vec;
		}
		for (int i = 0; i < (int)line.size(); i += 2)
		{
			vec.push_back(line.substr(i, 2));
		}
		return vec;
	}

	inline string conf_trim(string input)
	{
		//string input = boost::to_lower_copy(input_);
		if (input.size() > 1)
		{
			if (input[input.size() - 1] == '_')
			{
				return input.substr(0, input.size() - 1);
			}
			else if (input[0] == '_')
			{
				return input.substr(1);
			}
		}
		return input;
	}


	//@TODO move to some where else
	inline void normalize_feature_str(string& feature_str)
	{
		boost::trim(feature_str);
		feature_str = gezi::remove_dupspace(feature_str);
	}

	//@TODO move to somewhere else
	inline vector<string> get_words(vector<string>& l, int ngram = 3, string sep = "$#$")
	{
		int len = l.size();
		vector<string> result;
		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < ngram; j++)
			{
				if (i + j >= len)
					continue;
				result.push_back(join(l.begin() + i, l.begin() + i + j + 1, sep));
			}
		}
		return result;
	}

	inline void get_skipn_bigram(const svec& l, svec& li, int n, string sep = "$#$")
	{
		svec l2(2);
		int len = l.size();
		for (int i = 0; i < len - 1 - n; i++)
		{
			l2[0] = l[i];
			l2[1] = l[i + 1 + n];
			li.push_back(l2[0] + sep + l2[1]);
		}
	}

	inline void get_skip_bigram(const svec& l, svec& li, int n, string sep = "$#$")
	{
		for (int skip = 1; skip < n; skip++)
		{
			get_skipn_bigram(l, li, skip, sep);
		}
	}

	inline bool json_empty(string value)
	{
		return value.empty() || value == "null";
	}

	//@TODO ����gbk string��iterator? ���ֵ��ֽ� ˫�ֽ�
	template<typename Func>
	void gbk_foreach(string input, Func func)
	{

	}

	template<typename Func>
	void gbk_foreach_dual(string input, Func func)
	{
		for (size_t i = 0; i < input.size();)
		{
			if (((unsigned char)input[i]) >= 0x80 && i + 1 < input.size())
			{
				func(string(input.begin() + i, input.begin() + i + 2));
				i += 2;
			}
			else
			{
				i++;
			}
		}
	}

	template<typename Func>
	void gbk_dual_foreach(string input, Func func)
	{
		for (size_t i = 0; i < input.size(); i += 2)
		{
			func(string(input.begin() + i, input.begin() + i + 2));
		}
	}

	template<typename Func>
	void gbk_foreach_single(string input, Func func)
	{

	}
}

#endif  //----end of STRING_UTIL_H_
