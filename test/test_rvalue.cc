/**
 *  ==============================================================================
 *
 *          \file   test_rvalue.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-05-28 20:35:04.792198
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "stl_util.h"
using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void work(const ivec& a)
{
	VLOG(0) << "const &";
	ivec x = move(a);//仍然是值拷贝
	Pval(a.size());
	Pval(x.size());
}

void work(ivec& a)
{
	VLOG(0) << "&";
	ivec x = move(a);
	Pval(a.size());
	Pval(x.size());
}

void work(ivec&& a)
{
	VLOG(0) << "&&";
	//ivec x = move(a);
	ivec x = a;
	Pval(a.size());
	Pval(x.size());
}


TEST(rvalue, func)
{
	work(ivec{ 1, 2, 3 }); //会优先匹配&&

	ivec a{ 1 }; //如果没有& 会优先匹配 const& 仍然 值拷贝
	work(a);

	ivec c{ 1, 2, 3, 4 };
	work(move(c));

	const ivec b{ 1, 2 };
	work(b);

	dvec x{ 1.23, 3.545, 4.8, 9, 1024.328, 2 };
	svec y{ "a", "bcd", "ef", "iojdfs", "cd", "xooooo" };
	gezi::print(y, x);

	{
		std::cerr << "[" << 0 << "]" << "abc" << "\t";
		cerr.flush();
		dvec x{ 1.23, 3.545 };
		svec y{ "a", "bcd" };
		gezi::print(y, x, ":", "\t");
		cerr << "\n";
	}
		{
			std::cerr << "[" << 0 << "]" << "abcf" << "\t";
			cerr.flush();
			dvec x{ 1.233443, 3.54325 };
			svec y{ "aafsd", "bcd" };
			gezi::print(y, x, ":", "\t");
			cerr << "\n";
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

	return RUN_ALL_TESTS();
}
