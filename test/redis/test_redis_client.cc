/** 
 *  ==============================================================================
 * 
 *          \file   test_redis_client.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-08 21:49:00.148573
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "tools/redis/RedisClient.h"
using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");
DEFINE_string(key, "!####!", "");

RedisClient _client;

void run()
{

}

TEST(zrange, func)
{
	svec members = _client.Zrange(FLAGS_key, 0, 100);
	Pvec(members);
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
	
	_client.Init();

	return RUN_ALL_TESTS();
}
