/**
 *  ==============================================================================
 *
 *          \file   test_cached_fetcher.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-02 14:35:11.001635
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "other/CachedFetcher.h"
#include "tieba/get_parsed_info.h"
#include "container/LruMap.h"

using namespace std;
using namespace gezi;
using namespace gezi::tieba;
DEFINE_int32(vl, 0, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

CachedFetcher<uint64, tieba::ThreadInfo> _threadsFetcher;

TEST(get_threads_info, func)
{
	vector<uint64> tids = { 3271207055, 3271195189, 3271162283, 3271167101, 3271241387 };
	vector<tieba::ThreadInfo> tidInfos = tieba::get_threads_info(tids, true);
	PrintVec2(tidInfos, title, content);
}

//注意参考test_bind.cc 对于重载需要特殊处理，对于默认参数 都要强制写全
TEST(bind, func)
{
	vector<uint64> tids = { 3271207055, 3271195189, 3271162283, 3271167101, 3271241387 };
	using FuncPtr = vector<ThreadInfo>(*)(const vector<uint64>&, bool, bool);
	auto func = bind((FuncPtr)tieba::get_threads_info, _1, true, false);
	auto tidInfos = func(tids);
	PrintVec2(tidInfos, title, content);
}

//似乎这种有重载的 用lambda最方便
TEST(lambda, func)
{
	vector<uint64> tids = { 3271207055, 3271195189, 3271162283, 3271167101, 3271241387 };
	auto func = [](const vector<uint64>& tids) { return tieba::get_threads_info(tids, true); };
	auto tidInfos = func(tids);
	PrintVec2(tidInfos, title, content);
}

TEST(cached_fetcher, func)
{
	vector<uint64> tids = { 3271207055, 3271195189, 3271162283 };
	Pval(_threadsFetcher.CacheSize());
	using FuncPtr = vector<ThreadInfo>(*)(const vector<uint64>&, bool, bool);
	auto tidInfos = _threadsFetcher.GetValues(tids, bind((FuncPtr)tieba::get_threads_info, _1, true, false));
	PrintVec2(tidInfos, title, content);
	Pval(_threadsFetcher.CacheSize());
}

TEST(cached_fetcher, perf)
{
	vector<uint64> tids = { 3271207055, 3271195189, 3271162283 };
	Pval(_threadsFetcher.CacheSize());
	auto func = [](const vector<uint64>& tids) { return tieba::get_threads_info(tids, true); };
	auto tidInfos = _threadsFetcher.GetValues(tids, func);
	PrintVec2(tidInfos, title, content);
	Pval(_threadsFetcher.CacheSize());
}

TEST(cached_fetcher, perf2)
{
	vector<uint64> tids = { 3271207055, 3271195189, 3271162283, 3271167101, 3271241387 };
	Pval(_threadsFetcher.CacheSize());
	auto tidInfos = _threadsFetcher.GetValues(tids, [](const vector<uint64>& tids) { return tieba::get_threads_info(tids, true); });
	PrintVec2(tidInfos, title, content);
	Pval(_threadsFetcher.CacheSize());
}

class Worker
{
public:
	void Init()
	{
		_func = [](const vector<uint64>& tids) { return tieba::get_threads_info(tids, true); };
	}
	void Run()
	{
		vector<uint64> tids = { 3271207055, 3271195189, 3271162283, 3271167101, 3271241387 };
		auto tidInfos = _threadsFetcher.GetValues(tids, _func);
		PrintVec2(tidInfos, title, content);
		Pval(_threadsFetcher.CacheSize());
	}
private:
	std::function<vector<ThreadInfo>(const vector<uint64>&)> _func;
};

TEST(worker, func)
{
	Worker worker;
	worker.Init();
	worker.Run();
}

class Worker2
{
public:
	void Init()
	{
		_func = [this](const vector<uint64>& tids) { _count++;  return tieba::get_threads_info(tids, true); };
	}
	void Run()
	{
		vector<uint64> tids = { 3271207055, 3271195189, 3271162283, 3271167101, 3271241387 };
		Pval(_count);
		auto tidInfos = _threadsFetcher.GetValues(tids, _func);
		PrintVec2(tidInfos, title, content);
		Pval(_threadsFetcher.CacheSize());
		Pval(_count);
	}
private:
	std::function<vector<ThreadInfo>(const vector<uint64>&)> _func;
	int _count = 0;
};

TEST(worker2, func)
{
	Worker2 worker;
	worker.Init();
	worker.Run();
}

bool cmp(int a, int b)
{
	return a < b;
}

//Usually the function object causes faster code than the function pointer, because compilers often cannot inline calls made through function pointers, while the operator()() member function of the function object can easily be inlined.–  sbi Jun 9 '10 at 6:55
//
//@Heath: Using global variables is what got us into the mess prompting someone to invent an OO version of good old C.
//The main practical difference is the ability for a functor to maintain state.For example, sorting multi - column data the functor can have info on which column to sort by, the sort direction and even collation rules(case sensitivity etc.).
//http://www.cnblogs.com/rocketfan/archive/2010/12/28/1918529.html
//但是使用函数 c++11传递 也完全可以解决这个问题 利用类的成员函数 bind 或者利用传递lamba 当然Functor也是一种做法 看哪个比较方便吧。。 有时候懒得单独写一个Functor 很多时候bind lambda更灵活
TEST(sort, func)
{
	vector<int> vec = { 3, 2, 1 };
	sort(vec.begin(), vec.end(), cmp);
	Pvec(vec);
}

//#include <functional>
//#include <iostream>
//class Client
//{
//public:
//	void foobar(){ std::cout << "no argument" << std::endl; }
//	void foobar(int){ std::cout << "int argument" << std::endl; }
//	void foobar(double){ std::cout << "double argument" << std::endl; }
//};
//
//int main()
//{
//	Client cl;
//	//! This works 
//	auto a1 = std::bind(static_cast<void(Client::*)(void)>(&Client::foobar), cl);
//	a1();
//	//! This does not
//	auto a2 = [&](int)
//	{
//		std::bind(static_cast<void(Client::*)(int)>(&Client::foobar), cl);
//	};
//	a2(5);
//	return 0;
//}
//You need to use placeholders for the unbound arguments :
//
//auto a2 = std::bind(static_cast<void(Client::*)(int)>(&Client::foobar), cl,
//	std::placeholders::_1);
//a2(5);
//You can also perform the binding with a lambda capture(note that this is binds cl by reference, not by value) :
//
//auto a2 = [&](int i) { cl.foobar(i); };
//share | improve this answer
//answered Oct 25 '12 at 8:46
//
//ecatmur
//61k869137
//
//Thanks ecatmur, it works.–  Atul Oct 25 '12 at 8:56
//
//And the by - value capture can be done with[&, i] or[=, &cl].–  Xeo Oct 26 '12 at 2:50

//Func func;
//func(1);
//cout << "func.a: " << func.a << endl;   //1
//sort(boost::bind<void>(boost::ref(func), _1));
//cout << "func.a: " << func.a << endl;  //4    //状态改变了，我们传递的是引用~
//我这里举得如何functor 传递引用 改变自身状态 因为sort最后是传值的 另外的方案就是使用lambda..
struct Func
{
	int count = 0;
	bool operator()(int a, int b)
	{
		count++;
		return a < b;
	}
	bool cmp(int a, int b)
	{
		count++;
		return a < b;
	}
};
//lambda最灵活 有的时候写起来麻烦点而已
TEST(sort_ref, func)
{
	{
		vector<int> vec = { 3, 2, 1 };
		Func func;
		sort(vec.begin(), vec.end(), func);
		Pval(func.count);
		Pvec(vec);
	}
	{
	vector<int> vec = { 3, 2, 1 };
	sort(vec.begin(), vec.end(), Func());
	Pvec(vec);
}
	/// functional:485 : 10 : error : declared here
	//	void ref(const _Tp&&) = delete;
	//	test_cached_fetcher.cc:238 : 44 : error : invalid use of void expression
		/*{
			vector<int> vec = { 3, 2, 1 };
			sort(vec.begin(), vec.end(), ref(Func()));
			Pvec(vec);
		}*/
	{
	vector<int> vec = { 3, 2, 1 };
	Func func;
	sort(vec.begin(), vec.end(), ref(func));
	Pval(func.count);
	Pvec(vec);
}
	{
		vector<int> vec = { 3, 2, 1 };
		Func func; //lambda必须const int& &是不可少的...
		sort(vec.begin(), vec.end(), [&func](const int& a, const int& b) { return func(a, b); });
		Pval(func.count);
		Pvec(vec);
	}
	{
		vector<int> vec = { 3, 2, 1 };
		Func func;
		sort(vec.begin(), vec.end(), bind(&Func::cmp, func, _1, _2));
		Pval(func.count);
		Pvec(vec);
	}
	{
		{
			vector<int> vec = { 3, 2, 1 };
			sort(vec.begin(), vec.end(), bind(&Func::cmp, Func(), _1, _2));
			Pvec(vec);
		}
	}
	{
		vector<int> vec = { 3, 2, 1 };
		Func func;
		
		//--ok  count = 2
		//auto func2 = bind(&Func::cmp, ref(func), _1, _2); 
		//sort(vec.begin(), vec.end(), ref(func2));

		//---ok count = 2  不管sort( ref(func2))还是sort(func2)都能改变count值
		//auto func2 = bind(&Func::cmp, ref(func), _1, _2);
		//sort(vec.begin(), vec.end(), func2);
		sort(vec.begin(), vec.end(), bind(&Func::cmp, ref(func), _1, _2)); 
		Pval(func.count);
		Pvec(vec);
	}
}

CachedFetcher<uint64, tieba::ThreadInfo, LruHashMap> _threadsFetcher2;
TEST(lrumap, func)
{
	_threadsFetcher2.set_capacity(1024);
	vector<uint64> tids = { 3271207055, 3271195189, 3271162283, 3271167101, 3271241387};
	auto func = [](const vector<uint64>& tids) { return tieba::get_threads_info(tids, true); };
	auto tidInfos = _threadsFetcher2.GetValues(tids, func);
	PrintVec2(tidInfos, title, content);
	Pval(_threadsFetcher2.CacheSize());
}
TEST(lrumap, perf)
{
	vector<uint64> tids = { 3271207055, 3271195189, 3271162283, 3271167101, 3271241387 };
	auto func = [](const vector<uint64>& tids) { return tieba::get_threads_info(tids, true); };
	auto tidInfos = _threadsFetcher2.GetValues(tids, func);
	PrintVec2(tidInfos, title, content);
	Pval(_threadsFetcher2.CacheSize());
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
