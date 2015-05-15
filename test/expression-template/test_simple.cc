/** 
 *  ==============================================================================
 * 
 *          \file   test_simple.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-05-12 10:54:23.369821
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

class Vec
{
public:
	Vec(int len)
	{
		data.resize(len, 0);
		Pval(&data[0]);
	}
	Vec()
	{
		LOG(INFO) << "Default construct";
	}
	~Vec()
	{
		LOG(INFO) << "Destruct";
	}
	Vec(const initializer_list<int>& il)
		:data(il)
	{

	}
	vector<int> data;
};

inline Vec operator+(const Vec& l, const Vec& r)
{
	Vec vec(l.data.size());
	for (size_t i = 0; i < l.data.size(); i++)
	{
		vec.data[i] = l.data[i] + r.data[i];
	}
	Pvec(vec.data);
	return vec;
}


Vec test_return()
{
	Vec vec;
	return vec;
}

TEST(simple1, func)
{
	Vec vec = test_return();
}

TEST(simple2, func)
{
	Vec b{ 3, 2, 1 }, c{ 2, 3, 4 };
	Vec a = b + c;
}


TEST(simple3, func)
{
	Vec b{ 3, 2, 1 }, c{ 2, 3, 4 }, d{ 123, 45, 30 };
	Vec a = b + c + d;
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
