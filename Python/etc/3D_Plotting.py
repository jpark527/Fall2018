#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Oct  8 17:04:23 2018

@author: j
"""

#!/usr/bin/env python

''' 3D Plotting '''
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

''' Scatter Plot '''
x = np.linspace(0, 30, 100)
y = [ n for n in np.cos(x) ]
z = [ n for n in np.sin(x) ]
ax.scatter3D(x,y,z, c=z, cmap='Accent')

''' Line Plot '''
x = np.linspace(0, 30, 300)
y = np.cos(x)
z = np.sin(x)
ax.plot3D(x,y,z,'green')

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

#x = np.linspace(0.1,100,100)
#y1 = x**2
#y2 = x * np.log(x)
#plt.plot(x,y1, 'go', markersize=2)
#plt.plot(x,y2, 'ro', markersize=2)
#plt.xlabel('X')
#plt.ylabel('Y')
#
#plt.show()