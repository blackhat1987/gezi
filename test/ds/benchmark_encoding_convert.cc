/** 
 *  ==============================================================================
 * 
 *          \file   benchmark_encoding_convert.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-07-21 22:55:55.974125
 *  
 *  \Description:  ÐèÒªv2»·¾³²âÊÔ
 *
 *  ==============================================================================
 */

#include "common_util.h"
#include "string_util.h"
#include "wstring_util.h"
#include "encoding_convert.h"

#include <folly/small_vector.h>
#include <folly/FBVector.h>
#include <folly/Benchmark.h>
#include <folly/Foreach.h>

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


inline string extract_gbk_dual_smallvec(string temp)
{
	folly::small_vector<char, kSmallStringLength> out(temp.size() + 1, 0);

	int index = 0;
	for (size_t i = 0; i < temp.size(); i++)
	{
		unsigned high = (unsigned)(0xff & temp[i]);
		if (high >= 0x81)
		{
			out[index] = temp[i];
			out[index + 1] = temp[i + 1];
			index += 2;
			i++;
		}

	}
	string ret(&out[0]);
	return ret;
}
inline string extract_gbk_dual_fbvec(string temp)
{
	folly::fbvector<char> out(temp.size() + 1, 0);

	int index = 0;
	for (size_t i = 0; i < temp.size(); i++)
	{
		unsigned high = (unsigned)(0xff & temp[i]);
		if (high >= 0x81)
		{
			out[index] = temp[i];
			out[index + 1] = temp[i + 1];
			index += 2;
			i++;
		}

	}
	string ret(&out[0]);
	return ret;
}

inline string extract_gbk_dual1(string temp)
{
	vector<char> out(temp.size() + 1, 0);

	int index = 0;
	for (size_t i = 0; i < temp.size(); i++)
	{
		unsigned high = (unsigned)(0xff & temp[i]);
		if (high >= 0x81)
		{
			out[index] = temp[i];
			out[index + 1] = temp[i + 1];
			index += 2;
			i++;
		}
	}
	string ret(&out[0]);
	return ret;
}

inline string extract_gbk_dual2(string temp)
{
	char* out = new char[temp.size() + 1];
	int index = 0;
	for (size_t i = 0; i < temp.size(); i++)
	{
		unsigned high = (unsigned)(0xff & temp[i]);
		if (high >= 0x81)
		{
			out[index] = temp[i];
			out[index + 1] = temp[i + 1];
			index += 2;
			i++;
		}
	}
	out[index] = '\0';
	string ret(out);
	delete[] out;
	return ret;
}

inline string extract_gbk_dual3(string temp)
{
	string out(temp.size() + 1, '\0');
	int index = 0;
	for (size_t i = 0; i < temp.size(); i++)
	{
		unsigned high = (unsigned)(0xff & temp[i]);
		if (high >= 0x81)
		{
			out[index] = temp[i];
			out[index + 1] = temp[i + 1];
			index += 2;
			i++;
		}
	}
	out.resize(index);
	return out;
}

BENCHMARK(vec, n) {
	FOR_EACH_RANGE(i, 0, n) {
		string s = extract_gbk_dual1("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
	}
}

BENCHMARK_RELATIVE(vec2, n) {
	FOR_EACH_RANGE(i, 0, n) {
		string s = extract_gbk_dual2("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
	}
}

BENCHMARK_RELATIVE(vec3, n) {
	FOR_EACH_RANGE(i, 0, n) {
		string s = extract_gbk_dual3("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
	}
}

BENCHMARK_RELATIVE(fbvec, n) {
	FOR_EACH_RANGE(i, 0, n) {
		string s = extract_gbk_dual_fbvec("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
	}
}

BENCHMARK_RELATIVE(smallvec, n) {
	FOR_EACH_RANGE(i, 0, n) {
		string s = extract_gbk_dual_smallvec("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
	}
}

BENCHMARK(vec_)
{
	FOR_EACH_RANGE(i, 0, 1024000) {
		string s = extract_gbk_dual1("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
	}
}

BENCHMARK_RELATIVE(vec2_)
{
	FOR_EACH_RANGE(i, 0, 1024000) {
		string s = extract_gbk_dual2("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
	}
}

BENCHMARK_RELATIVE(vec3_)
{
	FOR_EACH_RANGE(i, 0, 1024000) {
		string s = extract_gbk_dual3("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
	}
}

BENCHMARK_RELATIVE(fbvec_)
{
	FOR_EACH_RANGE(i, 0, 1024000) {
		string s = extract_gbk_dual_fbvec("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
	}
}

BENCHMARK_RELATIVE(smallvec_)
{
	FOR_EACH_RANGE(i, 0, 1024000) {
		string s = extract_gbk_dual_smallvec("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
	}
}

void test()
{
	Pval(extract_gbk_dual1("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²abc"));
	Pval(extract_gbk_dual2("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²abc"));
	Pval(extract_gbk_dual3("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²abc"));
}

int main(int argc, char *argv[])
{
	test();
	runBenchmarks();
}
