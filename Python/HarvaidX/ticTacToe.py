#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Oct  6 09:09:19 2018

@author: j
"""
#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt
import random
def createBoard():
    board = np.zeros((3,3))
    return board

def place(board, player, position):
    board[position[0]][position[1]] = player
    
def possibilities(board):
    emp = list()
    x,y = np.where(board==0)
    for i in range(len(x)):
        emp.append((x[i], y[i]))
    return emp

def randomPlace(board, player):
    pos = random.choice(possibilities(board))
    place(board, player, pos)

def rowWin(board, player):
    for i in range(len(board)):
        if np.all(board[i] == player):
            return True
    return False

def colWin(board, player):
    for i in range(len(board)):
        if np.all(board.transpose()[i] == player):
            return True
    return False

def diagWin(board, player):
    left = True
    right = True
    for i in range(len(board)):
        if left:
            left = (board[i][i] == player)
        if right:
            right = (board[i][len(board)-i-1] == player)
    return left or right

def evaluate(board):
    winner = 0
    for player in [1, 2]:
        if rowWin(board,player) or colWin(board,player) or diagWin(board,player):
            winner = player
            break
    if np.all(board != 0) and winner == 0:
        winner = -1
    return winner

def playGame():
    board = createBoard()
    over = i = 0
    player = (1,2)
    while not over:
        randomPlace(board, player[i])
        over = evaluate(board)
        i = (i + 1) % len(player)
    return over

def playStrategicGame():
    board, winner = createBoard(), 0
    board[1,1] = 1
    while winner == 0:
        for player in [2,1]:
            randomPlace(board, player)
            winner = evaluate(board)
            if winner != 0:
                break
    return winner


import time
#data = []
#start = time.clock()

#for i in range(1000):
#    data.append(playGame())
#    
#stop = time.clock()
#print((stop - start)/time.time())
#
#plt.hist(data, np.linspace(-1.5, 2.5, 4))
#plt.show()


data = []
start = time.clock()

for i in range(1000):
    data.append(playStrategicGame())
    
stop = time.clock()
print((stop - start)/time.time())

plt.hist(data, np.linspace(-1.5, 2.5, 4))
plt.show()
