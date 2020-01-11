#!/bin/env python3

import sys
import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import r2_score

if len(sys.argv) < 2:
    print(f"Usage: {sys.argv[0]} qqnorm_file [image_file]\nDefault image file is qqnorm_file.pdf")
    sys.exit(1)

x = []
y = []

with open(sys.argv[1], 'r') as f:
    for line in f.readlines():
       x.append(float(line.split()[0]))
       y.append(float(line.split()[1]))

plt.plot(x,y,"+", ms=10, mec="k")
z = np.polyfit(x, y, 1)
y_hat = np.poly1d(z)(x)

plt.plot(x, y_hat, "r--", lw=1)
text = f"$y={z[0]:0.3f}\;x{z[1]:+0.3f}$\n$R^2 = {r2_score(y,y_hat):0.3f}$"
plt.gca().text(0.05, 0.95, text,transform=plt.gca().transAxes,
     fontsize=14, verticalalignment='top')

outfile = sys.argv[2] if len(sys.argv) >= 3 else sys.argv[1]+'.pdf'

plt.savefig(outfile)

