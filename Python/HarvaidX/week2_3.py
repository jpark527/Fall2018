#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct  6 18:28:23 2018

@author: j
"""
''' Matplotlib and Pyplot '''
import numpy as np
import matplotlib.pyplot as plt
#plt.plot([0,2,4,9,16,25])

''' In terminal or not in console, use plt.show() after call plot attribute '''
x = np.linspace(0,100,20)
y = x**2
plt.plot(x,y)

y2 = x ** 2.5
plt.plot(x, y, "go-", linewidth=2, markersize=6, label='Green')
plt.plot(x, y2, "bs-", linewidth=2, markersize=6, label='Blue')
#plt.plot(x, y, "rd-", linewidth=2, markersize=6)

''' Customizing plots '''
#xMin = yMin = -10
#xMax = yMax = 10

plt.xlabel('time')
plt.ylabel('amplitute')
#plt.axis(xMin, xMax, yMin, yMax)
plt.legend(loc='upper left')

''' Saves plot to a file '''
#plt.savefig('myPlot.pdf')

''' Plotting using logarithmic axes '''
x = np.logspace(-1,1,10)
y = x**2
y2 = x ** 2.5
plt.loglog(x, y, "rd-", linewidth=2, markersize=6, label='Red')
plt.loglog(x, y2, "yo-", linewidth=2, markersize=6, label='Yellow')
plt.legend(loc='upper left')
