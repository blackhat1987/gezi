/** 
 *  ==============================================================================
 * 
 *          \file   test_pinyin.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-03-15 11:43:03.639157
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "tools/pinyin/Pinyin.h"
using namespace std;
using namespace gezi;
DEFINE_int32(level, 0, "min log level");
DEFINE_string(i, "data/pinyin", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(test_pinyin, func)
{
	Pinyin::Load(FLAGS_i);
	size_t length = 12;

#pragma omp parallel for 
	for (size_t i = 0; i < length; i++)
	{
		Pval(Pinyin::Convert("abc你好"));
		Pval(Pinyin::Convert("美女基情音乐"));
	}

	Pval(Pinyin::Convert("ab音乐乐趣12很多123"));
	Pval(Pinyin::Convert("圆顺达驾校是呼巿一所"));
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
