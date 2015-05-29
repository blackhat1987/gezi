/**
 *  ==============================================================================
 *
 *          \file   test_binfinder.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-04-08 23:41:55.935761
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "Numeric/BinFinder.h"
#include "statistic_util.h"

using namespace std;
using namespace gezi;
DEFINE_int32(level, 0, "min log level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(t, func1)
{
	{
		Fvec vec = { 1, 1.1, 2, 2.1, 3, 3.1, 4, 4.1, 4.2, 4.3, 4.4 };
		Pvec(vec);
		Fvec result = find_bins(vec, 4);
		Pvec(result);
	}

	{
		Fvec vec = { 1, 1.1, 2, 2.1, 3, 3.1, 4, 4.1, 4.2, 4.3, 4.4 };
		Pvec(vec);
		Fvec result, medians;
		find_bins(vec, 4, result, medians);
		Pvec(result);
		Pvec(medians);
	}
}
TEST(test_binfinder, func)
{
	BinFinder finder;
	{
		Fvec vec = { 1.0, 2.0, 1.0, 1.2, 1.3, 2.4, 3.8, 4.6, 4.9, 7.2, 7.8, 100.0, 330.1, 10.2 };
		Pvec(vec);
		Fvec result = finder.FindBins(vec, 3);
		Pvec(result);
		result = finder.FindBins(vec, 5);
		Pvec(result);
		result = finder.FindBins(vec, 1);
		Pvec(result);
	}

	{
		Fvec vec = { 1.0, 2.0, 1.0, 1.2, 1.3, 2.4, 3.8, 4.6, 4.9, 7.2, 7.8, 100.0, 330.1, 10.2 };
		Pvec(vec);
		Fvec result = find_bins(vec, 3);
		Pvec(result);
		result = find_bins(vec, 5);
		Pvec(result);
		result = find_bins(vec, 1);
		Pvec(result);
	}
	{
		Fvec vec2;
		vec2.resize(3);
		Pvec(vec2);
	}

	{
		Fvec vec = { 1, 1, 2, 2, 3, 3, 4, 4, 4, 4, 4 };
		Pvec(vec);
		Fvec result = finder.FindBins(vec, 4);
		Pvec(result);
	}
	/*{
		Fvec vec = { 1.0, 2.0, 1.0, 1.2, 1.3, 2.4, 3.8, 4.6, 4.9, 7.2, 7.8, 100.0, 330.1, 10.2, 3, 3, 3, 54, 234, 321, 123.9, 33.3, 33.3, 33.4, 1.093, 32.98, 99, 99, 99, 88, 88, 78, 78, 78, 781, 32, 32, 123, 1234, 4321, 12, 3 };

		Pvec(vec);
		Fvec result, medians;
		find_bins(vec, 4, result, medians);
		Pvec(result);
		Pvec(medians);
		}*/

	{
		Fvec vec = { -2, -2, -100, -32, -0.9, -0.7, 1.0, 2.0, 1.0, 1.2, 1.3, 2.4, 3.8, 4.6, 4.9, 7.2, 7.8, 100.0, 330.1, 10.2, 3, 3, 3, 54, 234, 321, 123.9, 33.3, 33.3, 33.4, 1.093, 32.98, 99, 99, 99, 88, 88, 78, 78, 78, 781, 32, 32, 123, 1234, 4321, 12, 3, 0, 0, 0, 0, 0, 0, 0 };

		Pvec(vec);
		Fvec result, medians;
		find_bins(vec, 4, result, medians);
		Pvec(result);
		Pvec(medians);
	}
	{
		Fvec vec = { -2, -2, -100, -32, -0.9, -0.7, 1.0, 2.0, 1.0, 1.2, 1.3, 2.4, 3.8, 4.6, 4.9, 7.2, 7.8, 100.0, 330.1, 10.2, 3, 3, 3, 54, 234, 321, 123.9, 33.3, 33.3, 33.4, 1.093, 32.98, 99, 99, 99, 88, 88, 78, 78, 78, 781, 32, 32, 123, 1234, 4321, 12, 3 };

		Pvec(vec);
		Fvec result, medians;
		find_bins(vec, vec.size() + 7, 4, result, medians);
		Pvec(result);
		Pvec(medians);
	}

	{
		Fvec vec = { 1.0, 2.0, 1.0, 1.2, 1.3, 2.4, 3.8, 4.6, 4.9, 7.2, 7.8, 100.0, 330.1, 10.2, 3, 3, 3, 54, 234, 321, 123.9, 33.3, 33.3, 33.4, 1.093, 32.98, 99, 99, 99, 88, 88, 78, 78, 78, 781, 32, 32, 123, 1234, 4321, 12, 3, 0, 0, 0, 0, 0, 0, 0 };

		Pvec(vec);
		Fvec result, medians;
		find_bins(vec, 4, result, medians);
		Pvec(result);
		Pvec(medians);
	}
	{
		Fvec vec = { 1.0, 2.0, 1.0, 1.2, 1.3, 2.4, 3.8, 4.6, 4.9, 7.2, 7.8, 100.0, 330.1, 10.2, 3, 3, 3, 54, 234, 321, 123.9, 33.3, 33.3, 33.4, 1.093, 32.98, 99, 99, 99, 88, 88, 78, 78, 78, 781, 32, 32, 123, 1234, 4321, 12, 3 };

		Pvec(vec);
		Fvec result, medians;
		find_bins(vec, vec.size() + 7, 4, result, medians);
		Pvec(result);
		Pvec(medians);
	}
}

TEST(special, func)
{
	{
		Fvec vec;

		Pvec(vec);
		Fvec result, medians;
		find_bins(vec, 4, result, medians);
		Pvec(result);
		Pvec(medians);
	}
}
TEST(test_binfinder, perf1)
{
	Fvec vec = { 1.0, 2.0, 1.0, 1.2, 1.3, 2.4, 3.8, 4.6, 4.9, 7.2, 7.8, 100.0, 330.1, 10.2, 3, 3, 3, 54, 234, 321, 123.9, 33.3, 33.3, 33.4, 1.093, 32.98, 99, 99, 99, 88, 88, 78, 78, 78, 781, 32, 32, 123, 1234, 4321, 12, 3 };

	for (size_t i = 0; i < 100000; i++)
	{
		Fvec result = find_bins(vec, 20);
	}
}

TEST(test_binfinder, perf2)
{
	Fvec vec = { 1.0, 2.0, 1.0, 1.2, 1.3, 2.4, 3.8, 4.6, 4.9, 7.2, 7.8, 100.0, 330.1, 10.2, 3, 3, 3, 54, 234, 321, 123.9, 33.3, 33.3, 33.4, 1.093, 32.98, 99, 99, 99, 88, 88, 78, 78, 78, 781, 32, 32, 123, 1234, 4321, 12, 3 };
	BinFinder finder;
	for (size_t i = 0; i < 100000; i++)
	{
		Fvec result = finder.FindBins(vec, 20);
	}
}

TEST(special, wrong)
{
	{
		Fvec vec = { 1, 2, 2, 2, 2, 3 };
		Pvec(vec);
		Fvec result, medians;
		find_bins(vec, 2, result, medians);
		Pvec(result);
		Pvec(medians);
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
