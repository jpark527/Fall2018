#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Oct  5 12:42:42 2018

@author: j
"""

class Animal(object):
    tag = 1
    def __init__(self, age):
        self.age = age
        self.name = None   
        self.tag = Animal.tag
        Animal.tag += 1
    def getAge(self):
        return self.age    
    def getName(self):
        return self.name    
    def setAge(self, age):
        self.age = age    
    def setName(self, name=str()):
        self.name = name    
    def __str__(self):
        return 'Name: ' + str(self.name) + '\nAge: ' + str(self.age)    
    def __repr__(self):
        return 'Animal(' + str(self.name) + ',' + str(self.age) + ')'
    
class Cat(Animal):
    def __init__(self, age):
        Animal.__init__(self, age)
    def speak(self):
        return 'Meow~'
    def __repr__(self):
        return 'Cat(' + str(self.name) + ',' + str(self.age) + ')'
    
class Cow(Animal):
    def __init__(self, age):
        Animal.__init__(self, age)
    def speak(self):
        return 'Mooo~'
    def __repr__(self):
        return 'Cow(' + str(self.name) + ',' + str(self.age) + ')'
    
class Person(Animal):
    def __init__(self, age):
        Animal.__init__(self, age)
    def speak(self):
        return 'Hola~'
    def __repr__(self):
        return 'Person(' + str(self.name) + ',' + str(self.age) + ')'