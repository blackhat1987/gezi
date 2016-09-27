#ifndef URL_UTIL_H_
#define URL_UTIL_H_

#define _HTTP_REQ_BUF_SIZE_ 512
#define _XML_BUF_SIZE_ 100*1024
DECLARE_string(host);

// --- Url类别 --- //
enum EUrlType
{
    E_URL_LINK = 0, // 计入页面出度的链接
    E_URL_SRC = 1, // 不计入页面出度的链接
    E_URL_FILTED = 2 // 被过滤的链接
};


#include <string>
#include <iostream>
// --- Url的字符类别 --- //
enum
{
    // --- RFC1738 reserved chars + "$" and ",". --- //
    E_URL_CHR_RESERVED = 1,

    // --- RFC1738 unsafe chars, plus non-printables. --- //
    E_URL_UNSAFE = 2
};

#define URL_CHR_TEST(c, mask)   (URL_CHR_TABLE[(unsigned char)(c)] & (mask))
#define URL_RESERVED_CHAR(c)    URL_CHR_TEST(c, E_URL_CHR_RESERVED)
#define URL_UNSAFE_CHAR(c)      URL_CHR_TEST(c, E_URL_UNSAFE)

#define XNUM_TO_DIGIT(x)        ("0123456789ABCDEF"[x] + 0)

//--- Shorthands for the table --- //
#define R   E_URL_CHR_RESERVED
#define U   E_URL_UNSAFE
#define RU  R|U

// U是不安全字符，是必须编码的；R是保留字符，可以编码也可以不编
const unsigned char URL_CHR_TABLE[256] = {
    U, U, U, U, U, U, U, U, /* NUL SOH STX ETX  EOT ENQ ACK BEL */
    U, U, U, U, U, U, U, U, /* BS  HT  LF  VT   FF  CR  SO  SI  */
    U, U, U, U, U, U, U, U, /* DLE DC1 DC2 DC3  DC4 NAK SYN ETB */
    U, U, U, U, U, U, U, U, /* CAN EM  SUB ESC  FS  GS  RS  US  */
    U, 0, U, RU, R, U, R, 0, /* SP  !   "   #    $   %   &   '   */
    0, 0, 0, R, R, 0, 0, R, /* (   )   *   +    ,   -   .   /   */
    0, 0, 0, 0, 0, 0, 0, 0, /* 0   1   2   3    4   5   6   7   */
    0, 0, RU, R, U, R, U, R, /* 8   9   :   ;    <   =   >   ?   */
    RU, 0, 0, 0, 0, 0, 0, 0, /* @   A   B   C    D   E   F   G   */
    0, 0, 0, 0, 0, 0, 0, 0, /* H   I   J   K    L   M   N   O   */
    0, 0, 0, 0, 0, 0, 0, 0, /* P   Q   R   S    T   U   V   W   */
    0, 0, 0, RU, U, RU, U, 0, /* X   Y   Z   [    \   ]   ^   _   */
    U, 0, 0, 0, 0, 0, 0, 0, /* `   a   b   c    d   e   f   g   */
    0, 0, 0, 0, 0, 0, 0, 0, /* h   i   j   k    l   m   n   o   */
    0, 0, 0, 0, 0, 0, 0, 0, /* p   q   r   s    t   u   v   w   */
    0, 0, 0, U, U, U, 0, U, /* x   y   z   {    |   }   ~   DEL */

    U, U, U, U, U, U, U, U, U, U, U, U, U, U, U, U,
    U, U, U, U, U, U, U, U, U, U, U, U, U, U, U, U,
    U, U, U, U, U, U, U, U, U, U, U, U, U, U, U, U,
    U, U, U, U, U, U, U, U, U, U, U, U, U, U, U, U,

    U, U, U, U, U, U, U, U, U, U, U, U, U, U, U, U,
    U, U, U, U, U, U, U, U, U, U, U, U, U, U, U, U,
    U, U, U, U, U, U, U, U, U, U, U, U, U, U, U, U,
    U, U, U, U, U, U, U, U, U, U, U, U, U, U, U, U,
};

#undef RU
#undef U
#undef R
inline string EncodeUrl(string strUrl, bool bEncodeReserved = false)
{
	string strEncodedUrl;
	string::size_type nPos;
	unsigned char Chr;

	for (nPos = 0; nPos < strUrl.size(); nPos++)
	{
		Chr = strUrl.at(nPos);
		if ('%' == Chr)
		{
			// %后面是16进制的数字就不需要再编码
			if (((nPos + 2) < strUrl.size()) && isxdigit((unsigned char) strUrl.at(nPos + 1)) && isxdigit((unsigned char) strUrl.at(nPos + 2)))
			{
				strEncodedUrl += Chr;
			}
			else
			{
				// 需要编码
				strEncodedUrl += '%';
				strEncodedUrl += XNUM_TO_DIGIT(Chr >> 4);
				strEncodedUrl += XNUM_TO_DIGIT(Chr & 0xf);
			}
		}
		else if (bEncodeReserved)
		{
			// 如果要对保留字符也编码
			if ((unsigned char) (Chr) < 128 && URL_UNSAFE_CHAR(Chr) || URL_RESERVED_CHAR(Chr))
			{
				strEncodedUrl += '%';
				strEncodedUrl += XNUM_TO_DIGIT(Chr >> 4);
				strEncodedUrl += XNUM_TO_DIGIT(Chr & 0xf);
			}
			else
			{
				strEncodedUrl += Chr;
			}
		}
		else
		{
			if (URL_UNSAFE_CHAR(Chr) && !URL_RESERVED_CHAR(Chr))
			{
				strEncodedUrl += '%';
				strEncodedUrl += XNUM_TO_DIGIT(Chr >> 4);
				strEncodedUrl += XNUM_TO_DIGIT(Chr & 0xf);
			}
			else
			{
				strEncodedUrl += Chr;
			}
		}
	}

	return strEncodedUrl;
}
#endif

