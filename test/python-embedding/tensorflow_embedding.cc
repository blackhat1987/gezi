/** 
 *  ==============================================================================
 * 
 *          \file   tensorflow_embedding.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-12-14 16:40:55.898467
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"

#include <boost/python.hpp>
using namespace boost::python;

using namespace std;
using namespace gezi;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf,false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

void run()
{
	Py_Initialize();

	object main_module = import("__main__");
	object main_namespace = main_module.attr("__dict__");
	exec("hello = file('hello.txt', 'w')\n"
		"hello.write('Hello world!')\n"
		"hello.close()",
		main_namespace);
	exec("result = 5 ** 2", main_namespace);
	int five_squared = extract<int>(main_namespace["result"]);
	cout << "The five_squeared caculated by python is " << five_squared << endl;

	// Load the sys module.
	object sys = import("sys");

	// Extract the python version.
	std::string version = extract<std::string>(sys.attr("version"));
	std::cout << version << std::endl;


	//Ҫ��simple.py���ִ���ļ�����ͬ·����! ����ok
	object simple = exec_file("simple.py", main_namespace, main_namespace);
	//dict global;
	//object result = exec_file("simple.py", global, global);
	object foo = main_namespace["foo"];
	int val = extract<int>(foo(5));
	cout << "Python has caculated foo as " << val << endl;

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
