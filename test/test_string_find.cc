/** 
 *  ==============================================================================
 * 
 *          \file   test_string_find.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-10-07 20:23:30.189406
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{

}

//not work!
size_t find(string input, const char mark, int start, int len)
{
		if (start + len >= input.size())
			return input.find(mark, start);
		input[len] = '\0';
		return input.find(mark, start);
}

TEST(string_find, func)
{
	using ::find;
	string s("abcdehj");
	Pval(s.find('k'));
	Pval(s.find('h'));
	Pval(find(s, 'h', 0, 6));
	Pval(find(s, 'h', 0, 7));
	Pval(find(s, 'h', 0, 5));

	Pval(s.find('b'));
	s[1] = '\0';
	Pval(s.find('d', 2));
	Pval(s.find('d', 0));
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
