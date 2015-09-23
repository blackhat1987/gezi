#include <stdio.h>
#include <fstream>
#include "mpi.h"

using namespace std;
int main(int argc, char *argv[])
{
  int nproc;
  int iproc;
  char proc_name[MPI_MAX_PROCESSOR_NAME];
  int nameLength;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&nproc);
  MPI_Comm_rank(MPI_COMM_WORLD,&iproc);
  
  MPI_Get_processor_name(proc_name,&nameLength);
  printf("Hello World, Iam host %s with rank %d of %d\n", proc_name,iproc,nproc);
  
  ofstream ofs("a.txt");
  ofs << iproc << endl;

  MPI_Finalize();
  
  return 0;
}

