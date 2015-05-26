/**
 *  ==============================================================================
 *
 *          \file   test_derive_vector.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-05-26 13:03:35.402424
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"

using namespace std;
using namespace gezi;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

struct A
{
	int x = 5.82;
};

struct B : public A
{
	int y = 5;
};

void test(vector<A*>& vec)
{
	Pval(vec[0]->x);
}

void run()
{
	vector<A*> vec;
	B b;
	vec.push_back(static_cast<A*>(&b));
	test(vec);
}

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	google::SetVersionString(get_version());
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	FLAGS_minloglevel = FLAGS_level;
	//LogHelper::set_level(FLAGS_level);
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;

	run();

	return 0;
}
