#!/bin/bash -l
#SBATCH --constraint=elves
#SBATCH --nodes=16
#SBATCH --tasks-per-node=2
#SBATCH --time=24:00:00
#SBATCH --mem-per-cpu=256MB
/homes/rpkruse/cis520/proj4/solutions/mpi/output.out
