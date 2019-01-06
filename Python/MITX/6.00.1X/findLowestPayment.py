#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Sep 16 19:59:10 2018

@author: j
"""

balance = 3926
annualInterestRate = 0.2

mthlyInterestRate = annualInterestRate / 12.0
def balanceLeft(balance, prevBalance, mthlyInterestRate, fixedMthlyPayment, mth):
    prevBalance = balance
    mthlyUnpaidBalance = prevBalance - fixedMthlyPayment
    balance = mthlyUnpaidBalance + mthlyInterestRate * mthlyUnpaidBalance
    if(mth):
        return balanceLeft(balance, prevBalance, mthlyInterestRate, fixedMthlyPayment, mth-1)
    else:
        # print(mthlyUnpaidBalance)
        return mthlyUnpaidBalance
answer = 1
while(balanceLeft(balance, balance, mthlyInterestRate, answer, 11) > 0):
    answer += 1
# print("answer = " + str(answer))
answer = round((answer+5)*.1) * 10
print("Lowest Payment: " + str(answer))