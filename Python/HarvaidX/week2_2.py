#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct  6 01:08:08 2018

@author: j
"""

''' NumPy '''
''' numpy array's length cannot be modified once created '''
import numpy as np
arr = np.zeros(5)
arr2 = np.zeros((5,3))

myArr = np.array([1,2,3])
myArr2 = np.array([[1,2], [7,8]])
myArrTrans = myArr2.transpose()

print(myArr2[:,1])
print(myArr2[1,:])

x = np.array([1,2,5]) 
print(x[1:2])

''' This causes an error since the arrays' len don't match ''' 
#a = np.array([1,2]) 
#b = np.array([3,4,5]) 
#print(a + b)

''' Indexing numpy arrays '''
a = np.array([1,2,3,4,5,6,7])
print(a[[1,2,3]])
b = np.array([1,2,3])
print(a[b])
print(a>2)
print(a[a>2])

a = np.array([1,2]) 
b = np.array([3,4,5]) 
b[a]
c = b[1:] 
print(b[a] is c)

''' More numpy arrays '''
a = np.linspace(10, 100, 90)        # linear (space) array
b = np.logspace(1, 2, 10) 
''' log space - this case, the first param is 10 ,and second param is 100, and length of 10 '''
c = np.logspace(np.log10(200), np.log10(250), 5)

''' returns shape of an array in a tuple of (row, col) '''
print(a.shape)

''' Checks the element of the array by returning a boolean val '''
print(np.any(c > 230))
print(np.all(c > 230))















