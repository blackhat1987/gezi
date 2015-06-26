/** 
 *  ==============================================================================
 * 
 *          \file   test_enum.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-06-24 10:32:54.826494
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

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf,false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

class Test
{
    public:
        enum IdTypes { NullId = -1, };
};

void run()
{
    Pval(Test::NullId);
}

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();
    google::SetVersionString(get_version());
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
