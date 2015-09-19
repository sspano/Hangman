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




int check_guess(char guess_list[], char guess) {
  /*
  Given a list of guessed letters (organized by ASCII value to index) this function sees if the guess has already been guessed. If it has, it returns a 0, if it is a new guess, this function returns a 1.
  */
  // convert char to ascii value
  // checks that the character is within the ranges for lower or uppercase letters (if not returns 0)
  // converts to uppercase (adds some int to int value)
  // subtracts value of 'A' to get index value
  // sees if that guess_list[index] == 0 if so valid guess, change value to 0
  // otherwise invalid guess, return 0
  // later on we can add complexity where we return different numbers to indicate different reasons for invalidity (eg. 1 means already guessed 2 means non-alpha char)
  return 0;
}

char prompt_guess(char* guess_list[]){
  /*
  Prompts user for a guess and returns a valid guess. If invalid (checks validity by calling check_guess), prompts user continuously for a valid guess.
  */
  char current_guess = 'A';
  printf ("Enter a character: ");
  scanf ("%c", &current_guess); // need to change the character to upper case
  printf ("You entered: %c\n", current_guess);
  int valid_guess = 1;
//  int valid_guess = check_guess(guess_list, current_guess);
  while (!valid_guess){
    //prompt
    printf("Invalid Guess. You have either guessed this letter already or entered a non-alphabetic single character. Please enter a new character.");
    scanf ("%c", &current_guess);
    printf ("You entered: %c\n", current_guess);
  }
  return 0;
}




int main() {
 
  char guess;
  char guess_list[126] = {0};
  guess = prompt_guess(&guess_list);
  
  return 0;
  
}








	    
	    