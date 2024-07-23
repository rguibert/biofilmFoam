
#    ]3 | () /= | |_ |\/| /= () /\ |\/|

#    Copyright 2023 Toulouse INP
#    Romain Guibert

#  warning
# postProcess sample can encouter problems on MacOS

import os
import sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import MultipleLocator
from mpl_toolkits.mplot3d.axes3d import Axes3D
from mpl_toolkits.mplot3d import proj3d

import sys
if sys.version_info<(3,5,0):
  sys.stderr.write("You need python 3.0 or later!\n")
  exit(1)

plt.rcParams.update({
    "text.usetex": True,
    "font.family": "sans-serif",
    "font.serif": ["cm"],
    "font.size": 14,
    "text.latex.preamble": r'\usepackage[cm]{sfmath}'
})

path = './postProcessing/sample/'

name_list = os.listdir(path)
full_list = [os.path.join(path,i) for i in name_list]
time_sorted_list = sorted(full_list, key=os.path.getmtime)

data = np.loadtxt(path+'/0/line_C_M.xy')
X = data[:,0]
nbx = len(X)

matX = 0*np.eye(len(time_sorted_list),nbx)
matT = 0*np.eye(len(time_sorted_list),nbx)
matC = 0*np.eye(len(time_sorted_list),nbx)
matM = 0*np.eye(len(time_sorted_list),nbx)

j = 0

for i in time_sorted_list:
    data = np.loadtxt(i+'/line_C_M.xy')
    X = data[:,0]
    C = data[:,1]
    M = data[:,2]
    matX[j,:] = np.arange(nbx) + 1
    matT[j,:] = 0*np.arange(nbx)+j
    matM[j,:] = np.asarray(M)
    matC[j,:] = np.asarray(C)
    j += 1


fig = plt.figure(figsize=(20,10))
ax = fig.add_subplot(111, projection='3d')
    
# ---
    
x_scale=4
y_scale=4
z_scale=2

scale=np.diag([x_scale, y_scale, z_scale, 1.0])
scale=scale*(1.0/scale.max())
scale[3,3]=1.0

def short_proj():
  return np.dot(Axes3D.get_proj(ax), scale)

ax.get_proj=short_proj

# ---

ax.plot_wireframe(matX, matT, matM, rstride=12, cstride=4, color="blue", alpha=0.75, label='M')
ax.plot_wireframe(matX, matT, matC, rstride=12, cstride=4, color="red", alpha=0.25, label='C')
## case 1d-D
#ax.plot_wireframe(matX, matT, matM, rstride=24, cstride=4, color="blue", alpha=0.75, label='M')
#ax.plot_wireframe(matX, matT, matC, rstride=24, cstride=4, color="red", alpha=0.25, label='C')

ax.set_xlabel('Discretization')
ax.set_ylabel('Time (h)')

ax.xaxis.set_major_locator(MultipleLocator(16))
ax.yaxis.set_major_locator(MultipleLocator(50))
## case 1d-D
#ax.yaxis.set_major_locator(MultipleLocator(100))
ax.zaxis.set_major_locator(MultipleLocator(0.25))

ax.legend(loc='lower left', frameon=False)

plt.show()

fig.savefig("plot.pdf", dpi=300)
