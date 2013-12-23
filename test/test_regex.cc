/** 
 *  ==============================================================================
 * 
 *          \file   test_regex.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2013-12-20 13:18:43.518531
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
  string s = "<div class=\"pic_src_wrapper\"><img class=\"BDE_Image\" src=\"http://imgsrc.baidu.com/forum/pic/item/97d8c2177f3e670915c4d58d39c79f3df9dc555e.jpg\" pic_ext=\"gif\"  pic_type=\"2\" height=\"146\" width=\"220\"><span class=\"apc_src_wrapper\">Í¼</span></div><div class=\"pic_src_wrapper\"><img class=\"BDE_Image\" src=\"http://imgsrc.baidu.com/forum/pic/item/f949743e6709c93dad369e859d3df8dcd000545e.jpg\" pic_ext=\"gif\"  pic_type=\"2\" height=\"155\" width=\"191\"><span class=\"apc_src_wrapper\">Í¼</span></div>";
  Pval(s);
  {
    string pattern = "<div (.*?)=";
    Pval(pattern);
    Pval(reg_search(s, pattern));
    Pval(reg_search(s, pattern, 0));
  }
  {
    string pattern = "<img class=\"BDE_Image\" src=\"(.+?)\"";
    Pval(pattern);
    Pval(reg_search(s, pattern));
    Pval(reg_search(s, pattern, 0));
  }
  {
    string pattern = "=\"(.+?)\"";
    Pval(pattern);
    Pval(reg_search(s, pattern));
    Pval(reg_search(s, pattern, 0));
    vector<string> vec;
    reg_search(s, pattern, vec);
    Pvec(vec);
  }
  {
    string pattern = "=\"(.+?)\".*?=\"(.+?)\"";
    Pval(pattern);
    Pval(reg_search(s, pattern));
    Pval(reg_search(s, pattern, 0));
    Pval(reg_search(s, pattern, 2));
    vector<string> vec;
    reg_search(s, pattern, vec);
    Pvec(vec);
    vec.clear();
    reg_search(s, pattern, vec, 2);
    Pvec(vec);
  }
  {
    string line = read_file("./test.data/regex/reg_input.txt");
    Pval(line);
    string pattern = "<img class=\"BDE_Image\" src=\"(.+?)\"";
    Pval(pattern);
    Pval(reg_search(line, pattern));
    Pval(reg_search(line, pattern, 0));
    vector<string> vec;
    reg_search(line, pattern, vec);
    Pvec(vec);
  }
  {
    string line = read_file("./test.data/regex/reg_input.txt");
    Pval(line);
    string pattern = read_file("./test.data/regex/reg_pattern.txt");
    Pval(pattern);
    Pval(reg_search(line, pattern));
    Pval(reg_search(line, pattern, 0));
    vector<string> vec;
    reg_search(line, pattern, vec);
    Pvec(vec);
  }
  
  {
    string line = read_file("./test.data/regex/reg_input.txt");
    Pval(line);
    unordered_map<string, string> m;
    read_map("./test.data/regex/patterns", m);
    string pattern = m["PICTURE"];
    Pval(pattern);
    Pval(reg_search(line, pattern));
    Pval(reg_search(line, pattern, 0));
    vector<string> vec;
    reg_search(line, pattern, vec);
    Pvec(vec);
  }
  {
      string line = "";
      string pattern = "";
      Pval(reg_search(line, pattern));
  }
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
