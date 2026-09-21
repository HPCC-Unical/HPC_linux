program hello_world

  include 'mpif.h'

  integer :: ierr, rank, size

  call mpi_init( ierr )
  call mpi_comm_size( MPI_COMM_WORLD, size, ierr )
  call mpi_comm_rank( MPI_COMM_WORLD, rank, ierr )

  if ( rank == 0 ) then
     print *,'Hello World from process rank n. ', rank, ' (master!)'
  else
     print *,'Hello World from process rank n. ', rank, ' (slave!)'
  end if

  call mpi_finalize( ierr )

end program hello_world
