/**
 *  ==============================================================================
 *
 *          \file   test_cereal.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-10-01 20:02:57.824999
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include <stdlib.h>
#include <string.h>
#include <complex>      // std::complex, std::abs
#include <cmath>

//#define NO_BAIDU_DEP
//#define USE_CEREAL
//#define NO_CEREAL
#include "Identifer.h"
//#include "serialize_util.h"

#include "common_util.h"

using namespace std;
//using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

struct MyRecord
{
	uint8_t x, y;
	float z;

	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(x, y, z);
	}
};

struct SomeData
{
	int32_t id;
	std::shared_ptr<std::unordered_map<uint32_t, MyRecord>> data;

	template <class Archive>
	void save(Archive & ar) const
	{
		ar(data);
	}

	template <class Archive>
	void load(Archive & ar)
	{
		static int32_t idGen = 0;
		id = idGen++;
		ar(data);
	}
};


void run()
{

}

TEST(cereal, func)
{
	std::ofstream os("out.cereal", std::ios::binary);
	cereal::BinaryOutputArchive archive(os);

	SomeData myData;
	archive(myData);
}

TEST(serialize_vector, func)
{
	vector<uint64> pids = { 56934773506, 56929671202, 56921814305, 56921851753, 56921859840 };
	serialize_util::save(pids, "./pids.bin");
	{
		vector<uint64> pids;
		serialize_util::load("./pids.bin", pids);
		Pvec(pids);
	}
}

TEST(serialize_text_vector, func)
{
	vector<uint64> pids = { 56934773506, 56929671202, 56921814305, 56921851753, 56921859840 };
	serialize_util::save_text(pids, "./pids.txt");
	{
		vector<uint64> pids;
		serialize_util::load_text("./pids.txt", pids);
		Pvec(pids);
	}
}

TEST(seralize_xml_vector, func)
{
	vector<uint64> pids = { 56934773506, 56929671202, 56921814305, 56921851753, 56921859840 };
	serialize_util::save_xml(pids, "./pids.xml");
	{
		vector<uint64> pids;
		serialize_util::load_xml("./pids.xml", pids);
		Pvec(pids);
	}
}

TEST(seralize_text_map, func)
{
	map<string, uint64> m = { { "abc", 3 }, { "def", 4 } };
	serialize_util::save_text(m, "./map.txt");
	{
		map<string, uint64> m;
		serialize_util::load_text("./map.txt", m);
		for (auto& item : m)
		{
			Pval2(item.first, item.second);
		}
	}
}

TEST(seralize_xml_map, func)
{
	map<string, uint64> m = { { "abc", 3 }, { "def", 4 } };
	serialize_util::save_xml(m, "./map.xml");
	{
		map<string, uint64> m;
		serialize_util::load_xml("./map.xml", m);
		for (auto& item : m)
		{
			Pval2(item.first, item.second);
		}
	}
}

struct Node
{
	string name = "abc";
	int age = 32;
	int _id = 1024;

	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar(CEREAL_NVP(name));
		ar(CEREAL_NVP(age));
		//ar(CEREAL_NVP(_id));
		ar & GEZI_SERIALIZATION_NVP(_id);
	}

	virtual void Name()
	{
		LOG(INFO) << "Node";
	}

	void Save(string path)
	{
		//serialize_util::save_xml(*this, path); //基类这样 子类调用Save没办法保存子类的任何信息
		Save_(path);
	}

	virtual void Save_(string path)
	{

	}
	void SaveJson(string path)
	{
		//serialize_util::save_xml(*this, path); //基类这样 子类调用Save没办法保存子类的任何信息
		SaveJson_(path);
	}

	virtual void SaveJson_(string path)
	{

	}
};

struct ChildNode : public Node
{
	int height = 178;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar(CEREAL_BASE_OBJECT_NVP(Node));
		ar(CEREAL_NVP(height));
	}

	virtual void Name() override
	{
		LOG(INFO) << "ChildNode";
	}

	virtual void Save_(string path) override
	{
		serialize_util::save_xml(*this, path);
	}

	virtual void SaveJson_(string path) override
	{
		serialize_util::save_json(*this, path);
	}
};

struct ChildNode2 : public Node
{
	int height = 166;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar(CEREAL_BASE_OBJECT_NVP(Node));
		ar(CEREAL_NVP(height));
	}

	virtual void Name() override
	{
		LOG(INFO) << "ChildNode2";
	}

	virtual void Save_(string path) override
	{
		serialize_util::save_xml(*this, path);
	}

	virtual void SaveJson_(string path) override
	{
		serialize_util::save_json(*this, path);
	}
};

TEST(seralize_text_vector_struct, func)
{
	Node node;
	vector<Node> vec;
	vec.push_back(node);
	node.name = "meixi";
	node.age = 27;
	vec.push_back(node);
	serialize_util::save_text(vec, "./nodeVec.txt");
	{
		vector<Node> vec;
		serialize_util::load_text("./nodeVec.txt", vec);
		Pval(vec.size());
		PrintVec2(vec, name, age);
	}
}

TEST(seralize_binary_vector_struct, func)
{
	Node node;
	vector<Node> vec;
	vec.push_back(node);
	node.name = "meixi";
	node.age = 27;
	vec.push_back(node);
	serialize_util::save(vec, "./nodeVec.bin");
	{
		vector<Node> vec;
		serialize_util::load("./nodeVec.bin", vec);
		Pval(vec.size());
		PrintVec2(vec, name, age);
	}
}

TEST(seralize_xml_vector_struct, func)
{
	Node node;
	vector<Node> vec;
	vec.push_back(node);
	node.name = "meixi";
	node.age = 27;
	vec.push_back(node);
	serialize_util::save_xml(vec, "./nodeVec.xml");
	{
		vector<Node> vec;
		serialize_util::load_xml("./nodeVec.xml", vec);
		PrintVec2(vec, name, age);
	}
}
TEST(seralize_xml_map_struct, func)
{
	Node node;
	map<uint64, Node> m;
	m[1982] = node;
	node.name = "meixi";
	node.age = 27;
	m[1987] = node;
	serialize_util::save_xml(m, "./nodeMap.xml");
	{
		map<uint64, Node> m;
		serialize_util::load_xml("./nodeMap.xml", m);
		for (auto& item : m)
		{
			Pval3(item.first, item.second.name, item.second.age);
		}
	}
}

TEST(seralize_derived, func)
{
	ChildNode cnode;
	cnode.Save("./cnode.xml");
	cnode.SaveJson("./cnode.json");
}


TEST(seralize_as_conf, func)
{
	ChildNode cnode;
	serialize_util::load_xml("./cnode2.xml", cnode);
	Pval3(cnode.name, cnode.age, cnode.height);
	serialize_util::load_json("./cnode2.json", cnode);
	Pval3(cnode.name, cnode.age, cnode.height);
}

CEREAL_REGISTER_TYPE(ChildNode)
CEREAL_REGISTER_TYPE(ChildNode2)
TEST(shared_ptr, func)
{
	{
		shared_ptr<Node> child = make_shared<ChildNode>();
		child->height = 12345;
		shared_ptr<Node> child2 = make_shared<ChildNode2>();
		shared_ptr<Node> base = make_shared<Node>();

		std::ofstream os("shared_ptr.json");
		{
			cereal::JSONOutputArchive oar(os);
			oar(child, child2, base);
		}
	}
	{
		shared_ptr<Node> child, child2, base;
		std::ifstream is("shared_ptr.json");
		{
			cereal::InputArchive iar(is);
			iar(child, child2, base);
		}
		Pval2(child->Name(), child->height);
		Pval2(child2->Name(), child2->height);
		Pval2(base->Name(), base->height);
	}
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);

	return RUN_ALL_TESTS();
}
