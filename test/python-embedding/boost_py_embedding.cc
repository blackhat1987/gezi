/** 
 *  ==============================================================================
 * 
 *          \file   boost_py_embedding.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-30 19:55:21.749604
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"

#include <boost/python.hpp>
using namespace boost::python;

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{

}

TEST(boost_py_embedding, func)
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


	//要求simple.py与可执行文件在相同路径下! 运行ok
	object simple = exec_file("simple.py", main_namespace, main_namespace);
	//dict global;
	//object result = exec_file("simple.py", global, global);
	object foo = main_namespace["foo"];
	int val = extract<int>(foo(5));
	cout << "Python has caculated foo as " << val << endl;
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
