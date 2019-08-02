import sys
import matplotlib.pyplot as plt
import numpy as np

try:
    dataFile = open(sys.argv[1], "r")

    xAndy = dataFile.readline().split(",")

    plt.xlabel(xAndy[0])
    plt.ylabel(xAndy[1])
    plt.title("Data")

    xs = []
    ys = []
    for line in dataFile:
    	xAndY = line.split(",")
    	xs.append(float(xAndY[0]))
    	ys.append(float(xAndY[1]))

    plt.scatter(xs, ys)

    minX = float(sys.argv[2])
    yMinX = float(sys.argv[3])

    maxX = float(sys.argv[4])
    yMaxX = float(sys.argv[5])

    x = [minX, maxX]
    y = [yMinX, yMaxX]

    plt.plot(x, y)

    plt.show()

except:
    print("Unable to visualize")
