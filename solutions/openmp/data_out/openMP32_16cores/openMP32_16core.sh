#!/bin/bash -l
#SBATCH --constraint=elves
#SBATCH --time=24:00:00
#SBATCH --mem-per-cpu=512MB
#SBATCH --cpus-per-task=16
/homes/rpkruse/cis520/proj4/solutions/openmp/output10k.out
