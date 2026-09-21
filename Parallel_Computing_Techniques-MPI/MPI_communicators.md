# MPI Communicators

As said, MPI works spawning a set of subprocesses that, in principle, should work in parallel on a single partition of the problem.

In order to operate on the different partitions of the problem (being either a subdomain of a global domain, or a subset of data, etc.), each subprocess must have some reference to itself, in order to know on what data it is operating as well as the others.

Here enters the concept of **COMMUNICATOR**!

A communicator is an abstract object containing a reference to all processes that spawned by the MPI run. There is in general no need to create such object, MPI creates automatically one for you, called **`MPI_COMM_WORLD`**, that will contain a reference to each subprocess of the team. In particular, each subprocess is assigned a **unique identifier** called **RANK**, such that each of the subprocess can know what is its own RANK.

Notice that it is not necessary that one uses only `MPI_COMM_WORLD`: further communicators can be created for special purposes, to allow for instance some of the processes to communicate independently from the other. However, this feature will not be treated here.

Once the run using MPI has been launched, the team of subprocesses created with `MPI_Init`, each subprocess can get information about the total number of subprocesses involved in the communicator and its own rank by calling the following two MPI functions:

- in C:

    int MPI_Comm_size( MPI_comm comm, int * size );

- in Fortran:

    integer :: comm, size, ierr

    call mpi_comm_size( comm, size, ierr )

to determine the total number (size) of the processes involved in the communicator,

- in C:

    int MPI_Comm_rank( MPI_comm comm, int * rank );

- in Fortran:

    integer :: comm, rank, ierr

    call mpi_comm_rank( comm, rank, ierr )

to determine the rank of the current subprocess in the communicator.

**Note as:**

1. in C, all MPI functions return an integer value (which can be omitted!) that represents an error status;
2. in Fortran, where functions and subroutines are clearly distinct objects, it is necessary for the library to return the status in the last parameter passed to the subroutines, the integer value `ierr`;
3. this happens for all the MPI functions!
4. C is **case sensitive**, therefore one has to be careful with the name of the functions, that always start with `MPI_` and a capital letter;
5. Fortran is **NOT case sensitive**, so on can use both capital or lowercase letters to specify the functions to invoke.
6. in C, the communicator `comm` is a variable of type MPI_comm (actually a pointer), in Fortran, for compatibility reasons, `comm` is an integer (a default integer in Fortran has the same number of bytes as a pointer in C!)

The size of the communicator coincides with the number `size` of processes the MPI program was executed with. The `RANK` is an integer value that ranges from 0 to `size-1`. Generally, the subprocess with `RANK=0` is called `the master` and generally the others are called `slaves`. Notice that there is **NOTHING SPECIAL** in the `master process` with respect to the others, simply MPI keeps this distinction because sometimes the result of some operation must be addressed to a single process and that is generally the `master`.

The following is a simple example of MPI `Hello World`: [hello_world.f90](file:hello_world.f90) in Fortran...

The following is instead a slightly more complicated program in C that splits a domain `[0,2\pi]` with `N` evenly spaced gridpoints on `n` processors: [partition_interval.c](file:partition_interval.c)

Notice one problem here: the output is (almost!) completely mixed up! This is typical, since there is no predefined order in which the subprocesses can write on the output. This is seldom a true problem in practice, since many times the output is managed by only **ONE SUBPROCESS** (generally the **MASTER**) that receives all the data from all other subprocesses and prints them in order. But there are also several other ways to manage the output correctly. We will see some at the end of the lectures.

## Point-To-Point communications

In case we want to do exactly what we cited before, namely we want to send each chunk of the vector, defined on the different processes, to the master to be printed in the correct order, what do we do?

This is a general and most important case, in which we want the different processes to **COMMUNICATE** each with the others.

To manage communications in MPI one can use two functions (though we will see later several variants of these two!):

- in C:

    int MPI_Send( buffer, count, datatype, dest, tag, comm );

    int MPI_Recv( buffer, count, datatype, source, tag, comm, status );

- in Fortran:

    call mpi_send( buffer, count, datatype, dest, tag, comm, ierr )

    call mpi_recv( buffer, count, datatype, source, tag, comm, status, ierr )

Note the usual presence of the final `ierr` variable in Fortran, due to the fact that MPI functions are actually subroutines in Fortran!

Here we describe the meaning of the different formal parameters of the function/subroutine:

- **buffer**: a contiguous area of memory containing the data to be transmitted (basically an **ARRAY**);

- **count**: the dimension of the data (the **size of the array** to be transmitted);

- **datatype**: one of the data type accepted by MPI (see later);

- **dest**: the rank of the process that has to receive the data;

- **source**: the rank of the process that has to send the data;

- **tag**: can be any integer number and identifies the communication;

- **comm**: the communicator (generally `MPI_COMM_WORLD`);

- **status**: a status vector of integers (of type `MPI_Status` in C, a vector of integer with dimension `mpi_status_size` in Fortran!) describing the result of the communication (generally ignored, except for debugging).

What type of data can be transmitted/received in a communication?

- in C:

| MPI Data type | C Data type |
| :---- | :---- |
| MPI_CHAR | signed char |
| MPI_SHORT | signed short int |
| MPI_INT | signed int |
| MPI_LONG | Signed long int |
| MPI_UNSIGNED_CHAR | unsigned char |
| MPI_UNSIGNED_SHORT | unsigned short int |
| MPI_UNSIGNED | unsigned int |
| MPI_UNSIGNED_LONG | unsigned long int |
| MPI_FLOAT | float |
| MPI_DOUBLE | double |
| MPI_LONG_DOUBLE | long double |
| MPI_BYTE | unsigned char |

- in Fortran:

| MPI Data type | Fortran Data type |
| :---- | :---- |
| MPI_INTEGER | INTEGER |
| MPI_REAL | REAL |
| MPI_DOUBLE_PRECISION | DOUBLE PRECISION !
| MPI_COMPLEX | COMPLEX |
| MPI_DOUBLE_COMPLEX | DOUBLE COMPLEX |
| MPI_LOGICAL | LOGICAL |
| MPI_CHARACTER | CHARACTER(1) |
| MPI_BYTE | BYTE |

Note that those are only the **BASIC TYPES OF DATA**. It is possible to construct **more complex structures of data!**

**Very important note:**

since the **buffer** can be **any** contiguous area of memory, like a vector or even an array, one **must ensure** that the sent and received datatypes **ARE THE SAME** and that the data are **NOT SCATTERED** in memory, like it happens with arrays!

Here is another example of the previous program, `partition_interval.c`, in which all the data computed on the `slave` subprocesses are subsequently sent to the `master` to be print in order: [partition_interval_ord.c](file:partition_interval_ord.c)

The following program is useful to illustrate a rather common problem: the **SEND** and **RECV** functions are **NOT** interchangeble! If they are **NOT** called in the proper order it may happen that all processes for instance wait for **receiving data** without any of them **sending data**, that translates into a **neverending waiting!**. Such a situation is called **DEADLOCK**.

Have a look at the program: [swap_vectors.f90](file:swap_vectors.f90) and check that it works properly in the present form. Then, exchange the send/receive order of one of the processor and see what happens!

All the communication subroutines/functions seen until now are **BLOCKING**, that is when the subprocesses communicate among them, everything is blocked to wait for the end of the communication. This is the easiest and safest thing to do, however it may decrease consistently the performances. We will see later on other forms of communications that are **NON-BLOCKING**!
