/**
 *  ==============================================================================
 *
 *          \file   test_lambda.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-04 10:48:51.591122
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
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, ""); 
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

struct Node
{
	//ע��c++ 11 gcc4.8֧��ֱ�Ӷ����Աԭ�ظ��� ����index = 0 value = 0
	int index = 0;
	int value = 0;

	Node(int i, int j)
	{
		index = i; vector<int> vec = { 1, 2, 3, 4 };
		Pval(*(find_if(vec.begin(), vec.end(), (_1 % 2 == 0))));
		Pvec(vec);

		//----------------boost foreach �� c++11 foreach

		foreach(auto item, vec)
		{
			Pval(item);
		}
		for (auto item : vec)
		{
			Pval(item);
		}
		value = j;
	}

	Node()
	{

	}

	bool operator<(const Node& other)
	{
		return value < other.value;
	}
};

TEST(sort, func)
{
	//---------------�������򷽷�
	vector<Node> vec = { Node(), Node(4, -1), Node(2, 2) };
	Pval(vec.size());
	PrintVec2(vec, index, value);
	std::sort(vec.begin(), vec.end());
	PrintVec2(vec, index, value);
	//write one functor outiside
	std::sort(vec.begin(), vec.end(), gezi::CmpNodeValue());
	PrintVec2(vec, index, value);
	//boost bind
	sort(vec.begin(), vec.end(), boost::bind(&Node::value, _1) < boost::bind(&Node::value, _2));
	PrintVec2(vec, index, value);
	//c++11
	sort(vec.begin(), vec.end(), [](const Node&l, const Node & r)
	{
		return l.value < r.value;
	});
	PrintVec2(vec, index, value);
}

TEST(lambda, func)
{
	vector<int> vec = { 1, 2, 3, 4 };
	//----------c++ 11 lambda
	//����ֵ���cout ������ʾ������ @TODO
	for_each(vec.begin(), vec.end(), [](int item)
	{
		cout << item;
	});
	//���������ʾ����
	for_each(vec.begin(), vec.end(), [](int item)
	{
		Pval(item);
	});
	//���ǵ��µ���������
	for_each(vec.begin(), vec.end(), [](int& item)
	{
		item *= 2;
	});
	Pvec(vec);

	//----------boost.phonei���Կ�����boost::lambda���� boost lambda��_1 �� boost::bind�г�ͻ
	//һ������������ֿ�ܸ���Ƕ��仯�ĺ���֮���ô�����̫��  ������range based for���
	for_each(vec.begin(), vec.end(), _1 *= 2);
	Pvec(vec);
	//���Ҳ��ʾ������������
	for_each(vec.begin(), vec.end(), cout << _1);
	Pvec(vec);
}

TEST(find_if, func)
{
	vector<int> vec = { 1, 2, 3, 4 };
	Pval(*(find_if(vec.begin(), vec.end(), (_1 % 2 == 0))));
}


TEST(foreach, func)
{
	//----------------boost foreach �� c++11 foreach
	vector<int> vec = { 1, 2, 3, 4 };
	foreach(auto item, vec)
	{
		Pval(item);
	}
	for (auto item : vec)
	{
		Pval(item);
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
	FLAGS_minloglevel = FLAGS_level;

	boost::progress_timer timer;
	return RUN_ALL_TESTS();
}
