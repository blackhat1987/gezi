#include <boost/mpi.hpp>
#include <iostream>
#include <string>
#include <boost/serialization/string.hpp>
#include <glog/logging.h>
#include <gflags/gflags.h>
namespace mpi = boost::mpi;
using namespace std;
int main(int argc, char* argv[])
{
	mpi::environment env(argc, argv);
	mpi::communicator world;

	std::string value = "abc";
	if (world.rank() == 0) {
		value = "Hello, World!";
	}
	if (world.rank() == 1)
	{
		value = "Hello, world 1";
	}

	
	broadcast(world, value, 1);
	
	

	std::cout << "Process #" << world.rank() << " says " << value 
		<< std::endl;

	return 0;

	world.barrier();

	int start = 0;
	int rank = world.rank();
	int size_ = world.size();
	while (1)
	{
		if (start >= size_ )
		{
			break;
		}
		
		LOG(INFO) << rank << " start: " << start << endl;
		if (rank >= start && rank < start + 2)
		{
			LOG(INFO) << rank << " Start downloading " << endl;
			LOG(INFO) << rank << " End downloading  " << " ..." << endl;
			world.barrier();
			//LOG(INFO) << rank << " Before brodacast" << endl;
			//if (rank == start)
			//{
				//start += 2;
				//broadcast(world, start, rank);    //this will not work ,how can fix?
				//LOG(INFO) << rank << " Now " << start << endl;
			//}
			
			//LOG(INFO) << rank << " After brodacast" << endl;
			//break;
		}
		else
		{
			world.barrier();
			LOG(INFO) << rank << " " << start << endl;
		}
		start += 2;
	}

	//world.barrier();
	LOG(INFO) << rank << " finish" << endl;

	return 0;
} 