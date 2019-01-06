#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct 20 09:32:53 2018

@author: j
"""

from matplotlib import animation
import matplotlib.pyplot as plt
import numpy as np
import scipy as sp
from scipy.integrate import odeint

def myInit():
    line.set_data([],[])
    return line,

def myAnimate(i):
    x = np.linspace(0, 2, 100000)
    y = np.sin(2 * np.pi * (x - 0.01 * i))
    line.set_data(x, y)
    return line,

fig = plt.figure()
ax = plt.axes(xlim=(0,2), ylim=(-2, 2))
line, = ax.plot([], [], lw=2)

anim = animation.FuncAnimation(fig, myAnimate, init_func=myInit, frames=500, interval=2, blit=True)

plt.show()

