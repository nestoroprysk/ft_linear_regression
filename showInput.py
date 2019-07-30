import matplotlib.pyplot as plt
import numpy as np

file = open("data.txt", "r")

xAndy = file.readline().split(",")

plt.xlabel(xAndy[0])
plt.ylabel(xAndy[1])
plt.title("Data")

xs = []
ys = []
for line in file:
	kmAndPrice = line.split(",")
	xs.append(int(kmAndPrice[0]))
	ys.append(int(kmAndPrice[1]))

plt.scatter(xs, ys)

lineFile = open("line.txt", "r")

aAndB = lineFile.readline().split(",")

a = float(aAndB[0])
b = float(aAndB[1])

x = np.linspace(min(xs), max(xs))
y = a + b * x

plt.plot(x, y)

plt.show()
