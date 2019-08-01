import sys
import matplotlib.pyplot as plt
import numpy as np

dataFile = open(sys.argv[1], "r")

xAndy = dataFile.readline().split(",")

plt.xlabel(xAndy[0])
plt.ylabel(xAndy[1])
plt.title("Data")

xs = []
ys = []
for line in dataFile:
	kmAndPrice = line.split(",")
	xs.append(int(kmAndPrice[0]))
	ys.append(int(kmAndPrice[1]))

plt.scatter(xs, ys)

lineFile = open(sys.argv[2], "r")

aAndB = lineFile.readline().split(",")

a = float(aAndB[0])
b = float(aAndB[1])

x = np.linspace(min(xs), max(xs))
y = a + b * x

plt.plot(x, y)

plt.show()
