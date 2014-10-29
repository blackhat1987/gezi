/** 
 *  ==============================================================================
 * 
 *          \file   get_rsc_thread_infos.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-10-27 17:32:23.698259
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "tieba/rsc/rsc_threads_info.h"
//#include "container/lru_containers.h" @FIXME 为什么如果rsc_threads_info.h里面有#include "container/LruMap.h"会出现 LruMap重定义？
using namespace std;
using namespace gezi;
using namespace gezi::tieba;
using namespace gezi::tieba::rsc;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "thread.txt", "input file");
DEFINE_string(label, "thread.label.txt", "input file");
DEFINE_string(o, "feature", "output file");
DEFINE_string(feature_dir, "./feature/", "");
DEFINE_string(history, "./history", "");

map<uint64, int> _labelMap; //@TOD

CachedFetcher<uint64, tieba::ThreadInfo, LruHashMap> _threadsFetcher;
CachedFetcher<uint, tieba::UserInfo, LruHashMap> _usersFetcher;

void run()
{
	try_create_dir(FLAGS_history);

	{
		int normalCount = 0, spamCount = 0;

		ifstream ifs(FLAGS_label);
		string line;
		while (getline(ifs, line))
		{
			string id_, label_;
			gezi::split(line, '\t', id_, label_);
			_labelMap[UINT64(id_)] = INT(label_);
		}

		for (auto& item : _labelMap)
		{
			if (item.second == 1)
			{
				spamCount++;
			}
			else
			{
				normalCount++;
			}
		}
		Pval2(normalCount, spamCount);
	}

	Pval(_labelMap.size());

	ifstream ifs(FLAGS_i);
	string line;
	string substr = "";
	using tieba::rsc::ReplyInfo;
	vector<ReplyInfo> tids;
	int numSubstrs = 0;
	while (getline(ifs, line))
	{
		PVAL(line);
		svec vec = gezi::split(line, '\t');
		if (vec[2] != substr)
		{
			if (!tids.empty())
			{
				rsc::RscThreadsInfo info;
				info.Fetch(substr, tids, _threadsFetcher, _usersFetcher, false, FLAGS_history);
				numSubstrs++;
			}

			tids.clear();
			substr = vec[2];
		}
		ReplyInfo node;
		node.tid = UINT64(vec[0]);
		node.threadRatio = DOUBLE(vec[4]);
		node.time = UINT64(vec.back());
		node.ip = UINT64(vec[vec.size() - 2]);
		node.userId = UINT64(vec[vec.size() - 3]);
		tids.emplace_back(node);
	}

	if (!tids.empty())
	{   //注意这里是没有重复的
		rsc::RscThreadsInfo info;
		info.Fetch(substr, tids, _threadsFetcher, _usersFetcher, false, FLAGS_history);
		numSubstrs++;
	}
	Pval(numSubstrs);
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
