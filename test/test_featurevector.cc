/** 
 *  ==============================================================================
 * 
 *          \file   test_featurevector.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-04-10 14:27:39.544342
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "feature/FeatureVector.h"
using namespace std;
using namespace gezi;
DEFINE_int32(level, 0, "min log level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(featurevector, func)
{
	FeatureVector fv(5);
	fv.Add(1, 3);
	fv.Add(3, 4);
	Pval(fv[1]); // 3 or 4 ?
}


void show(Vector& fv)
{
	Pval(fv[1]);
}
TEST(featurevector2, func)
{
	{
		VectorPtr fv = make_shared<FeatureVector>(10);
		fv->Add(1, 3);
		fv->Add(3, 4);
		show(*fv);
	}
	{
		FeatureVectorPtr fv = make_shared<FeatureVector>(10);
		fv->Add(1, 3);
		fv->Add(3, 4);
		show(*fv);
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
  FLAGS_minloglevel = FLAGS_level;
  boost::progress_timer timer;
  
  return RUN_ALL_TESTS();
}
