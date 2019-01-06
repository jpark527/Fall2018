#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Sep 30 04:17:43 2018

@author: j
"""

# Week 1 - 2
def jReverse(arr):    
    return jRevHelper(arr, 0, len(arr)//2)
def jRevHelper(arr, count, until):
    if count == until:
        return 
    arr[count],arr[len(arr)-1-count] = arr[len(arr)-1-count],arr[count]
    jRevHelper(arr, count+1, until)
    
arr = [1,2,3,4,5,6]
jReverse(arr)
#print(arr)
#print("this"[1])

s1 = set(range(1,11))
s2 = set([1,11,111,1111,11111])

''' Union set operator | '''
print(s1 | s2)  
''' Intersection set operator & '''   
print(s1 & s2)     
''' You can also use '+' and '-' '''

''' Finding Unique letters in a str '''
s = "this is a test string"
unique = len(set(s))

