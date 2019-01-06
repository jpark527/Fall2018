#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Oct 28 02:35:06 2018

@author: j
"""

# Let's look at the lowercase letters.
import string
alphabet = ' ' + string.ascii_lowercase

positions = dict()
for n in range(0,27):
    positions[alphabet[n]] = n
reverse = dict(zip(positions.values(), positions.keys()))

def encode(message, n):
    encodedMessage = str()
    for c in message:
        encodedMessage += reverse[(positions[c]+n) % 27]
    return encodedMessage

def decode(message, n):
    decodedMessage = str()
    for c in message:
        decodedMessage += reverse[(positions[c]-n) % 27]
    return decodedMessage