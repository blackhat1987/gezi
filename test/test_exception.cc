/** 
 *  ==============================================================================
 * 
 *          \file   test_exception.cc
 *
 *        \author   gezi   
 *
 *          \date   2014-02-17 15:01:25.020289
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "Exception.h"
using namespace std;
using namespace gezi;

DEFINE_string(type, "simple", "");

void play()
{
	THROW("fail in play");
}
TEST(test_exception, catch)
{
	try
	{
		play();
	}
	catch (Exception e)
	{
		THROW(e.what());
	}
}

TEST(test_exception, func)
{
	THROW("fail here");
}

int main(int argc, char *argv[])
{
  FLAGS_logtostderr = true;
  testing::InitGoogleTest(&argc, argv); 
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  int s = google::ParseCommandLineFlags(&argc, &argv, false);
  boost::progress_timer timer;
  return RUN_ALL_TESTS();
}
