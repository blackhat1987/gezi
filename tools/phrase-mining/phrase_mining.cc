/** 
 *  ==============================================================================
 * 
 *          \file   phrase_mining.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-08-18 16:28:17.352068
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "ds/Rstree.h"

using namespace std;
using namespace gezi;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf,false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");


class PhraseMinner
{
public:

	///输入是文本文件 输出是词特征文件
	static void run(string input, string output)
	{
		ifstream ifs(input);

		//----------建立后缀树
		Rstree 
		string line;
		while (getline(ifs, line))
		{
			
		}
		ofstream ofs(output);
	}

};

void run()
{

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

	 return 0;
}
