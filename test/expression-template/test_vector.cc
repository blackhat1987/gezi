/**
 *  ==============================================================================
 *
 *          \file   test_vector.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-05-12 17:40:22.289575
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "Numeric/Vector/Vector.h"
using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(vector_add_bothSparse, func)
{
	Vector A("1:3,5:2.3", 0, 6);
	Pval(A.DenseStr());
	Vector B("1:1,2:4,5:3.5", 0, 6);
	Pval(B.DenseStr());
	A += B;
	Pval(A.DenseStr());
	Pval(B.DenseStr());

	A += A;
	Pval(A.DenseStr());
}

TEST(vector_add_bothSparse2, func)
{
	Vector A("1:3,5:2.3,6:4.8", 0, 7);
	Pval(A.DenseStr());
	Vector B("1:1,2:4,5:3.5", 0, 7);
	Pval(B.DenseStr());
	A += B;
	Pval(A.DenseStr());
	Pval(B.DenseStr());

	A += A;
	Pval(A.DenseStr());
}

TEST(vector_add_bothSparse3, func)
{
	Vector A("1:3,5:2.3", 0, 7);
	Pval(A.DenseStr());
	Vector B("1:1,2:4,5:3.5,6:4.8", 0, 7);
	Pval(B.DenseStr());
	A += B;
	Pval(A.DenseStr());
	Pval(B.DenseStr());

	A += A;
	Pval(A.DenseStr());
}



TEST(vector_add_bothDense, func)
{
	Vector A{ 0.1, 3, 0.2, 0.5, 0.6, 2.3 };
	Pval(A.DenseStr());
	Vector B{ 0, 1, 4, 0, 0, 3.5 };
	Pval(B.DenseStr());
	A += B;
	Pval(A.DenseStr());
	Pval(B.DenseStr());

	A += A;
	Pval(A.DenseStr());
}


TEST(vector_add_denseSparse, func)
{
	Vector A{ 0.1, 3, 0.2, 0.5, 0.6, 2.3 };
	Pval(A.DenseStr());
	Vector B("1:1,2:4,5:3.5", 0, 6);
	Pval(B.DenseStr());
	A += B;
	Pval(A.DenseStr());
	Pval(B.DenseStr());

	A += A;
	Pval(A.DenseStr());
}

TEST(vector_add_sparseDense, func)
{
	Vector A{ 0.1, 3, 0.2, 0.5, 0.6, 2.3 };
	Pval(A.DenseStr());
	Vector B("1:1,2:4,5:3.5", 0, 6);
	Pval(B.DenseStr());
	B += A;
	Pval(A.DenseStr());
	Pval(B.DenseStr());

	B += B;
	Pval(B.DenseStr());
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
