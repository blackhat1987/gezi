/**
 *  ==============================================================================
 *
 *          \file   test_derive.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-05-21 15:01:54.463482
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
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

class IBase
{
public:
	virtual void eval() = 0;
	virtual void speed_virtual() = 0;
	virtual void speed_template() = 0;
	virtual void speed_function() = 0;
};

template<typename Derived>
class Base : public IBase
{
public:
	virtual void eval() override
	{
		deal();
		func();
		Derived::func();
		_func();
		/*	using Derived::func2;
			func2();*/
		//(Derived)(*this).func2();
		func2();
                static_cast<Derived*>(this)->func2();
	}

	virtual void deal()
	{
		VLOG(0) << "base deal";
	}

	static void func()
	{
		VLOG(0) << "base func";
	}

	void func2()
	{
		VLOG(0) << "base func2";
	}

	virtual void speed_virtual() override
	{
		for (size_t i = 0; i < 10000000; i++)
		{
			deal();
		}
	}

	virtual void speed_template() override
	{
		for (size_t i = 0; i < 10000000; i++)
		{
			Derived::func();
		}
	}

	virtual void speed_function()
	{
		for (size_t i = 0; i < 10000000; i++)
		{
			_func();
		}
	}

	std::function<void()> _func;
};

class A : public Base < A >
{
public:
	A()
	{
		_func = A::func;
	}
	virtual void deal()
	{
		VLOG(0) << "A deal";
	}

	static void func()
	{
		VLOG(0) << "A func";
	}

	void func2()
	{
		VLOG(0) << "A func2";
	}
};


class B : public Base < B >
{
public:
	B()
	{
		_func = B::func;
	}
	virtual void deal()
	{
		VLOG(0) << "B deal";
	}

	static void func()
	{
		VLOG(0) << "B func";
	}

	void func2()
	{
		VLOG(0) << "B func2";
	}
};

void run()
{
	shared_ptr<IBase> a = make_shared<A>();
	shared_ptr<IBase> b = make_shared<B>();
	a->eval();
	b->eval();
}

void run_perf()
{
	FLAGS_v = -1;
	shared_ptr<IBase> a = make_shared<A>();
	shared_ptr<IBase> b = make_shared<B>();
	{
		Notifer nt("std::function", -1);
		a->speed_function();
		b->speed_function();
	}
				{
					Notifer nt("virutal", -1);
					a->speed_virtual();
					b->speed_virtual();
				}
	{
		Notifer nt("template", -1);
		a->speed_template();
		b->speed_template();
	}
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

	run_perf();

	return 0;
}
