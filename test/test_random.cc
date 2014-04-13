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

struct Node
{
	vector<int> vec = { 1, 2, 3 };
};

template<typename _Node>
void move_it(_Node&& node)
{
	_Node node2 = node;
	Pvec(node2.vec);
}


TEST(test_random, func)
{
	{
		Node node;
		Pvec(node.vec);
		move_it(node);
		Pvec(node.vec);
		move_it(Node());
	}
	{
		vector<int> vec = cpplinq::range(0, 10) >> to_vector();
		Pvec(vec);
		shuffle(vec.begin(), vec.end(), random_engine(FLAGS_seed));
		Pvec(vec);
	}
	{
		vector<int> vec = cpplinq::range(0, 10) >> to_vector();
		Pvec(vec);
		RandomEngine rand = random_engine(FLAGS_seed);
		std::shuffle(vec.begin(), vec.end(), rand);
		Pvec(vec);
		shuffle(vec.begin(), vec.end(), rand);
		Pvec(vec);
	}
	{
		vector<int> vec = cpplinq::range(0, 10) >> to_vector();
		Pvec(vec);
		shuffle(vec.begin(), vec.end(), RandomEngine(FLAGS_seed));
		Pvec(vec);
	}

	std::array<int, 5> foo{ 1, 2, 3, 4, 5 };

	// obtain a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	shuffle(foo.begin(), foo.end(), std::default_random_engine(seed));

	std::cout << "shuffled elements:";
	for (int& x : foo) std::cout << ' ' << x;
	std::cout << '\n';

	RandomEngine rng = random_engine();
	std::uniform_int_distribution<uint32_t> uint_dist; // range [0,10]
	UintDistribution uint_dist10(0, 10); // range [0,10]
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
		shuffle(vec, (unsigned)FLAGS_seed);
		Pvec(vec);
	}

	{
		vector<int> vec = cpplinq::range(0, 10) >> to_vector();
		Pvec(vec);
		//sample(vec, 10, FLAGS_seed);
		sample(vec.begin(), vec.end(), 10, random_engine(FLAGS_seed));
		Pvec(vec);
	}
	{
		{
			vector<int> vec = cpplinq::range(0, 10) >> to_vector();
			Pvec(vec);
			shuffle2(vec.begin(), vec.end(), random_engine(FLAGS_seed));
			Pvec(vec);
		}
	}
	{
		vector<int> vec = cpplinq::range(0, 10) >> to_vector();
		Pvec(vec);
		sample(vec, 2, (unsigned)FLAGS_seed);
		Pvec(vec);
	}
	{
		vector<int> vec = cpplinq::range(0, 10) >> to_vector();
		Pvec(vec);
		sample(vec, 1, (unsigned)FLAGS_seed);
		Pvec(vec);
	}
	{
		RandomDouble rand;
		for (size_t i = 0; i < 10; i++)
		{
			Pval(rand.Next());
		}
	}
	{
		RandomInt rand(10);
		for (size_t i = 0; i < 20; i++)
		{
			Pval(rand.Next());
		}
	}
	{
		RandomRange rand(10);
		for (size_t i = 0; i < 10; i++)
		{
			Pval(rand.Next());
		}
		for (size_t i = 0; i < 10; i++)
		{
			Pval(rand.Next());
		}
		for (size_t i = 0; i < 10; i++)
		{
			Pval(rand.Next());
		}
	}
	{
		Random rand;
		for (size_t i = 0; i < 10; i++)
		{
			Pval(rand.Next());
			Pval(rand.Next(3));
			Pval(rand.Next(1, 3));
			Pval(rand.NextDouble());
		}
	}
}

TEST(simple, func)
{
	unsigned seed = random_seed();
	Pval(seed);
	seed = random_seed();
	Pval(seed);

	{
		int seed = random_seed();
		Pval(seed);
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
