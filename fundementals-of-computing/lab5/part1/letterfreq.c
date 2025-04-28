// Author: Owen Dorweiler
// Class: Fundementals of Computing
// Assignment: Lab 5, Part 1
// Due: 6 October 2024

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHA_SIZE 26

void countLetters(FILE *file, int letterCount[], int *charTotal, int *letterTotal);
void printResult(char filename[], int letterCount[], int charTotal, int letterTotal);
double findPercent(int occurances, int letterTotal);

int main() {
   char filename[30];
   
   // Read in file name from user
   printf("Enter file name: ");
   scanf("%30s", filename);
   
   // Check if file can be opened; if not, display error
   FILE *file = fopen(filename, "r");
   if (!file) {
      printf("Error opening file. Restart program to try again.\n");
      return 1;
   }

   int letterCount[ALPHA_SIZE] = {0};
   int charTotal = 0, letterTotal = 0;
   
   // Call function to count letters
   countLetters(file, letterCount, &charTotal, &letterTotal);
   fclose(file);

   // Call function to print results
   printResult(filename, letterCount, charTotal, letterTotal);

   return 0;
}

void countLetters(FILE *file, int letterCount[], int *charTotal, int *letterTotal) {
   char target;
   while ((target = fgetc(file)) != EOF) {
      (*charTotal)++;
      if (isalpha(target)) {
	 (*letterTotal)++;
	 target = tolower(target);
	 letterCount[target - 'a']++;
      }
   }
}

void printResult(char filename[], int letterCount[], int charTotal, int letterTotal) {
   printf("\nStatistics for %s:\n", filename);
   printf("  %d characters\n", charTotal);
   printf("  %d letters\n\n", letterTotal);
   
   printf("Letter counts:");
   for (int i = 0; i < ALPHA_SIZE; i++) {
      if (i % 6 == 0)
	 printf("\n  ");
      printf("%c:\t%d\t", 'a' + i, letterCount[i]);
   }

   printf("\n\n");

   printf("Letter percents:");
   for (int i = 0; i < ALPHA_SIZE; i++) {
      if (i % 6 == 0)
	 printf("\n  ");
      printf("%c:\t%.1f%\t", 'a' + i, findPercent(letterCount[i], letterTotal));
   }

   printf("\n\n");
}


double findPercent(int occurances, int letterTotal) {
   double percent;
   percent = 100 * (double)occurances / letterTotal;
   return percent;
}
