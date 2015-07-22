/**
 *  ==============================================================================
 *
 *          \file   encoding_def.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-07-21 22:21:41.830338
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef GEZI_ENCODING_DEF_H_
#define GEZI_ENCODING_DEF_H_

namespace gezi {
	const char* const kEncodings[] = { "GBK", "UTF8" };
	enum class EncodingType
	{
		GBK,
		UTF8,
	};
#ifndef GEZI_UTF8_AS_DEFAULT_ENCODING
	static const EncodingType kDefaultEncoding = EncodingType::GBK;
#else 
	static const EncodingType kDefaultEncoding = EncodingType::UTF8;
#endif //GEZI_UTF8_AS_DEFAULT_ENCODING
	
}  //----end of namespace gezi

#endif  //----end of GEZI_ENCODING_DEF_H_
