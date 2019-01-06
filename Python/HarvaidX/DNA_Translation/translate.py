#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Oct 28 00:27:34 2018

@author: j
"""
''' SOURCE: https://www.ncbi.nlm.nih.gov/nuccore/NM_207618.2 '''

import dnaTable as table

def readFile(file):
    '''
    Reads and returns the input data with special characters removed. '''
    r = open(file, 'r')
    data = r.read().replace('\n', '')
    r.close()
    return data.replace('\r', '')   # For other operating system
    
def translate(s):
    ''' 
    Translate a string containing a nucleotide sequence into a string containing
    the corresponding sequence of amino acids. Nucleotides are translated in
    triplets using the dnaTable dictionary. Each amino acid is encoded with a 
    string of length 1.
    '''
    newS = temp = str()
    count = 0   
    # Check that the seq length is divisible by 3
    if len(s) % 3:
        return temp   
    # Loop over the seq
    for c in s:
        temp += c
        count += 1       
        # Extract a single codon
        if count == 3:
            count = 0
            # Look up the codon and store the result
            newS += table.dnaTable.get(temp)
            temp = str()
    return newS

dna = readFile('dna.txt') 
protein = readFile('aminoAcid.txt')
trans = translate(dna[20:938]) # CDS section specifies that the sequence should start from 21 to 938.
trans = trans[:-1] # If translated correctly, last codon should always end with '_' which is a stop codon.

if trans == protein:
    print('Translated successfully!')