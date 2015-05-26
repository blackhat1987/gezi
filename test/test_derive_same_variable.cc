/** 
 *  ==============================================================================
 * 
 *          \file   test_derive_same_variable.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-05-25 14:14:32.004825
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "serialize_util.h"
using namespace std;
using namespace gezi;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf,false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

class A
{
public:
	double _x;
};

class B : public A
{
public:
	A ToOnline()
	{
		A::_x = _x + 0.5;
		return *this;
	}
	int _x =  3;
};

void run()
{
	B b;
	Pval(b._x);
	//b.ToOnline();
	//Pval(dynamic_cast<A>(B)._x);
	A a = b.ToOnline();
	Pval(a._x);
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
