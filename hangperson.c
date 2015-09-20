#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>


/*
 * linked list data structure definitions
 */
struct _wordnode {
    char word[256];
    struct _wordnode *next;
};
typedef struct _wordnode wordnode;


/*
 * Be happy you didn't have to write this function.
 * Prints a low-tech ASCII gallows.  Max number of misses
 * is 7 (i.e., if there are 7 misses, the player loses and
 * the poor sap gets hung).  
 */
void print_gallows(int num_missed) {
    // make sure that we got called in a reasonable way
    assert(num_missed >= 0 && num_missed <= 7);

    printf("\n\n       |||========|||\n");
    if (num_missed > 0) {
        printf ("       |||         |\n");
    } else {
        printf ("       |||          \n");
    }

    if (num_missed > 1) {
        printf ("       |||         O\n");
    } else {
        printf ("       |||          \n");
    }

    if (num_missed > 2) {
        if (num_missed > 4) {
            printf ("       |||        /|\\\n");
        } else if (num_missed > 3) {
            printf ("       |||        /| \n");
        } else {
            printf ("       |||        /  \n");
        }
    } else {
        printf ("       |||           \n");
    }

    if (num_missed > 5) {
        if (num_missed > 6) {
            printf ("       |||        / \\\n");
        } else {
            printf ("       |||        /  \n");
        }
    } else {
        printf ("       |||           \n");
    }

    printf ("       |||\n");
    printf ("       |||\n");
    printf ("     =================\n\n");
}



int valid_guess(bool* guess_list, char* current_guess) {
  /*
  Given a list of guessed letters (organized by ASCII value to index) this function sees if the guess has already been guessed. If it has, it returns a 0, if it is a new guess, this function returns a 1.
  */
  
  // later on we can add complexity where we return different numbers to indicate different reasons for invalidity (eg. 1 means already guessed 2 means non-alpha char)
    
  printf("Checking guess...\n");
  if (strlen(current_guess) !=1) {
    return 0;
  }
  
  *current_guess = toupper(*current_guess);
  if (*current_guess <= 'Z' && *current_guess >= 'A') {
    printf("Guess is a character.\n");
    int index = *current_guess - 'A';
    if (guess_list[index]) {
      return 0;
    }
    else {
      printf("Valid guess\n");
      guess_list[index] = true;
      return 1;
    }
  }
  else {
    return 0;
  }
}

char prompt_guess(bool* guess_list){
  /*
  Prompts user for a guess and returns a valid guess. If invalid (checks validity by calling valid_guess), prompts user continuously for a valid guess.
  */
  int buffer = 256;
  char current_guess = 'A';
  printf ("Enter a character: ");
  fgets(&current_guess, buffer*sizeof(char), stdin);
  printf ("You entered: %c\n", current_guess);
  int valid_guess = valid_guess(guess_list, &current_guess);
  while (valid_guess != 1){
    current_guess = 'A';
    printf("Invalid Guess. You have either guessed this letter already or entered a non-alphabetic character. \nPlease enter a new character :\t");
    fgets(&current_guess, buffer*sizeof(char), stdin);
    current_guess = toupper(current_guess);
    printf ("You entered: %c\n", current_guess);
    valid_guess = valid_guess(guess_list, &current_guess);
  }
  return current_guess;
}

/*
 * Play one game of Hangperson.  The secret word is passed as a
 * parameter.  The function should return true if the player won,
 * and false otherwise.
 */
bool one_game(const char *word) {
    int guess_count = 0;
    int max_guesses = 7;
    char* secret_word_cpy = strdup(word);
    char state[strlen(word) + 1];
    for (int i=0; i<strlen(word); i++){
        state[i] = '_';
    } //initialize state as a bunch of blanks
    state[strlen(word)] = '\0';
    printf("Welcome to Hangman! \n");
    printf("Your word is:\t%s\n", state);
    print_gallows(guess_count);
    printf("Let the fun begin!\n");
   // bool is_over = false; 
    bool did_win = false; //bool that will be returned
    bool guessed[26] = {false}; //where we store guesses
    char current_guess;
    bool in_word = false; // true if guess is in secret word 
    while (guess_count < max_guesses){
      current_guess = prompt_guess(&guessed);
      in_word = check_word(state, secret_word_cpy, current_guess);
      if (!in_word){
        guess_count++;
      }
      printf("Your word is:\t%s\n", state);
      print_gallows(guess_count);
    }
    //if check if state == word
    //  win
    //else
    // lose
  return did_win;
}

