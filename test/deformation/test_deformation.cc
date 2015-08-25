/** 
 *  ==============================================================================
 * 
 *          \file   test_deformation.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-08-04 13:55:30.505185
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "deformation-procs/deformation_text.h"

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");
DEFINE_string(conf, "pinyin_to_chi.conf", "");

TEST(deformation, func)
{
	//deformation_text dtext;
	//dtext.init("./conf", "pinyin_to_chi.conf");
	//vector<trans_unit> vec;
	//Pval2(dtext.line_procs("国●岛av资~源●关注嶶^信^呺● weyoou", vec), vec.size());
	//vec.clear();
	//Pval2(dtext.line_procs("国岛av资源关注嶶信呺weyoou", vec), vec.size());
}

TEST(deformation2, func)
{
	deform_conf::init(FLAGS_conf.c_str(), "./conf");
	deformation_text d_text;
	
	string input = "有缠品,没课元,你需要芳法!!! ";
	vector<trans_unit> trans_info;
	string output = d_text.line_procs(input, trans_info);
	cout << output << endl;
	{
		vector<trans_unit> vec;
		Pval(d_text.line_procs("国●岛av资~源●关注嶶^信^呺● weyoou", vec));
		Pval(vec.size());
		PrintVec4(vec, src_word, des_word, trans_pro, trans_ss);
		vec.clear();
		Pval(d_text.line_procs("国岛av资源关注嶶信呺weyoou", vec));
		Pval(vec.size());
		PrintVec4(vec, src_word, des_word, trans_pro, trans_ss);

		Pval(d_text.line_procs("如果你是se女 加我qq，全不收钱，想加我qq的，看第二楼", vec));
		Pval(d_text.line_procs("分的小菜鸟～有需求加微 xin sysy_sy_sy有事没事加我聊聊天也好呢", vec));

		Pval(d_text.line_procs("看90后少妇関注薇信cba850"));
	}
	{
		ifstream ifs(FLAGS_i);
		ofstream ofs(FLAGS_o);
		string line;
		while (getline(ifs, line))

		{
			vector<trans_unit> trans_info;
			string line2 = d_text.line_procs(line, trans_info);
			ofs << line << endl;
			ofs << line2 << endl;
			ofs << trans_info.size() << endl;
		}
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
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;
	
	//deformation_text d_text;

	///*if (argc != 3)
	//{
	//cerr << "./file_procs filein fileout" << endl;
	//return -1;
	//}
	//*/
	//const char* config_path = "./conf/";
	//const char* config_file = "pinyin_to_chi.conf";
	//int ret = d_text.init(config_path, config_file);
	//if (ret <0)
	//{
	//	cout << "init err" << endl;
	//	return -1;
	//}
	//string input = "有缠品,没课元,你需要芳法!!! ";
	//vector<trans_unit> trans_info;
	//string output = d_text.line_procs(input, trans_info);
	//cout << output << endl;
	
	LogHelper logger(4);
	//logger.set_level(4);

	return RUN_ALL_TESTS();
}
