#!/bin/bash -l
#SBATCH --constraint=elves
#SBATCH --nodes=2
#SBATCH --tasks-per-node=8
#SBATCH --time=24:00:00
#SBATCH --mem-per-cpu=512MB
/homes/rpkruse/cis520/proj4/solutions/mpi/output.out
