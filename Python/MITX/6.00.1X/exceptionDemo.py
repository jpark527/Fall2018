#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Sep 29 18:19:26 2018

@author: j
"""

def getNumInput():
    n = ""
    while(1):
        try:
            n = input("Enter a numberr: ")
            n = float(n)
            break
        except ValueError:
            print("Invalid input. Please try again.")            
    return n

def getRatios(l1, l2):
    ratioL = []
    for i in range(len(l1)):
        try:
            ratioL.append(l1[i] / l2[i])
        except ZeroDivisionError:
            ratioL.append(float('NaN'))
        except:
            raise ValueError("Invalid Argument!")
    return ratioL

def ave(grades):
    ''' if grades is empty, returns assertionError '''
    assert len(grades), 'No data is given'
    return sum(grades) / len(grades)