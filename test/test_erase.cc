/**
 *  ==============================================================================
 *
 *          \file   test_erase.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-21 10:08:35.513965
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{
	ivec vec = { 1, 2, 3, 4, 5, 6 };
	Pvec(vec);
	vec.erase(remove_if(vec.begin(), vec.end(), [](int a) { return a % 2 == 0; }), vec.end());
	Pvec(vec);
}

TEST(erase, func)
{
	run();
}

TEST(erase_ufo, func)
{
	ivec vec = { 1, 2, 3, 4, 5, 6, 3 };
	Pvec(vec);
	ufo::erase_if(vec, [](int a) { return a % 2 == 0; });
	Pvec(vec);
	ufo::erase(vec, 3);
	Pvec(vec);

	map<string, int> m = {{"a",3},{"b",4}};
	Pval(m["a"]);
	Pval(m["c"]);
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
