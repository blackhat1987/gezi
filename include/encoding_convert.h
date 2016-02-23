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
#include "string_def.h"
#include "encoding_def.h"
#include "uconv.h"

namespace gezi {
	inline string gbk_to_utf8(string src, int flags = UCONV_INVCHAR_IGNORE)
	{
		int outlen = src.length() * 3 + 1;
		std::vector<char> outbuf(outlen, 0);

		if (::gbk_to_utf8(src.c_str(), src.length(), &outbuf[0], outlen, flags) < 0)
		{
			//LOG_WARNING("Convert from gbk_to_utf8 fail:%s", src.c_str());
			return "";
		}

		string rs = &outbuf[0];
		return rs;
	}

	inline string utf8_to_gbk(string src, int flags = UCONV_INVCHAR_IGNORE)
	{
		int outlen = src.length() * 2 + 1;
		std::vector<char> outbuf(outlen, 0);

		if (::utf8_to_gbk(src.c_str(), src.length(), &outbuf[0], outlen, flags) < 0)
		{
			//LOG_WARNING("Convert from utf8_to_gbk fail:%s", src.c_str());
			return "";
		}

		string rs = &outbuf[0];
		return rs;
	}

	inline string gbk2utf8(string src, int flags = UCONV_INVCHAR_IGNORE)
	{
		return gbk_to_utf8(src, flags);
	}

	inline string utf82gbk(string src, int flags = UCONV_INVCHAR_IGNORE)
	{
		return utf8_to_gbk(src, flags);
	}

	inline string to_gbk(string src, int flags = UCONV_INVCHAR_IGNORE)
	{
		return utf8_to_gbk(src, flags);
	}

	inline string to_utf8(string src, int flags = UCONV_INVCHAR_IGNORE)
	{
		return gbk_to_utf8(src, flags);
	}

} // namespace gezi
#undef uint16_t
#undef uint8_t
#undef uint32_t

#include "common_define.h"
#if defined(IS_HIGH_COMPILER)
//----------------------------boost based 
//参见 ds/benchmark_encoding_convert.cc 测试 boost 性能较差
//== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
//benchmark_encoding_convert.cc                   relative  time / iter  iters / s
//== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
//convert                                                    466.43ns    2.14M
//boostConvert                                      14.67%     3.18us  314.45K
//boostConvertDirect                                14.93%     3.13us  319.99K
//encodingConvert                                              1.67us  600.07K
//boostEncodingConvert                              42.11%     3.96us  252.68K

#include <boost/locale.hpp>
namespace gezi {
	inline string convert(string src, EncodingType fromType, EncodingType toType)
	{
		return boost::locale::conv::between(src, kEncodings[static_cast<int>(fromType)], kEncodings[static_cast<int>(toType)]);
	}

	inline string convert(string src, string fromType, string toType)
	{
		return boost::locale::conv::between(src, fromType, toType);
	}
} // namespace gezi

#endif // __GNUC__ > 3
#endif	/* ENCODING_CONVERT_H_ */

