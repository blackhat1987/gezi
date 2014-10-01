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

#define NO_BAIDU_DEP
#define USE_CEREAL
#include "serialize_util.h"

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

TEST(save_load, func)
{

}

TEST(save_load_json, func)
{

}

TEST(json_as_conf, func)
{

}

TEST(derive, func)
{

}

TEST(shared_ptr, func)
{

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
