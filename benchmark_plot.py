import matplotlib.pyplot as plt
import csv
import numpy as np

# csv_path = input('Input the path to csv:')

time = []
vals = []


with open("RPQ/result.csv", 'r') as file:
    reader = csv.reader(file, delimiter=';')
    for row in reader:
        vals.append(int(row[0]))
        time.append(int(row[1]) / 1000)

plt.figure()
plt.plot(time, vals, 'bo')
plt.xlabel(r"Time ($\mu$s)")
plt.ylabel(r"Num. of processes")
plt.grid()
plt.show()
