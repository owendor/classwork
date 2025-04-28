// Author: Owen Dorweiler
// Class: Fundamentals of Computing
// Assignment: Lab 8
// Due: 17 November 2024

#include "crossfunc.h"

int main(int argc, char *argv[]) {
   //Initialize solution board
   char board[BOARD_SIZE][BOARD_SIZE];
   initBoard(board);

   // Initialize words list and numWords
   Wordstruct words[MAX_WORDS];
   int numWords;
   
   printf("\nCrossword Generator\n-------------------\n\n");

   if (argc == 1)
      // Get words from user and return number of words
      numWords = getUserWords(words);
   else if (argc == 2)
      // Read in the words from file and return number of words
      numWords = getFileWords(words, argv[1]);
   else if (argc == 3) {
      freopen(argv[2], "w", stdout);
      numWords = getFileWords(words, argv[1]);
   }
   else printf("Wrong number of arguments. Restart and try again.");
   
   // End program if no words or getFileWords returned error
   if (numWords == 0) abort();
   
   // Process and place the words
   processWords(words, numWords);
   placeWords(board, words, numWords);

   randomize(words, numWords);
   
   // Print words that could not be placed
   for (int a = 0; a < numWords; a++)
      if (!words[a].placed)
	 printf("\"%s\" could not be placed.\n", words[a].word);
  
   // Print boards and clues
   printBoards(board);
   printClues(words, numWords);

   // Close stdout if writing to file
   if (argc == 3) fclose(stdout);

   return 0;
}
