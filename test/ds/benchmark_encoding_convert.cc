/** 
 *  ==============================================================================
 * 
 *          \file   benchmark_encoding_convert.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-07-21 22:55:55.974125
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#include "common_util.h"
#include "string_util.h"
#include "wstring_util.h"
#include "encoding_convert.h"
#include <folly/Benchmark.h>
#include <folly/Foreach.h>

using namespace std;
using namespace gezi;
using namespace folly;

BENCHMARK(convert, n) {
	FOR_EACH_RANGE(i, 0, n) {
		string s = wstr2str(wstr("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²"));
	}
}
BENCHMARK_RELATIVE(boostConvert, n) {
	FOR_EACH_RANGE(i, 0, n) {
		string s = wstr2str(wstr("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²", kDefaultEncoding), kDefaultEncoding);
	}
}

BENCHMARK_RELATIVE(boostConvertDirect, n) {
	FOR_EACH_RANGE(i, 0, n) {
		string s = boost::locale::conv::from_utf((boost::locale::conv::to_utf<wchar_t>("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²", "GBK")), "GBK");
	}
}

BENCHMARK(encodingConvert, n) {
	FOR_EACH_RANGE(i, 0, n) {
		string s = utf82gbk(gbk2utf8("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²"));
	}
}

BENCHMARK_RELATIVE(boostEncodingConvert, n) {
	FOR_EACH_RANGE(i, 0, n) {
		string s = convert(convert("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²", "GBK", "UTF8"), "UTF8", "GBK");
	}
}

int main(int argc, char *argv[])
{
	runBenchmarks();
}
