/** 
 *  ==============================================================================
 * 
 *          \file   test_vector_copy.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-07-29 11:19:45.909125
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
DEFINE_bool(perf,false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

struct Node
{
	Node() 
	{
		cout << "defautl construct\n";
	}
	Node(int x_, int y_)
	:x(x_), y(y_)
	{
		cout << "construct with\n";
	}
	Node(const Node& other)
	:x(other.x), y(other.y)
	{
		cout << "copy construct\n";	
	}
	Node& operator =(const Node& other)
	{
		x = other.x;
		y = other.y;
		cout << "assign construct\n";
		return *this;
	}

	Node& operator =(const Node&& other)
	{
		cout << "assign move construct\n";
		return *this;
	}

	//�������� ��ô ����� push_back, emplace_back һ�� �������Ǹ�copy_construct ���ǻ���������destruct
	//�������move������ ��������Node�ڲ�û����ʾ�ṩ && ��ôЧ���Ͳ�ʹ��move��һ����
	//Node(Node&& ) = default; 
	//Node(Node&&)
	//{
	//	cout << "move \n";
	//}

	~Node()
	{
		cout << "destruct\n";	
	}

	int x;
	int y;
};

struct Node2
{
	int x;
	int y;
};

void play(const Node& n)
{
	cout << "play const&\n";		
}
//void play(Node&& n)
//{
//	cout << "play &&\n";
//}
void play(const Node2& n)
{
	cout << "play const&\n";		
}
//void play(Node2&& n)
//{
//	cout << "play &&\n";
//}
//���������Ҫ�����ṩ&&����,����ʹ��emplace back2��д��
void run()
{
		{
			play(Node(3,4)); //����ƥ��&&
			cout << "after play\n";
		}
		cout  << "----------------\n";
		{
			Node n(3,4);
			play(n); //����ƥ��const& 
			cout  << "----------------\n";
			play(move(n));
		}
		cout  << "----------------\n";
		play(Node2()); //����ƥ��&&
		cout  << "----------------\n";
		Node2 n2;
		play(n2); //����ƥ��const& 
		cout  << "----------------\n";
		play(move(n2));
		cout  << "----------------\n";
		
		{
			cout << "----------push_back\n";
			vector<Node> vec;
			vec.reserve(10);
			vec.push_back(Node(3,4));
		}
		{
			cout << "---------emplace back move\n";
			vector<Node> vec;
			vec.emplace_back(move(Node(3,4)));
		}
		{
			cout << "---------emplace back\n";
			vector<Node> vec;
			vec.emplace_back(Node(3,4));
		}
		{
			cout << "---------emplace back2\n";
			vector<Node> vec;
			vec.emplace_back(3, 4);
		}
		//{
		//	cout << "---------emplace back3\n";
		//	vector<Node2> vec;
		//	vec.emplace_back({3, 4});
		//}
		{
			cout << "--------assing\n";
			vector<Node> vec;
			vec.resize(1);
			Node node(3,4);
			vec[0] = move(node);
		}
		{
			cout << "------copy\n";
			Node node(3,4);
			Node node2 = node;
		}
		{
			cout << "------move\n";
			Node node(3,4);
			Node node2 = move(node);
			Pval(node.x);
			Pval(node2.x);
		}
		{
			map<string, int> m;
			Pval(sizeof(m));
		}
		{
			int* x;
			Pval(sizeof(x));
		}
		{
			unordered_map<string, int> m;
			Pval(sizeof(m));
		}
		{
			vector<int> vec;
			Pval(sizeof(vec));
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

	 return 0;
}
