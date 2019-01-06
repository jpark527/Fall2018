#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Nov  2 19:38:05 2018

@author: j
"""

import urllib.request

def saveContentsFromURL(filename, address):
    '''
    Get the data in a text format from the given URL, and save to the location given. 
    '''
    data = urllib.request.urlopen(address).read().decode('utf-8')
    writer = open(filename, 'w')
    writer.write(data)
    writer.close()