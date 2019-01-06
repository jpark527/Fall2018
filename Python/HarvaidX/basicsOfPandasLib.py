#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Nov  3 12:31:39 2018

@author: j
"""

import pandas as pd

''' There are two data structures in pandas, Series, and DataFrame.
    Series is 1-dimensional array-like object while DataFrame is 2-dimensional. '''
s = pd.Series([7,2,5,1])
print(s, '\n')

s = pd.Series([7,2,5,1], index=['A','B','C','D'])
print(s, '\n')

# Dictionary can be easily converted to Series.
age = {'Chris':13, 'Drew':25, 'Andre':33, 'Bree':21, 'ET':52}
s = pd.Series(age)
print(s, '\n') 
print(s[ ['Andre', 'Drew', 'ET'] ], '\n') # Can also call by multiple key values.

# You can also sort the index by using the reindex attribute.
l = sorted(s.index)
s = s.reindex(l)
print(s, '\n')

# You can also add Series.
s = pd.Series([7,2,5,1], index=['A','B','C','D'])
s2 = pd.Series([10,20,30,40], index=['B','C','E','F'])
print(s+s2, '\n')

print('=======================================================\n')

''' DataFrames represent table-like data, and they have both row and column index. '''
data = {'name':['Bill', 'Alice', 'Riley', 'Pam', 'Sam'], 
        'age':[42,21,53,34,23], 
        'ZIP':['08240','00213','20184','91204','91214']}
d = pd.DataFrame(data, columns=data.keys())
print(d)
