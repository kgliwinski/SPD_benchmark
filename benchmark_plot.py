import matplotlib.pyplot as plt
import csv
import numpy as np

# csv_path = input('Input the path to csv:')

time = []
vals = []


with open("WiTi/BruteForce.csv", 'r') as file:
    reader = csv.reader(file, delimiter=';')
    for row in reader:
        vals.append(int(row[0]))
        time.append(float(row[1]) / 10E6)


plt.figure()
plt.plot(vals, time, 'bo')
plt.xlabel(r"Num. of processes")
plt.ylabel(r"Time (ms)")
plt.xticks(np.arange(4, 11, 1))
# create a legend
plt.grid()
plt.show()

