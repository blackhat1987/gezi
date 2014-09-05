/** 
 *  ==============================================================================
 * 
 *          \file   test_get_full_posts_info.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-03 17:00:51.072945
 *  
 *  \Description: ��������id ��ȡ����¥��Ϣ
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "tieba/get_parsed_info.h"

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 0, "vlog level");
DEFINE_string(i, "", "input"); 
DEFINE_int32(res_num, 10, "return num");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{

}

TEST(get_full_posts_info, func)
{
	tieba::FullPostsInfo info = tieba::get_full_posts_info(3273051494, FLAGS_res_num);
	Pval5(info.tid, info.title, info.fid, info.forumName, info.isDeleted);
	Pval(info.posts.size());
	for (auto& post : info.posts)
	{
		Pval2(post.uname, post.content);
	}
}

//10 res 20ms  100 res 67ms
TEST(get_full_posts_info, perf)
{
	tieba::FullPostsInfo info = tieba::get_full_posts_info(3273051494, FLAGS_res_num);
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