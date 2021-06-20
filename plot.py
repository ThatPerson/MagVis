import numpy as np
import sys


import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
plt.rcParams['font.family'] = 'sans-serif'
plt.rcParams['font.size'] = 14
plt.rcParams['font.sans-serif'] = 'Cantarell'
font = {'fontname': 'Cantarell'}
try:
	fn = sys.argv[1]
	oup = sys.argv[2]
except IndexError:
	print("python plot.py <filename> <output>")
	exit(-1)

d = np.loadtxt(fn, usecols=[1,2,3,0])
x = d[:, 0]
y = d[:, 1]
z = d[:, 2]
t = d[:, 3]
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.plot(x, y, z, c='black')
ax.set_xlim([-1, 1])
ax.set_ylim([-1, 1])
ax.set_zlim([-1, 1])

ax.w_xaxis.set_pane_color((1.0, 1.0, 1.0, 1.0))
ax.w_yaxis.set_pane_color((1.0, 1.0, 1.0, 1.0))
ax.w_zaxis.set_pane_color((1.0, 1.0, 1.0, 1.0))

ax.grid(False)

ax.set_xticks([-1, 0, 1])
ax.set_yticks([-1, 0, 1])
ax.set_zticks([-1, 0, 1])

ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")

ax.view_init(elev=10., azim=130)
#plt.show(block=True)
plt.savefig(oup)
