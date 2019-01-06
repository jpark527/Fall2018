#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Sep 29 10:50:10 2018

@author: j
"""

def jMergeSort(arr):
    return jMergeHelper(arr, 0, len(arr)-1)

def jMergeHelper(arr, startIndex, lastIndex):
    if len(arr)==1:
        return 
    first = []
    second = []
    midIndex = (startIndex + lastIndex + 1) / 2
    for i in range(int(startIndex), int(midIndex)):
        first.append(arr[i])
    for i in range(int(midIndex), int(lastIndex+1)):
        second.append(arr[i])
    jMergeHelper(first, 0, len(first)-1) 
    jMergeHelper(second, 0, len(second)-1)
    
    ind = startIndex = startIndex2 = 0
    while startIndex < len(first) and startIndex2 < len(second):
        if first[startIndex] > second[startIndex2]:
            arr[ind] = second[startIndex2]
            startIndex2 += 1
        else:
            arr[ind] = first[startIndex]
            startIndex += 1
        ind += 1
    while startIndex < len(first) and ind < len(arr):
        arr[ind] = first[startIndex]
        ind += 1
        startIndex += 1
    while startIndex2 < len(second) and ind < len(arr):
        arr[ind] = second[startIndex2]
        ind += 1
        startIndex2 += 1
    
def isSorted(l):
    if(len(l) < 2):
        return True
    for i in range(1, len(l)):
        if l[i-1] > l[i]:
            return False
    return True

def jBinarySearch(arr, element):                 
    if(not arr):
        return -1
    return jBinarySearchHelper(arr, element, 0, len(arr)-1)

def jBinarySearchHelper(arr, element, startI, endI): # works but VERY MESSY!
    curI = (startI+endI)//2
    if arr[endI] == element:
        return endI
    if arr[curI] == element:
        return curI
    if abs(startI-endI)==1:
        return -1
    if arr[curI] > element:
        return jBinarySearchHelper(arr, element, startI, curI)
    else:
        return jBinarySearchHelper(arr, element, curI, endI)
        
        
        
        
        
    # print("arr =", arr)