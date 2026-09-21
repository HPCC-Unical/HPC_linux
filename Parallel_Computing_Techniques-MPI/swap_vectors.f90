! Program swap_vectors:
! fills up two arrays with the first 20 even and odd integer numbers
! on two processors, then it swaps the two vectors by sending and receiving
! the two.

program swap_vectors

   implicit none

   include 'mpif.h'

   integer, parameter :: N = 20
   integer :: nproc, rank, ierr
   integer :: status( mpi_status_size )
   integer :: ieven, iodd
   integer :: even(N), odd(N)

   call mpi_init( ierr )
   call mpi_comm_size( mpi_comm_world, nproc, ierr)
   call mpi_comm_rank( mpi_comm_world, rank, ierr)

   if ( nproc /= 2 ) then
      write( 6, * ) 'Error! The number of MPI processes MUST be = 2!'
      write( 6, * ) 'Please, run again the program with: mpirun -np 2 ...'
      call mpi_finalize( ierr )
      stop
   endif

   if ( rank == 0 ) then
      do ieven = 1, N
         even( ieven ) = 2 * ieven
      enddo
      write( 6, * ) "Rank #: ", rank, "   Vector of even numbers before swapping:"
      write( 6, * ) even( 1 : N )

      call mpi_send( even, N, MPI_INTEGER, 1, 10, mpi_comm_world, ierr )
      call mpi_recv( odd, N, MPI_INTEGER, 1, 11, mpi_comm_world, status, ierr )
   else if ( rank == 1 ) then
      do iodd = 1, N
         odd( iodd ) = 2 * ( iodd - 1 ) + 1
      enddo
      write( 6, * ) "Rank #: ", rank, "   Vector of odd numbers before swapping:"
      write( 6, * ) odd( 1 : N )

      call mpi_recv( even, N, MPI_INTEGER, 0, 10, mpi_comm_world, status, ierr )
      call mpi_send( odd, N, MPI_INTEGER, 0, 11, mpi_comm_world, ierr )
   end if

   ! Prints the two swapped vectors

   if ( rank == 0 ) then
      write( 6, * ) "Rank #: ", rank, "   Vector of odd numbers after swapping:"
      write( 6, * ) odd( 1 : N )
   else if ( rank == 1 ) then
      write( 6, * ) "Rank #: ", rank, "   Vector of even numbers after swapping:"
      write( 6, * ) odd( 1 : N )
   end if

   call mpi_finalize( ierr )

end program swap_vectors
