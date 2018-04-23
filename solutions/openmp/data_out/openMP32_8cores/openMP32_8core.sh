#!/bin/bash -l
#SBATCH --constraint=elves
#SBATCH --time=24:00:00
#SBATCH --mem-per-cpu=1GB
#SBATCH --cpus-per-task=8
/homes/rpkruse/cis520/proj4/solutions/openmp/output.out
