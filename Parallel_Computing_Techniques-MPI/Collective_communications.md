# Collective communications

These are type of communications among the subprocesses that allow a basic exchange of information without the complexity of the **SEND/RECEIVE** mechanisms.

This kind of communications **MUST** involve **ALL** processes in the communicator alltogether.

Broadly speaking, we have five types of collective communications:

- **Syncronization**: the program stops until all processes have reached the same point;
- **Broadcast**: the same data are sent by one subprocess to all the remaining ones;
- **Scatter**: the data in a vector/array are evenly distributed from one subprocess to the others;
- **Gather**: data distributed on all subprocesses are gathered on only one of them (the opposite of **Scatter**!);
- **Reduction**: data are all used in a computation that is executed independently on all subprocesses and then finally the individual results are merged together and sent to one of the processes (e.g. when computing averages, maxima, etc.).

Benefits of **collective communications** are:

1. the code tends to be simpler than writing it with the classic SEND/RECEIVE;
2. there is generally also a **performance advantage**.

Things to consider are:

1. these routines **MUST** be called by all subprocesses, therefore they must stay outside a rank evaluation (`if (rank == ...) ...`);
2. the total amount of data transferred **MUST** be the same for all subprocesses;
3. the order of execution is fixed, therefore no **TAG** is necessary and often a syncronization is implied!

## Data synchronization
There is not so much to say on this: there are some situations in which a program cannot continue until all subprocesses have reached that point. In this case, it is mandatory to impose a **BARRIER** where a subprocess have to wait until also all others have reached that point.

