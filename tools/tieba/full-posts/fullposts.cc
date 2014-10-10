/**
 *  ==============================================================================
 *
 *          \file   fullposts.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-25 15:43:06.935509
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "tools/redis/RedisClient.h"
#include "tieba/fullposts/fullposts_features.h"
#include "container/lru_containers.h"
using namespace std;
using namespace gezi;
using namespace gezi::tieba;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 10, "");
DEFINE_uint64(tid, 3301924466, "");
DEFINE_string(i, "", "input file");

DEFINE_double(thre, 0.85, "");
DEFINE_string(ip_dingtie_key, "#!dt_ip!#", "相同ip不同uid");
DEFINE_int32(max_allowed_span, 3600, "只考虑扫描最近一小时的pid");

DEFINE_string(o, "fullposts.result.txt", "output file");
DEFINE_bool(write_db, false, "");
DEFINE_bool(multidelete, false, "");
DEFINE_string(db_exe, "write-db.py", "");
DEFINE_string(multidelete_exe, "multi-delete.py", "");

DEFINE_int32(nt, 12, "thread num");


const int kMaxTids = 1e+5;
LruHashSet<uint64> _deletedTids(kMaxTids);
CachedFetcher<uint64, UrateInfo, LruHashMap> _fetcher(kMaxTids);
TimerMap<uint64, LruHashMap> _timerMap(60, kMaxTids);
PredictorPtr _predictor;
RedisClient _redisClient;


void run(uint64 tid)
{
	//--------------get info
	if (_deletedTids.count(tid) || _timerMap.count(tid))
	{
		VLOG(2) << "Deleted or deal this tid not long before";
		return;
	}

	Features fe = gen_fullposts_features(tid, FLAGS_num, _fetcher);
	Pval(fe.str());

	if (fe.empty())
	{
		return;
	}

	//----------------predict
	double score = 0;
	ExtendedFullPostsInfo& node = FullPostsExtractor::info();

	const double deletedScore = 100;
	if (node.isDeleted)
	{
		score = deletedScore;
	}
	else
	{
		score = _predictor->Predict(fe);
	}
	Pval(score);
	
	if (score >= FLAGS_thre)
	{
#pragma  omp critical
		{
			_deletedTids.insert(tid);
		}
		if (score <= 1)
		{//只考虑独立召回 其它策略未删除的
			//----------------write info
			ofstream ofs(FLAGS_o);
			{
				ofs << node.threadId << "\t" << node.postId << "\t" << node.uids[0] << "\t"
					<< node.forumId << "\t" << node.ips[0] << "\t"
					<< node.times[0] << "\t" << score << "\t" << node.title << "\t"
					<< gezi::erase(node.contents[0], "\n") << "\t" << node.forumName << "\t" << node.unames[0] << endl;
			}

			if (FLAGS_multidelete)
			{
				AutoTimer("MultiDelete");
				string command = "python " + FLAGS_multidelete_exe + " " + FLAGS_o;
				EXECUTE(command);
			}

			if (FLAGS_write_db)
			{
				AutoTimer timer("WriteDB");
				string command = "python " + FLAGS_db_exe + " " + FLAGS_o;
				EXECUTE(command);
			}
		}
	}
}

void run()
{
	omp_set_num_threads(FLAGS_nt);
	while (true)
	{
		vector<uint64> tids;
		auto func = [&](string value, double score)
		{
			int64 occcurTime = INT64(-score);
			if (now_time() - occcurTime > FLAGS_max_allowed_span)
			{
				return false;
			}
			tids.push_back(UINT64(value));
			return true;
		};

		_redisClient.ZrangeFirstNElementWithScoresIf(FLAGS_ip_dingtie_key, 100, func);

		Features::useNames() = false;
#pragma omp parallel for
		for (size_t i = 0; i < tids.size(); i++)
		{
			run(tids[i]);
		}
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

	//SharedConf::init("fullposts_strategy.conf");
	SharedConf::init("fullposts.conf");

	string fullpostsModelPath = "./model";
	PSCONF(fullpostsModelPath, "Global");
	_predictor = PredictorFactory::LoadPredictor(fullpostsModelPath);

	int redisRet = _redisClient.Init();
	CHECK_EQ(redisRet, 0);

	run();

	return 0;
}
