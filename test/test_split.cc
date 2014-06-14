/** 
 *  ==============================================================================
 * 
 *          \file   test_split.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-06-11 11:48:55.130797
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
DEFINE_int32(vl, 0, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(split, func)
{
	{
		string s = "abc|def|";
		svec vec = gezi::reg_split(s, "|");
		Pvec(vec);
	}
	{
		string s = "abc|def|";
		svec vec = gezi::split(s, '|');
		Pvec(vec);
	}
	{
		string s = "abc|def|";
		svec vec = gezi::split(s, "|");
		Pvec(vec);
	}
	{
		string s = "abc|def|";
		svec vec = gezi::splits(s, "|");
		Pvec(vec);
	}
	{
		string s = "abc|def|";
		svec vec = gezi::splits(s, "|", false);
		Pvec(vec);
	}

	{
		string s = "abc";
		svec vec = gezi::split(s, '|');
		Pvec(vec);
	}
	{
		string s = "abc";
		svec vec = gezi::split(s, "|");
		Pvec(vec);
	}
	{
		string s = "abc";
		svec vec = gezi::splits(s, "|");
		Pvec(vec);
	}
	{
		string s = "abc";
		svec vec = gezi::splits(s, "|", false);
		Pvec(vec);
	}


	{
		string s = "";
		svec vec = gezi::split(s, '|');
		Pvec(vec);
	}
	{
		string s = "";
		svec vec = gezi::split(s, "|");
		Pvec(vec);
	}
	{
		string s = "";
		svec vec = gezi::splits(s, "|");
		Pvec(vec);
	}
	{
		string s = "";
		svec vec = gezi::splits(s, "|", false);
		Pvec(vec);
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
