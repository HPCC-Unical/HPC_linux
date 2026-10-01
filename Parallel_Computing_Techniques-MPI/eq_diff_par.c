/*
 * Program eq_diff_par.c:
 * it solves the dissipative advection equation with periodic boundary conditions
 * in an interval: x \in [0,2\pi], in parallel on np processes.
 * Each process allocate vectors of dimension N for the variables and the derivatives.
 * Therefore, the total spatial grid resolution will be: np x N.
 */

#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

/* Main program */

int main( int argc, char **argv )
{
    /* Constant (vector dimensions) */
    const int N = 100;

    /* Variables */
    double dt, Tprint, Tend;   /* Time variables: time step size, interval between printouts, final time */
    double dx, d2x, dx2;       /* Spatial variables: width of spatial interval, 2*dx, dx^2 */
    double cc, nu, kk;         /* Simulation parameters: cc = propagation speed, nu = viscosity, wavevector of initial perturbation */
    double energ, tot_energ;   /* Partial energy and total energy */
    int Nsteps, Nprints;       /* Total number of time steps and number of steps between printouts */
    int debug;                 /* If requested, prints out informations on the state of the simulation */
    int Ntot;                  /* Total number of gridpoints ( nprocs * N ) */

    /* Vector allocation */
    double xx[N], ff[N], df[N], d2f[N];   /* Gridpoints, solution, first and second derivative */

    /* Vector to contain the total vectors (meaningful only for root!) */
    double *total_xx, *total_vect;

    /* MPI variables */
    int rank, nprocs;
    MPI_Status status;
    int proc_prev, proc_next;

    /* Generic variables (for loops, files, and so on) */
    double pi, ff_lbound, ff_rbound;
    double tt;
    int nt, nouts, j;
    FILE *finp, *fout;
    char fnstr[256];


    /* Begin of the program */

    /* MPI initialization */
    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &nprocs );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    proc_prev = rank - 1;
    proc_next = rank + 1;
    if ( rank == 0 ) proc_prev = nprocs - 1;
    if ( rank == nprocs - 1 ) proc_next = 0;
 
    /* Reading the parameters from the parameters file (only root does this!) */
    if ( rank == 0 )
       {
	finp = fopen( "parameters.data", "r" );
        fscanf( finp, "%lf", &dt );
        fscanf( finp, "%lf", &Tend );
        fscanf( finp, "%lf", &Tprint );
	fscanf( finp, "%lf", &cc );
	fscanf( finp, "%lf", &nu );
	fscanf( finp, "%lf", &kk );
	fscanf( finp, "%d", &debug );
       }

    /* The root process sends the values of the parameters to all other processes through a call to MPI_broadcast */
    MPI_Bcast( &debug, 1, MPI_INT, 0, MPI_COMM_WORLD );
    MPI_Bcast( &dt, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Bcast( &Tend, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Bcast( &Tprint, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Bcast( &cc, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Bcast( &nu, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );
    MPI_Bcast( &kk, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD );

    /* Debugging */
    if ( debug )
       {
	 printf( "--------------- Parameters on each process -------------------\n" );
	 printf( "Rank: %d, dt = %lf\n", rank, dt );
	 printf( "Rank: %d, Tend = %lf\n", rank, Tend );
	 printf( "Rank: %d, Tprint = %lf\n", rank, Tprint );
	 printf( "Rank: %d, cc = %lf\n", rank, cc );
	 printf( "Rank: %d, nu = %lf\n", rank, nu );
	 printf( "Rank: %d, kk = %lf\n", rank, kk );
	 printf( "--------------- Previous and following procs ------------------\n" );
	 printf( "Rank: %d, \t Previous process: %d,\t Following process: %d\n", rank, proc_prev, proc_next );
       }

    Nsteps = ( int ) ( Tend / dt );
    Nprints = ( int ) ( Tprint / dt );

    /* Construction of the grid-points and initial condition (on the root only!) */
    pi = acos( -1.0 );
    Ntot = N * nprocs;
    dx = 2.0 * pi / Ntot;
    d2x = 2.0 * dx;
    dx2 = dx * dx;

    if ( rank == 0 )
       {
         total_xx = malloc( Ntot * sizeof( double ) );
         for ( j = 0; j < Ntot; j++ ) total_xx[j] = j * dx;
       }
    MPI_Scatter( total_xx, N, MPI_DOUBLE, xx, N, MPI_DOUBLE, 0, MPI_COMM_WORLD ); 

    if ( rank == 0 )
       {
         total_vect = malloc( Ntot * sizeof( double ) );
         for ( j = 0; j < Ntot; j++ ) total_vect[j] = sin( kk * j * dx );
       }
    MPI_Scatter( total_vect, N, MPI_DOUBLE, ff, N, MPI_DOUBLE, 0, MPI_COMM_WORLD ); 

    /* Prints on a file the initial condition */
    nouts = 0;
    tt = 0.0;
    if ( rank == 0 )
       {
         printf( "Print the solution at time: %lf\n", tt );
         sprintf( fnstr, "out-%d.dat", nouts );
	 fout = fopen( fnstr, "w" );
	 for ( j = 0; j < Ntot; j++ ) fprintf( fout, "%g\t%g\n", total_xx[j], total_vect[j] );
	 fclose( fout );
	 nouts++;
        }

    /* Puts a barrier here to ensure that all processes start the time loop at the same time */
    MPI_Barrier( MPI_COMM_WORLD );

    /* Time loop */
    for ( nt = 1; nt <= Nsteps; nt++ )
	{
          tt = nt * dt;                   /* Current time */

	  /* Computation of the first and second derivative at the current time */
	  /* Calculation for the internal points */
	  for ( j = 1; j < N - 1; j++ )
	      {
		df[j] = ( ff[j+1] - ff[j-1] ) / d2x;
		d2f[j] = ( ff[j+1] + ff[j-1] - 2.0 * ff[j] ) / dx2;
	      }
	  /* Each process transmits the boundary values of the solution to the previous and following process */
	  ff_lbound = ff[0];
	  ff_rbound = ff[N-1];
	  MPI_Send( &ff_lbound, 1, MPI_DOUBLE, proc_prev, 10, MPI_COMM_WORLD );
	  MPI_Send( &ff_rbound, 1, MPI_DOUBLE, proc_next, 11, MPI_COMM_WORLD );
	  /* Each process receives the boundary values from the previous and following process... */
	  MPI_Recv( &ff_rbound, 1, MPI_DOUBLE, proc_next, 10, MPI_COMM_WORLD, &status );
	  MPI_Recv( &ff_lbound, 1, MPI_DOUBLE, proc_prev, 11, MPI_COMM_WORLD, &status );
	  /* ... then computes the derivatives on the boundaries ... */
	  df[0] = ( ff[1] - ff_lbound ) / d2x;
	  df[N-1] = ( ff_rbound - ff[N-2] ) / d2x;
       	  d2f[0] = ( ff[1] + ff_lbound - 2.0 * ff[0] ) / dx2;
	  d2f[N-1] = ( ff_rbound + ff[N-2] - 2.0 * ff[N-1] ) / dx2;

	  /* Updates the solution at the next time step */
	  for ( j = 0; j < N; j++ )
	      {
		ff[j] = ff[j] + dt * ( - cc * df[j] + nu * d2f[j] );
	      }

	  /* At printout time, prints the solution on a file */
	  if ( ( nt % Nprints ) == 0 )
	     {
	      /* Gather all pieces of the solution scattered on the different processes on the root */
	      MPI_Gather( ff, N, MPI_DOUBLE, total_vect, N, MPI_DOUBLE, 0, MPI_COMM_WORLD );
	      /* The root process prints the values on a file */
	      if ( rank == 0 )
	         {
	           printf( "Print the solution at time: %lf\n", tt );
		   sprintf( fnstr, "out-%d.dat", nouts );
	           fout = fopen( fnstr, "w" );
	           for ( j = 0; j < Ntot; j++ ) fprintf( fout, "%g\t%g\n", total_xx[j], total_vect[j] );
	           fclose( fout );
		   nouts++;
	         }
	     }
    /* Puts another barrier here to ensure that all processes start the next cycle of the time loop at the same time */
    MPI_Barrier( MPI_COMM_WORLD );

 }

    /* MPI ends here */
    MPI_Finalize();

    return 0;
}
