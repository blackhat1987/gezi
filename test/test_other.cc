/**
 *  ==============================================================================
 *
 *          \file   test_other.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-07 15:48:44.608755
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "convert_type.h"
#include "common_util.h"
#include "feature/Feature.h"
#include "feature/feature_util.h"
#include "tieba/util.h"

using namespace std;
using namespace gezi;

DEFINE_int32(logv, 4, "16 debug, 8 trace, 4 online");
DEFINE_string(logdir, "./log", "");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

void write_a(ostream& s)
{
	cout << "ostream" << endl;
	s << "ostream" << endl;
}

void write_a(string s)
{
	cout << "string" << endl;
}

struct Node
{
	int a;
	int b;
};
void run()
{
	Pval(is_thread("回复：昆明这种情况要是发生在东北  是不是暴徒就被百姓歼灭了"));
	Pval(is_thread("昆明这种情况要是发生在东北  是不是暴徒就被百姓歼灭了"));
	Pval((get_real_title("回复：昆明这种情况要是发生在东北  是不是暴徒就被百姓歼灭了")));
	Pval(get_real_title("昆明这种情况要是发生在东北  是不是暴徒就被百姓歼灭了"));
	vector<Node> vec;
	Pval(distinct_count(vec, [](const Node& a) { return a.a; }));

	write_a("abc");
	ofstream ofs("abc");
	write_a(ofs);

	Feature fv;

	write_header(fv, "def");
	write_header(fv, ofs);

	Pval((0.0000000001 == 0));
	double val = 0.0;
	Pval((val == 0));
}

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	FLAGS_log_dir = FLAGS_logdir;
	if (FLAGS_logv >= 4)
	{
		FLAGS_stderrthreshold = 0;
	}
	//  LogHelper log_helper(FLAGS_logv);
	LogHelper::set_level(FLAGS_logv);

	run();

	return 0;
}
