/**
 *  ==============================================================================
 *
 *          \file   test.cc
 *
 *        \author   gezi
 *
 *          \date   2014-02-15 18:19:05.223340
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "linq/boolinq.h"
#include "common_util.h"
#include "linq/cpplinq.hpp"
using namespace std;
using namespace gezi;

DEFINE_string(type, "simple", "");

struct Node
{
	int index;
	double value;
	double other;
	Node(int index_, double value_)
		:index(index_), value(value_)
	{

	}
};
TEST(distinct_count, func)
{
	//TODO check 初始化
	vector<Node> vec = { Node(3, 4.5), Node(4, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(4, 5.2), Node(3, 1.2), 
		Node(3, 4.5), Node(6, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(4, 5.2), Node(3, 1.2)};
	//TODO how to remove end
	Pval(distinct_count<int>(vec.begin(), vec.end(), bind(&Node::index, _1)));
	Pval(distinct_count<int>(vec.begin(), vec.end(), [](const Node& a) { return a.index; }));
	{
		using namespace boolinq;
		Pval((from(vec).distinct([](const Node& a) { return a.index; }).count()));
	}
	{
		using namespace cpplinq;
		Pval((from(vec) >> select([](const Node& a) { return a.index; }) >> distinct() >> count()));
	}
}
TEST(distinct_count, p1)
{
	vector<Node> vec = { Node(3, 4.5), Node(4, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(4, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(6, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(4, 5.2), Node(3, 1.2) };
	for (size_t i = 0; i < 1000000; i++)
	{
		distinct_count<int>(vec.begin(), vec.end(), bind(&Node::index, _1));
	}
}
TEST(distinct_count, p2)
{
	vector<Node> vec = { Node(3, 4.5), Node(4, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(4, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(6, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(4, 5.2), Node(3, 1.2) };
	size_t val;
	for (size_t i = 0; i < 1000000; i++)
	{
		val = distinct_count<int>(vec.begin(), vec.end(), [](const Node& a) { return a.index; });
	}
}
TEST(distinct_count, p3)
{
	vector<Node> vec = { Node(3, 4.5), Node(4, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(4, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(6, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(4, 5.2), Node(3, 1.2) };
	size_t val;
	for (size_t i = 0; i < 1000000; i++)
	{
		val = distinct_count<int>(vec, [](const Node& a) { return a.index; });
	}
}
TEST(distinct_count, p4)
{
	vector<Node> vec = { Node(3, 4.5), Node(4, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(4, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(6, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(4, 5.2), Node(3, 1.2) };
	size_t val;
	for (size_t i = 0; i < 1000000; i++)
	{
		val = distinct_count(vec, [](const Node& a) { return a.index; });
	}
}
TEST(distinct_count, boolinq)
{
	using namespace boolinq;
	vector<Node> vec = { Node(3, 4.5), Node(4, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(4, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(6, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(4, 5.2), Node(3, 1.2) };
	size_t val;
	for (size_t i = 0; i < 1000000; i++)
	{
		val = from(vec).distinct([](const Node& a) { return a.index; }).count();
	}
}

TEST(distinct_count, cpplinq)
{
	using namespace cpplinq;
	vector<Node> vec = { Node(3, 4.5), Node(4, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(4, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(6, 5.2), Node(3, 1.2),
		Node(3, 4.5), Node(4, 5.2), Node(3, 1.2) };
	size_t val;
	for (size_t i = 0; i < 1000000; i++)
	{
		val = (from(vec) >> select([](const Node& a) { return a.index; }) >> distinct() >> count());
	}
}

TEST(boolinq, func)
{
	using namespace boolinq;
	vector<Node> vec = { Node(3, 4.5), Node(4, 5.2), Node(3, 1.2) };
	PrintVec2(vec, index, value);
	
	vector<Node> vec2 = from(vec).distinct([](const Node& a) { return a.index; })
		.orderBy([](const Node& a) { return a.value; }).toVector();
	PrintVec2(vec2, index, value);
}

TEST(boolinq, perf)
{
	using namespace boolinq;
	
	int src[] = { 1, 2, 3, 3, 4, 5, 6, 7, 8 };
	auto dst = from(src).where([](int a){return a % 2 == 1; })    // 1,3,5,7
		.select([](int a){return a * 2; })         // 2,6,10,14
		.where([](int a){return  a > 2 && a < 12; }) // 6,10
		.distinct()
		.toVector();
	Pvec(dst);
	LOG(INFO) << "begin";
	for (size_t i = 0; i < 100000; i++)
	{
		auto dst = from(src).where([](int a){return a % 2 == 1; })
			.select([](int a){return a * 2; })
			.where([](int a){return a > 2 && a < 12; })
			.distinct()
			.toVector();
	}
	LOG(INFO) << "end";
}
TEST(cpplinq, func)
{
	using namespace cpplinq;
	
	vector<Node> vec = { Node(3, 4.5), Node(4, 5.2), Node(3, 1.2) };
	PrintVec2(vec, index, value);

	vector<Node> vec2 = cpplinq::from(vec)
		>> cpplinq::orderby([](const Node& a) { return a.index; })
		>> cpplinq::thenby_descending([](const Node& a) { return a.value; })
		>> to_vector();
	
	PrintVec2(vec2, index, value);
}
//[RUN] boolinq.perf
//I0216 22:31 : 12.230059  9359 test.cc : 54] dst-- - 2
//I0216 22:31 : 12.230072  9359 test.cc : 54] 0         6
//I0216 22:31 : 12.230077  9359 test.cc : 54] 1         10
//I0216 22:31 : 12.230083  9359 test.cc : 55] begin
//I0216 22:31 : 17.349370  9359 test.cc : 64] end

//[RUN] cpplinq.perf
//I0216 22:31 : 17.349591  9359 test.cc : 89] dst-- - 2
//I0216 22:31 : 17.349599  9359 test.cc : 89] 0         6
//I0216 22:31 : 17.349606  9359 test.cc : 89] 1         10
//I0216 22:31 : 17.349611  9359 test.cc : 90] begin
//I0216 22:31 : 17.618379  9359 test.cc : 100] end

//cpplinq速度快很多 唯一比boolinq差的是不支持distinct(func) TODO 可以考虑以后加上 一般不会用到
TEST(cpplinq, perf)
{
	using namespace cpplinq;
	int src[] = { 1, 2, 3, 3, 4, 5, 6, 7, 8 };
	auto dst = cpplinq::from_array(src)
		>> where([](int a){return a % 2 == 1; })    // 1,3,5,7
		>> select([](int a){return a * 2; })         // 2,6,10,14
		>> where([](int a){return  a > 2 && a < 12; }) // 6,10
		>> distinct()
		>> to_vector();
	Pvec(dst);
	LOG(INFO) << "begin";
	for (size_t i = 0; i < 100000; i++)
	{
		auto dst = cpplinq::from_array(src)
			>> where([](int a){return a % 2 == 1; })    // 1,3,5,7
			>> select([](int a){return a * 2; })         // 2,6,10,14
			>> where([](int a){return  a > 2 && a < 12; }) // 6,10
			>> distinct()
			>> to_vector();
	}
	LOG(INFO) << "end";
}

TEST(common, perf)
{
	int src[] = { 1, 2, 3, 3, 4, 5, 6, 7, 8 };
	LOG(INFO) << "begin";
	for (size_t i = 0; i < 100000; i++)
	{
		set<int> set_;
		vector<int> vec;
		for (size_t i = 0; i < 8; i++)
		{
			if (src[i] % 2 == 1)
			{
				int val = src[i] * 2;
				if (val > 2 && val < 12)
				{
					set_.insert(val);
				}
			}
		}
		vec.assign(set_.begin(), set_.end());
	}
	LOG(INFO) << "end";
}

int main(int argc, char *argv[])
{
	FLAGS_logtostderr = true;
	testing::InitGoogleTest(&argc, argv);
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	boost::progress_timer timer;
	return RUN_ALL_TESTS();
}
