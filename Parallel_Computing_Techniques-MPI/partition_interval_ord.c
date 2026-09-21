/*
 * Program partition_interval_ord:
 * now each processor fills up a vector of type double, containing the coordinates
 * of the gridpoints and sends it to the master to print all the gridpoints in
 * the correct order
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

int main( int argc, char **argv )
{
  int nprocs, rank, np, start, len;
  MPI_Status status;
  const int total_length = 100;
  int len_chunk, sta_chunk, end_chunk;
  int n, i;
  double pi, dx;
  double *coords, *buff;

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
  coords = malloc( len_chunk * sizeof( double ) );
  for ( n = 0; n < len_chunk; n++ )
     {
	for ( i = 0; i < rank; i++ ) printf( "\t" );
	coords[n] = ( sta_chunk + n ) * dx;
	printf( "Process rank: %d, n = %d, x[n] = %lf\n", rank, n, coords[n] );
     }

  /* Final print in order: 
     each subprocess sends the starting chunk index, the length of the chunk and the data
     to the master!
     */

  if ( rank == 0 )     /* master process */
     {
       // First, the master prints its own chunk of data
       for ( n = 0; n < len_chunk; n++ )
	   printf( "n = %d, x[n] = %lf\n", n, coords[n] );

       // then, it receives the start position, the length of the chunk and the chunks of data from the slaves and prints it!
       for ( np = 1; np < nprocs; np++ )
	   {
	      // Notice we have to pass a vector, so we pass the address of both start and len
	      MPI_Recv( &start, 1, MPI_INT, np, 0, MPI_COMM_WORLD, &status );
	      MPI_Recv( &len, 1, MPI_INT, np, 0, MPI_COMM_WORLD, &status );
              buff = malloc( len * sizeof( double ) );
	      // in this case, "buff" is already a vector!
	      MPI_Recv( buff, len, MPI_DOUBLE, np, 0, MPI_COMM_WORLD, &status );
	      for ( n = 0; n < len; n++ )
	          printf( "n = %d, x[n] = %lf\n", start + n, buff[n] );
	      free( buff );
	   }
     }
  else                 /* slave process */
     {
	MPI_Send( &sta_chunk, 1, MPI_INT, 0, 0, MPI_COMM_WORLD );
	MPI_Send( &len_chunk, 1, MPI_INT, 0, 0, MPI_COMM_WORLD );
	MPI_Send( coords, len_chunk, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD );
     }

  MPI_Finalize();

  exit(0);
}
