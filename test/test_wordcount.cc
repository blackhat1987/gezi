/** 
 *  ==============================================================================
 * 
 *          \file   test_vocabulary.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2016-09-24 22:51:26.996104
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "nlp/WordCounter.h"

using namespace std;
using namespace gezi;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf,false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "./test.data/vocab.bin", "input file");
DEFINE_string(o, "", "output file");

void run()
{
    WordCounter counter(2);

    counter.add("a", 10);
    counter.add("b", 20);
    counter.add("c", 5);
    counter.add("<TotalCount>", 1000);

    cout << "done add";
    counter.save_text("/tmp/vocab.txt");
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
