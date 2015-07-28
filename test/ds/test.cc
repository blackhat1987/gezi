/**
 *  ==============================================================================
 *
 *          \file   test.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-07-24 14:32:55.400118
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"

#include <folly/small_vector.h>
#include <folly/FBVector.h>
#include <folly/Foreach.h>

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

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

inline string extract_gbk_dual11(string temp)
{
	vector<char> out(temp.size() + 1);

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
	string ret(&out[0]);
	return ret;
}
//std::unique_ptr<int> dflt(new int(42));

inline string extract_gbk_dual_uniqueptr(string temp)
{
	unique_ptr<char[]> out(new char[temp.size() + 1]);

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
	string ret(out.get());
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

inline string extract_gbk_stack(string temp)
{
	char out[temp.size() + 1];
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
	return out;
}

#define CREATE_BUFFER(out, T, Length)\
	char* out; \
	bool bufferIsOnHeap = false;\
	if (Length > kSmallStringLength)\
	{\
		out = new T[Length]; \
		bufferIsOnHeap = true; \
	}\
	else\
	{\
			T temp[Length]; \
			out = temp; \
	}

#define FREE_BUFFER(out)\
	if (bufferIsOnHeap) \
		delete[] out 

inline void extract_gbk_stack_or_heap_(char * out, string temp)
{
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
}
inline string extract_gbk_stack_or_heap(string temp)
{
	int length = temp.size() + 1;
	if (length > kSmallStringLength)
	{
		char* out = new char[length];
		extract_gbk_stack_or_heap_(out, temp);
		string ret(out);
		delete[] out;
		return ret;
	}
	else
	{
		char out[length];
		extract_gbk_stack_or_heap_(out, temp);
		return out;
	}
}

//TEST(vec2_, perf)
//{
//	FOR_EACH_RANGE(i, 0, 10240000) {
//		string s = extract_gbk_dual2("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
//	}
//}
//
//TEST(vec3_, perf)
//{
//	FOR_EACH_RANGE(i, 0, 10240000) {
//		string s = extract_gbk_dual3("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
//	}
//}
//
//TEST(fbvec_, perf)
//{
//	FOR_EACH_RANGE(i, 0, 10240000) {
//		string s = extract_gbk_dual_fbvec("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
//	}
//}
//
//TEST(smallvec_, perf)
//{
//	FOR_EACH_RANGE(i, 0, 10240000) {
//		string s = extract_gbk_dual_smallvec("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
//	}
//}
//
//TEST(vec_, perf)
//{
//	FOR_EACH_RANGE(i, 0, 10240000) {
//		string s = extract_gbk_dual1("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
//	}
//}
//
//TEST(vec11_, perf)
//{
//	FOR_EACH_RANGE(i, 0, 10240000) {
//		string s = extract_gbk_dual11("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
//	}
//}
//
//
//TEST(uniqueptr_, perf)
//{
//	FOR_EACH_RANGE(i, 0, 10240000) {
//		string s = extract_gbk_dual_uniqueptr("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
//	}
//}
//
//TEST(vec22_, perf)
//{
//	FOR_EACH_RANGE(i, 0, 10240000) {
//		string s = extract_gbk_dual2("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
//	}
//}
//
//
//TEST(stack_, perf)
//{
//	FOR_EACH_RANGE(i, 0, 10240000) {
//		string s = extract_gbk_stack("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
//	}
//}
//
//TEST(stack_or_heap_, perf)
//{
//	FOR_EACH_RANGE(i, 0, 10240000) {
//		string s = extract_gbk_stack_or_heap("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²");
//	}
//}


vector<string> titles;
vector<string> contents;
vector<string> titles2;
vector<string> contents2;

TEST(file_new, perf)
{
	FOR_EACH_RANGE(i, 0, titles.size())
	{
		titles2[i] = extract_gbk_dual2(titles[i]);
	}

	FOR_EACH_RANGE(i, 0, contents.size())
	{
		contents2[i] = extract_gbk_dual2(contents[i]);
	}
}

TEST(file_vector, perf)
{
	FOR_EACH_RANGE(i, 0, titles.size())
	{
		titles2[i] = extract_gbk_dual1(titles[i]);
	}

	FOR_EACH_RANGE(i, 0, contents.size())
	{
		contents2[i] = extract_gbk_dual1(contents[i]);
	}
}

TEST(file_vector_noinit, perf)
{
	FOR_EACH_RANGE(i, 0, titles.size())
	{
		titles2[i] = extract_gbk_dual11(titles[i]);
	}

	FOR_EACH_RANGE(i, 0, contents.size())
	{
		contents2[i] = extract_gbk_dual11(contents[i]);
	}
}

TEST(file_inplace_string, perf)
{
	FOR_EACH_RANGE(i, 0, titles.size())
	{
		titles2[i] = extract_gbk_dual3(titles[i]);
	}

	FOR_EACH_RANGE(i, 0, contents.size())
	{
		contents2[i] = extract_gbk_dual3(contents[i]);
	}
}

TEST(file_uniqueptr, perf)
{
	FOR_EACH_RANGE(i, 0, titles.size())
	{
		titles2[i] = extract_gbk_dual_uniqueptr(titles[i]);
	}

	FOR_EACH_RANGE(i, 0, contents.size())
	{
		contents2[i] = extract_gbk_dual_uniqueptr(contents[i]);
	}
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;

	Pval(extract_gbk_dual_uniqueptr("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²"));
	Pval(extract_gbk_stack("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²"));
	Pval(extract_gbk_stack_or_heap("gbk×Ö·û´®ÄãÊÇË­Ë­ÊÇÄãÀ²À²À²"));


	ifstream ifs(FLAGS_i);
	string line;
	while (getline(ifs, line))
	{
		svec l = gezi::split(line, '\t');
		titles.push_back(l[2]);
		contents.push_back(l[3]);
		titles2.push_back(l[2]);
		contents2.push_back(l[3]);
	}

	return RUN_ALL_TESTS();
}
