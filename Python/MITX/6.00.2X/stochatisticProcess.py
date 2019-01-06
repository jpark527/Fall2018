#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Dec 11 00:13:35 2018

@author: j
"""

''' Stochatistic Process '''
import random

def rollDice(n):
    result = str()
    for i in range(n):
        result += (' ' + str(random.choice([1,2,3,4,5,6])))
    return result

def genEven():
    '''
    Returns a random even number x, where 0 <= x < 100
    '''
    return random.choice([2*x for x in range(50)])

def deterministicNumber():
    '''
    Deterministically generates and returns an even number between 9 and 21
    '''
    return 10

def stochasticNumber():
    '''
    Stochastically generates and returns a uniformly distributed even number between 9 and 21
    '''
    return random.choice([2*x for x in range(5,11)]) #random.randrange(0,10) is another way

print(rollDice(10))

