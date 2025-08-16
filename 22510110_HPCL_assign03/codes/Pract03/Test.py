import matplotlib.pyplot as plt

# Given data
sizes = [250, 500, 750, 1000, 2000]
threads = [1, 2, 4, 8]

times = [
    [0.00352567, 0.00283674, 0.00170095, 0.00693983],  # 250x250
    [0.0250542,  0.00833602, 0.005809,   0.0161602],   # 500x500
    [0.0377679,  0.0195827,  0.0141873,  0.0150471],   # 750x750
    [0.0477372,  0.0296183,  0.0209154,  0.0258666],   # 1000x1000
    [0.177736,   0.100567,   0.0826265,  0.0807635]    # 2000x2000
]

# ---- Execution Time Plot ----
plt.figure(figsize=(8, 6))
for i, size in enumerate(sizes):
    plt.plot(threads, times[i], marker='o', label=f"{size}x{size}")

plt.xlabel("Number of Threads")
plt.ylabel("Execution Time (seconds)")
plt.title("Matrix Addition Performance with OpenMP")
plt.xticks(threads)
plt.legend(title="Matrix Size")
plt.grid(True)
plt.show()

# ---- Speedup Plot ----
plt.figure(figsize=(8, 6))
for i, size in enumerate(sizes):
    t1 = times[i][0]  # single-thread time
    speedup = [t1 / t for t in times[i]]
    plt.plot(threads, speedup, marker='o', label=f"{size}x{size}")

plt.xlabel("Number of Threads")
plt.ylabel("Speedup (T1 / Tp)")
plt.title("Speedup vs Threads for Matrix Addition")
plt.xticks(threads)
plt.legend(title="Matrix Size")
plt.grid(True)
plt.show()
