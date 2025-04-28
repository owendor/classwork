// Author: Owen Dorweiler
// Class: Fundamentals of Computing
// Assignment: Lab 4, Part 3
// Due: 1 October 2024

#include <stdio.h>

int printMenu();;
void statDisplay(int wins[], int losses[]);
void winPercent(int size, int wins[], int losses[]);
void graphWins(int wins[]);

int main() {
   int size, selection;
   
   int wins[] = 
   { 6, 8, 6, 8, 5, 5, 6, 6, 8, 7, 4, 6,
   7, 7, 6, 7, 8, 6, 3, 9, 9, 10, 8, 9,
   10, 7, 9, 7, 5, 9, 10, 6, 6, 3, 6, 7, 
   6, 6, 8, 7, 7, 8, 7, 9, 8, 7, 8, 9,
   9, 10, 4, 7, 7, 9, 9, 8, 2, 7, 6, 5, 
   2, 5, 5, 2, 9, 7, 9, 8, 7, 8, 10, 8, 
   8, 11, 10, 8, 9, 11, 9, 7, 9, 5, 6, 7, 
   7, 5, 5, 8, 12, 12, 9, 10, 10, 11, 6, 9, 
   8, 7, 9, 5, 9, 5, 10, 5, 6, 9, 10, 3, 
   7, 6, 8, 8, 12, 9, 8, 10, 4, 10, 12, 11, 
   10, 11, 9, 10 };

   int losses[] = 
   { 3, 1, 2, 0, 3, 4, 1, 0, 1, 0, 1, 0,
   0, 0, 2, 1, 1, 1, 1, 0, 0, 1, 1, 1,
   0, 2, 1, 1, 4, 0, 0, 2, 2, 5, 3, 1,
   2, 2, 1, 2, 2, 0, 2, 1, 2, 2, 0, 0,
   0, 0, 4, 2, 2, 0, 1, 2, 8, 3, 4, 5,
   8, 5, 5, 7, 1, 2, 0, 2, 2, 2, 1, 2,
   3, 0, 2, 3, 3, 1, 3, 4, 2, 6, 4, 5,
   5, 6, 6, 4, 0, 1, 3, 3, 1, 1, 5, 3,
   3, 6, 3, 7, 3, 6, 3, 7, 6, 3, 3, 9,
   6, 6, 5, 5, 1, 4, 5, 3, 8, 3, 1, 2,
   2, 2, 4, 3 };

   size = sizeof(wins) / sizeof(wins[0]);
   
   // Print menu and get selection by calling function
   selection = printMenu(); 

   // Call functions based on selection  
   while (selection != 0) {
      switch (selection) {
      	 case 1:
	    statDisplay(wins, losses);
            break;
	 case 2:
	    winPercent(size, wins, losses);
	    break;
	 case 3:
	    graphWins(wins);
	    break;
	 default:
	    printf("Invalid input. Try again.\n\n");
      }

      selection = printMenu();
   }

   return 0;
}

int printMenu() {
   int selection;
   
   // Print options and get input
   printf("1) Print stats for a specific year\n");
   printf("2) Display years with at least n% wins\n");
   printf("3) Graph wins for range of years\n");
   printf("0) Exit\n");
   printf("Make selection: ");
   scanf("%d", &selection);

   printf("\n");

   return selection;
}

void statDisplay(int wins[], int losses[]) {
   int year, index;
   float winPer, lossPer;
   printf("Enter year (1900-2023): ");
   scanf("%d", &year);
   
   index = year - 1900;

   // If no losses, wins = 100%, losses = 0%; otherwise, calculate percentages
   if (losses[index] == 0) {
      winPer = 100.00;
      lossPer = 0.00;
   }
   else {
      winPer = (float)wins[index] / (wins[index] + losses[index]) * 100;
      lossPer = 100 - winPer;
   }
   
   // Print wins and losses with percentages
   printf("Wins: %d (%.2f%)\n", wins[index], winPer);
   printf("Losses: %d (%.2f%)\n\n", losses[index], lossPer);
}

void winPercent(int size, int wins[], int losses[]) {
   float percent, tempPer;
   printf("Enter minimum win %: ");
   scanf("%f", &percent);

   // Calculate win percentage for each year, display if over threshold
   for (int i = 0; i < size; i++) {
      tempPer = (float)wins[i] / (wins[i] + losses[i]) * 100;
      if (tempPer >= percent)
	 printf("%d ", 1900 + i);
   }

   printf("\n\n");
}

void graphWins(int wins[]) {
   int start, end;
   printf("Enter start year: ");
   scanf("%d", &start);
   printf("Enter end year: ");
   scanf("%d", &end);
   
   // COnvert years to indexes
   start = start - 1900;
   end = end - 1900;
   
   // Graph wins in user-specified range
   for (int i = start; i <= end; i++) {
      printf("%d ", 1900 + i);
      for (int j = 0; j < wins[i]; j++) {
	 printf("#");
      }
      printf("\n");
   }

   printf("\n");
}
