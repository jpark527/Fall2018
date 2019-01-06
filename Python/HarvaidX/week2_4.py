#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct  6 19:46:36 2018

@author: j
"""

''' Simulating Randomness & Clock '''
import random
import numpy as np
import matplotlib.pyplot as plt

for i in range(10):
    print(random.choice(['head', 'tail']))

''' case 1: '''
n = 10000
data = []
#print('\nRolling dice', str(n), 'times..')
#
#for i in range(n):
#    data.append(random.choice(range(1,7)))

#plt.hist(data, normed=True, bins=np.linspace(.5, 6.5, 7))

''' case 2: '''
dice = 10
#print('\nRolling', str(dice), 'dice', str(n), 'times..')

#for i in range(n):
#    mySum = np.sum(np.random.randint(1,7,dice))
#    data.append(mySum)
#
#plt.hist(data)

X = np.random.randint(1,7,(n, dice))
Y = np.sum(X, axis=1)
#plt.hist(Y)

''' Numpy Random Module '''
''' Generating random numpy array '''
a = np.random.random(5)     # 1D-array
b = np.random.random((3,5)) # 2D-array

c = np.random.normal(0,1,5)     # (mean, standardDeviation, arrayLen)
d = np.random.normal(0,1,(5,3))

''' Generating random int array in numpy '''
e = np.random.randint(1,7,10)
f = np.random.randint(1,7,(5,3))

''' Measuring Time '''
import time
startTime = time.clock()
endTime = time.clock()
endTime - startTime

''' Random Walk Demo '''
print('Random Walk Demo..')

numOfWalk = 7
X0 = np.array([[0], [0]])
deltaX = np.random.normal(0, 1, (2,numOfWalk))
X = np.concatenate( (X0, np.cumsum(deltaX, axis = 1)), axis = 1 )
plt.plot(X[0], X[1], 'go-')
#plt.savefig('randomWalkDemo.pdf')


























