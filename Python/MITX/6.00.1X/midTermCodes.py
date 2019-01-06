#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Sep 28 11:50:50 2018

@author: j
"""
# Notice:
x = 10
y = 20
x,y = y,x
print(x)
print(y)

# 1
def closest_power(base, num):
    '''
    base: base of the exponential, integer > 1
    num: number you want to be closest to, integer > 0
    Find the integer exponent such that base**exponent is closest to num.
    Note that the base**exponent may be either greater or smaller than num.
    In case of a tie, return the smaller value.
    Returns the exponent.
    '''
    return closestPowerHelper(base, num, 1)

def closestPowerHelper(base, num, exp):
    big = (base**exp) < num
    if not big:
        if abs(base**exp - num) >= abs(base**(exp-1) - num):
            return exp-1
        else:
            return exp
    return closestPowerHelper(base, num, exp+1) 

# 2
def lessThan4(aList):
    '''
    aList: a list of strings
    '''
    myList = []
    return lessThan4Helper(aList, myList, 0)

def lessThan4Helper(aList, myList, index):
    if index == len(aList):
        return myList
    if len(aList[index]) < 4:
        myList.append(aList[index])
    return lessThan4Helper(aList, myList, index+1)

# 3
def uniqueValues(aDict):
    '''
    aDict: a dictionary
    '''
    myDict = []
    for key in aDict:
        rep = -1
        for key2 in aDict:
            if aDict[key]==aDict[key2]:
                rep += 1
        if not rep:
            myDict.append(key)
    return myDict

# 4
def sumDigits(N):
    '''
    N: a non-negative integer
    '''
    if not N:
        return 0
    return (N%10) + sumDigits(N//10)

'''
def sumDigits(N):
    return sumDigitsHelper(N, 0)       

def sumDigitsHelper(N, mySum):
    if not N:
        return mySum
    mySum += (N%10)
    return sumDigitsHelper(N//10, mySum)
'''
  
# 5
def satisfiesF(L):
    """
    Assumes L is a list of strings
    Assume function f is already defined for you and it maps a string to a Boolean
    Mutates L such that it contains all of the strings, s, originally in L such
            that f(s) returns True, and no other elements. Remaining elements in L
            should be in the same order.
    Returns the length of L after mutation
    """
    i = 0
    while i<len(L):
        if(not f(L[i])):
            L.pop(i)
        else:
            i += 1
    return len(L)
    
def f(s):
    return 'a' in s
      
L = ['c', 'a', 'b', 'a', 'a', 'd']
print (satisfiesF(L))
print (L)    