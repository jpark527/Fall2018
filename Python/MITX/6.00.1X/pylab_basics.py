#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct 20 04:03:05 2018

@author: j
"""

import numpy as np
import matplotlib.pyplot as plt

#xAxis = list()
#linear = list()
#quadratic = list()
#cubic = list()
#
#for i in range(30):
#    xAxis.append(i)
#    linear.append(i)
#    quadratic.append(i**2)
#    cubic.append(i**3)
#    
#plt.figure('Linear')
#plt.clf() # Clears the previous frame
#plt.title('Linear')
#plt.ylim(0,1000) #Sets y limits
#plt.xlabel('X')
#plt.ylabel('Linear y')
#plt.plot(xAxis, linear)
#
#plt.figure('Quadratic')
#plt.clf() # Clears the previous frame
#plt.title('Quadratic')
#plt.ylim(0,1000) #Sets y limits
#plt.xlabel('X')
#plt.ylabel('Quad y')
#plt.plot(xAxis, quadratic)
#
#plt.figure('Cubic')
#plt.clf() # Clears the previous frame
#plt.title('Cubic')
#plt.ylim(0,1000) #Sets y limits
#plt.xlabel('X')
#plt.ylabel('Cubic y')
#plt.plot(xAxis, cubic)
#
#plt.figure('LinQuad')
#plt.clf()
#plt.title('Linear vs Quadratic')
#plt.xlabel('X')
#plt.ylabel('Y')
#plt.plot(xAxis, linear, label='Linear')
#plt.plot(xAxis, quadratic, label='Quadratic')
#plt.legend()    #plt.legend(loc='upper left')
#
#plt.clf()

''' Subplotting '''
x1 = np.linspace(0, 5)
x2 = np.linspace(0, 3)
y1 = np.cos(2*np.pi*x1) * np.exp(-1*x1)
y2 = np.cos(2*np.pi*x2)

#Create two plots sharing y axis
myFig, (ax1, ax2) = plt.subplots(2, sharey=True)

ax1.plot(x1, y1)
ax2.plot(x2, y2)
plt.ylim(-1.5, 1.5)

plt.show()

