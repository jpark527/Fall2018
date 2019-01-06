#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Dec 17 22:24:06 2018

@author: j
"""

''' 
    Write a function, stdDevOfLengths(L) that takes in a list of strings, L, 
    and outputs the standard deviation of the lengths of the strings. 
    Return float('NaN') if L is empty.
'''
def stdDevOfLengths(L):
    """
    L: a list of strings

    returns: float, the standard deviation of the lengths of the strings,
      or NaN if L is empty.
    """
    if not L:
        return float('NaN')
    mean = sd = 0.
    for l in L:
        mean += len(l)
    mean /= len(L)
    for l in L:
        sd += (len(l)-mean)**2
    sd = (sd / len(L))**.5
    return sd
  