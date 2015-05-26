/** 
 *  ==============================================================================
 * 
 *          \file   test_shared_ptr.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-03-31 11:13:50.654108
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

struct Node
{
	//实验用share ptr 基类不用vitrual 析构 也表现正常 Node2会调用自己和父类析构
	virtual ~Node()
	{
		LOG(INFO) << "~";
	}
	int x = 2014;

	virtual void print()
	{
		LOG(INFO) << "In Node";
	}
};

struct Node2 : public Node
{
	~Node2()
	{
		LOG(INFO) << "2~";
	}
	virtual void print()
	{
		LOG(INFO) << "In Node2";
	}
};

void print(Node* node)
{
	LOG(INFO) << "**";
	node->print();
	Pval(node->x);
}

void print(const shared_ptr<Node>& node)
{
	LOG(INFO) << "!!";
	node->print();
	Pval(node->x);
}

void print(const Node& node)
{
	LOG(INFO) << "&&";
	node.print();
	Pval(node.x);
}

TEST(test_shared_ptr, func)
{
	{
		shared_ptr<Node> node = make_shared<Node>();
		print(node);
		print(node);
		print(node.get());
		print(*node);
	}
	{
		shared_ptr<Node2> node = make_shared<Node2>();
		print(node);
		print(node);
		print(node.get());
		print(*node);
	}
}

void play(vector<int>*& vec)
{
	shared_ptr<vector<int> > p = make_shared<vector<int> >(100, 2);
	Pval((*p)[3]);
	vec = p.get();
}

//vector<int>*& play2()
//{
//	shared_ptr<vector<int> > p = make_shared<vector<int> >(100, 3);
//	Pval((*p)[3]);
//	return p.get();
//}

vector<int>* play3()
{
	shared_ptr<vector<int> > p = make_shared<vector<int> >(100, 4);
	Pval((*p)[3]);
	vector<int>* vec = p.get();
	return vec;
}

TEST(test_shared_ptr, return_func)
{
	vector<int> *pvec;
	play(pvec);
	Pval((*pvec)[3]);
	Pval(pvec->size());

	//pvec = play2();
	//Pval((*pvec)[3]);
	
	pvec = play3();
	Pval((*pvec)[4]);
}

struct A
{
	int x = 5;
	~A()
	{
		VLOG(0) << "A desctruct";
	}
};

A* Get()
{
	auto a = make_shared<A>();
	a->x = 10;
	return a.get();
}

TEST(test_shared_ptr2, return_func)
{
	A* p = Get();
	Pval(p->x);
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
