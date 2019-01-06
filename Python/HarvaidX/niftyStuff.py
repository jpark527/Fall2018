#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Sep 30 03:06:56 2018

@author: j
"""

# week 1 - 1
# Review / some nifty features of python

import math as m
print(type(m))
print("5! =",m.factorial(5))

from math import factorial
print("5! =", factorial(5)) 

arr = [factorial(x) for x in range(1,6)]
print(arr)

print( [m.sqrt(x) for x in (1,4,9,16,25)] )

import numpy as n
print(n.sqrt(9))

#print(dir(n)) # shows u all the functions that is available for the object type
#print(help(n.abs))

# Numbers - _ can be used to type the number that u previously got.
import random as r
print(r.choice(range(1,11)))
print(r.choices(["a", "b", "c"]))