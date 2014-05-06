/** 
 *  ==============================================================================
 * 
 *          \file   test_binfinder.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-04-08 23:41:55.935761
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "Numeric/BinFinder.h"
using namespace std;
using namespace gezi;
DEFINE_int32(level, 0, "min log level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(test_binfinder, func)
{
	BinFinder finder;
	Fvec vec = {1.0, 2.0, 1.0, 1.2, 1.3, 2.4, 3.8, 4.6, 4.9, 7.2, 7.8, 100.0, 330.1, 10.2};
	Pvec(vec);
	Fvec result = finder.FindBins(vec, 3);
	Pvec(result);
	result = finder.FindBins(vec, 5);
	Pvec(result);
	result = finder.FindBins(vec, 1);
	Pvec(result);
	{
		Fvec vec2;
		vec2.resize(3);
		Pvec(vec2);
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
	FLAGS_minloglevel = FLAGS_level;
	boost::progress_timer timer;
	
	return RUN_ALL_TESTS();
}
