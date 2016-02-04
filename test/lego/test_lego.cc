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
DEFINE_string(m, "lego.model", "lego model path");
DEFINE_string(m2, "lego.model2", "lego model with normalizer path");
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

	LegoPredictor predictor2; //whith normalizer
	predictor2.Load(FLAGS_m2);
	//{
	//	Vector fe("37:0.0769231,250:0.333333,3152:0.5,24927:1,44234:1,69028:0.0769231,69241:0.25,72143:0.5,93918:1,113225:0.4");
	//	double  score = predictor.Predict(fe);
	//	Pval(score);
	//}
	//{
	//	Vector fe("45:0.166667	55:0.166667	66:0.111111	67:0.0714286	191:0.125	328:0.0909091	331:0.25	793:0.333333	887:0.166667	948:0.25	1685:0.5	4622:0.571429");
	//	double  score = predictor.Predict(fe);
	//	Pval(score);
	//}

	//first line of feature.trate.normed.1_2.txt
	{
		Vector fe("12:0.047619	23105:0.333333	26956:1	61668:0.333333	77480:0.5	422758:1	422760:1	2652681:0.2	2652682:0.333333	2652954:0.333333	2652970:0.142857	2653021:0.125	2653118:0.25	2653184:1	2653292:0.166667	2653396:0.25	2653579:0.125	2653582:0.25	2653857:0.125	2654204:0.5	2654260:0.2	2654375:0.333333	2654587:0.333333	2654711:0.142857	2655243:0.25	2655975:0.25	2658914:1	2659329:0.333333	2659643:0.333333	2660607:0.333333	2661998:0.5	2662743:0.333333	2665218:0.333333	2666637:0.5	2668674:0.5	2680448:0.333333	2689943:1	2695181:0.5	2699370:1	2715726:1	2730092:1	2731784:1	2746241:1	2746314:1	2762852:0.333333	2768778:1	2771862:1	2779699:1	2801600:1	2849704:1	2855092:1	2890422:1	2914085:1	3062376:1	3075382:0.5	3075383:0.5	3075387:1	3075390:1	3075394:1	3075397:1	3075398:1	3075403:1	3075404:1	3075408:1	3075409:1	3075412:1	3075414:1     3075416:1	3075417:1	3075422:1	3075423:1	3075426:1	3075433:1	3075436:1	3075439:1	3075441:1	3075446:1	3075451:1");
		double  score = predictor.Predict(fe);
		Pval(score);
	}
	//first line of feature.trate.1_2.txt
	{
		Vector fe("12:2.06525	23105:10.7589	26956:7.06862	61668:8.08556	77480:13.3549	422758:10.9188	422760:9.4147	2652681:4.14328	2652682:3.17464	2652954:4.14512	2652970:5.03622653021:4.14168	2653118:7.17936	2653184:14.9376	2653292:7.32778	2653396:8.15538	2653579:4.1058	2653582:7.45544	2653857:6.8914	2654204:10.3324	2654260:6.05078	2654375:10.8721	2654587:9.75466	2654711:4.38312	2655243:3.93637	2655975:10.0378	2658914:23.6459	2659329:9.357	2659643:4.63277	2660607:13.3263	2661998:10.7708	2662743:10.3388	2665218:12.6574	2666637:11.1721	2668674:6.2792	2680448:14.0951	2689943:15.0021	2695181:8.001	2699370:16.7861	2715726:16.2308	2730092:26.7098	2731784:17.8077	2746241:19.065	2746314:19.065	2762852:13.086	2768778:9.21402	2771862:8.31608	2779699:7.37781	2801600:8.39304	2849704:19.6403	2855092:17.4431	2890422:20.005	2914085:16.9529	3062376:19.065	3075382:8.5674	3075383:10.9188	3075387:23.2238	3075390:19.332	3075394:21.0266	3075397:11.6119	3075398:11.6119	3075403:23.2238	3075404:23.2238	3075408:21.0266	3075409:19.065	3075412:23.2238	3075414:23.2238	3075416:11.6119	3075417:11.6119	3075422:11.6119	3075423:23.2238	3075426:21.8376	3075433:11.6119	3075436:21.8376	3075439:21.8376	3075441:11.6119	3075446:11.6119	3075451:11.6119");
		double  score = predictor2.Predict(fe);
		Pval(score);
	}

	//last line of feature.trate.normed.1_2.txt
	{
		Vector fe("24:0.153846	69:0.115385	354:0.5	409:0.8	420:0.333333	1127:0.333333	1241:1	1645:0.333333	2058:0.333333	2217:0.333333	6613:1	6887:1	7350:0.5	9523:0.25	9681:0.25	16785:1	21710:0.5	22304:0.5	24282:1	28173:0.25	51361:1	52573:0.5	52876:1	54153:1	64670:1	96030:1	228161:0.5	520301:1	797757:1	1191766:1	1263784:1	1263785:1	1263791:1	1263793:1	1263794:1	1263797:1	1263801:1	1263805:1	1263806:1	1263809:1");
		double  score = predictor.Predict(fe);
		Pval(score);
	}
	//last line of feature.trate.1_2.txt
	{
		Vector fe("24:4.59172	69:3.10746	354:12.2213	409:16.5667	420:8.81108	1127:7.1998	1241:19.5476	1645:2.66217	2058:8.5974	2217:2.77729	6613:12.5296  6887:6.47612	7350:4.46909	9523:12.7193	9681:4.75968	16785:13.2982	21710:9.74044	22304:12.4919	24282:7.0168	28173:5.79481	51361:15.9487	52573:10.6856	52876:6.58148	54153:8.14618	64670:15.4402	96030:8.35382	228161:8.83933	520301:9.12701	797757:10.5133	1191766:18.8294	1263784:11.6119	1263785:11.6119	1263791:21.8376	1263793:21.0266	1263794:11.6119	1263797:10.9181263801:23.2238	1263805:10.9188	1263806:23.2238	1263809:21.0266");
		double  score = predictor2.Predict(fe);
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

#include <thread>



void thread_task(LegoPredictor& predictor) 
{
		predictor.InitThread();
		std::cout << "hello thread" << std::endl;
		{
			Vector fe("24:0.153846	69:0.115385	354:0.5	409:0.8	420:0.333333	1127:0.333333	1241:1	1645:0.333333	2058:0.333333	2217:0.333333	6613:1	6887:1	7350:0.5	9523:0.25	9681:0.25	16785:1	21710:0.5	22304:0.5	24282:1	28173:0.25	51361:1	52573:0.5	52876:1	54153:1	64670:1	96030:1	228161:0.5	520301:1	797757:1	1191766:1	1263784:1	1263785:1	1263791:1	1263793:1	1263794:1	1263797:1	1263801:1	1263805:1	1263806:1	1263809:1");
			double  score = predictor.Predict(fe);
			Pval(score);
		}
}

void run_pthread()
{
	LegoPredictor predictor;
	predictor.Load(FLAGS_m);
	int numThreads = 10;
	std::thread t[numThreads];
	for (int i = 0; i < numThreads; i++)
	{
		t[i] = std::thread(thread_task, ref(predictor));
	}

	for(int i = 0; i < numThreads; i++) 
	{
		t[i].join();
	}
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

	run_pthread();

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
