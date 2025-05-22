import numpy as np
import timeit

n = 10000

# Multi-operation

np.random.seed(123)
p = np.random.uniform(size=n)
q = np.random.uniform(size=n)
r = np.random.uniform(size=n)

def bench_multi_py(p, q, r):
    return float(np.dot(np.dot(p.T, np.linalg.inv(np.diag(q))), r))

def benchmark():
    return bench_multi_py(p, q, r)

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

with open("/scratch/s/shirimb/msep/cpp11armadillopaper/paper/data/benchmark-speed-multi-py.txt", "w") as file:
    file.write(results)

del p, q, r
