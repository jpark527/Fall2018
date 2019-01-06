#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Sep 16 17:16:02 2018

@author: j
"""

# Write to file
myfileIO = open('/Users/j/Desktop/pyTester', 'w')
while(1):
    data = input("Enter data: ")
    if(not len(data)):
        break
    myfileIO.write(data + '\n')
myfileIO.close()

# Read from file
myfileIO = open('/Users/j/Desktop/pyTester', 'r')
for line in myfileIO:
    print(line)
myfileIO.close()