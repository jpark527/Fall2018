#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Oct  2 22:57:40 2018

@author: j
"""

def makeExponents(n, x):
    ''' 
    THis function makes an array of exponents of number n that are less than number x given + one greater than x
    n: the base number
    x: the upper bound
    return an array of base n exponents, and an array of 0 that has the same arr length
    '''
    arr = []
    arr2 = []
    e = 0
    while x > n**e:
        arr.append(n**e)
        arr2.append(0)
        e += 1
    arr.append(n**e)
    arr2.append(0)
    return arr, arr2

def convertBase(n, x):
    ''' 
    This function converts decimal number x to the number in base n
    n: the changing base
    x: the decimal number that gets converted to n base
    return an integer of base n that is equivalent to the decimal number x 
    '''
    try:
        if not (x == int(x) and n == int(n) and x > 0 and n > 0 and n < 10):
            print('Invalid input!')
            return -1
    except:
        raise ValueError('Invalid input type.')
    exp, power = makeExponents(n,x)
    while x > 0:
        for i in range(len(exp)):
            if exp[i] > x:
                x -= exp[i-1]
                power[i-1] += 1
                break
    digit = 1
    converted = 0
    for e in power:
        converted += (digit*e)
        digit *= 10
    return converted       

def gcd(d, r):
    ''' Assuming d > r '''
    if d%r:
        return gcd(r, d%r) 
    else:
        return r


            
        
    