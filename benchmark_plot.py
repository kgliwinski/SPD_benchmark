import matplotlib.pyplot as plt
import csv
import numpy as np

# csv_path = input('Input the path to csv:')

time = []
vals = []


with open("Carlier/result.csv", 'r') as file:
    reader = csv.reader(file, delimiter=';')
    for row in reader:
        vals.append(int(row[0]))
        time.append(float(row[1]) / 10E6)

vals_lower = []
vals_higher = []

time_lower = []
time_higher = []

for (v, t) in zip(vals, time):
    if v / t < 204:
        vals_lower.append(v)
        time_lower.append(t)
    else:
        vals_higher.append(v)
        time_higher.append(t)

plt.figure()
plt.plot(vals_lower, time_lower, 'bo')
plt.plot(vals_higher, time_higher, 'ro')
plt.plot(vals, np.polyval(func_lower := np.polyfit(
    vals_lower, time_lower, 2), vals), 'c-')
plt.plot(vals, np.polyval(func_higher := np.polyfit(
    vals_higher, time_higher, 2), vals), 'g-')
plt.xlabel(r"Num. of processes")
plt.ylabel(r"Time (ms)")
# create a legend
plt.grid()
plt.show()

print(func_lower)
print(func_higher)
