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

DEFINE_double(thre, 0.3, "");
DEFINE_double(thre2, 0.98, "");

DEFINE_string(ip_dingtie_key, "#!dt_ip!#", "相同ip不同uid");
DEFINE_string(uid_dingtie_key, "#!dt_uid!#", "相同uid不同ip");
DEFINE_string(ip_self_dingtie_key, "#!dt_ip_self!#", "相同ip不同uid并且是和楼主相同ip");
DEFINE_string(uid_self_dingtie_key, "#!dt_uid_self!#", "相同uid不同ip并且是和楼主相同uid");
DEFINE_string(pic_key, "#!pic!#", "");
DEFINE_string(pic_self_key, "#!pic_thread!#", "");
DEFINE_string(url_key, "#!url!#", "");
DEFINE_string(url_self_key, "#!url_thread!#", "");
DEFINE_string(at_key, "#!at!#", "");
DEFINE_string(at_self_key, "#!at_thread!#", "");
DEFINE_int32(max_allowed_span, 3600, "只考虑扫描最近一小时的pid");

DEFINE_string(keys, "ip", "choose which keys to read from redis");

DEFINE_int32(buffer_size, 1, "for writing to db");

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

int _numDeals;
int _numPredicts;
int _numRecalls;
int _numSelfRecalls;

vector<string> _buffer;

void run(uint64 tid, double thre)
{
	//--------------get info
	//_timerMap.count非线程安全 但是内部保障openmp安全
	if (_deletedTids.count(tid) || _timerMap.count(tid))
	{
		VLOG(2) << "Deleted or deal this tid not long before";
		return;
	}

#pragma  omp critical
	{
		_numDeals++;
	}

	Features fe = gen_fullposts_features(tid, FLAGS_num, _fetcher);
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

	VLOG(0) << "deal: " << node.threadId << "\t" << node.title << "\t" << node.contents[0] << "\t" << node.unames[0]
		<< "\t" << node.forumName << "\t" << node.numPosts << "\t" << gezi::to_time_str(node.times[0])
		<< "\t" << gezi::to_time_str(node.times.back()) << "\t" << thre << "\t" << score;
	VLOG(0) << "feature: " << node.threadId << "\t" << node.postId << "\t" << score << "\t" << fe.str();

#pragma  omp critical
	{
		_numPredicts++;
	}

	if (score >= thre)
	{
#pragma  omp critical
		{
			_deletedTids.insert(tid);
			_numRecalls++;
		}
		{
		if (score <= 1)
		{//只考虑独立召回 其它策略未删除的
			//----------------write info
			{
				stringstream ss;
				ss << node.threadId << "\t" << node.postId << "\t" << node.uids[0] << "\t"
					<< node.forumId << "\t" << node.ips[0] << "\t"
					<< node.times[0] << "\t" << score << "\t" << node.title << "\t"
					<< gezi::erase(node.contents[0], "\n") << "\t" << node.forumName << "\t"
					<< node.unames[0] << "\t" << gezi::now_time() << "\t" << node.numPosts << "\t" << thre << endl;

#pragma  omp critical
				{
					_buffer.push_back(ss.str());
					_numSelfRecalls++;
				}
			}

			if (_buffer.size() >= FLAGS_buffer_size)
			{
#pragma omp critical 
				{
					ofstream ofs(FLAGS_o);
					for (auto& line : _buffer)
					{
						ofs << line;
					}
					ofs.flush();

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

					_buffer.clear();
				}
			}
		}
	}
	}
}

void init()
{
	SharedConf::init("fullposts.conf");

	string fullpostsModelPath = "./model";
	PSCONF(fullpostsModelPath, "Global");
	_predictor = PredictorFactory::LoadPredictor(fullpostsModelPath);

	int redisRet = _redisClient.Init();
	CHECK_EQ(redisRet, 0);AutoTimer timer("WriteDB");

}

void run()
{
	init();

	omp_set_num_threads(FLAGS_nt);
	while (true)
	{
		//vector<uint64> tids;
		map<uint64, double> tidMap;
		auto func = [&](string value, double score, double thre)
		{
			int64 occcurTime = INT64(-score);
			if (now_time() - occcurTime > FLAGS_max_allowed_span)
			{
				return false;
			}
			//tids.push_back(UINT64(value));
			//tidSet.insert(UINT64(value));
			tidMap.insert(make_pair(UINT64(value), thre));
			return true;
		};

		auto func1 = [&](string value, double score)
		{
			return func(value, score, FLAGS_thre);
		};

		auto func2 = [&](string value, double score)
		{
			return func(value, score, FLAGS_thre2);
		};

		{
			AutoTimer timer("redis serarch", 1);

			if (gezi::contains(FLAGS_keys, "ip"))
				_redisClient.ZrangeFirstNElementWithScoresIf(FLAGS_ip_dingtie_key, 100, func1);
			if (gezi::contains(FLAGS_keys, "url"))
				_redisClient.ZrangeFirstNElementWithScoresIf(FLAGS_url_self_key, 100, func2);
			if (gezi::contains(FLAGS_keys, "at"))
				_redisClient.ZrangeFirstNElementWithScoresIf(FLAGS_at_self_key, 100, func2);
			if (gezi::contains(FLAGS_keys, "pic"))
				_redisClient.ZrangeFirstNElementWithScoresIf(FLAGS_pic_self_key, 100, func2);
		}

		{
			AutoTimer timer("run fullposts", 1);
			_numDeals = _numPredicts = _numRecalls = _numSelfRecalls = 0;
			Features::useNames() = false;

			//vector<uint64> tids(tidSet.begin(), tidSet.end());
			vector<uint64> tids;
			vector<double> thres;
			for (auto & item : tidMap)
			{
				tids.push_back(item.first);
				thres.push_back(item.second);
			}
#pragma omp parallel for
			for (size_t i = 0; i < tids.size(); i++)
			{
				//run(tids[i]);
				run(tids[i], thres[i]);
			}
			VLOG(0) << "tidSize: [" << tids.size() << "] numDeals:[" << _numDeals << "] numPredicts: [" << _numPredicts <<
				"] numRecalls: [" << _numRecalls << "] numSelfRecalls:[" << _numSelfRecalls << "] cacheSize:[" << _fetcher.CacheSize() << "]";
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

	run();

	return 0;
}
