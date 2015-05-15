/** 
 *  ==============================================================================
 * 
 *          \file   vector_simple.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-05-12 16:35:23.229498
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "Numeric/Vector/Vector.h"

using namespace std;
using namespace gezi;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf,false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

void run()
{
	Vector A{ 1, 2, 3, 4};
	Pval(A.IsDense());
	Pval(A.DenseStr());
	{
		Vector B("1:3,3:2.5", 0, 100);
		Pval(B.Str());
		Pval(B.IsDense());
	}
	Vector B("1:3,3:2.5", 0, 4);
	Vector C = A + B;
	Pval(C.DenseStr());
}

int main(int argc, char *argv[])
{
		google::InitGoogleLogging(argv[0]);
		google::InstallFailureSignalHandler();
		int s = google::ParseCommandLineFlags(&argc, &argv, false);
		if (FLAGS_log_dir.empty())
				FLAGS_logtostderr = true;
		FLAGS_minloglevel = FLAGS_level;
		//LogHelper::set_level(FLAGS_level);
		if (FLAGS_v == 0)
				FLAGS_v = FLAGS_vl;

		run();

	 return 0;
}
