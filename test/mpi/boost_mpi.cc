#include <boost/mpi.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
	boost::mpi::environment env(argc, argv);
	boost::mpi::communicator world;

	std::cout << argc << std::endl;
	std::cout << argv[0] << std::endl;
	std::cout << "Hello World! from process " << world.rank()  << " of " << world.size() << std::endl;

	return 0;
}
