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

//�Ƚ����� unorderd_map�ǲ�֧�������� ����ָ�� error: 'std::pair<_T1, _T2>::second' has incomplete type
//����map���ԡ���
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
	EXPECT_EQ(trie.search("���"), 0);
	EXPECT_EQ(trie.search("����"), 0);
	EXPECT_EQ(trie.search("������mvp"), 0);
	EXPECT_EQ(trie.prefix_search("����"), 0);
	trie.insert("���", 3);
	trie.insert("����˭", 4);
	trie.insert("÷���ڰ���", 5);
	trie.insert("÷��", 5);
	trie.insert("÷��", 10);
	trie.insert("������mvp", 6);
	trie.print();
	EXPECT_EQ(trie.size(), 5);
	EXPECT_EQ(trie.empty(), 0);
	EXPECT_EQ(trie.search("���"), 1);
	EXPECT_EQ(trie.search("����"), 0);
	EXPECT_EQ(trie.search("������mvp"), 1);
	EXPECT_EQ(trie.prefix_search("����"), 1);
	EXPECT_EQ(trie::get_default(trie, "����"), 0);
	EXPECT_EQ(trie::get_default(trie, "����", -1), -1);
	EXPECT_EQ(trie["����"], 0);
	trie["����"] = 9;
	EXPECT_EQ(trie.search("����"), 1);
	EXPECT_EQ(trie::get_default(trie, "����"), 9);
	trie["����"] = 10;
	EXPECT_EQ(trie["����"], 10);
	trie.insert("����", 11);
	EXPECT_EQ(trie::get_default(trie, "����"), 10);
	EXPECT_EQ(trie::get_default(trie, "÷��"), 5);
	EXPECT_EQ(trie.size(), 6);
	serialize_util::save(trie, "trie.bin");
	{
		Trie<string, int> trie;
		typedef Trie<string, int> Trie_;
		serialize_util::load(trie, "trie.bin");
		EXPECT_EQ(trie.size(), 6);
		EXPECT_EQ(trie.empty(), 0);
		EXPECT_EQ(trie.search("���"), 1);
		EXPECT_EQ(trie.search("����"), 1);
		EXPECT_EQ(trie.search("������"), 0);
		EXPECT_EQ(trie.search("������mvp"), 1);
		EXPECT_EQ(trie.prefix_search("����"), 1);
		EXPECT_EQ(trie.prefix_search("������"), 1);
		EXPECT_EQ(trie::get_default(trie, "����"), 10);
		EXPECT_EQ(trie::get_default(trie, "÷��"), 5);
		const Trie_::Node* node = NULL;
		node = Trie_::find(trie.root(), "÷����");
		EXPECT_NE(node, NULL);
		Trie_::Node* node2 = Trie_::find(node, "����");
		EXPECT_NE(node2, NULL);
		node2 = Trie_::find(node, "����");
		EXPECT_EQ(node2, NULL);
	}
}

TEST(trie_dict, func)
{
	TrieDict<string> trie;
	EXPECT_EQ(trie.size(), 0);
	EXPECT_EQ(trie.empty(), 1);
	EXPECT_EQ(trie.search("���"), 0);
	EXPECT_EQ(trie.search("����"), 0);
	EXPECT_EQ(trie.search("������mvp"), 0);
	EXPECT_EQ(trie.prefix_search("����"), 0);
	trie.insert("���", 3);
	trie.insert("����˭", 4);
	trie.insert("÷���ڰ���", 5);
	trie.insert("÷��", 5);
	trie.insert("÷��", 10);
	trie.insert("������mvp", 6);
	trie.print();
	EXPECT_EQ(trie.size(), 5);
	EXPECT_EQ(trie.empty(), 0);
	EXPECT_EQ(trie.search("���"), 1);
	EXPECT_EQ(trie.search("����"), 0);
	EXPECT_EQ(trie.search("������mvp"), 1);
	EXPECT_EQ(trie.prefix_search("����"), 1);
	EXPECT_EQ(trie::get_default(trie, "����"), 0);
	EXPECT_EQ(trie::get_default(trie, "����", -1), -1);
	EXPECT_EQ(trie["����"], -1);  //ע������Ĭ����null_index
	trie["����"] = 9;
	EXPECT_EQ(trie.search("����"), 1);
	EXPECT_EQ(trie::get_default(trie, "����"), 9);
	trie["����"] = 10;
	EXPECT_EQ(trie["����"], 10);
	trie.insert("����", 11);
	EXPECT_EQ(trie::get_default(trie, "����"), 10);
	EXPECT_EQ(trie::get_default(trie, "÷��"), 5);
	EXPECT_EQ(trie.size(), 6);
	serialize_util::save(trie, "trie.bin");
	{
		TrieDict<string> trie;
		typedef TrieDict<string> Trie_;
		serialize_util::load(trie, "trie.bin");
		EXPECT_EQ(trie.size(), 6);
		EXPECT_EQ(trie.empty(), 0);
		EXPECT_EQ(trie.search("���"), 1);
		EXPECT_EQ(trie.search("����"), 1);
		EXPECT_EQ(trie.search("������"), 0);
		EXPECT_EQ(trie.search("������mvp"), 1);
		EXPECT_EQ(trie.prefix_search("����"), 1);
		EXPECT_EQ(trie.prefix_search("������"), 1);
		EXPECT_EQ(trie::get_default(trie, "����"), 10);
		EXPECT_EQ(trie::get_default(trie, "÷��"), 5);
		const Trie_::Node* node = NULL;
		node = Trie_::find(trie.root(), "÷����");
		EXPECT_NE(node, NULL);
		Trie_::Node* node2 = Trie_::find(node, "����");
		EXPECT_NE(node2, NULL);
		node2 = Trie_::find(node, "����");
		EXPECT_EQ(node2, NULL);
	}
}

TEST(set, func)
{
	//or use Trie<string, null_type>
	TrieSet<string> trie;
	EXPECT_EQ(trie.size(), 0);
	EXPECT_EQ(trie.empty(), 1);
	EXPECT_EQ(trie.search("���"), 0);
	EXPECT_EQ(trie.search("����"), 0);
	EXPECT_EQ(trie.search("������mvp"), 0);
	EXPECT_EQ(trie.prefix_search("����"), 0);
	trie.insert("���");
	trie.insert("����˭");
	trie.insert("÷���ڰ���");
	trie.insert("÷��");
	trie.insert("������mvp");
	trie.print();
	EXPECT_EQ(trie.size(), 5);
	EXPECT_EQ(trie.empty(), 0);
	EXPECT_EQ(trie.search("���"), 1);
	EXPECT_EQ(trie.search("����"), 0);
	EXPECT_EQ(trie.search("������mvp"), 1);
	EXPECT_EQ(trie.prefix_search("����"), 1);
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
