#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Oct 23 21:27:57 2018

@author: j
"""

''' This Program simulates the Simple Harmonic Motion 
    y(t) = A * cos (wt + φ)
    A = 3
    w = 2
    φ = π / 6
'''

from matplotlib import animation
import matplotlib.pyplot as plt
import numpy as np

def initialize():
    ''' This function sets the initial point of our animation '''
    line.set_data([],[])    
    return line,

def animate(i):
    ''' This function sets the range and the equation of our animation '''
    t = np.linspace(0, np.pi, 100000)
    y = A * np.cos((np.pi * w * t + fi) - 0.05 * i)
    line.set_data(t, y)
    return line,

A = 3
w = 2
fi = np.pi / 6

''' Make an object for our plot '''
fig = plt.figure()  

''' Clear the plot (just in case) '''
fig.clf()

''' Set the axis for the plot '''
ax = plt.axes(xlim=(0, np.pi), ylim=(-1*A - 1, A + 1))

''' Set our plot to a default 2D plot '''
line, = ax.plot([], [], lw=2)

''' Make our complete animation plot by plugging in all the objects that we created above '''
anim = animation.FuncAnimation(fig, animate, init_func=initialize, frames=800, interval=2, blit=True)

plt.title('Simple Harmonic Motion')
plt.xlabel('Time')
plt.ylabel('Amplitude')

''' Show the animation plot that we created on screen '''
plt.show()
