/**
 *  ==============================================================================
 *
 *          \file   trate.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-01-08 17:53:34.135313
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "tools/redis/RedisClient.h"
#include "MLCore/PredictorFactory.h"
#include "container/lru_containers.h"
#include "tieba/info/post_info.h"

using namespace std;
using namespace gezi;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

DEFINE_int32(deal_count, 100, "");

DEFINE_string(reply_key, "#!post!#", "");
DEFINE_int32(replys_max_count, 101000, "");//缓存最近10w pid
DEFINE_string(thread_key, "#!thread!#", "");
DEFINE_int32(threads_max_count, 101000, "");//缓存最近10w tid
DEFINE_string(tid_key, "#!tid!#", "");
DEFINE_int32(tids_max_count, 101000, "");//缓存最近10w tid


const int kMaxIds = 1e+5;
LruHashSet<uint64> _visitedIds(kMaxIds);

RedisClient _redisClient;
PredictorPtr _predictor;

void init()
{
	SharedConf::init("fullposts.conf");

	_predictor = PredictorFactory::LoadPredictor("./data/ltrate.thread.model/");

	int redisRet = _redisClient.Init();
	CHECK_EQ(redisRet, 0);
}

void deal(const vector<uint64>& pids)
{
	auto infos = tieba::get_posts_info(pids);
	for (size_t i = 0; i < infos.size(); i++)
	{
		Pval7(infos[i].postId, infos[i].threadId, infos[i].forumName, infos[i].userName, to_time_str(infos[i].createTime), infos[i].title, infos[i].content);
	}
}

void run()
{
	init();
	uint64 round = 0;
	vector<uint64> pids;
	while (true)
	{
		svec vec;
		_redisClient.ZrangeFirstNElement(FLAGS_thread_key, 100, vec);
		PVAL2(round, vec.size());
		for (auto& pidStr : vec)
		{
			uint64 pid = UINT64(pidStr);
			if (!_visitedIds.count(pid))
			{
				_visitedIds.insert(pid);
				pids.push_back(pid);
				if (pids.size() == FLAGS_deal_count)
				{
					deal(pids);
					pids.clear();
				}
				PVAL2(round, pid);
			}
		}
		round++;
	}
}

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	FLAGS_minloglevel = FLAGS_level;
	LogHelper::set_level(FLAGS_level);
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;

	run();

	return 0;
}
