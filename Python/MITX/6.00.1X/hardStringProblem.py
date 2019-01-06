#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Sep 21 22:16:05 2018

@author: j
"""

s = 'mcoctsrpnaheyasjwqrmr'
# Paste your code into this box 
newStr = prev = ""
myStrs = []
for char in s:
    if prev <= char:
        newStr += char    
    else:
        myStrs.append(newStr)
        newStr = char
    prev = char
if len(newStr):
    myStrs.append(newStr)
word = ""
for w in myStrs:
    if len(word)<len(w):
        word = w
print("Longest substring in alphabetical order is:", word)