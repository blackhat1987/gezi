/**
 *  ==============================================================================
 *
 *          \file   test_numeric_limit.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-03-25 10:55:28.533955
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "statistic_util.h"

using namespace std;
using namespace gezi;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

template<typename T>
void run()
{
	Pval(numeric_limits<T>::lowest());
	Pval(numeric_limits<T>::min());  //所以 double 一般要用lowest才能表示真正最小值  而不是最小的正值
	Pval(numeric_limits<T>::max());
	Pval(numeric_limits<T>::infinity());
	Pval(numeric_limits<T>::epsilon());
	Pval(numeric_limits<T>::quiet_NaN());
	Pval(numeric_limits<T>::round_error());
}

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	FLAGS_minloglevel = FLAGS_level;
	LogHelper::set_level(FLAGS_level);
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;

	vector<vector<int> > v;
	v.resize(2);
	v[0].resize(3, 1);
	v[1].resize(4, 2);
	Pval2(*(&v[0][0] + 2), *(&v[0][0] + 3));

	LOG(INFO) << "int";
	run<int>();
	LOG(INFO) << "uint";
	run<unsigned int>();
	LOG(INFO) << "float";
	run<float>();
	LOG(INFO) << "double";
	run<double>();


	Pval(log(0));
	Pval(std::isnan(log(0)));
	Pval(std::isinf(log(0)));

	Pval(log(0.0));
	Pval(std::isnan(log(0.0)));
	Pval(std::isinf(log(0.0)));

	Pval(log(1 - 1));
	Pval(std::isnan(log(1 - 1)));
	Pval(std::isinf(log(1 - 1)));

	Pval(log(1 - 1.0));
	Pval(std::isnan(log(1 - 1.0)));
	Pval(std::isinf(log(1 - 1.0)));

	Pval(((1 - 1) * log(1 - 1)));
	Pval(((1 - 1.0) * log(1 - 1.0)));

	Pval(std::isnan((1 - 1.0) * log(1 - 1.0)));
	Pval(std::isinf((1 - 1.0) * log(1 - 1.0)));

	Pval((3.0 / 0));

	Pval((gezi::loss::logistic(1, 3)));
	Pval((gezi::loss::logistic(1, 30)));
	Pval((gezi::loss::logistic(1, 60)));
	Pval((gezi::loss::logistic(1, -3)));
	Pval((gezi::loss::logistic(1, -10)));
	Pval((gezi::loss::logistic(1, -20)));
				Pval(std::exp(380));
				Pval(std::exp(760));
				Pval((std::exp(760) > 30));
	Pval((gezi::loss::logistic(1, -380)));

	vector<int> vec{ 1, 2, 3 };
	vec.resize(3, 0);
	Pvec(vec);

  Pval((sizeof(size_t)));
  Pval((sizeof(int64)));

	//NaN是Not a Number的缩写。在matlab中以下情况会出现NaN：
	//	任何关于NaN的数值运算， 如sqrt(NaN)
	//	加减法， 如(+Inf) + (-Inf)
	//	乘法, 如0乘以Inf
	//	除法， 如0 / 0、Inf / Inf

	//----will core
	Pval((3 / 0));
	Pval(std::isnan((3 / 0)));
	Pval(std::isinf((3 / 0)));

	return 0;
}
