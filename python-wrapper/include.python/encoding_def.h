#ifndef GEZI_ENCODING_DEF_H_
#define GEZI_ENCODING_DEF_H_
namespace gezi {
#if __GNUC__ > 3 || defined(WIN32)
const char* const kEncodings[];
enum  EncodingType
{
EncodingType__enum__GBK,
EncodingType__enum__UTF8,
};
#ifndef GEZI_UTF8_AS_DEFAULT_ENCODING
static const EncodingType kDefaultEncoding = EncodingType::GBK;
#else
static const EncodingType kDefaultEncoding = EncodingType::UTF8;
#endif
#endif
}
#endif
