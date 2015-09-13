#Lillie Pentecost, Problem Set 4, Hangperson
import random
def play_hangperson():
    '''This function prompts the user if they want to play, runs through the game with the user, and at the end of the game it will prompt the user if they want to play again.'''
    response=raw_input("Hey! Do you want to play hangman? Type yes or no.")
    while response!='no':
        if response!= 'yes':
            print "Just say yes or no please."
            response=raw_input("Do you want to play hangman now? Type yes or no.")
        else:
            play_one_game()
            response=raw_input("Do you want to play again? Type yes or no.")
    print "Goodbye!  Hope you had a great time!"

def play_one_game():
    '''This function interacts with the user and executes a single game of hangperson.'''
    secret_word=get_word()
    guess_state=["__"]*len(secret_word)
    missed_letters=[]
    num_missed=len(missed_letters)
    guessed_letters=[]
    while ''.join(guess_state)!=secret_word:
        print_game(guess_state, missed_letters, num_missed)
        char, guessed_letters=verify_guess(guessed_letters)
        missed_letters, guess_state, num_missed=check_for_char(missed_letters, guess_state, secret_word, char, num_missed)
        if num_missed>7:
            break
    if ''.join(guess_state)==secret_word:
        print guess_state
        print "Yes! The word was", secret_word, "! Congratulations!"
    else:
        printGallows(7)
        print "You lost.  The secret word was", secret_word, ".  Your life is sad."
    return

def get_word():
    '''This function selects the secret word for the game of hangman from a wordlist.'''
    word_list=['ACCOUNT', 'ADJUSTMENT', 'AFTERTHOUGHT', 'AIRPORT', 'AMUSEMENT', 'BALANCE', 'BASKETBALL', 'CALCULATOR', 'CARPENTER', 'CATTLE', 'CEMETARY', 'DISCOVERY', 'DISTRIBUTION', 'EARTHQUAKE', 'EXPERT', 'EYES', 'FAIRIES', 'FIREMAN', 'FURNITURE', 'GOVERNMENT', 'GUITAR', 'HOBBIES', 'HYDRANT', 'INSTRUMENT', 'INVENTION', 'JOURNEY', 'KNOWLEDGE', 'LADYBUG', 'LEARNING', 'LIZARDS', 'MAILBOX', 'MIDDLE', 'MINISTER', 'NEEDLE', 'NOTEBOOK', 'OATMEAL', 'ORNAMENT', 'PAYMENT', 'PASSENGER', 'PICTURE', 'QUICKSAND', 'QUARTZ', 'QUIVER', 'RAINSTORM', 'RHYTHM', 'SCARECROW', 'SHOCK', 'TENDENCY', 'THUNDER', 'TURKEY', 'UNIT', 'UMBRELLA', 'UNDERWEAR', 'VEGETABLE', 'VOLLEYBALL', 'VOYAGE', 'WILDERNESS', 'WINTER', 'YARN', 'ZEBRA', 'ZIPPER'] #add words to wordlist
    secret_word= random.choice(word_list) #Taken from moodle help
    return secret_word

def print_game(guess_state, missed_letters, num_missed):
    '''This function takes the parameters of the guess state, the list of missed letters, and the number of missed letters to print the status of the word and the hanged person after each guess.'''
    printGallows(num_missed)
    print "Here are your failed guesses so far:", ''.join(missed_letters)
    print guess_state

def get_guess():
    '''This function gets the next letter guess from the user.'''
    char=raw_input("What is your guess?")
    return char.upper()

def verify_guess(guessed_letters):
    '''This function verifies that the user input is a valid guess and if it is, it is added to the list of guessed letters.'''
    char=get_guess()
    if char.isalpha()==False:
        print "Give me a letter next time."
        char=get_guess()
    if len(char)!=1:
        print "Try a single letter next time."
        char=get_guess()
    if char in guessed_letters:
        print "You already guessed this letter.  Try again."
        char=get_guess()
    guessed_letters+=char
    return char, guessed_letters

def check_for_char(missed_letters, guess_state, secret_word, char, num_missed):
    '''This function takes the parameters of the list of missed letters, the guess state, the secret word, and the number of missed letters and checks for the character in the secret word, updating the guess state and the list of missed letters accordingly.'''
    index=-1
    if char in secret_word:
        for i in range(secret_word.count(char)): #I got this idea from the Webcrawler example during Friday's class
            index=secret_word.find(char, index+1)
            guess_state[index]=char
    else:
        missed_letters+=char
        num_missed+=1
    return missed_letters, guess_state, num_missed
            
def printGallows(num_missed): #function taken from Moodle help
    '''
    Make a poor-human's representation of the hangperson gallows.
    Parameter to the function is the number of missed words (7 misses
    means that the player is fully strung up).
    '''
    print 
    print 
    print '       |||========|||'
    if num_missed > 0:
        print '       |||         |'
    else:
        print '       |||          '

    if num_missed > 1:
        print '       |||         O'
    else:
        print '       |||          '

    if num_missed > 2:

        if num_missed > 4:
            print '       |||        /|\\'
        elif num_missed > 3:
            print '       |||        /| '
        else:
            print '       |||        /  '
    else:
        print '       |||           '

    if num_missed > 5:
        if num_missed > 6:
            print '       |||        / \\'
        else:
            print '       |||        /  '
    else:
        print '       |||           '

    print '       |||'
    print '       |||'
    print '     ================='
    print  


play_hangperson()