bool check_word(char* state, char* word, char current_guess) {
  int letter_count = 0;
  /*
  Checks if letter in word, and how many times
  Updates State
  returns true if in word, false otherwise
  */
  for (int i = 0; i < strlen(word); i++) {
    if (word[i] == current_guess) {
      state[i] = current_guess;
      letter_count++;
    }
  }
  if (letter_count == 0) {
    return false;
  }
  return true;
}



char *fix_word(char *word){ 
  /* given a word this function returns NULL if the word is non-alphabetic. For alphabetic words, or an alpha word with the last character as a new line , deletes the new line character and returns the word with all uppercase letters
  */
  char *ret_word = malloc((strlen(word)+1)*sizeof(char));
	if (strlen(word) == 1 && isalpha(word[0]) == 0) {
	  return NULL;
	}
	for (int i = 0; i < strlen(word)-1; i++) {
		if (isalpha(word[i]) == 0) {
			return NULL;
		}
		ret_word[i] = toupper(word[i]);
	}
	//check if last char is  \n, strip if it is
	if (strlen(word) > 0 && word[strlen(word)-1] != '\n'){
    if (isalpha(word[strlen(word)-1])!=0) {  // alpha char
      ret_word[strlen(word)-1] = toupper(word[strlen(word)-1]); 
		  ret_word[strlen(word)] = word[strlen(word)] = '\0'; 
    }
    else { // non alpha character
      return NULL;
    }
  }
  else if (strlen(word) > 0 && word[strlen(word)-1] == '\n') {
		  ret_word[strlen(word)-1] = '\0';
	}

	return ret_word;
}


wordnode *list_insert(char *word, wordnode *head){
	//using list_insert_head2 as defined in class, passing in word as value
	wordnode *new_node = malloc(sizeof(wordnode));
	strcpy(new_node -> word, word);
	new_node -> next = head;
	return new_node;
}

/* 
 * wordbank-related functions. please don't change the
 * function prototypes for these three functions.
 * load_words takes the name of the file that should be
 * opened and words read from, and a pointer to an int
 * that should be indirectly modified to store the number
 * of words loaded from the file.  The function should 
 * return the linked list of words.
 */
wordnode *load_words(const char *filename, int *num_words) {
	FILE *raw_words = fopen(filename, "r");
	int size = 256; //arbitrary? what should size be?
	char *this_line = malloc(size*sizeof(char));
	fgets(this_line, size, raw_words);
	*num_words = 0;
	wordnode *head = malloc(sizeof(wordnode));
	head = NULL;
	char *next_word = NULL; //temp variable to store words to be added
        do{
	    next_word = fix_word(this_line);
    	    if (next_word != NULL){
		head = list_insert(next_word, head);
	    	*num_words = *num_words + 1; //dereference to indirectly modify
            }
            free(next_word);
	} while (fgets(this_line, size, raw_words) != NULL);
        
        free(this_line);
	return head;
}


/*
 * Completely free and deallocate the linked list of words.
 */
void free_words(wordnode *wordlist) {
	//using list_destroy code from worksheet
	while (wordlist != NULL){
                wordnode *tmp = wordlist;
		wordlist = wordlist -> next;
		free(tmp);
	}
}

/*
 * Choose one random word from the linked list and return it.
 */
const char *choose_random_word(wordnode *wordlist, int num_words) {
    int rand_i = random() % num_words ;
    for (int i = 0; i <rand_i; i++){
        wordlist = wordlist -> next;
    }
    const char *rand_word = wordlist -> word;
    return rand_word;
}


/*
 * The main function is where everything starts.  Choose a random
 * word and call one_game.  Start first on getting the word-loading
 * to work correctly, then handle the game playing capabilities.
 */
#ifndef AUTOTEST
int main() {
    srandom(time(NULL));
    int num_words = 0;
    wordnode *words = load_words("/usr/share/dict/words", &num_words);
    if (num_words == 0) {
        printf("Didn't load any words?!\n");
        return 0;
    }
    const char *word = choose_random_word(words, num_words);
    one_game(word);
    //char *test_str = "helLoO\n";
    //char *hopefully_fixed = fix_word(test_str);
    //printf("Test fix_word is 'helLoO', %s %s \n", hopefully_fixed, hopefully_fixed);
    printf("First word is %s \n", words -> word);
    printf("Random word is %s \n", word);
    free_words(words);
    return 0;
}
#endif
