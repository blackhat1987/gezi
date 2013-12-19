/** 
 *  ==============================================================================
 * 
 *          \file   test_datetime.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2013-12-18 13:25:47.044047
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"

#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

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
    time_duration td1(1, 10, 30, 1000);
    time_duration td2 = hours(1) + minutes(10) + seconds(30) + millisec(1);
    time_duration td3 = duration_from_string("1:10:30:001");
    cout << "td1: " << td1 << endl;
    cout << "td2: " << td2 << endl;
    cout << "td3: " << td3 << endl;
    cout << "hours: " << td3.hours() << "; minutes: " << td3.minutes() << "; seconds: " << td3.seconds() << endl;
    cout << "tota seconds: " << td3.total_seconds() << endl;
    cout << "simple string: " << to_simple_string(td3) << endl;
    cout << "iso string: " << to_iso_string(td3) << endl;

    tm t = to_tm(td3);
    cout << "to tm hours: " << t.tm_hour << "; minutes: " << t.tm_min << "; seconds: " << t.tm_sec << endl;
  }
  cout << "*********************************ptime************************************" << endl;
  {
    ptime p1(date(2013, 8, 4), hours(22));
    cout << "p1: " << p1 << endl;
    ptime p2 = time_from_string("2013-8-4 22:53:00");
    cout << "p2: " << p2 << endl;
    ptime p3 = from_iso_string("20130804T225300");
    cout << "p3: " << p3 << endl;

    //获取当前时间
    ptime p4 = second_clock::local_time();
    cout << "p4: " << p4 << endl;
    ptime p5 = microsec_clock::universal_time();
    cout << "p5: " << p5 << endl;

    cout << "to simple string: " << to_simple_string(p1) << endl;
    cout << "to iso string: " << to_iso_string(p1) << endl;
    cout << "to iso extend string: " << to_iso_extended_string(p1) << endl;

    tm t = to_tm(p1);
    cout << "to tm hours: " << t.tm_hour << "; minutes: " << t.tm_min << "; seconds: " << t.tm_sec << endl;

    ptime p6 = from_time_t(std::time(0));
    cout << "p6: " << p6 << endl;

    ptime p7(date(2013, 8, 4), hours(10));
    for (time_iterator t_iter(p7, minutes(10)); t_iter < p7 + hours(1); ++t_iter)
    {
      cout << *t_iter << endl;
    }
  }
  {
    //1386753192 2013-12-11 17:13:12
    ptime pt = from_time_t(1386753192);
    tm t = to_tm(pt);
    Pval(t.tm_hour); //需要+8
    Pval(t.tm_min);
    
    Pval(discretize(17, 0, 24, 6, false));
    Pval(discretize(0, 0, 24, 6, false));
    Pval(discretize(23, 0, 24, 6, false));
    
    
  }

  system("pause");

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
