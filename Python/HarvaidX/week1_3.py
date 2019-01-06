#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Sep 30 17:52:20 2018

@author: j
"""

# Week 1 - 3
import copy as c
arr = [[1],2,3]
arr2 = c.copy(arr)
arr3 = c.deepcopy(arr)

print(arr[0] is arr2[0])
print(arr[0] is arr3[0])     

names = {'Craig':33, 'Adam':31, 'Bree':19 }
for name in sorted(names.values()):
    print(name)

for name in sorted(names.keys(), reverse = True):
    print(name, names[name])
    
print(sum ([number for number in range(1, 10, 2)]) ) # 1 + 3 + 5 + 7 + 9 = 25

#myFile = open("/Users/j/Desktop/tester", 'w')
#myFile.write("hello, this is a test file\napple\norange\npear")
#myFile.close()

#for line in open("/Users/j/Desktop/tester", 'r'):
#    ''' removes \n at the end '''
#    print(line.rstrip())    

def addAndSubtract(x, y):
    return x+y, x-y

f = addAndSubtract
print(f(5,3))

def modify(mylist): 
    mylist[0] *= 10 
    return(mylist) 
L = [1, 3, 5, 7, 9] 
M = modify(L) 
print(M is L)

import string
from random import choice as c
def getRandomLetters(length):
    alphabets = string.ascii_letters + string.digits
    l = str()
    for i in range(length):
        l += c(alphabets)
    return l

s = str("hello")
s2 = str(s)
print(s2 is s)

''' Very ugly recursion with mutable obj, str '''
def randomLetters(length):  
    return getL(length, "")
def getL(length, l):
    if not length:
        return l
    alphabets = string.ascii_letters + string.digits
    l += c(alphabets)
    l = getL(length-1, l)
    return l












    