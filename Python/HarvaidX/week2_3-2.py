#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct  6 19:23:26 2018

@author: j
"""

''' Matplotlib and Pyplot - PART 2 '''
''' Generating Histogram '''
import numpy as np
import matplotlib.pyplot as plt
arr = np.random.normal(size=1000)
#plt.hist(arr)
''' Change y-axis from number of observation to proportions '''
#plt.hist(arr, normed=True)  

''' Change x-axis range / bins '''
#plt.hist(arr, normed=True, bins=np.linspace(-5,5,21)) # This case, 20 bins
#plt.hist(arr, normed=True, bins=np.linspace(-5,5,21), cummulative=True, histtype = 'step')

''' Generating Subplot (Gamma function) '''
x = np.random.gamma(2,3,10000)

plt.figure()
plt.subplot(221)
plt.hist(arr, normed=True, bins=np.linspace(-5,5,31))
plt.subplot(222)
plt.hist(arr)
plt.subplot(223)
plt.hist(x, bins=1000)
plt.subplot(224)
plt.hist(arr, normed=True, bins=np.linspace(-5,5,21), histtype = 'step')