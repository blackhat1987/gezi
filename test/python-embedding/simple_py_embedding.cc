/**
 *  ==============================================================================
 *
 *          \file   simple_py_embedding.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-30 19:42:59.130646
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "Python.h"
#include "python_util.h"
using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{

}

namespace bp = boost::python;

TEST(simple_py_embedding, func)
{
	
	DEF_MAP(id_map);

#define  COMMOA ,
	bp::class_< std::map< int, double > >("map_less__int_comma__double__greater_")
		.def(bp::map_indexing_suite< ::std::map< int, double >, true >())
		MAP_METHOD(::std::map< int COMMOA double >);

	Py_Initialize();
	PyRun_SimpleString("from time import time,ctime\n"
		"print 'Today is',ctime(time())\n");
	Py_Finalize();
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
