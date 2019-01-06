#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec 20 19:22:18 2018

@author: j
"""

''' Monte Carlo Simulation
You have a bucket with 3 red balls and 3 green balls. Assume that once you draw a ball out of the bucket, 
you don't replace it. What is the probability of drawing 3 balls of the same color?
Write a Monte Carlo simulation to solve the above problem. Feel free to write a helper function if you wish.
'''

import random

def noReplacementSimulation(numTrials):
    '''
    Runs numTrials trials of a Monte Carlo simulation
    of drawing 3 balls out of a bucket containing
    3 red and 3 green balls. Balls are not replaced once
    drawn. Returns the a decimal - the fraction of times 3 
    balls of the same color were drawn.
    
    Notice: actual value = 1 / 10 = (2 / 5) * (1 / 4)
    '''
    # Your code here
    bucket = 'R', 'R', 'R', 'G', 'G', 'G'
    same = 0
    for trial in range(numTrials):
        pick1 = pick2 = pick3 = random.choice(range(6))
        while pick1 == pick2 or pick1 == pick3 or pick2 == pick3:
            pick2 = random.choice(range(6))
            pick3 = random.choice(range(6))
        if bucket[pick1] == bucket[pick2] == bucket[pick3]:
            same += 1
    return same / numTrials
            
# Write a Monte Carlo simulation to solve the above problem. 
# Feel free to write a helper function if you wish.
# Paste your entire function (including the definition) in the box.
# Restrictions:
# Do not import or use functions or methods from pylab, numpy, or matplotlib.
# Do not leave any debugging print statements when you paste your code in the box.


# Paste your code here
def drawing_without_replacement_sim(numTrials):
    '''
    Runs numTrials trials of a Monte Carlo simulation
    of drawing 3 balls out of a bucket containing
    4 red and 4 green balls. Balls are not replaced once
    drawn. Returns a float - the fraction of times 3 
    balls of the same color were drawn in the first 3 draws.
    
    Notice: actual value = 1 / 7 = (3 / 7) * (2 / 6)
    '''
    counter = 0
    for i in range(numTrials):
        bucket = ['R', 'R', 'R', 'R', 'G', 'G', 'G', 'G']
        picks = []
        for j in range(3):
            k = random.choice(bucket)
            picks.append(k)
            bucket.remove(k)
        if picks[0] == picks[1] == picks[2]:
            counter += 1
    return counter / numTrials   


