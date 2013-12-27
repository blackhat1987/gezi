/* 
 * File:   encoding_convert.h
 * Author: chenghuige
 *
 * Created on 2013年11月3日, 上午9:57
 */

#ifndef ENCODING_CONVERT_H_
#define	ENCODING_CONVERT_H_

namespace gezi
{
//----------------------------------------gbk utf8 convert
inline int code_convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
  iconv_t cd;
  char **pin = &inbuf;
  char **pout = &outbuf;

  cd = iconv_open(to_charset, from_charset);
  if (cd == 0)
  {
    return -1;
  }

  memset(outbuf, 0, outlen);

  if (int(iconv(cd, pin, &inlen, pout, &outlen)) == -1)
  {
    return -1;
  }

  iconv_close(cd);

  return 0;
}

inline string gbk_to_utf8(char* src)
{
  int outlen = strlen(src) * 3 + 1;
  char* outbuf = new char[outlen];
  memset(outbuf, 0, sizeof (outbuf));

  if (code_convert("gbk", "utf-8", src, strlen(src), outbuf, outlen) < 0)
  {
    LOG_WARNING("Convert from gbk_to_utf8 fail:%s", src);
    return "";
  }

  string rs = outbuf;
  delete [] outbuf;
  return rs;
}

inline string gbk_to_utf8(const string & src)
{
  int outlen = src.length()* 3 + 1;
  char* outbuf = new char[outlen];
  memset(outbuf, 0, sizeof (outbuf));

  if (code_convert("gbk", "utf-8", const_cast<char*> (src.c_str()), src.length(), outbuf, outlen) < 0)
  {
    LOG_WARNING("Convert from gbk_to_utf8 fail:%s", src.c_str());
    return "";
  }

  string rs = outbuf;
  delete [] outbuf;
  return rs;
}

inline string gbk2utf8(const string& src) 
{
  return gbk_to_utf8(src);
}

inline string utf8_to_gbk(char* src)
{
  int outlen = strlen(src) * 2 + 1;
  char* outbuf = new char[outlen];
  memset(outbuf, 0, sizeof (outbuf));

  if (code_convert("utf-8", "gbk", src, strlen(src), outbuf, outlen) < 0)
  {
    LOG_WARNING("Convert from utf8_to_gbk fail:%s", src);
    return "";
  }

  string rs = outbuf;
  delete [] outbuf;
  return rs;
}

inline string utf8_to_gbk(const string & src)
{
  int outlen = src.length()* 2 + 1;
  char* outbuf = new char[outlen];
  memset(outbuf, 0, sizeof (outbuf));

  if (code_convert("utf-8", "gbk", const_cast<char*> (src.c_str()), src.length(), outbuf, outlen) < 0)
  {
    LOG_WARNING("Convert from utf8_to_gbk fail:%s", src.c_str());
    return "";
  }

  string rs = outbuf;
  delete [] outbuf;
  return rs;
}

inline string utf82gbk(const string& src) 
{
  return utf8_to_gbk(src);
}

inline string to_gbk(const string& src)
{
  return utf8_to_gbk(src);
}

inline string to_utf8(const string& src)
{
  return gbk_to_utf8(src);
}

}


#endif	/* ENCODING_CONVERT_H_ */