The main function involved in data synchronization is **`MPI_Barrier**:

- in **C**:

    int MPI_Barrier( comm );

- in **Fortran**:

    integer :: ierr

    call mpi_barrier( comm, ierr )

Here **comm** is obviously the communicator, and **ierr** is used in Fortran for the usual error checking scope.

It is useful sometimes to impose an explicit synchronization like this, to ensure that each subprocess starts to work on consistent data. However, as said, many other collective operations imply directly that all processes have reached the same point, then an explicit call may not be necessary.

##  Data broadcasting
Sometimes one single subprocess has a value that needs to be sent to all the others. A typical example is when, for instance, the master process reads some input from the keyboard or from a file of parameters and those parameters need to be transmitted to all the other subprocesses.

This is realized throught the following functions/subroutines:

- in **C**:

    int MPI_Bcast( buffer, count, datatype, root, comm );

- in **Fortran**:

    integer :: count, type, root, comm, ierr

    call mpi_bcast( buffer, count, datatype, root, comm, ierr )

where:

- **buffer**: is a vector/array containing the information to be sent to all subprocesses;

- **count**: integer value, dimension of the buffer;

- **datatype**: one of the MPI data types;

- **root**: the rank of the subprocess that sends the information;

- **comm**: the communicator;

- **ierr**: the error status (integer in Fortran, pointer in C).

Let us consider the following example:

A(10) is a Fortran (or C) vector read from a file by the master process and it has to be sent to all subprocesses.

Normally one should do something like:

    if ( rank == 0 ) then
       do i = 1, nprocs-1
          call mpi_send( A, 10, MPI_REAL, i, tag, MPI_COMM_WORLD, ierr )
       end do
    else
       call mpi_recv( A, 10, MPI_REAL, 0, tag, MPI_COMM_WORLD, status, ierr )
    end if

By using **mpi_bcast**, one obtains the same result more quickly with less rows of code:

    call mpi_bcast( A, 10, MPI_REAL, 0, MPI_COMM_WORLD, ierr )

## Data scattering
This allows to take a vector/array present on one subprocess and distribute it (**scatter**) among all subprocesses.

The format of the call is:

- in **C**:

    int MPI_Scatter( send_buffer, send_count, send_datatype, recv_buffer, recv_count, recv_datatype, root, comm )

- in **Fortran**:

    call mpi_scatter( send_buffer, send_count, send_datatype, recv_buf, recv_count, recv_datatype, root, comm, ierr )

where:

- **send_buffer**: the initial buffer vector to be scattered among the subprocesses;

- **send_count**: the number of elements sent by the **root** subprocess (notice: **NOT** the total size of `send_buffer`, which is `send_count x nprocs`);

- **send_datatype**: the type of the data to be sent;

- **recv_buf**: the final buffer in which each subprocess will receive the data;

- **recv_count**: the number of elements actually received by each subprocess (should be equal to `send_count`!);

- **recv_datatype**: the type of the data to be received;

- **root**: the subprocess that actually sends the data to all the others;

- **comm**: the communicator;

- **ierr**: the usual error information in Fortran.

Note: it may seem **redundant** to specify both the **send_count** and **recv_count** as well as **send_datatype** and **recv_datatype**, since they should be coincident. However, one could imagine that, when defining new data types, this function could also work as some sort of type conversion among the subprocesses. Remember however that the total size of data transmitted and received **MUST** be the same!

For instance, suppose to have a vector `A(16)` of 16 integer elements that has to be distributed from the master with 4 consecutive elements on each subprocess. Normally, by using `send/receive` one would have:

    integer :: A(16), B(4)
    
    if (rank==0) then
       do i = 1, 16
          A(i) = i
       end do
       do np = 1, 3
          B(1:4) = A(np*4+1:(np+1)*4)
          call mpi_send( B, 4, MPI_INTEGER, np, tag, MPI_COMM_WORLD, ierr )
       end do
       B(1:4) = A(1:4)
    end if
    else
       call mpi_recv( B, 4, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, status, ierr )
    end if

With `mpi_scatter`:

    if (rank==0) then
       do i = 1, 16
          A(i) = i
       end do
    end if
    call mpi_scatter( A, 4, MPI_INTEGER, B, 4, MPI_INTEGER, 0, MPI_COMM_WORLD, ierr )

which is more compact!

## Data gathering
Gathering of data is the **opposite** operation of data scattering: a vector distributed among the different subprocesses can be transferred with one single call to a function to a single **root** subprocess (typically the `master`).

The format of the function/subroutine is:

- in **C**:

    int MPI_Gather( send_buffer, send_count, send_datatype, recv_buffer, recv_count, recv_datatype, root, comm )

- in **Fortran**:

    call mpi_gather( send_buffer, send_count, send_datatype, recv_buffer, recv_count, recv_datatype, root, comm, ierr )

where:

- **send_buffer**: the initial buffer vector to be gathered from the different subprocesses;

- **send_count**: the number of elements sent to the **root** by all subprocesses (should be equal to `recv_count`!);

- **send_datatype**: the type of the data to be sent;

- **recv_buf**: the final buffer in which the root subprocess will receive the data;

- **recv_count**: the number of elements actually received by the root subprocess (notice: **NOT** the total size of `recv_buffer`, which is `recv_cou
nt x nprocs`);

- **recv_datatype**: the type of the data to be received by the root;

- **root**: the subprocess that actually receives the data from all the others;

- **comm**: the communicator;

- **ierr**: the usual error information in Fortran.

Example:

Let `A(4)` be a vector present on all 4 subprocesses and we want to gather all values of the different `A`s on a unique vector `B(16)` of 16 elements on the root. Normally, by using send/receive one would write:

    integer :: A(4), B(16)

    do i = 1, 4
       A(i) = rank * 4 + i
    enddo
    if ( rank /= 0 ) then
       call mpi_send( A, 4, MPI_INTEGER, 0, tag, MPI_COMM_WORLD, ierr )
    endif
    if (rank==0) then
       B(1:4) = A
       do np = 1, 3
          call mpi_recv( A, 4, MPI_INTEGER, np, tag, MPI_COMM_WORLD, status, ierr )
       do i = 1, 3
          B(i*4+1:i*4+4) = A
       end do
    end if

With `mpi_gather`:

    if (rank==0) then
       do i = 1, 16
          A(i) = i
       end do
    end if
    call mpi_gather( A, 4, MPI_INTEGER, B, 4, MPI_INTEGER, 0, MPI_COMM_WORLD, ierr )

which is more compact!

## Data reduction
This refers to a computational operation performed on data distributed over different processes.

This is generally very useful when one has to compute statistical operations on data distributed on the different subprocesses or global quantities related to a field (e.g. the total energy of a field on a partitioned domain).

The main **reduction** function in MPI is:

- in **C**:

    int MPI_Reduce( send_buffer, recv_buffer, count, datatype, operation, root, comm );

- in **Fortran**:

    call mpi_reduce( send_buffer, recv_buffer, count, datatype, operation, root, comm, ierr )

where:

- **send_buffer**: the original data, spreaded on the subprocesses, to be combined with the **operation**;

- **recv_buffer**: the buffer that receives the result of **operation** on the **root**;

- **count**: the size of the buffer(both send and recv);

- **datatype**: the type of data to be combined;

- **operation**: the actual operation to be performed (sum, max, min, prod, etc.);

- **root**: the process that receives the result in `recv_buffer`;

- **comm**: the communicator;

- **ierr**: the usual error flag in Fortran.

In general, using MPI_Reduce instead of gathering the data from all processes and performing the final operation on **root** can involve a consistent saving of cpu time and memory.

The **operations** are:

| MPI operation | Mathematical operation |
| :---- | :---- |
| MPI_MAX | Maximum |
| MPI_MIN | Minimum |
| MPI_SUM | Sum |
| MPI_PROD | Product |
| MPI_MAXLOC | Maximum and location |
| MPI_MINLOC | Minimum and location |

Example:

suppose to have to compute the total sum of a vector `A(N)` of `N` real values on 4 subprocesses. Normally, by using SEND/RECEIVE one would write:

    real :: A(N), RES(4), TOT_SUM

    do i = 1, N
       A(i) = ...
    enddo
    RES( rank ) = sum( A )
    if ( rank /= 0 ) then
       call mpi_send( RES, 1, MPI_REAL, 0, MPI_COMM_WORLD )
    else
       TOT_SUM = RES                ! Saves the local sum first in TOT_SUM
       do np = 1, nprocs
          call mpi_recv( RES, 1, MPI_REAL, np, MPI_COMM_WORLD, status, ierr ) 
          TOT_SUM = TOT_SUM + RES   ! Then add the contribution of all other subprocesses
       end do
       print *, 'The total sum is: ', TOT_SUM
    end if

with mpi_reduce:

    real :: A(N), RES(N)

    do i = 1, N
       A(i) = ...
    enddo
    call mpi_reduce( A, RES, N, MPI_REAL, MPI_SUM, 0, MPI_COMM_WORLD, ierr )
    ! Only the root process (the master, in this case!) receives the result...
    if ( rank == 0 ) then
       print *,'The total sum is: ', sum( RES )
    endif

There exist **more advanced** forms of collective communications that will be treated in next lectures.
