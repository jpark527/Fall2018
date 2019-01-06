#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Nov  3 20:49:53 2018

@author: j
"""
import greedyAlgorithms as ga

def maxVal(toConsider, available):
    ''' 
    Assumes toConsider a list of items, available a weight.
    Returns a tuple of the total value of a solution to 0/1 knapsack problem and
    the items of that solution.
    toConsider: those items that nodes higher up in the tree (corresponding to the
                earlier calls in the recursive call stack) have not yet considered.
    available: the amount of space still available.
    '''
    if not toConsider or not available:
        result = (0,())
    elif toConsider[0].getCalories() > available:
        # Explore right branch only
        result = maxVal(toConsider[1:], available)
    else:
        nextItem = toConsider[0]
        # Explore left branch
        withVal, withToTake = maxVal(toConsider[1:], available-nextItem.getCalories())
        withVal += nextItem.getCost()
        # Explore right branch
        withoutVal, withoutToTake = maxVal(toConsider[1:], available)
        
        # Choose a better branch
        if withVal > withoutVal:
            result = withVal, withToTake + (nextItem, ) 
        else:
            result = withoutVal, withoutToTake

    return result

def testMaxVal(foods, maxUnits, printItems=True):
    print('Use search tree to allocate', maxUnits, 'calories.')
    val, taken = maxVal(foods, maxUnits)
    print('Total value of items taken =', val)
    if printItems:
        for item in taken:
            print(item)
            
def fastMaxVal(toConsider, available, memo=dict()):     
    ''' 
    Modified veersion of maxVal by using dynamic programming / memoization.
    Way faster than maxVal.
    '''
    if (len(toConsider), available) in memo:
        result = memo[len(toConsider), available]
    elif not toConsider or not available:
        result = (0,())
    elif toConsider[0].getCalories() > available:
        # Explore right branch only
        result = fastMaxVal(toConsider[1:], available)   
    else:
        nextItem = toConsider[0]
        # Explore left branch
        withVal, withToTake = fastMaxVal(toConsider[1:], available-nextItem.getCalories())
        withVal += nextItem.getCost()
        # Explore right branch
        withoutVal, withoutToTake = fastMaxVal(toConsider[1:], available)
        
        # Choose a better branch
        if withVal > withoutVal:
            result = withVal, withToTake + (nextItem, ) 
        else:
            result = withoutVal, withoutToTake
    memo[len(toConsider), available] = result
    return result
        
print('\n')
testMaxVal(ga.foods, 750)   # O(2**8) efficiency

''' Exercise 1 '''
def yieldAllCombos(items):
    """
        Generates all combinations of N items into two bags, whereby each 
        item is in one or zero bags.

        Yields a tuple, (bag1, bag2), where each bag is represented as a list 
        of which item(s) are in each bag.
    """
    # Enumerate the 3**N possible combinations   
    N = len(items)
    for i in range(3**N):
        bag1, bag2 = list(), list()
        for j in range(N):
            if (i // (3 ** j)) % 3 == 1:
                bag1.append(items[j])
            elif (i // (3 ** j)) % 3 == 2:
                bag2.append(items[j])
        yield bag1, bag2
            
            
            
            
            
            