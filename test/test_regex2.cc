/** 
 *  ==============================================================================
 * 
 *          \file   test_regex2.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2013-12-20 20:54:06.029112
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
DEFINE_int32(level, 0, "min log level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(test_regex2, func)
{
  setlocale(LC_ALL, "zh_CN.GB18030");
  //setlocale(LC_ALL, "zh_CN.GB2312");
  string content = read_file("./test.data/regex/video.txt");
  //string pattern = "(�ظ�[^:]{2,40}:)|([ͼƬ|����|��Ƶ]����.{1,3}<a href[^<]*</a>) ";
  {
    string pattern = "(��Ƶ����.{1,3}<a href[^<]*</a>)";
    Pval(content);
    Pval(pattern);
    Pval(reg_remove(content, pattern));
    Pval(to_str(reg_remove(to_wstr(content), to_wstr(pattern))));
    Pval(reg_search(content, pattern));
  }
  {
    string pattern = "([ͼƬ|����|��Ƶ]����.{1,3}<a href[^<]*</a>)";
    Pval(content);
    Pval(pattern);
    Pval(reg_remove(content, pattern));
    Pval(to_str(reg_remove(to_wstr(content), to_wstr(pattern))));
    Pval(reg_search(content, pattern));
    Pval(to_str(to_wstr(pattern)));
    Pval(to_str(reg_search(to_wstr(content), to_wstr(pattern))));
  }
  {
    string pattern = "([��Ƶ����|ͼƬ����].{1,3}<a href[^<]*</a>)";
    Pval(content);
    Pval(pattern);
    Pval(reg_remove(content, pattern));
    Pval(to_str(reg_remove(to_wstr(content), to_wstr(pattern))));
    Pval(reg_search(content, pattern));
    Pval(to_str(to_wstr(pattern)));
    Pval(to_str(reg_search(to_wstr(content), to_wstr(pattern))));
  }
  {
    string pattern = "(��Ƶ����.{1,3}<a href[^<]*</a>|ͼƬ����.{1,3}<a href[^<]*</a>)";
    Pval(content);
    Pval(pattern);
    Pval(reg_remove(content, pattern));
    Pval(to_str(reg_remove(to_wstr(content), to_wstr(pattern))));
    Pval(reg_search(content, pattern));
    Pval(to_str(to_wstr(pattern)));
    Pval(to_str(reg_search(to_wstr(content), to_wstr(pattern))));
  }
  {
    string content = "���㷨�ɿ�һ��";
    string pattern = "(��.*?��)";
    Pval(content);
    Pval(pattern);
    Pval(reg_remove(content, pattern));
    Pval(to_str(reg_remove(to_wstr(content), to_wstr(pattern))));
    Pval(reg_search(content, pattern));
    Pval(to_str(to_wstr(pattern)));
    Pval(to_str(reg_search(to_wstr(content), to_wstr(pattern))));
  }
  {
    string content = "5һ��34����8?";
    string pattern = "[\\d|��|һ|��|��|��|��|��|��|��|��]{5,10}";
    Pval(content);
    Pval(pattern);
    Pval(reg_remove(content, pattern));
    Pval(to_str(reg_remove(to_wstr(content), to_wstr(pattern))));
    Pval(reg_search(content, pattern, 0));
    Pval(to_str(to_wstr(pattern)));
    Pval(to_str(reg_search(to_wstr(content), to_wstr(pattern), 0)));
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
