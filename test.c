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



wordnode *list_insert(char *word, wordnode *head){
	//using list_insert_head2 as defined in class, passing in word as value
	wordnode *new_node = malloc(sizeof(wordnode));
	strcpy(new_node -> word, word);
	new_node -> next = head;
	return new_node;
}




int check_guess(bool* guess_list, char* current_guess) {
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
  Prompts user for a guess and returns a valid guess. If invalid (checks validity by calling check_guess), prompts user continuously for a valid guess.
  */
  int buffer = 256;
  char current_guess = 'A';
  printf ("Enter a character: ");
  fgets(&current_guess, buffer*sizeof(char), stdin);
  printf ("You entered: %c\n", current_guess);
  int valid_guess = check_guess(guess_list, &current_guess);
  while (valid_guess != 1){
    current_guess = 'A';
    printf("Invalid Guess. You have either guessed this letter already or entered a non-alphabetic character. \nPlease enter a new character :\t");
    fgets(&current_guess, buffer*sizeof(char), stdin);
    current_guess = toupper(current_guess);
    printf ("You entered: %c\n", current_guess);
    valid_guess = check_guess(guess_list, &current_guess);
  }
  return current_guess;
}




int main() {
  char guess;
  int guess_count = 0;
  int max_guesses = 7;
  bool guess_list[26] = {false};
  if (guess_count < max_guesses) {
    guess = prompt_guess(guess_list);
    printf("Return to main guess value : %c\n", guess);
    printf("Value of %c in guess list (should be true) : %d\n", guess, guess_list[guess - 'A']);
  }
  return 0; 
}








	    
	    
