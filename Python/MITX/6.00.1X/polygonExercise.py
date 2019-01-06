#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Sep 16 17:51:43 2018

@author: j
"""

'''
A regular polygon has n number of sides. Each side has length s.

The area of a regular polygon is: (.25 * n * s**2) / tan(pi / n)
The perimeter of a polygon is: length of the boundary of the polygon
Write a function called polysum that takes 2 arguments, n and s. 
This function should sum the area and square of the perimeter of the regular polygon. 
The function returns the sum, rounded to 4 decimal places.
'''

import math
def polysum(n, s):
    def polyArea(n,s):
        return (.25*n*s**2)/math.tan(math.pi/n)
    def polyPerimeter(n,s):
        return n * s
    ans = polyArea(n,s) + polyPerimeter(n, s)**2
    return round(ans, 4)