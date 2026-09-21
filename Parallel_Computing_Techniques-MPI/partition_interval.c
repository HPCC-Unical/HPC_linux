#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main( int argc, char **argv )
{
  int nprocs, rank;
  const int total_length = 100;
  int len_chunk, sta_chunk, end_chunk;
  int n, i;
  double pi, dx;

  MPI_Init( &argc, &argv );
  MPI_Comm_size( MPI_COMM_WORLD, &nprocs );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );

  len_chunk = ( int ) ( total_length * 1.0 / nprocs );
  sta_chunk = rank * len_chunk;
  end_chunk = sta_chunk + len_chunk - 1;
  if ( rank == nprocs - 1 )
     {
       end_chunk = total_length;
       len_chunk = total_length - sta_chunk + 1;
     }


  pi = acos( -1.0 );
  dx = 2.0 * pi / total_length;
  for ( n = sta_chunk; n <= end_chunk; n++ )
     {
	for ( i = 0; i < rank; i++ ) printf( "\t" );
	printf( "Process rank: %d, n = %d, x = %lf\n", rank, n, n * dx );
     }

  MPI_Finalize();

  exit(0);
}
