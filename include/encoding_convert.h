/*
 * File:   encoding_convert.h
 * Author: chenghuige
 *
 * Created on 2013年11月3日, 上午9:57
 */

#ifndef ENCODING_CONVERT_H_
#define	ENCODING_CONVERT_H_

#include <string>
#include <vector>
//#include "log_util.h"
#include "uconv.h"

namespace gezi {

	inline std::string gbk_to_utf8(const std::string & src, int flags = UCONV_INVCHAR_IGNORE)
	{
		int outlen = src.length() * 3 + 1;
		std::vector<char> outbuf(outlen, 0);

		if (::gbk_to_utf8(src.c_str(), src.length(), &outbuf[0], outlen, flags) < 0)
		{
			//LOG_WARNING("Convert from gbk_to_utf8 fail:%s", src.c_str());
			return "";
		}

		std::string rs = &outbuf[0];
		return rs;
	}

	inline std::string utf8_to_gbk(const std::string & src, int flags = UCONV_INVCHAR_IGNORE)
	{
		int outlen = src.length() * 2 + 1;
		std::vector<char> outbuf(outlen, 0);

		if (::utf8_to_gbk(src.c_str(), src.length(), &outbuf[0], outlen, flags) < 0)
		{
			//LOG_WARNING("Convert from utf8_to_gbk fail:%s", src.c_str());
			return "";
		}

		std::string rs = &outbuf[0];
		return rs;
	}

	inline std::string gbk2utf8(const std::string& src, int flags = UCONV_INVCHAR_IGNORE)
	{
		return gbk_to_utf8(src, flags);
	}

	inline std::string utf82gbk(const std::string& src, int flags = UCONV_INVCHAR_IGNORE)
	{
		return utf8_to_gbk(src, flags);
	}

	inline std::string to_gbk(const std::string& src, int flags = UCONV_INVCHAR_IGNORE)
	{
		return utf8_to_gbk(src, flags);
	}

	inline std::string to_utf8(const std::string& src, int flags = UCONV_INVCHAR_IGNORE)
	{
		return gbk_to_utf8(src, flags);
	}

}

#undef uint16_t
#undef uint8_t
#undef uint32_t
#endif	/* ENCODING_CONVERT_H_ */

