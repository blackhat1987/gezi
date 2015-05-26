/** 
 *  ==============================================================================
 * 
 *          \file   test_derive_override.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-05-23 19:20:16.973364
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

class Base
{
public:
	virtual void print()
	{
		VLOG(0) << "Base";
	}
};

class A : public Base
{
public:
	//virtual void print()
	//{
	//	VLOG(0) << "A";
	//}
	using Base::print;
	virtual void print(int a, int b)
	{
		VLOG(0) << "a + b = " << a + b;
		//print() //can not find A::pirnt()
		//Base::print();
		print();
	}
};

class B : public A
{
public:
	virtual void print()
	{
		VLOG(0) << "B";
	}
	virtual void print(int a, int b)
	{
		VLOG(0) << "a * b = " << a * b;
		print();
	}
};

TEST(derive_override, func)
{
	shared_ptr<Base> a = make_shared<A>();
	shared_ptr<Base> b = make_shared<B>();
	(a->print());
	(b->print());
	
	if (IS_POINTER_TYPE_OF(a, A))
	{
		dynamic_pointer_cast<A>(a)->print(1, 2);
	}
	if (IS_POINTER_TYPE_OF(b, A))
	{
		dynamic_pointer_cast<A>(b)->print(1, 2);
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
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;
	
	return RUN_ALL_TESTS();
}
