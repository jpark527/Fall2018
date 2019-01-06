#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Oct  4 21:36:00 2018

@author: j
"""

''' L ocal - the current function you are in
    E nclosing Function - the function that called the current functon, if any
    G lobal - the module in which the function was defined
    B uilt-in - python's built-in namespace '''
    

''' Scope Test '''
def update(x, n):
    x.append(10)
    n += 3
    
def main():
    x = [1,2,3]
    n = 5
    print(x, n)
    update(x,n)
    print(x, n)

#main()
    
''' Class Demo '''
class mySet(set):
    def removeMin(self):
        self.remove(min(self))
    def removeMax(self):
        self.remove(max(self))
    def __str__(self):
        ans = str()
        for e in self:
            ans += str(e) + ', '
        return ans[:-2]
    
n = mySet()
for i in range(1, 11):
    n.add(i)

''' These two below are same thing '''
n.removeMin()
mySet.removeMin(n)
#print(n)

print(isinstance(n, mySet))




