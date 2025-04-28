// Author: Owen Dorweiler
// Class: Fundementals of Computing
// Assignment: Lab 7
// Due: 5 November 2024

#include "lifefunc.h"

void initBoard(char board[][SIZE]) {
   for (int y = 0; y < SIZE; y++) {
      for (int x = 0; x < SIZE; x++) {
         board[x][y] = ' ';
      }
   }
}

void interactiveMode(char board[][SIZE]) {
   char action;
   int xCoor, yCoor;

   // Print blank board and ask for first command
   printBoard(board);
   printf("COMMAND: ");
   scanf(" %c", &action);

   while (action != 'q') {
      switch (action) {
         case 'a':
            // Read coordinates, add point, print board
            scanf(" %d %d", &xCoor, &yCoor);
	    board[xCoor][yCoor] = 'X';
            printBoard(board);
            break;
         case 'r':
            // Read coordinates, remove point, print board
            scanf(" %d %d", &xCoor, &yCoor);
	    board[xCoor][yCoor] = ' ';
            printBoard(board);
            break;
         case 'n':
            // Iterate once and print board
            iterateBoard(board);
            printBoard(board);
            break;
         case 'p':
            // Run game until user interrupts
            runGame(board);
            break;
         default:
            // Print error message
            printf("Unknown command. Please try again.");
            break;
      }
      
      printf("COMMAND: ");
      scanf(" %c", &action);  
   }
}

void batchMode(char board[][SIZE], char *filename) {
   int xCoor, yCoor;
   
   FILE *file = fopen(filename, "r");
   if (file == NULL) {
      printf("Error opening file. Please try again.\n");
      return;
   }
   
   char command[10];
   while (1) {
      fgets(command, 10, file);
      
      if (command[0] == 'a') {
	 sscanf(command, "a %d %d", &xCoor, &yCoor);
	 board[xCoor][yCoor] = 'X';
      }
      else if (command[0] == 'p')
	 runGame(board);
      else {
	 printf("No 'run' command in file. Exiting...\n");
	 break;
      }
   }
}

void printBoard(char board[][SIZE]) {
   // Clear the screen
   system("clear");
   
   // Print top border
   for (int x = 0; x < SIZE + 2; x++) {
      printf("-");
   }
   
   // Print board data
   for (int y = 0; y < SIZE; y++) {
      printf("\n|");
      for (int x = 0; x < SIZE; x++) {
	 printf("%c", board[x][y]);
      }
      printf("|");
   }
   printf("\n");

   // Print bottom border
   for (int x = 0; x < SIZE + 2; x++) {
      printf("-");
   }
   printf("\n");
}

void iterateBoard(char board[][SIZE]) {
   int cpyBrd[SIZE][SIZE];
   int neighborSum;

   // Copy the contents of board to copyBrd
   for (int y = 0; y < SIZE; y++) {
      for (int x = 0; x < SIZE; x++) {
         cpyBrd[x][y] = board[x][y];
      }
   }
   
   
   for (int y = 0; y < SIZE; y++) {
      for (int x = 0; x < SIZE; x++) {
         neighborSum = 0;
	 
	 // Sum 9 cells (including test cell)
	 for (int j = y-1; j < y+2; j++) {
	    for (int i = x-1; i < x+2; i++) {
	       if (i >= 0 && j >= 0)
		  if (cpyBrd[i][j] == 'X')
		     neighborSum++;
	    }
	 }
         
	 // Subtract test cell from neighborSum
	 if (board[x][y] == 'X')
	    neighborSum--;
         
	 // If the cell is dead and has 3 neighbors, make it alive
	 if (board[x][y] == ' ' && neighborSum == 3)
	    board[x][y] = 'X';
	 // If the cell is alive and does not have 2 or 3 neighbors, kill it
	 else if (board[x][y] == 'X' && (neighborSum < 2 || neighborSum > 3))
	    board[x][y] = ' ';
      }
   }
}

void runGame(char board[][SIZE]) {
   while (1) {
      iterateBoard(board);
      printBoard(board);
      usleep(100000);
   }
}
