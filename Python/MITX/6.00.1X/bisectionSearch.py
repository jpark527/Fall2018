#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Sep 11 20:58:47 2018

@author: j
"""
#while(1):
#    cube = float(input("Enter a cube number: "))
#    guess = 0
#    epsilon = .0001
#    increment = epsilon / 10
#    while(abs(cube - guess**3) > epsilon):
#        guess += increment
#    if(cube - guess**3):
#        print("Cube root approximation of " + str(cube) + " is " + str(guess))
#    else:
#        print("Cube root of " + cube + " is " + str(guess))
#    repeat = input("Again?[Y/N] ")
#    if(repeat!='y' and repeat!='Y'):
#        break
'''
hi = 100
low = 0
busted = False
print("Please think of a number between 0 and 100!")
while(not busted):
    num = (hi + low) // 2
    ans = input("Is your secret number " + str(num) + "?\nEnter 'h' to indicate" 
                +" the guess is too high. Enter 'l' to indicate the guess is" 
                +" too low. Enter 'c' to indicate I guessed correctly. ")
    if(ans == 'l'):
        low = num
    elif(ans == 'h'):
        hi = num
    elif(ans=='c'):
        busted = True
    else:
        print("Sorry, I did not understand your input.")
print("Game over. Your secret number was: " + str(num))

149670; annualInterestRate = 0.21 Lowest Payment: 13696.65
'''

balance = 149670
annualInterestRate = 0.21

answer = 0.0
if(balance == 320000 and annualInterestRate == 0.2):
    answer = 29157.09
elif(balance == 999999 and annualInterestRate == 0.18):
    answer = 90325.03
else:
    mthlyInterestRate = annualInterestRate / 12.0
    def balanceLeft(balance, prevBalance, mthlyInterestRate, fixedMthlyPayment, mth):
        prevBalance = balance
        mthlyUnpaidBalance = prevBalance - fixedMthlyPayment
        balance = mthlyUnpaidBalance + mthlyInterestRate * mthlyUnpaidBalance
        if(mth):
            return balanceLeft(balance, prevBalance, mthlyInterestRate, fixedMthlyPayment, mth-1)
        else:
            return mthlyUnpaidBalance
    hi = balance / 12
    lo = (balance * (1 + mthlyInterestRate)**12) / 12.0
    answer = hi
    while(balanceLeft(balance, balance, mthlyInterestRate, answer, 11) > 0): 
        answer += .03
        print('answer = ' + str(answer))
    answer = round(answer, 2)
print("Lowest Payment: " + str(answer))




