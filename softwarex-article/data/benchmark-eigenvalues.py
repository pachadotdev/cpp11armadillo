import numpy as np
import timeit

n = 10000

# Eigenvalues

np.random.seed(123)
M = np.random.uniform(size=(n, n))
M = (M + M.T) / 2

def bench_eigenvalues_py(M):
    return np.linalg.eigvals(M)

def benchmark():
    return bench_eigenvalues_py(M)

execution_times = timeit.repeat("benchmark()", globals=globals(), repeat=100, number=1)

min_time = np.min(execution_times)
p25_time = np.percentile(execution_times, 25)
median_time = np.median(execution_times)
p75_time = np.percentile(execution_times, 75)
max_time = np.max(execution_times)

results = (
    f"Min execution time: {min_time:.6f} seconds\n"
    f"25th percentile (p25) execution time: {p25_time:.6f} seconds\n"
    f"Median execution time: {median_time:.6f} seconds\n"
    f"75th percentile (p75) execution time: {p75_time:.6f} seconds\n"
    f"Max execution time: {max_time:.6f} seconds\n"
)

with open("/scratch/s/shirimb/msep/cpp11armadillopaper/paper/data/benchmark-speed-eigenvalues-py.txt", "w") as file:
    file.write(results)

del M
