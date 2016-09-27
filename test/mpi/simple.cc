/**
 *  ==============================================================================
 *
 *          \file   simple.cc
 *
 *        \author   chenghuige
 *
 *          \date   2011-05-30 10:18:50.115476
 *
 *   \Description
 *
 *  ==============================================================================
 */

#include <mpi.h>
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	cout << "ok" << endl;
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int nproc;
	char proc_name[MPI_MAX_PROCESSOR_NAME];
	int nameLength;
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Get_processor_name(proc_name, &nameLength);

	if (rank == 0)
	{
		int value = 17;
		int result = MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		if (result == MPI_SUCCESS)
		{
			std::cout << "Rank 0 OK!" << std::endl;
			printf("Hello World, Iam host %s with rank %d of %d\n", proc_name, rank, nproc);
			ofstream ofs("temp");
			ofs << "hi i am host " << proc_name << " rank: " << rank << " of " << nproc;
		}
		else
			cout << result << endl;
	}
	else if (rank == 1)
	{
		int value;
		int result = MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);
		if (result == MPI_SUCCESS && value == 17)
		{
			std::cout << "Rank 1 OK!" << std::endl;
			printf("Hello World, Iam host %s with rank %d of %d\n", proc_name, rank, nproc);
			ofstream ofs("temp");
			ofs << "hi I am host: " << proc_name << " with rank: " << rank << " of " << nproc << " value:" << value;
		}
		else
		{
			cout << result << endl;
			cout << value << endl;
		}
	}
	MPI_Finalize();
	return 0;
}
