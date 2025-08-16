import matplotlib.pyplot as plt

threads = [1, 2, 4, 8]
times = [0.020, 0.008, 0.006, 0.005] 
speedup = [times[0]/t for t in times]

plt.plot(threads, speedup, marker='o')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup')
plt.title('Speedup vs Number of Threads (Matrix Size 2000x2000)')
plt.grid(True)
plt.show()