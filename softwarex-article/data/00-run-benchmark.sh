#!/bin/bash
#SBATCH --job-name=cpp11armadillobenchmark
#SBATCH --output=/scratch/s/shirimb/msep/cpp11armadillopaper/paper/data/cpp11armadillobenchmark.txt
#SBATCH --nodes=1
#SBATCH --ntasks=40
#SBATCH --time=12:00:00
#SBATCH --account=def-shirimb

# Load necessary modules
module load gcc/8.3.0
module load r/4.2.2-batteries-included
# module load fftw

export MKLROOT=/gpfs/fs1/scinet/intel/2019u4/compilers_and_libraries_2019.4.243/linux/mkl
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$MKLROOT/lib/intel64_lin
export R_LIBS_USER=/scratch/s/shirimb/msep/cpp11armadillopaper/Rlib
export OMP_NUM_THREADS=40
export MKL_NUM_THREADS=40

export R_LIBS_USER=/scratch/s/shirimb/msep/cpp11armadillopaper/Rlib

# install.packages("devtools")
# devtools::install("/scratch/s/shirimb/msep/cpp11armadillopaper/paper/benchcpp11armadillo/")
# devtools::install("/scratch/s/shirimb/msep/cpp11armadillopaper/paper/benchrcpparmadillo/")

# Run the R script
Rscript benchmarks.r
