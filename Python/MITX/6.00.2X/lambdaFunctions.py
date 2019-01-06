#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Nov  3 19:25:09 2018

@author: j
"""

''' Lambda Function : lambda used to create anonymous functions.
                      * lambda <id1, id2, ... idn> : <expression>
                      * Returns a function of n arguments           '''

f1 = lambda x : x # identity function. Basically returns the same thing as you put in.
print(f1(5), '=', 5)

add = lambda x, y : x + y # returns the sum of x + y
print(5, '+', 6, '=', add(5,6))
print(add('Merry', ' Christmas!'))

isDivisible = lambda x, y : False if x%y else True
print('15 | 30 ?', isDivisible(30,15))
print('3 | 31 ?', isDivisible(31,3))