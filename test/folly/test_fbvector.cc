/** 
 *  ==============================================================================
 * 
 *          \file   test_fbvector.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-07-20 11:02:17.262888
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#define USE_FOLLY_VECTOR
#include "common_util.h"
//#include "common_def.h"
//#include "Numeric/find_bins.h"
//#include <gtest/gtest.h> //很奇怪 这里引入了std::vector具体没有查明
#include <gflags/gflags.h>
#include <glog/logging.h>

////using namespace gezi;
//DEFINE_int32(vl, 5, "vlog level");
//DEFINE_string(i, "", "input");
//DEFINE_string(o, "", "output");
//DEFINE_string(type, "simple", "");
//
//TEST(fbvector, func)
//{
//	vector<int> vec;
//	vec.push_back(3);
//	//Pval(vec.size());
//}
//inline int find_distinct_counts(Fvec& values)
//{
//	int numDistinctValues = 1;
//	if (!values.empty())
//	{ //兼容边界条件 value是空的时候 返回1个bin max最大值，median设置为0
//		sort(values.begin(), values.end());
//	}
//
//	return numDistinctValues;
//}
int main(int argc, char *argv[])
{
	//testing::InitGoogleTest(&argc, argv);
	//google::InitGoogleLogging(argv[0]);
	//google::InstallFailureSignalHandler();
	//int s = google::ParseCommandLineFlags(&argc, &argv, false);
	//if (FLAGS_log_dir.empty())
	//	FLAGS_logtostderr = true;
	//if (FLAGS_v == 0)
	//	FLAGS_v = FLAGS_vl;
	//
	//return RUN_ALL_TESTS();

	vector<int> vec;
	vec.push_back(3);
	vec.push_back(2);
	vec.push_back(4);
	sort(vec.begin(), vec.end());
	{
		vector<Float> vec;
		vec.push_back(3.5);
		vec.push_back(2.5);
		vec.push_back(4.5);

		sort(vec.begin(), vec.end());

		//find_distinct_counts(vec);
	}
}
