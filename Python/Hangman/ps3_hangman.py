import random

WORDLIST_FILENAME = "/Users/j/Python/Hangman/words.txt"

def loadWords():
    print("Loading word list from file...")
    inFile = open(WORDLIST_FILENAME, 'r')
    line = inFile.readline()
    wordlist = line.split()
    print("  ", len(wordlist), "words loaded.")
    return wordlist

def chooseWord(wordlist):
    return random.choice(wordlist)

def isWordGuessed(secretWord, lettersGuessed):
    count = len(secretWord)
    for char in secretWord:
        if char in lettersGuessed:
            count -= 1
    return not count

def getGuessedWord(secretWord, lettersGuessed):
    newSW = ""
    for char in secretWord:
        if char in lettersGuessed:
            newSW += char
        else:
            newSW += "_"
    return newSW


def getAvailableLetters(lettersGuessed):
    alphabets = "abcdefghijklmnopqrstuvwxyz"
    availables = ""
    for char in alphabets:
        if char not in lettersGuessed:
            availables += char
    return availables

def getInput(chance, lettersGuessed):
    letter = input("-------------\nYou have " + 
                   str(chance) + " guesses left.\nAvailable letters: " + 
                   getAvailableLetters(lettersGuessed) + 
                   "\nPlease guess a letter: ")
    return letter

def generateOutput(letter, lettersGuessed, secretWord):
    output = ""
    if(letter in lettersGuessed):
        output = "Oops! You've already guessed that letter: ", False
    elif(letter in secretWord):
        output = "Good guess: ", False
    else:
        output = "Oops! That letter is not in my word: ", True
    return output
 
def hangman(secretWord):
    display = ("     -----|\n     |\n     |\n     |\n     |\n     |\n    ---",
               "     -----|\n     |    O\n     |\n     |\n     |\n     |\n    ---",
               "     -----|\n     |    O\n     |    |\n     |\n     |\n     |\n    ---",
               "     -----|\n     |    O\n     |   /|\n     |\n     |\n     |\n    ---",
               "     -----|\n     |    O\n     |   /|\\\n     |\n     |\n     |\n    ---",
               "     -----|\n     |    O\n     |   /|\\\n     |   /\n     |\n     |\n    ---",
               "     -----|\n     |    O\n     |   /|\\\n     |   / \\\n     |\n     |\n    ---",
               "     -----|\n     |    O\n     |   /|\\\n     |  _/ \\\n     |\n     |\n    ---",
               "     -----|\n     |    O\n     |   /|\\\n     |  _/ \\_\n     |\n     |\n    ---")
    print("Welcome to the game, Hangman!\nI am thinking of a word that is "
          +str(len(secretWord))+" letters long.\n")
    chance = 8
    lettersGuessed = set()
    output = ()
    while chance and not isWordGuessed(secretWord,lettersGuessed):
        print(display[chance])
        letter = getInput(chance, lettersGuessed).lower()
        output = generateOutput(letter, lettersGuessed, secretWord)
        lettersGuessed.add(letter)
        print(output[0] + getGuessedWord(secretWord, lettersGuessed) +
              "\n-------------\n")
        if output[1]:
            chance -= 1
    print(display[chance])
    if(chance):
        print("Congratulations, you won!")
    else:
        print("Sorry, you ran out of guesses. The word was " 
              + secretWord + ".")
        
def again():
    ans = input("Again?[Y/N] ")
    return ans=="y" or ans=="Y"

'''
     -----|
     |    O
     |   /|\
     |  _/ \_
     |
     |
    ---
'''

wordlist = loadWords()
while(1):
    secretWord = chooseWord(wordlist).lower()
    hangman(secretWord)
    if(not again()):
        break

