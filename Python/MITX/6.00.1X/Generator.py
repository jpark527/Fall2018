#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Oct  5 20:19:34 2018

@author: j
"""

''' Generator '''

def genTest():
    yield 1
    yield 2
    yield 3
    yield 4
    yield 5
    
''' This raises StopIteration exception after iteration 5. '''
#foo = genTest()
#for i in range(1,10):
#    print(foo.__next__())

''' Example of generator '''
def genFib():
    fib1 = 0
    fib2 = 1
    while True:
        fib = fib1 + fib2
        yield fib
        fib1 = fib2
        fib2 = fib

def genPrime():
    num = 2
    while True:
        if num < 4:
            yield num
        else:
            for n in range(2,num):
                count = 0
                if not num % n:
                    count += 1
                    if count:
                        break
                elif (num == n+1) and (not count):
                    yield num
        num += 1
                