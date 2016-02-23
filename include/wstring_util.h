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
#include "string_def.h"
#include "vector_def.h"
#include "encoding_def.h"
#include <boost/locale.hpp>
namespace gezi
{

	//-----------------------------------wstring convert
#ifdef GEZI_UTF8_AS_DEFAULT_ENCODING
	inline void setlocale()
	{
		std::locale::global(std::locale("zh_CN.UTF-8"));
	}
#else
	inline void setlocale()
	{
		std::locale::global(std::locale("zh_CN.GB18030"));
	}
#endif //GEZI_UTF8_AS_DEFAULT_ENCODING
	inline void setlocale_gbk()
	{
		std::locale::global(std::locale("zh_CN.GB18030"));
	}
	inline void setlocale_utf8()
	{
		std::locale::global(std::locale("zh_CN.UTF-8"));
	}
	/*!
	* \brief 字符串转化成宽string
	*				注意转化前需要配置locale 如   setlocale(LC_ALL, "zh_CN.UTF-8"); 当前gcc高版本动态链接 转换不成功,及时默认的高版本gcc也不行。。V2环境ok
	*				或者使用 	std::locale::global(std::locale("zh_CN.GB18030")); //这个也是需要v2环境 否则core
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

	/*!
	* \brief 将宽字符串转化为string
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
	
	inline wstring str2wstr(string src)
	{
		return str_to_wstr(src);
	}

	///suggested
	inline string wstr2str(const wstring& src)
	{
		return wstr_to_str(src);
	}

	//like python
	inline string encode(const wstring& src)
	{
		return wstr_to_str(src);
	}

	///suggested
	inline wstring wstr(string src)
	{
		return str_to_wstr(src);
	}

	//like python
	inline wstring decode(string src)
	{
		return str_to_wstr(src);
	}

#include "common_define.h"
#if defined(IS_HIGH_COMPILER)
	//------however benchmark show boost conv is much slow
	//Considering that the enumerators use the specified type unsigned short as an underlying type, as Alok Save pointed out, it is probably a good idea to pass such objects by value (unless you want to change their value in the function as a side effect, in which case you should use a reference.)
	inline string wstr2str(const wstring& src, EncodingType encodingType)
	{
		return boost::locale::conv::from_utf(src, kEncodings[static_cast<int>(encodingType)]);
	}

	inline wstring wstr(string src, EncodingType encodingType)
	{
		return  boost::locale::conv::to_utf<wchar_t>(src, kEncodings[static_cast<int>(encodingType)]);
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
#endif // __GNUC__ > 3
}
#endif  //----end of WSTRING_UTIL_H_
