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

#include <gtest/gtest.h> 
#include <glog/logging.h>
#include <gflags/gflags.h>

#include "common_def.h"

#include "hashmap_util.h"

#include "string_util.h" //will remove baidu dependence 
#include "log_util.h"
//#include "conf_util.h"

#include "debug_util.h"
#include "serialize_util.h"
//#include "Matrix.h"
//#include "sort_util.h"
//
//#include "statistic_util.h"
//#include "datetime_util.h"
//#include "time_util.h"
//
//#include "file_util.h"
//
//#include "serialize_util.h"
//
//#include "linq.h"
//#include "stl_util.h"
//
//#include "Exception.h"
//
//#include "ProgressBar.h"
//
//#include "LoadSave.h"
//
//#ifndef NO_GEZI_CONVERT
//#include "convert_type.h"
//#endif
//
//#include "sort_map_by_value.h"
//
//#include "openmp_util.h"
//
//#include "ThreadLocalAnyMap.h"
//#include "SharedAnyMap.h"
//#include "Singleton.h"
//#include "Identifer.h"
//#include "SharedIdentifers.h"
//
//#include "SharedObjects.h"

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <fstream>

using namespace std;
using namespace gezi;
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
