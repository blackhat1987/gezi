/** 
 *  ==============================================================================
 * 
 *          \file   test_weight_vector.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-06-22 08:15:10.751829
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "Numeric/Vector/WeightVector.h"
using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(weight_vector, func)
{
		WeightVector vec;
		Vector vec2;
		vec.Add(vec2);
		vec.Add(3.0); //explicit Vector(int length_) 没有explicit可能会调用Add vector!

		double x = vec.Value(0);
		Pval(vec.Value(0));
		//vec.Value(0) = 35;
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
