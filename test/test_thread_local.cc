/**
 *  ==============================================================================
 *
 *          \file   test_thread_local.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-10 07:52:27.756912
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{



}

thread_local int i = 0;

void f(int newval){
	i = newval;
}

void g(){
	std::cout << i;
}

void threadfunc(int id)
{
	f(id);
	++i;
	g();
}

TEST(thread_local, func)
{
	i = 9;
	std::thread t1(threadfunc, 1);
	std::thread t2(threadfunc, 2);
	std::thread t3(threadfunc, 3);

	t1.join();
	t2.join();
	t3.join();
	std::cout << i << std::endl;
}

class SharedAnyMap
{
public:
	static AnyMap& Instance()
	{
		static thread_local AnyMap _map;
		return _map;
	}
};

void threadfunc2(int id)
{
	SharedAnyMap::Instance()["abc"] = id;
	Pval(any_cast<int>(SharedAnyMap::Instance()["abc"]));
}

TEST(shared_anymap, func)
{
	std::thread t1(threadfunc2, 1);
	std::thread t2(threadfunc2, 2);
	std::thread t3(threadfunc2, 3);

	t1.join();
	t2.join();
	t3.join();
}

class SharedAnyMap2
{

public:
	static AnyMap& Instance()
	{
		static AnyMap _map;
		return _map;
	}
};

void threadfunc3(int id)
{
	SharedAnyMap2::Instance()["abc"] = id;
	Pval(any_cast<int>(SharedAnyMap2::Instance()["abc"]));
}

TEST(shared_anymap_global, func)
{
	std::thread t1(threadfunc3, 1);
	std::thread t2(threadfunc3, 2);
	std::thread t3(threadfunc3, 3);

	t1.join();
	t2.join();
	t3.join();
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
