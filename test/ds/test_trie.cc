/**
 *  ==============================================================================
 *
 *          \file   test_trie.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-07-21 14:43:11.106352
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "ds/Trie.h"
//#include "folly/MapUtil.h"  //@TODO compile error?
using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

//比较神奇 unorderd_map是不支持这样的 必须指针 error: 'std::pair<_T1, _T2>::second' has incomplete type
//但是map可以。。
//struct Trie
//{
//	struct Node
//	{
//		unordered_map<int, Node> next;
//	};
//	Node node;
//};

TEST(map, func)
{
	Trie<string, int> trie;
	EXPECT_EQ(trie.size(), 0);
	EXPECT_EQ(trie.empty(), 1);
	EXPECT_EQ(trie.search("你好"), 0);
	EXPECT_EQ(trie.search("库里"), 0);
	EXPECT_EQ(trie.search("库里是mvp"), 0);
	EXPECT_EQ(trie.prefix_search("库里"), 0);
	trie.insert("你好", 3);
	trie.insert("你是谁", 4);
	trie.insert("梅西在巴萨", 5);
	trie.insert("梅西", 5);
	trie.insert("梅西", 10);
	trie.insert("库里是mvp", 6);
	trie.print();
	EXPECT_EQ(trie.size(), 5);
	EXPECT_EQ(trie.empty(), 0);
	EXPECT_EQ(trie.search("你好"), 1);
	EXPECT_EQ(trie.search("库里"), 0);
	EXPECT_EQ(trie.search("库里是mvp"), 1);
	EXPECT_EQ(trie.prefix_search("库里"), 1);
	EXPECT_EQ(trie::get_default(trie, "库里"), 0);
	EXPECT_EQ(trie::get_default(trie, "库里", -1), -1);
	EXPECT_EQ(trie["库里"], 0);
	trie["库里"] = 9;
	EXPECT_EQ(trie.search("库里"), 1);
	EXPECT_EQ(trie::get_default(trie, "库里"), 9);
	trie["库里"] = 10;
	EXPECT_EQ(trie["库里"], 10);
	trie.insert("库里", 11);
	EXPECT_EQ(trie::get_default(trie, "库里"), 10);
	EXPECT_EQ(trie::get_default(trie, "梅西"), 5);
	EXPECT_EQ(trie.size(), 6);
	serialize_util::save(trie, "trie.bin");
	{
		Trie<string, int> trie;
		typedef Trie<string, int> Trie_;
		serialize_util::load(trie, "trie.bin");
		EXPECT_EQ(trie.size(), 6);
		EXPECT_EQ(trie.empty(), 0);
		EXPECT_EQ(trie.search("你好"), 1);
		EXPECT_EQ(trie.search("库里"), 1);
		EXPECT_EQ(trie.search("库里是"), 0);
		EXPECT_EQ(trie.search("库里是mvp"), 1);
		EXPECT_EQ(trie.prefix_search("库里"), 1);
		EXPECT_EQ(trie.prefix_search("库里是"), 1);
		EXPECT_EQ(trie::get_default(trie, "库里"), 10);
		EXPECT_EQ(trie::get_default(trie, "梅西"), 5);
		const Trie_::Node* node = NULL;
		node = Trie_::find(trie.root(), "梅西在");
		EXPECT_NE(node, NULL);
		Trie_::Node* node2 = Trie_::find(node, "巴萨");
		EXPECT_NE(node2, NULL);
		node2 = Trie_::find(node, "皇马");
		EXPECT_EQ(node2, NULL);
	}
}

TEST(trie_dict, func)
{
	TrieDict<string> trie;
	EXPECT_EQ(trie.size(), 0);
	EXPECT_EQ(trie.empty(), 1);
	EXPECT_EQ(trie.search("你好"), 0);
	EXPECT_EQ(trie.search("库里"), 0);
	EXPECT_EQ(trie.search("库里是mvp"), 0);
	EXPECT_EQ(trie.prefix_search("库里"), 0);
	trie.insert("你好", 3);
	trie.insert("你是谁", 4);
	trie.insert("梅西在巴萨", 5);
	trie.insert("梅西", 5);
	trie.insert("梅西", 10);
	trie.insert("库里是mvp", 6);
	trie.print();
	EXPECT_EQ(trie.size(), 5);
	EXPECT_EQ(trie.empty(), 0);
	EXPECT_EQ(trie.search("你好"), 1);
	EXPECT_EQ(trie.search("库里"), 0);
	EXPECT_EQ(trie.search("库里是mvp"), 1);
	EXPECT_EQ(trie.prefix_search("库里"), 1);
	EXPECT_EQ(trie::get_default(trie, "库里"), 0);
	EXPECT_EQ(trie::get_default(trie, "库里", -1), -1);
	EXPECT_EQ(trie["库里"], -1);  //注意这里默认是null_index
	trie["库里"] = 9;
	EXPECT_EQ(trie.search("库里"), 1);
	EXPECT_EQ(trie::get_default(trie, "库里"), 9);
	trie["库里"] = 10;
	EXPECT_EQ(trie["库里"], 10);
	trie.insert("库里", 11);
	EXPECT_EQ(trie::get_default(trie, "库里"), 10);
	EXPECT_EQ(trie::get_default(trie, "梅西"), 5);
	EXPECT_EQ(trie.size(), 6);
	serialize_util::save(trie, "trie.bin");
	{
		TrieDict<string> trie;
		typedef TrieDict<string> Trie_;
		serialize_util::load(trie, "trie.bin");
		EXPECT_EQ(trie.size(), 6);
		EXPECT_EQ(trie.empty(), 0);
		EXPECT_EQ(trie.search("你好"), 1);
		EXPECT_EQ(trie.search("库里"), 1);
		EXPECT_EQ(trie.search("库里是"), 0);
		EXPECT_EQ(trie.search("库里是mvp"), 1);
		EXPECT_EQ(trie.prefix_search("库里"), 1);
		EXPECT_EQ(trie.prefix_search("库里是"), 1);
		EXPECT_EQ(trie::get_default(trie, "库里"), 10);
		EXPECT_EQ(trie::get_default(trie, "梅西"), 5);
		const Trie_::Node* node = NULL;
		node = Trie_::find(trie.root(), "梅西在");
		EXPECT_NE(node, NULL);
		Trie_::Node* node2 = Trie_::find(node, "巴萨");
		EXPECT_NE(node2, NULL);
		node2 = Trie_::find(node, "皇马");
		EXPECT_EQ(node2, NULL);
	}
}

TEST(set, func)
{
	//or use Trie<string, null_type>
	TrieSet<string> trie;
	EXPECT_EQ(trie.size(), 0);
	EXPECT_EQ(trie.empty(), 1);
	EXPECT_EQ(trie.search("你好"), 0);
	EXPECT_EQ(trie.search("库里"), 0);
	EXPECT_EQ(trie.search("库里是mvp"), 0);
	EXPECT_EQ(trie.prefix_search("库里"), 0);
	trie.insert("你好");
	trie.insert("你是谁");
	trie.insert("梅西在巴萨");
	trie.insert("梅西");
	trie.insert("库里是mvp");
	trie.print();
	EXPECT_EQ(trie.size(), 5);
	EXPECT_EQ(trie.empty(), 0);
	EXPECT_EQ(trie.search("你好"), 1);
	EXPECT_EQ(trie.search("库里"), 0);
	EXPECT_EQ(trie.search("库里是mvp"), 1);
	EXPECT_EQ(trie.prefix_search("库里"), 1);
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
