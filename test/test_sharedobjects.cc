/** 
 *  ==============================================================================
 * 
 *          \file   test_sharedobjects.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-19 15:55:44.474421
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "RegexSearcher.h"
using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

struct Node
{
	Node() = default;
	virtual ~Node()
	{
		VLOG(0) << "Free Node";
	}
	Node(int age_)
	:age(age_)
	{
		VLOG(0) << "Create Node";
	}
	int age = 32;
};
struct Demo
{
	Demo()
	{

	}
	static RegexSearcher& blackRegSearcher()
	{
		string blackPatternFile = "./data/wordlist/black.pattern";
		return SharedObjects<RegexSearcher>::Instance(blackPatternFile);
	}

	operator ()(int x)
	{
		Node* _info = info(x);
		Pval(_info->age);
		free();
	}
	static Node* info(int x = 123)
	{
		static thread_local Node* _info = NULL;
		if (_info == NULL)
		{
			_info = new Node(x);
		}
		
		return _info;
	}

	static void free()
	{
		Node* _info = info();
		if (_info)
		{
			delete _info;
		}
	}
	//Node* _info = info();

	void Show()
	{
		Pval(_searcher.reg_count());
	}

	RegexSearcher& _searcher = blackRegSearcher();
};

void run()
{
	Demo demo;
	demo.Show();

	std::thread threads[2];
	int i = 0;
	for (auto& thread : threads)
	{
		thread = std::thread(Demo(), i++);
	}
	
	for (auto& thread : threads)
	{
		thread.join();
	}

	//Demo::free();
}

TEST(sharedobjects, func)
{
	run();
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
