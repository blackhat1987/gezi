/** 
 *  ==============================================================================
 * 
 *          \file   test_static_thread_safe.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-10-09 22:37:55.236080
 *  
 *  \Description:
 [chenghuige@cp01-rdqa-pool405.cp01.baidu.com test]$ ./test_static_thread_safe -nt 10000 &> temp
 [chenghuige@cp01-rdqa-pool405.cp01.baidu.com test]$ vi temp
 [chenghuige@cp01-rdqa-pool405.cp01.baidu.com test]$ grep cons temp
 I1009 22:57:46.475589 12784 test_static_thread_safe.cc:39] construct
 [chenghuige@cp01-rdqa-pool405.cp01.baidu.com test]$ grep get temp
 I1009 22:57:46.475569 12323 test_static_thread_safe.cc:51] get data
 [chenghuige@cp01-rdqa-pool405.cp01.baidu.com test]$ grep Deal4 temp
 I1009 22:57:46.475714 12784 test_static_thread_safe.cc:87] Deal4: 3
 I1009 22:57:46.475720 12739 test_static_thread_safe.cc:87] Deal4: 4
 I1009 22:57:46.475713 12741 test_static_thread_safe.cc:87] Deal4: 2
 I1009 22:57:46.475704 12776 test_static_thread_safe.cc:87] Deal4: 1
 [chenghuige@cp01-rdqa-pool405.cp01.baidu.com test]$ grep Deal5 temp
 I1009 22:57:46.475729 12813 test_static_thread_safe.cc:104] Deal5: 2
 I1009 22:57:46.475730 12739 test_static_thread_safe.cc:104] Deal5: 3
 I1009 22:57:46.475723 12784 test_static_thread_safe.cc:104] Deal5: 1
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
DEFINE_int32(nt, 12, "thread num");

void run()
{

}

struct Data
{
	Data() = default;
	Data(int x_)
		:x(x_)
	{
		VLOG(0) << "construct";
	}
	Data& operator = (const Data& other)
	{
		x = other.x;
		VLOG(0) << "operator =";
	}
	void Load(string path_)
	{
		path = path_;
		Pval(path);
	}

	static Data Load2(string path2)
	{
		Pval(path2);
		return Data();
	}

	int x = 0;
	string path;
};

Data get_data()
{
	VLOG(0) << "get data";
	Data a;
	a.x = 5;
	return a;
}

struct SharedObj
{
	static Data& Instance()
	{
		static Data data = get_data();
		return data;
	}

	static Data& Instance2()
	{
		static Data data(125);
		return data;
	}

	static void Deal(Data& data)
	{
		data.x++;
		Pval(data.x);
	}

	static Data& Instance3()
	{
		static Data data;
		Deal(data);
		return data;
	}

	static void Deal4(Data& data)
	{
		data.x++;
		VLOG(4) << "Deal4: " << data.x;
	}
	static Data& Instance4()
	{
		static Data data;
		static bool isInited = false;
		if (!isInited)
		{
			Deal4(data);
			isInited = true;
		}
		return data;
	}

	static void Deal5(Data& data)
	{
		data.x++;
		VLOG(4) << "Deal5: " << data.x;
	}
	static Data& Instance5()
	{
		static Data data;
		if (!isInited())
		{
			Deal5(data);
			isInited() = true;
		}
		return data;
	}

	static bool& isInited()
	{
		static bool _isInited = false;
		return _isInited;
	}

	static bool DoInit()
	{
		VLOG(0) << "DoInit";
		return true;
	}

	static bool Init()
	{
		static bool ret = DoInit();
		return ret;
	}

	static map<string, Data>& MapInstance()
	{
		static map<string, Data> _identifers;
		return _identifers;
	}
	static Data& ConstructInstance(string path)
	{
		VLOG(0) << "ConstructInstance";
		map<string, Data>& _identifers = MapInstance();
		auto iter = _identifers.find(path);
		if (iter != _identifers.end())
		{
			return iter->second;
		}
		else
		{
			auto& identifer = _identifers[path];
			identifer.Load(path);
			return identifer;
		}
	}
	static Data& Instance(string path)
	{
		static Data identifer = ConstructInstance(path);
		return identifer;
	}
	static Data& Instance2(string modelPath)
	{
		static map<string, Data> _predictors;
		auto iter = _predictors.find(modelPath);
		if (iter != _predictors.end())
		{
			return iter->second;
		}
		else
		{
			return _predictors[modelPath] = Data::Load2(modelPath);
		}
	}
	
};

TEST(static_thread_safe, func)
{
	omp_set_num_threads(FLAGS_nt);
#pragma omp parallel for
	for (size_t i = 0; i < 1000; i++)
	{
		//Pval(i);
		SharedObj::Instance3();
		SharedObj::Instance();
		SharedObj::Instance2();
		SharedObj::Instance4();
		SharedObj::Instance5();
		SharedObj::Init();
		SharedObj::Instance("kobe");
		SharedObj::Instance("jordan");
		SharedObj::Instance("kobe");

		SharedObj::Instance2("meixi");
		SharedObj::Instance2("ronaldo");
	}
}

TEST(static_thread_safe2, func)
{
	omp_set_num_threads(FLAGS_nt);
	mutex m;
#pragma omp parallel for
	for (size_t i = 0; i < 1000; i++)
	{
		{
			//mutex m; //放在这里就是线程内部的没有意义了
			lock_guard<mutex> lk(m);
			SharedObj::Instance2("ms");
			SharedObj::Instance2("baidu");
		}
	}
#pragma omp parallel for
	for (size_t i = 0; i < 1000; i++)
	{
		SharedObj::Instance2("ms");
		SharedObj::Instance2("baidu");
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
