/**
 *  ==============================================================================
 *
 *          \file   wstring_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-02 11:10:20.282912
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef WSTRING_UTIL_H_
#define WSTRING_UTIL_H_
#include <string>
namespace gezi
{
	using namespace std;
	//-----------------------------------wstring convert
	/**
	 * @brief 字符串转化成宽string
	 *注意转化前需要配置locale 如   setlocale(LC_ALL, "zh_CN.UTF-8"); 当前gcc高版本动态链接 转换不成功,及时默认的高版本gcc也不行。。
	 */
	inline wstring str_to_wstr(const char* pc, int len)
	{
		if (!pc || len <= 0)
		{
			return L"";
		}
		vector<wchar_t>  pw(len + 1, L'\0'); //or can use size dSize=mbstowcs(dBuf, sBuf, 0)+1;  
		mbstowcs(&pw[0], pc, len);
		wstring val(&pw[0]);
		return val;
	}

	inline wstring str_to_wstr(string src)
	{
		return str_to_wstr(src.c_str(), src.length());
	}

	inline wstring to_wstr(string src)
	{
		return str_to_wstr(src);
	}

	/**
	 * @brief 将宽字符串转化为string
	 *
	 */
	inline string wstr_to_str(const wchar_t *pw, int len)
	{
		if (!pw || len <= 0)
		{
			return "";
		}
		int dlen = (len + 1) * 4;
		vector<char> pc(dlen, '\0');

		wcstombs(&pc[0], pw, dlen); //if fail will return (size_t)-1  all return >= 0

		string val(&pc[0]);

		return val;
	}

	inline string wstr_to_str(const wstring& src)
	{
		return wstr_to_str(src.c_str(), src.length());
	}

	inline string to_str(const wstring& src)
	{
		return wstr_to_str(src);
	}

	inline string wstr2str(const wstring& src)
	{
		return wstr_to_str(src);
	}

	inline wstring str2wstr(string src)
	{
		return str_to_wstr(src);
	}

	inline wstring wstr(string src)
	{
		return str_to_wstr(src);
	}

	//can use boost instead
	inline wstring wstr_replace_all(const wstring& tstr, const wstring& old_value, const wstring& new_value)
	{
		wstring str = tstr;
		while (true) {
			wstring::size_type pos(0);
			if ((pos = str.find(old_value)) != wstring::npos)
				str.replace(pos, old_value.length(), new_value);
			else break;
		}
		return str;
	}

}
#endif  //----end of WSTRING_UTIL_H_
