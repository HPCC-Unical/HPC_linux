# Message Passing Interface (MPI)

## General overview on computational machines

Computational machines for **High Performance Computing** (HPC) are generally divided into 2 categories:

- **shared memory machines** (SMM), in which the computational appliance (CA) is built as a single monolitic computer made of an ensemble of one or more powerful **CPUs** each made of many **cores** and a **large memory array**, that can be seen by all the cores of the machine (although **NOT** at the same speed, on different NUMA nodes!);

- **distributed memory machines** (DMM), in which the CA is built as a **Cluster**, namely by putting together a (possibly!) large number of **computational nodes** (basically single PCs, each one equipped with its own CPUs and interconnected through a (possibly!) **high speed network connection**.

In the first case, one can run programs that fork into a team of threads that execute computations in parallel, one for each CPU-Core. The threads can access (read/write) the same memory areas at the same time.

In the second case, the different nodes are interconnected through the network, but the program runs as an ensemble of independent sub-processes, isolated each from the others and communicating when necessary by exchanging **messages** through the network connection.

The OpenMP paradigm works on **SMMs only!**.

The **Message Passing Interface** (MPI) is a library to run parallel codes on **DMMs**.

## Advantages and disadvantages

There are advantages and disadvantages in both approaches:

**Advantages** of shared memory computation:

- the memory of the machine is **shared** among all threads, so there is no need for communicating over the network, that can be a slow operation, depending on the network speed;

- writing a parallel program can be a more or less easy task, in the sense that an existing program requires few modifications to run in parallel by using only simple **compiler directives**.

**Disadvantages** of shared memory computation:

- the speed-up of the computation can be drastically reduced when too much memory is required, due to the limited bandwidth of the memory bus;

- generally, on shared memory machines, the sequence of fork/join of the threads is managed by the software (see the case of OpenMP) and is the program is made of several of these sequences, this can become a true bottleneck, due to the slowness of opening/closing processes operations;

- on SMM each processor has a **single cache**, i.e. the total amount of cache is shared among the different threads, resulting in a smaller amount of cache available for each thread.

**Advantages** of distributed memory computation:

- the approach is **highly scalable** since both CPU-Cores and memory are distributed among the nodes;

- the cluster can, in principle, be eterogeneous (i.e. made of nodes with different speeds) or even localized in different places (**grid computing**);

- the distributed memory approach is more generic, that is: MPI can be used with very good performances even on single nodes, or on a SMM; OpenMP or a generic multi-threaded paradigm can be only executed on SMM and **not** on DMM!

- on DMMs, each CPU has its own cache, thus resulting in a larger amount of fast memory available, that can reduce drastically the execution of the codes.

**Disadvantages** of distributed memory computation:

- the communications happen through the interconnection network, that is much slower than the memory bus of the single node, that is one has to **limit the internode communications as much as possible**;

- the code has to be written **as parallel since the beginning**, porting a serial code to a DMM can be a difficult task.

In principle, also for sake of lowering the costs and increasing the scalability, the majority of the [**TOP 500**](https://www.top500.org/lists/top500/2026/06/) computers are **clusters**, that is, DMMs!

However, it is rather common to use a **hybrid approach** on clusters, that is use MPI for the internode communication and use a multi-threaded approach (like OpenMP) on the single nodes, that may improve the performances in some cases. This technique can be advantageous in some cases, depending on the structure of the program, the number of cores on the single nodes, and so on.


## Introduction to MPI

The **Message Passing Interface** (MPI) is a **library** or, more properly an **API** (Application Programming Interface) for distributed parallel computing.

The first version (1.0) was issued in 1994. The latest version is the 5.0, issued in 2025! [https://www.mpi-forum.org/docs/](https://www.mpi-forum.org/docs/)

There is a standard, but different implementations (theoretically all equivalent, but there can be differences!):

- OpenMPI (not to be confused with OpenMP!) [https://www.open-mpi.org/](https://www.open-mpi.org/)
- LAM-MPI (Local Area Multicomputer-MPI) [https://www.dcs.ed.ac.uk/home/trollius/www.osc.edu/lam.html](https://www.dcs.ed.ac.uk/home/trollius/www.osc.edu/lam.html)
- MPICH/MPICH2 [https://www.mpich.org/](https://www.mpich.org/)
- Intel MPI [https://www.intel.com/content/www/us/en/developer/tools/oneapi/mpi-library.html](https://www.intel.com/content/www/us/en/developer/tools/oneapi/mpi-library.html)
- and several others...

Again, each one has its own features:

- OpenMPI is completely open-source and based on open-source components. It is rather fast, though it implements older versions of MPI;
- MPICH has very good support for debugging;
- Intel MPI has very good performances because it exploits some special features of the Intel CPUs, but cannot run on different CPUs (like AMD clusters), non-free, part of the MKL library suite.

We will use in the course **OpenMPI**, which is freely available on any linux distribution.

To install it on a Debian/Ubuntu GNU-Linux:

   # apt install openmpi-bin libopenmpi-dev

On clusters where the system is managed by administrators, generally one can find the different implementations of MPI that can be compiled with different compilers (e.g. **gnu** or **intel**) and loaded as **modules**.

For instance, on **alarico.hpcc.unical.it**:

| Syntax | Action |
| :--- | :--- |
| `module load gnu12 openmpi4` | loads the openmpi implementation compiled with the GNU compiler suite |
| `module load gnu12 mpich` | loads the mpich implementation compiled with the GNU compiler suite |
| `module load intel impi` | loads the Intel MPI implementation compiled with the Intel compiler |

etc.

The standard MPI can be called by both **C** and **Fortran** programs (notice that there is no specific **C++** implementation! **C++** users must compile the codes along with the C library).

However, there are also some specific implementations that can be called from **Python**, **Rust**, **R**, and so on...

To compile a **C** code that uses MPI, use:

   $ mpicc mpi_program_name.c

or, for a Fortran code:

   $ mpif90 mpi_program_name.f90

To execute a binary compiled with the MPI library, use:

   $ mpirun -np number_of_cores mpi_program_binary

where `number_of_cores` is the number of CPU-Cores (in principle, the number of subprocessed to be spawned) on which the program has to run!

An equivalent statement is: `mpiexec`

Notice that, for testing purposes of the installation, **ANY** program, even a serial one, can be run with `mpirun`, that simpley invokes several instances of the same process.

On clusters of different nodes, in which a scheduler of queues is installed (like **SLURM**, for instance), one **MUST** use the scheduler commands to run the program, instead of `mpirun`!

## Structure of an MPI program

Being **MPI** a library, the first thing a program has to do to use it is **to include** the header of the library:

- `#include <mpi.h>` in C;
- `use mpif.h` in Fortran.

Notice that modern Fortran compilers should include **mpif_08** instead of **mpif.h**, that allows the use of the new Fortran 2008 bindings with type-safety detection and full compile-time arguments checking. However, this is **NOT** supported on many systems!

The MPI implementation requires that, when launched, a MPI program spawns **a team of subprocesses, each one running on a different node/CPU-Core** (notice that, in principle, it is also possible to run more than one subprocess on the same CPU-Core, however the performances will be degraded! Remember to **not run MPI codes with a number of processes larger than the number of available CPU-Cores!**).

This operation is realized through an initial call to the function:

| C | Fortran |
| :----: | :----: |
|`MPI_Init( &argc, &argv );`|`call mpi_init()`|

At the end of the parallel execution, the team of subprocesses can be shut down with the call to the function:

| C | Fortran |
| :----: | :----: |
|`MPI_Finalize();`|`call mpi_finalize()`|

Note a **huge difference** between the approach of **MPI** and the one of a multi-threaded paradigm like **OpenMP**!

In OpenMP the program can alternate serial parts with multi-threaded parts that are executed in parallel. In general all the variables of the program are **PUBLIC** (that is, visible to all threads) and only the ones that change their values in each thread are **PRIVATE**.

In MPI, there is no sequence of serial/parallel parts, but the program should start with `MPI_Init` and end with `MPI_Finalize`, that is should be thought as parallel since the beginning! As a consequence, since each subprocess has no access to the memory of other subprocesses (except when the values of the variables are explicitly transmitted through **messages**) all variables are necessarily **PRIVATE**.

Therefore, the parallelism in MPI is realized by partitioning the problem in such a way that each subprocess executes operations on each single element of the partition. Whenever a subprocess needs an information that is owned by another subprocess of the team, the transmission of the information happens through the **exchange of messages**. These are called **Communication operations**.

Equivalently, if the result of a calculation depends on the results obtained for each element of the partition, each subprocess can send its own result (through suitable calls to the appropriate subroutines) to the others and the final operation will be performed and sent to one specific subprocess. These are called **Reduction operations**.

Examples:

1. Consider the case in which one wants to execute a large matrix by matrix (`A x B`, each of dimensions `n x n`) multiplication in parallel on `N` CPU-Cores. Therefore one should:
- assign `n/N` rows of `A` and `n/N` columns of `B` to each core;
- each core can compute separately the products and the sums for the `n/N` rows and `n/N` columns hold by it;
- when it has to execute the products for the other cores, it needs to know, for instance, columns of the matrix that are stored on another core, therefore it expects to **RECEIVE** the missing piece of data from the other core, that **SEND**s it;
- in turn the first core has to **SEND** its piece of columns to the other cores in order to complete the operation.

2. Consider the case in which one has to solve a differential equation on a one-dimensional domain made of `M` gridpoints on `n` CPU-Cores with a finite-difference method. One can:
- partition the domain assigning each core `M/n` gridpoints on which to carry on the computations;
- compute the derivatives on all internal gridpoints of each subdomain;
- on the boundaries of each subdomain, in order to compute the derivatives, each core has to **SEND** its boundary values to the previous and subsequent core, as well as all other core has to **RECEIVE** the same data by the others;
- once the derivatives are computed, each core can advance the equation in time independently on each subdomain.

3. Consider a statistical program that has to compute the average, standard deviation and other statistical moments on a dataset of `n` elements, on `N` CPU-Cores. One can:
- partition the dataset by assigning `n/N` elements to each core;
- each core computes the sum, sum of the squares, etc. for each element it knows;
- then, through a **REDUCTION OPERATION +**, the total sum of the partial sums is computed and send to all subprocesses or to one single process.

Now, the problem is: how can a subprocess distinguish itself from the other, for instance to know which part of the domain has been assigned to it?

This will be the subject of the following topic: [MPI_COMMUNICATORS](file://mpi_communicators.md)
