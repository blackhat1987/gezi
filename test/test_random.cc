/** 
 *  ==============================================================================
 * 
 *          \file   test_random.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-03-30 13:37:29.869194
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "random_util.h"
using namespace std;
using namespace gezi;
DEFINE_int32(level, 0, "min log level");
DEFINE_uint64(seed, 0, "seed");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(test_random, func)
{
	{
		vector<int> vec = cpplinq::range(0, 10) >> to_vector();
		Pvec(vec);
		shuffle(vec.begin(), vec.end(), get_random(FLAGS_seed));
		Pvec(vec);
	}
	{
		vector<int> vec = cpplinq::range(0, 10) >> to_vector();
		Pvec(vec);
		shuffle(vec.begin(), vec.end(), Random(FLAGS_seed));
		Pvec(vec);
	}

	std::array<int, 5> foo{ 1, 2, 3, 4, 5 };

	// obtain a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	shuffle(foo.begin(), foo.end(), std::default_random_engine(seed));

	std::cout << "shuffled elements:";
	for (int& x : foo) std::cout << ' ' << x;
	std::cout << '\n';

	Random rng = get_random();
	std::uniform_int_distribution<uint32_t> uint_dist; // range [0,10]
	RandomRange uint_dist10(0, 10); // range [0,10]
	std::normal_distribution<double> normal_dist(0, 1);  // N(mean, stddeviation)
	int x = 0;
	while (x++ < 100)
	{
		std::cout << uint_dist(rng) << " "
			<< uint_dist10(rng) << " "
			<< normal_dist(rng) << std::endl;
	}

	{
		vector<int> vec = cpplinq::range(0, 10) >> to_vector();
		Pvec(vec);
		shuffle(vec, FLAGS_seed);
		Pvec(vec);
	}

	{
		vector<int> vec = cpplinq::range(0, 10) >> to_vector();
		Pvec(vec);
		sample(vec, 10, 1982);
		Pvec(vec);
	}
	{
		vector<int> vec = cpplinq::range(0, 10) >> to_vector();
		Pvec(vec);
		sample(vec, 3, 1982);
		Pvec(vec);
	}
	{
		vector<int> vec = cpplinq::range(0, 10) >> to_vector();
		Pvec(vec);
		sample(vec, 1, 1982);
		Pvec(vec);
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
