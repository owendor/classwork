// Author: Owen Dorweiler
// Class: Fundementals of Computing
// Assignment: Lab 7
// Due: 5 November 2024

#include "lifefunc.h"

int main(int argc, char *argv[]) {

   char board[SIZE][SIZE];
   initBoard(board);
   
   if (argc == 1)
      // Enter interactive mode
      interactiveMode(board);
   else if (argc == 2) {
      batchMode(board, argv[1]);
   }
   else printf("Too many arguments. Please try again.");

   return 0;
}
