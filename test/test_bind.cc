/**
 *  ==============================================================================
 *
 *          \file   test_bind.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-02 17:42:20.788376
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
DEFINE_int32(vl, 0, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void show(const string& a, const string& b, const string& c)
{
	cout << a << "; " << b << "; " << c << endl;
}

void show2(const string& a, const string& b, const string& c)
{
	cout << a << "; " << b << "; " << c << endl;
}

void show2(const int& a, const int& b, const int& c)
{
	cout << a << "; " << b << "; " << c << endl;
}

void show_show(const string& a, const string& b, const string& c = "def")
{
	cout << a << "; " << b << "; " << c << endl;
}

TEST(bind, func)
{
	auto x = bind(show, _1, _2, _3);
	auto y = bind(show, _3, _1, _2);
	auto z = bind(show, "hello", _2, _1);

	x("one", "two", "three");
	y("one", "two", "three");
	z("one", "two");
}

//默认参数处理,不成功
//TEST(bind_default, func)
//{
//	auto x = bind(show_show, _1, _2, _3);
//	auto y = bind(show_show, _3, _1, _2);
//	auto z = bind(show_show, "hello", _2, _1);
//
//	auto u = bind(show_show, _2, _1);
//
//	x("one", "two", "three");
//	y("one", "two", "three");
//	z("one", "two");
//	u("one", "two"); // error: too few arguments to function typename add_cv<_Functor>::type > ::type > ()(
//}

//默认参数处理 lambda http://stackoverflow.com/questions/17998635/bind-to-overloaded-method-using-boostfunction
//1 - You can overload foo() and have it call the original with defaults :
//void foo(int a, int b)
//{
//	std::cout << a << " " << b << std::endl;
//}
//inline void foo(int a)
//{
//	foo(a, 23);
//}
//auto g = [] (){ foo( 23 ); };
TEST(lambda, func)
{
	auto u = [](const string& a, const string& b){ show_show(a, b); };
	u("one", "two");
}

//  auto a1 = std::bind(static_cast<void(Client::*)(void)>(&Client::foobar),cl); 对于类成员函数重载的情况
TEST(bind_overloading, func)
{
	auto x = bind((void(*)(const string&, const string&, const string&))show2, _1, _2, _3);
	auto y = bind((void(*)(const string&, const string&, const string&))show2, _3, _1, _2);
	auto z = bind((void(*)(const string&, const string&, const string&))show2, "hello", _2, _1);

	x("one", "two", "three");
	y("one", "two", "three");
	z("one", "two");
}

TEST(bind_using, func)
{
	using FunctionPtr = void(*)(const string&, const string&, const string&);
	auto x = bind((FunctionPtr)show2, _1, _2, _3);
	auto y = bind((FunctionPtr)show2, _3, _1, _2);
	auto z = bind((FunctionPtr)show2, "hello", _2, _1);

	x("one", "two", "three");
	y("one", "two", "three");
	z("one", "two");
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
