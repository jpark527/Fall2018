#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct 27 09:39:01 2018

@author: j
"""

''' Final Problem Sets '''
''' #1 '''
def McNuggets(n):
    '''
    n is an int

    Returns True if some integer combination of 6, 9 and 20 equals n
    Otherwise returns False.
    '''
    if n >= 20 and n % 3:
        return McNuggets(n-20)
    elif n >= 9 and n % 6:
        return McNuggets(n-9)
    elif n >= 6:
        return McNuggets(n-6)
    elif not n:
        return True
    else:
        return False
    
def McNuggets2(n):
    '''
    n is an int

    Returns True if some integer combination of 6, 9 and 20 equals n
    Otherwise returns False.
    '''
    while n >= 20 and n % 3:
        n -= 20
    while n >= 9 and n % 6:
        n -= 9
    while n >= 6:
        n -= 6
    if n:
        return False
    else:
        return True
    
''' #2 '''
def longestRun(L):
    ind = run = 1
    prev = L[0]
    store = list()
    while ind < len(L):      
        if prev <= L[ind]:
            run += 1          
        else:
            ind -= (run-1)
            store.append(run)
            run = 1
        prev = L[ind]  
        ind += 1
    store.append(run)
    return max(store)

''' #3 
Assume you are given two dictionaries d1 and d2, each with integer keys and integer values. 
You are also given a function f, that takes in two integers, performs an unknown operation on them, 
and returns a value.
Write a function called dict_interdiff that takes in two dictionaries (d1 and d2). 
The function will return a tuple of two dictionaries: a dictionary of the intersect of d1 and d2 
and a dictionary of the difference of d1 and d2, calculated as follows:
    intersect: The keys to the intersect dictionary are keys that are common in both d1 and d2. 
               To get the values of the intersect dictionary, look at the common keys in d1 and d2 
               and apply the function f to these keys' values -- the value of the common key in d1 
               is the first parameter to the function and the value of the common key in d2 is 
               the second parameter to the function. Do not implement f inside your dict_interdiff code -- 
               assume it is defined outside.
    difference: a key-value pair in the difference dictionary is (a) every key-value pair in d1 whose 
                key appears only in d1 and not in d2 and (b) every key-value pair in d2 whose key appears 
                only in d2 and not in d1.
'''
def f(n,m):
    return n + m

def dict_interdiff(d1, d2):
    '''
    d1, d2: dicts whose keys and values are integers
    Returns a tuple of dictionaries according to the instructions above
    '''
    intersect = dict()
    difference = dict()
    for k1 in d1.keys():
        found = False
        for k2 in d2.keys():
            if k1 == k2:
                intersect[k1] = f(d1[k1], d2[k1])
                found = True
                break
        if not found:
            difference[k1] = d1[k1]
    for k2 in d2.keys():
        found = False
        for k1 in d1.keys():
            if k1 == k2:
                found = True
                break
        if not found:
            difference[k2] = d2[k2]
    return intersect, difference
    
''' #4 '''
## DO NOT MODIFY THE IMPLEMENTATION OF THE Person CLASS ##
class Person(object):
    def __init__(self, name):
        #create a person with name name
        self.name = name
        try:
            firstBlank = name.rindex(' ')
            self.lastName = name[firstBlank+1:]
        except:
            self.lastName = name
        self.age = None
    def getLastName(self):
        #return self's last name
        return self.lastName
    def setAge(self, age):
        #assumes age is an int greater than 0
        #sets self's age to age (in years)
        self.age = age
    def getAge(self):
        #assumes that self's age has been set
        #returns self's current age in years
        if self.age == None:
            raise ValueError
        return self.age
    def __lt__(self, other):
        #return True if self's name is lexicographically less
        #than other's name, and False otherwise
        if self.lastName == other.lastName:
            return self.name < other.name
        return self.lastName < other.lastName
    def __str__(self):
        #return self's name
        return self.name
        
class USResident(Person):
    """ 
    A Person who resides in the US.
    """
    def __init__(self, name, status):
        """ 
        Initializes a Person object. A USResident object inherits 
        from Person and has one additional attribute:
        status: a string, one of "citizen", "legal_resident", "illegal_resident"
        Raises a ValueError if status is not one of those 3 strings
        """
        # Write your code here
        Person.__init__(self, name)
        if status != "citizen" and status != "legal_resident" and status != "illegal_resident":
            raise ValueError
        self.status = status
        
    def getStatus(self):
        """
        Returns the status
        """
        # Write your code here
        return self.status

''' #5 '''
## DO NOT MODIFY THE IMPLEMENTATION OF THE Container CLASS ##
class Container(object):
    """ Holds hashable objects. Objects may occur 0 or more times """
    def __init__(self):
        """ Creates a new container with no objects in it. I.e., any object 
            occurs 0 times in self. """
        self.vals = {}
    def insert(self, e):
        """ assumes e is hashable
            Increases the number times e occurs in self by 1. """
        try:
            self.vals[e] += 1
        except:
            self.vals[e] = 1
    def __str__(self):
        s = ""
        for i in sorted(self.vals.keys()):
            if self.vals[i] != 0:
                s += str(i)+":"+str(self.vals[i])+"\n"
        return s
    
class ASet(Container):
    def __init__(self):
        Container.__init__(self)
        
    def remove(self, e):
        """assumes e is hashable
           removes e from self"""
        # write code here
        if self.is_in(e):
            del self.vals[e]

    def is_in(self, e):
        """assumes e is hashable
           returns True if e has been inserted in self and
           not subsequently removed, and False otherwise."""
        # write code here
        return e in self.vals.keys()


















