#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Nov  3 18:45:23 2018

@author: j
"""

class Food(object):
    def __init__(self, n, v, c):
        self.name = n
        self.value = v
        self.calories = c
        
    def getCost(self):
        return self.value
    
    def getCalories(self):
        return self.calories
    
    def getDensity(self):
        return self.value / self.calories
    
    def __str__(self):
        return 'Name: ' + self.name + '\nCost: ' + str(self.value) + '\nCalories: ' + str(self.calories)
    
    def __repr__(self):
        return '<Food>\nName: ' + self.name + '\nCost: ' + str(self.value) + '\nCalories: ' + str(self.calories) + '\n'

def buildMenu(names, values, calories):
    ''' 
    Takes in the lists of SAME length, names, values, and calories. 
    And returns list of Foods.
    names : a list of string
    values, calories : lists of numbers
    '''
    menu = list()
    for i in range(len(names)):
        menu.append(Food(names[i], values[i], calories[i]))
    return menu

def greedy(items, maxCal, keyFunction): # Costs n log n which is (<< 2**n)
    ''' 
    items: a list of items
    maxCal >= 0
    keyFunction: maps elements of items to numbers
    '''
    itemsCopy = sorted(items, key = keyFunction, reverse = True) # n log n HERE
    result = list()
    totalCost, totalCal = 0., 0.
    
    for i in range(len(itemsCopy)):
        if (totalCal + itemsCopy[i].getCalories()) <= maxCal:
            result.append(itemsCopy[i])
            totalCal += itemsCopy[i].getCalories()
            totalCost += itemsCopy[i].getCost()
    
    return result, totalCost

def testGreedys(foods, maxUnits):
    print('Use greedy by calories to allocate', maxUnits, 'calories:\n', 
          greedy(foods, maxUnits, Food.getCalories))
    print('\nUse greedy by cost to allocate', maxUnits, 'calories:\n',
          greedy(foods, maxUnits, lambda x : 1/Food.getCost(x)))    # Cheaper the better
    print('\nUse greedy by density to allocate', maxUnits, 'calories:\n',
          greedy(foods, maxUnits, Food.getDensity))
   
    
    
names = ['wine', 'bear', 'pizza', 'burger', 'fries', 'cola', 'apple', 'donut']
values = [89, 90, 95, 100, 90, 79, 50, 10]
calories = [123, 154, 258, 354, 365, 150, 95, 195]
foods = buildMenu(names, values, calories)
testGreedys(foods, 750)
        
        
        
        