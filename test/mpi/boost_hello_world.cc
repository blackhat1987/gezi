#include <boost/mpi.hpp>
#include <iostream>
#include <string>
#include <boost/serialization/string.hpp>
#define  NO_BAIDU_DEP
#include "common_util.h"
namespace mpi = boost::mpi;

int main(int argc, char* argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	FLAGS_logtostderr = true;

	mpi::environment env(argc, argv);
	mpi::communicator world;

	std::pair<int, float> p;
	p.first = 5;
	p.second = 3.0;
	if (world.rank() == 0)
	{
		p.first = 3;
		p.second = 1.5;
		world.send(1, 0, string("Hello")); //必须有string否则传递不全
		std::string msg;
		world.recv(1, 1, msg);
		VLOG(0) << msg << "!" << std::endl;
		world.send(1, 0, p);
	}
	else if (world.rank() == 1)
	{
		std::string msg;
		world.recv(0, 0, msg);
		VLOG(0) << msg << ", ";
		//std::cout.flush();
		world.send(0, 1, string("world2"));
		world.recv(0, 0, p);
		Pval(p.first);
		Pval(p.second);
	}
	VLOG(0) << "Finish";
	return 0;
}