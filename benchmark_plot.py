import matplotlib.pyplot as plt
import csv
import numpy as np

# csv_path = input('Input the path to csv:')

time = []
vals = []


with open("Schrage/result.csv", 'r') as file:
    reader = csv.reader(file, delimiter=';')
    for row in reader:
        vals.append(int(row[0]))
        time.append(float(row[1]))

plt.figure()
plt.plot(vals, time, 'bo')
plt.plot(vals, np.polyval(np.polyfit(vals, time, 2), vals), 'r-')
plt.xlabel(r"Num. of processes")
plt.ylabel(r"Time (s)")
# create a legend
func = np.polyfit(vals, time, 2)
plt.grid()
plt.show()

print(func)