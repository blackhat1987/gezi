/* 
 * File:   encoding_convert.h
 * Author: chenghuige
 *
 * Created on 2013年11月3日, 上午9:57
 */

#ifndef ENCODING_CONVERT_H_
#define	ENCODING_CONVERT_H_

#include "uconv.h"

namespace gezi
{

inline string gbk_to_utf8(const string & src, int flags = UCONV_INVCHAR_IGNORE)
{
  int outlen = src.length()* 3 + 1;
  char* outbuf = new char[outlen];
  memset(outbuf, 0, sizeof (outbuf));

  if (::gbk_to_utf8(src.c_str(), src.length(), outbuf, outlen, flags) < 0)
  {
    LOG_WARNING("Convert from gbk_to_utf8 fail:%s", src.c_str());
    return "";
  }

  string rs = outbuf;
  delete [] outbuf;
  return rs;
}

inline string utf8_to_gbk(const string & src, int flags = UCONV_INVCHAR_IGNORE)
{
  int outlen = src.length()* 2 + 1;
  char* outbuf = new char[outlen];
  memset(outbuf, 0, sizeof (outbuf));

  if (::utf8_to_gbk(src.c_str(), src.length(), outbuf, outlen, flags) < 0)
  {
    LOG_WARNING("Convert from utf8_to_gbk fail:%s", src.c_str());
    return "";
  }

  string rs = outbuf;
  delete [] outbuf;
  return rs;
}

inline string gbk2utf8(const string& src, int flags = UCONV_INVCHAR_IGNORE)
{
  return gbk_to_utf8(src, flags);
}

inline string utf82gbk(const string& src, int flags = UCONV_INVCHAR_IGNORE)
{
  return utf8_to_gbk(src, flags);
}

inline string to_gbk(const string& src, int flags = UCONV_INVCHAR_IGNORE)
{
  return utf8_to_gbk(src, flags);
}

inline string to_utf8(const string& src, int flags = UCONV_INVCHAR_IGNORE)
{
  return gbk_to_utf8(src, flags);
}

}

#undef uint16_t
#undef uint8_t
#undef uint32_t
#endif	/* ENCODING_CONVERT_H_ */

