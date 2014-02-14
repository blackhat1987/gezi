/**
 *  ==============================================================================
 *
 *          \file   test_bins.cc
 *
 *        \author   chenghuige
 *
 *          \date   2013-12-16 14:44:52.767163
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"

using namespace std;
using namespace gezi;

DEFINE_int32(logv, 16, "16 debug, 8 trace, 4 online");
DEFINE_string(logdir, "./log", "");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");
void run()
{
	{
		int a;
		{
			stringstream s;
			s << "0.0";
			s >> a;
		}
		Pval(a);
	}
	Pval(INT("0.0"));
	Pval(UINT64("43820119745.0"));
	char out[2 * 10];
	memset(out, 0, sizeof (out));
	Pval(sizeof(out));

	vector<double> vec;
	to_vec("0.1,0.1,0.3,0.3,0.2,0.4,0.05,0.8,0.7,1.0,0.5,0.6", vec);
	vector<double> thres;
	to_vec("0.3,0.5,0.7", thres);
	vector<int> bins = bin_counts(vec, thres);
	Pvec(bins);
	vector<double> binvalues = bin_values(vec, thres);
	Pvec(binvalues);
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
