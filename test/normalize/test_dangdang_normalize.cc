/** 
 *  ==============================================================================
 * 
 *          \file   test_dangdang_normalize.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-07-23 16:32:20.491999
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"

#include "segment/gbk_ch_converter.h"

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(dangdang_normalize, func)
{
	ch_convert::CharacterConverter converter;
	string input = "123456789£¬£®£¯£¿¡²£û¡³£ý£¡£À££¡ç£¥Ü‡";
	Pval(input);
	Pval(converter.Normalize(input));
	string simplfied = "123456789,./?[{]}!@#$%³µ";
	CHECK_EQ(converter.Normalize(input), simplfied);
}

TEST(dangdang_normalize, perf)
{
	ch_convert::CharacterConverter converter;
	ifstream ifs(FLAGS_i);
	ofstream ofs(FLAGS_o);
	string line;
	while (getline(ifs, line))
	{
		ofs << converter.Normalize(line) << endl;
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
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;
	
	return RUN_ALL_TESTS();
}
