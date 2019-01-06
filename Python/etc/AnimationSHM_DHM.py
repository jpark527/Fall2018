#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Oct 24 20:57:12 2018

@author: Jae Hyun Park

    This Program simulates and Compares
    Simple Harmonic Motion, y(t) = A * cos (wt + φ), with
    Damped Harmonic Motion, y(t) = A * e ** (-b/2m * t) * cos (wt + φ).
"""
from matplotlib import animation
import matplotlib.pyplot as plt
import numpy as np

''' My Values for A, w, φ, b, m 
    A: amplitude
    w: angular frequency
    φ: phase constant
    b: damping coefficient
    m: mass
'''
A = 6
w = 9
fi = np.pi / 30
b = 15
m = 50

''' Create two figures for our plot, one for SHM, and the other one for DHM. '''
fig, (axForSHM, axForDHM) = plt.subplots(2,1)

''' Intialize two line objects (set them to default 2D, and green for SHM, and red for DHM)'''
simpleHarmonicMotion, = axForSHM.plot([], [], lw=2, color='g')
dampedHarmonicMotion, = axForDHM.plot([], [], lw=2, color='r')
line = [simpleHarmonicMotion, dampedHarmonicMotion]

''' Set the axis for both SHM and DHM '''
for axis in [axForSHM, axForDHM]:
    axis.set_ylim(-1.2 * A, 1.2 * A)
    axis.set_xlim(0, np.pi)
    axis.grid()

''' Initialize the data arrays for SHM and DHM '''
xdata, ySHMdata, yDHMdata = [], [], []

def ocillationGenerator():
    ''' This function adapts the data generator to yield both SHM and DHM '''
    t = count = 0
    while count < 600:
        count += 1
        t += 0.05
        ySHM = A * np.cos(w * t + fi)
        yDHM = A * np.exp(-b / (2 * m) * t) * np.cos(w * t + fi)
        yield t, ySHM, yDHM


def animate(data):
    ''' This function updates the data for both SHM and DHM by putting the data 
        into our data arrays. Also, if our data happens to go beyond our initial 
        limit for x-axis, it expends it '''
    t, y1, y2 = data
    xdata.append(t)
    ySHMdata.append(y1)
    yDHMdata.append(y2)

    ''' Checks for x_axis limit here and expands if needed '''
    for axis in [axForSHM, axForDHM]:
        xmin, xmax = axis.get_xlim()
        if t >= xmax:
            axis.set_xlim(xmin, 1.06*xmax)
            axis.figure.canvas.draw()

    ''' Update the data of both SHM and DHM here '''
    line[0].set_data(xdata, ySHMdata)
    line[1].set_data(xdata, yDHMdata)

    return line

''' Make our complete animation plot by plugging in all the objects that we created above '''
anim = animation.FuncAnimation(fig, animate, ocillationGenerator, blit=True, interval=10, repeat=False)

axForSHM.set_title('SHM vs DHM')
plt.xlabel('Time')
plt.ylabel('Amplitude')

''' Show the animation plot that we created on screen '''
plt.show()
