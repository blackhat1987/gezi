/** 
 *  ==============================================================================
 * 
 *          \file   test_identifer.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-03-11 17:40:09.414513
 *  
 *  \Description: /home/users/chenghuige/urate/app/search/sep/anti-spam/tieba-urate/exp/mis/reply.train/train.v1/words.idf.txt
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "Numeric/Vector/Vector.h"
#include "Identifer.h"
using namespace std;
using namespace gezi;
DEFINE_int32(level, 0, "min log level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(test_identifer, func)
{
	DoubleIdentifer identifer;
	identifer.load(FLAGS_i);
	serialize_util::save_json(identifer, "test.data/identifer.json");
	serialize_util::save(identifer, "test.data/identifer.bin");

	{
		DoubleIdentifer identifer;
		serialize_util::load(identifer, "test.data/identifer.bin");
		Pval(identifer.size());
	}

	{
		DoubleIdentifer identifer2;
		identifer.Save("test.data/identifer2.bin");
		identifer2.Load("test.data/identifer2.bin");
		Pval(identifer2.size());
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
