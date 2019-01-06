#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Nov  3 22:17:10 2018

@author: j
"""

''' Dynamic Programming '''

def badFib(n):
    ''' Inefficient fibonacci '''
    if n < 2:
        return 1
    else:
        return badFib(n-1) + badFib(n-2)
    
def fib(n, memo=dict()):
    ''' 
    Generate fibonacci sequence using memoization and recursion for better efficiency.
    '''
    if n < 2:
        return 1
    try:
        return memo[n]
    except KeyError:
        memo[n] = fib(n-1, memo) + fib(n-2, memo)
        return memo[n]
    
print('\nTesting slow fibonacci..')
for i in range(37):
    print('fib(' + str(i) + ') = ' + str(badFib(i)) )
    
print('\nTesting fast fibonacci..')
for i in range(100):
    print('fib(' + str(i) + ') = ' + str(fib(i)) )