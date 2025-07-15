# SLURM Lecture Notes

## 1. Introduction to SLURM

### 1.1 What is SLURM?

SLURM (Simple Linux Utility for Resource Management) is an open-source, fault-tolerant, and highly scalable cluster management and job scheduling system for large and small Linux clusters.

### 1.2 History and Background

- Developed by Lawrence Livermore National Laboratory (LLNL).
- Designed to manage workloads on large clusters.
- Widely used in HPC centers globally.

### 1.3 Key Features

- Open source and highly configurable.
- Supports batch and interactive jobs.
- Manages resources (CPU, memory, GPUs).
- Provides fair sharing, job prioritization.
- Scales to millions of cores.

---

## 2. SLURM Basics

### 2.1 Job Submission Types

- **Batch jobs**: Scheduled using job scripts.
- **Interactive jobs**: Launched directly from the terminal.

### 2.2 SLURM Job Lifecycle

1. Job submission (`sbatch` or `srun`)
2. Job queuing and scheduling
3. Job execution
4. Job completion or cancellation

---

## 3. Creating a SLURM Batch File

### 3.1 Basic Structure

```bash
#!/bin/bash
#SBATCH --job-name=my_job
#SBATCH --output=output_%j.txt
#SBATCH --error=error_%j.txt
#SBATCH --time=01:00:00
#SBATCH --partition=standard
#SBATCH --ntasks=4
#SBATCH --nodes=1
#SBATCH --mem=4G
```

### 3.2 Common Options

| Option            | Description                         |
| ----------------- | ----------------------------------- |
| `--job-name`      | Name of the job                     |
| `--output`        | Standard output file                |
| `--error`         | Standard error file                 |
| `--time`          | Max runtime (HH\:MM\:SS)            |
| `--partition`     | Target partition/queue              |
| `--ntasks`        | Number of parallel tasks (e.g. MPI) |
| `--nodes`         | Number of nodes                     |
| `--cpus-per-task` | CPUs per task (for OpenMP)          |
| `--mem`           | Total memory                        |
| `--gres=gpu:N`    | Number of GPUs                      |

---

## 4. Setting Environment Variables for OpenMP

In your batch script or before running the job:

```bash
export OMP_NUM_THREADS=4
export OMP_PROC_BIND=spread
export OMP_PLACES=cores
```

---

## 5. Batch Script Examples

### 5.1 MPI Job

```bash
#!/bin/bash
#SBATCH --job-name=mpi_job
#SBATCH --ntasks=8
#SBATCH --time=00:30:00
#SBATCH --partition=standard

module load mpi
srun ./my_mpi_program
```

### 5.2 OpenMP Job

```bash
#!/bin/bash
#SBATCH --job-name=openmp_job
#SBATCH --cpus-per-task=8
#SBATCH --time=00:30:00
#SBATCH --partition=standard

export OMP_NUM_THREADS=8
./my_openmp_program
```

### 5.3 Hybrid MPI + OpenMP Job

```bash
#!/bin/bash
#SBATCH --job-name=hybrid_job
#SBATCH --ntasks=4
#SBATCH --cpus-per-task=4
#SBATCH --time=00:30:00
#SBATCH --partition=standard

export OMP_NUM_THREADS=4
srun ./my_hybrid_program
```

### 5.4 GPU Job

```bash
#!/bin/bash
#SBATCH --job-name=gpu_job
#SBATCH --gres=gpu:1
#SBATCH --time=00:30:00
#SBATCH --partition=gpu

module load cuda
./my_gpu_program
```

---

## 6. Useful SLURM Commands

### 6.1 `squeue`

Show the job queue.

```bash
squeue
squeue -u username  # Jobs of specific user
squeue -j jobid     # Specific job info
```

### 6.2 `scancel`

Cancel a job.

```bash
scancel jobid
```

### 6.3 `sbatch`

Submit a batch job.

```bash
sbatch job_script.sh
```

### 6.4 `sinfo`

View cluster/node/partition info.

```bash
sinfo
sinfo -N -l    # Detailed node list
```

### 6.5 `scontrol`

Inspect and modify job or configuration.

```bash
scontrol show job jobid
```

### 6.6 `srun`

Run a job directly (interactive or batch).

```bash
srun --ntasks=4 ./program
```

---

## 7. Tips for Beginners/Mid-Level Users

- Always specify a time limit.
- Use modules to load required environments.
- Monitor jobs with `squeue` and `scontrol`.
- Prefer batch mode unless debugging.
- Use `--output` and `--error` to capture logs.

---

## 8. Additional Resources

- SLURM Documentation: [https://slurm.schedmd.com/documentation.html](https://slurm.schedmd.com/documentation.html)
- HPC Cluster User Guides (specific to your institution)
- Online tutorials and training videos

