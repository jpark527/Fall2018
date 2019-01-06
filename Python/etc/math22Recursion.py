#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Sep 29 21:11:55 2018

@author: j
"""

#WarmUp
def fac(x):
    if not x:
        return 1
    return x * fac(x-1)

# 1
def f(arr, x, count):
    return fHelper(arr, x, count, count)

def fHelper(arr, x, count, countStill):
    if len(arr) == countStill:
        return  # if I return arr than the type of the return becomes nonType.. why??????
    arr.append(x**2)
    print("arr =", arr)
    fHelper(arr, x**2, count-1, countStill)

# 2
def f2(arr, prevX, x, count):
    return f2Helper(arr, prevX, x, count, count)
def f2Helper(arr, prevX, x, count, countStill):
    if(len(arr)==countStill):
        return
    n = x + 3*prevX
    arr.append(n)
    f2Helper(arr, x, n, count-1, countStill)
    
# 3
def f3(arr, prevX, x, count):
    arr.append(prevX)
    arr.append(x)
    return f3Helper(arr, prevX, x, 2, count+1)
def f3Helper(arr, prevX, x, n, count):
    if n==count:
        return 
    nextX = n*x + n*n*prevX
    arr.append(nextX)
    f3Helper(arr, x, nextX, n+1, count)
    
#4
def f4(arr, ppX, pX, x, count):
    arr.append(ppX)
    arr.append(pX)
    arr.append(x)
    return f4Helper(arr, ppX, pX, x, len(arr), count)
def f4Helper(arr, ppX, pX, x, n, count):
    if n==count:
        return
    nextX = x + ppX
    arr.append(nextX)
    f4Helper(arr, pX, x, nextX, n+1, count)

# 5
def f5(x):
    arr = []
    for i in range(0, x+1):
        arr.append(2**i + 5*3**i)
    print(arr)

# 6
def f6(arr, x, count):
    return f6Helper(arr, x, 0, count)
def f6Helper(arr, x, count, countStill):
    if count == countStill:
        return
    x = (count+1) * x - count
    arr.append(x)
    f6Helper(arr, x, count+1, countStill)
def f7(arr, x):
    for i in range(1,x+1):
        n = fac(i)+1
        arr.append(n)
    # INTERESTING FACT: a(n) = n!+1 = n * a(n-1) - (n-1), assuming a(1)=2 ?!
    # f6 and f7 are essentially the same.

#arr = []
#f6(arr, 2, 12)
#print(arr)
#
#arr2 = []
#f7(arr2, 12)
#print(arr2)
#
#arr3 = [fac(x)+1 for x in range(1,13)]
#print(arr3)

def isPrimeR(x):
    return isPrimeHelper(x, 2)
def isPrimeHelper(x, x0):
    if x <= x0:
        return True
    if not (x % x0):
        return False
    return isPrimeHelper(x, x0 + 1)

def isPrime(x):
    for n in range(2,x):
        if not (x % n):
            return False
    return True
    
def getPrimeNumbers(x):
    for p in range(2,x):
        if isPrime(p):
            print(p, end=' ', flush=True)











