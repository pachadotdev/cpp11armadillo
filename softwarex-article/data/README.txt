run this:

sbatch 00-run-benchmark.sh 
sbatch 00-run-benchmark-py.sh 

cancel with:

squeue -u msep
scancel -i 012345
