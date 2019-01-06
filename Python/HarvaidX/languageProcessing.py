#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Oct 29 17:26:42 2018

@author: j
"""
import os
import pandas as pd
import matplotlib.pyplot as plt

def countWords(text):
    '''
    Count the number of times each word occurs in text (str).
    Return dictionary where keys are unique words and values are word counts.
    Skip punctuation.
    '''
    text = text.lower()
    punctuation = '.', ',', ':', ';', '"', "'", '?', '!', '~', '_', '-', '(', ')'
    for p in punctuation:
        text = text.replace(p, ' ')
    
    words = dict()
    for w in text.split(' '):
        if w in words.keys():
            words[w] += 1
        else:
            words[w] = 1
    return words

def readBook(path):
    '''
    Read a book and return it as a string.
    '''
    text = str()
    with open(path, 'r', encoding='utf8') as file:
        text = file.read()
        text = text.replace('\n', '').replace('\r', '')
    return text

def wordStats(words):
    '''
    Return number of unique words and word frequencies
    '''
    uniqueWords = len(words)
    counts = words.values()
    return uniqueWords, counts
    

BOOKS_DIR = '/Users/j/Python/HarvaidX/Books'

dataTable = pd.DataFrame(columns = ('  title', '  unique', '  total'))
count = 1
for book in os.listdir(BOOKS_DIR):
    path = BOOKS_DIR + '/' + book
    txt = readBook(path)
    uniqueWords, counts = wordStats(countWords(txt))
    dataTable.loc[count] = book.replace('.txt', ''), uniqueWords, sum(counts)
    count += 1

''' Adding a new column to pd.DataFrame '''
numStr = ['one', 'two', 'three', 'four', 'five']
dataTable = dataTable.assign(count=pd.Series(numStr).values)

print(dataTable)

plt.plot(dataTable['  total'], dataTable['  unique'], 'go', label='books')
#plt.loglog(dataTable['  total'], dataTable['  unique'], 'bx', label='books')

plt.legend()
plt.xlabel('total')
plt.ylabel('unique')

