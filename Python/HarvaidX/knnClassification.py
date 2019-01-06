#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Nov  2 23:38:02 2018

@author: j
"""

import numpy as np
import random
import scipy.stats as ss
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

def getDistance(p1, p2):
    '''
    Find the distance between p1 and p2.
    '''
    p1 = np.array(p1)
    p2 = np.array(p2)
    return np.sqrt(np.sum(np.power(p2-p1, 2)))

def majorityVote(votes):
    '''
    Returns the most common element in votes.
    '''
    voteCount = dict()
    for v in votes:
        if v in voteCount:
            voteCount[v] += 1
        else:
            voteCount[v] = 1    
    maxVote = max(voteCount.values())
    winners = list()
    for key, value in voteCount.items(): # this items() allows user to get both key and value at the same time
        if value == maxVote:
            winners.append(key)
    return random.choice(winners)

def majorityVote2(votes):
    '''
    Same as majorityVote
    '''
    mode, count = ss.mstats.mode(votes)
#    print(mode, count)
    return random.choice(mode)
    
def findNearestPoints(p, points, k=5):
    '''
    Find the k nearest neighbors of point p and return their indices
    '''
    distances = np.zeros(points.shape[0])
    for i in range(len(distances)):
        distances[i] = getDistance(p, points[i])
    d = np.argsort(distances) # gives the array of original indices in a sorted order.
    return d[:k%len(d)]

def knnPredict(p, points, outcomes, k=5):
    ind = findNearestPoints(p, points, k)
    return majorityVote(outcomes[ind])

def generateSyntheticData(n=50):
    '''
    Generate 2 sets of points from bivariate normal distributions.
    '''
    points = np.concatenate((ss.norm(0,1).rvs((n,2)), ss.norm(1,1).rvs((n,2))), axis=0)
    outcomes = np.concatenate((np.repeat(0,n), np.repeat(1,n)))
    return points, outcomes

def makePredictionGrid(predictors, outcomes, limits, h, k):
    '''
    Classify each point on the prediction grid.
    '''
    xMin, xMax, yMin, yMax = limits
    x = np.arange(xMin, xMax, h)
    y = np.arange(yMin, yMax, h)
    xx, yy = np.meshgrid(x,y)
    
    predictionGrid = np.zeros(xx.shape, dtype = int)
    for k1, v1 in enumerate(x):
        for k2, v2 in enumerate(y):
            p = np.array([v1, v2])
            predictionGrid[k2, k1] = knnPredict(p, predictors, outcomes, k)
    return x, y, predictionGrid

def plotPredictionGrid (xx, yy, predictionGrid):
    ''' 
    Plot KNN predictions for every point on the grid.
    '''
    backgroundColormap = ListedColormap (['hotpink', 'lightskyblue', 'yellowgreen'])
    observationColormap = ListedColormap (['red', 'blue', 'green'])
    plt.figure(figsize =(10,10))
    plt.pcolormesh(xx, yy, predictionGrid, cmap = backgroundColormap, alpha = 0.5)
    plt.scatter(predictors[:,0], predictors [:,1], c = outcomes, cmap = observationColormap, s = 50)
    plt.xlabel('Variable 1'); plt.ylabel('Variable 2')
    plt.xticks(()); plt.yticks(())
    plt.xlim (np.min(xx), np.max(xx))
    plt.ylim (np.min(yy), np.max(yy))


#n = 5; k = 5; h = 0.1; limits=(-3,5,-3,5)
#predictors, outcomes = generateSyntheticData(20)
#xx, yy, predictionGrid = makePredictionGrid(predictors, outcomes, limits, h, k)
#plotPredictionGrid(xx, yy, predictionGrid)

#''' Plot points to visualize '''
#plt.figure()
#plt.plot(predictors[:n,0], predictors[:n,1], 'rd')
#plt.plot(predictors[n:,0], predictors[n:,1], 'go')
#plt.axis(limits)

''' Different Data (Fisher 1988)'''
from sklearn import datasets

k = 5; h = 0.1; limits=(3,9,1.5, 5)
iris = datasets.load_iris()
predictors = iris.data[:, 0:2]
outcomes = iris.target
xx, yy, predictionGrid = makePredictionGrid(predictors,outcomes,limits,h,k)
plotPredictionGrid(xx,yy,predictionGrid)

#plt.plot(predictors[outcomes==0][:,0], predictors[outcomes==0][:,1], 'ro')
#plt.plot(predictors[outcomes==1][:,0], predictors[outcomes==1][:,1], 'bo')
#plt.plot(predictors[outcomes==2][:,0], predictors[outcomes==2][:,1], 'go')


''' More prediction using knn algorithm and sklearn library '''
from sklearn.neighbors import KNeighborsClassifier
knn = KNeighborsClassifier(n_neighbors=5)
knn.fit(predictors, outcomes)
skPredictions = knn.predict(predictors)

myPredictions = np.array([knnPredict(p, predictors, outcomes, 5) for p in predictors])

print(100 * np.mean(skPredictions==myPredictions))

print(100 * np.mean(skPredictions==outcomes))

print(100 * np.mean(myPredictions==outcomes))




