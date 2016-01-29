/**
 *  ==============================================================================
 *
 *          \file   test.cc
 *
 *        \author   chenghuige
 *
 *          \date   2016-01-06 20:31:29.771593
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "liblego/lego.h"

using namespace std;
using namespace gezi;

using namespace liblego;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

DEFINE_string(net, "net.prototxt", "lego net config file");
DEFINE_string(m, "model", "lego model path");

DEFINE_string(test, "test_text", "test file name");

DEFINE_bool(parallel, false, "use parallel mode");

//void run()
//{
//	Net net;
//	EXPECT_EQ(net.set_net_parameter_from_file(FLAGS_net.c_str()), 0);
//	EXPECT_EQ(net.init(FLAGS_model.c_str()), 0);
//	void* tlr_ptr = net.register_thread();
//	EXPECT_TRUE(tlr_ptr);
//
//	Blob* blob = NULL;
//	blob = net.input_blob_by_name(FLAGS_fname, tlr_ptr);
//	EXPECT_TRUE(blob);
//
//	{
//		vector<int> indexes = { 37, 250, 3152, 24927, 44234, 69028, 69241, 72143, 93918, 113225 };
//		blob->dim0 = indexes.size();
//		for (size_t i = 0; i < indexes.size(); i++)
//		{
//			blob->data[i] = indexes[i];
//		}
//
//		EXPECT_EQ(net.predict(tlr_ptr), 0);
//
//		double score = net.result_blob(tlr_ptr)->data[1];
//
//		Pval(score);
//	}
//
//	{
//		vector<int> indexes = { 45, 55, 66, 67, 191, 328, 331, 793, 887, 948, 1685, 4622 };
//		blob->dim0 = indexes.size();
//		for (size_t i = 0; i < indexes.size(); i++)
//		{
//			blob->data[i] = indexes[i];
//		}
//
//		EXPECT_EQ(net.predict(tlr_ptr), 0);
//
//		double score = net.result_blob(tlr_ptr)->data[1];
//
//		Pval(score);
//	}
//
//	net.destroy_thread(tlr_ptr);
//}

#include "Predictors/LegoPredictor.h"
//假设model路径下面没有normalizer
void run()
{
	LegoPredictor predictor;
	predictor.Load(FLAGS_m);
	{
		Vector fe("37:0.0769231,250:0.333333,3152:0.5,24927:1,44234:1,69028:0.0769231,69241:0.25,72143:0.5,93918:1,113225:0.4");
		double  score = predictor.Predict(fe);
		Pval(score);
	}
	{
		Vector fe("45:0.166667	55:0.166667	66:0.111111	67:0.0714286	191:0.125	328:0.0909091	331:0.25	793:0.333333	887:0.166667	948:0.25	1685:0.5	4622:0.571429");
		double  score = predictor.Predict(fe);
		Pval(score);
	}
}

void run_file()
{
	LegoPredictor predictor;
	predictor.Load(FLAGS_m);

	ifstream ifs(FLAGS_test);
	string line;
	double score;
	vector<double> scores;
	while (getline(ifs, line))
	{
		string feStr = (gezi::split(line, ';'))[1];
		Vector fe(feStr, 0, 0, " ", true);
		//Pval(fe.str());
		score = predictor.Predict(fe);
		scores.push_back(score);
/*		cout << score << endl*/;
	}
	Pval(scores.size());
}

void run_file_parallel()
{
	gezi::set_num_threads(0);
	Pval(gezi::get_num_threads());
	LegoPredictor predictor;
	predictor.Load(FLAGS_m);

	ifstream ifs(FLAGS_test);
	string line;
	vector<Vector> fes;
	while (getline(ifs, line))
	{
		string feStr = (gezi::split(line, ';'))[1];
		Vector fe(feStr, 0, 0, " ", true);
		fes.push_back(fe);
	}
	auto results = predictor.BulkPredict(fes);
	Pval(results.size());
	//for (auto score : results)
	//{
	//	cout << score << endl;
	//}
}

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	google::SetVersionString(get_version());
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	FLAGS_minloglevel = FLAGS_level;
	//LogHelper::set_level(FLAGS_level);
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;

	run();

	//run2();

	//if (FLAGS_parallel)
	//{
	//	run_file_parallel();
	//}
	//else
	//{
	//	run_file();
	//}

	return 0;
}
