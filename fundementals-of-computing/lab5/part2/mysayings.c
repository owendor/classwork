// Author: Owen Dorweiler
// Class: Fundementals of Computing
// Assignment: Lab 5, Part 2
// Due: 13 October 2024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 50
#define MAX_LENGTH 256

int printMenu();
void rmNewLine(char *str);
void printSayings(char sayings[][MAX_LENGTH], int);
void addSaying(char sayings[][MAX_LENGTH], int*);
void contains(char sayings[][MAX_LENGTH], int);
void saveToFile(char sayings[][MAX_LENGTH], int);

int main() {
   char filename[31];
   char sayings[MAX_LINES][MAX_LENGTH];
   int lineCount = 0;
   int choice;
   
   // Get file name from user
   printf("Enter sayings file name: ");
   scanf("%30s", filename);
   
   // Open file, display error if no match
   FILE *file = fopen(filename, "r");
   if (file == NULL) {
      printf("Error opening file. Restart program and try again.\n");
      return -1;
   }
   
   // Transfer file contents to array
   while (lineCount < MAX_LINES && fgets(sayings[lineCount], MAX_LENGTH, file) != NULL) {
      // Remove new line character
      rmNewLine(sayings[lineCount]); 
      lineCount++;
   }
   
   fclose(file);

   // Print menu and get choice from user
   choice = printMenu();

   // Call functions based on input; give error if not 1-5
   while (choice != 5) {
      switch (choice) {
	 case 1:
	    printSayings(sayings, lineCount);
	    break;
	 case 2:
	    addSaying(sayings, &lineCount);
	    break;
	 case 3:
	    contains(sayings, lineCount);
	    break;
	 case 4:
	    saveToFile(sayings, lineCount);
	    break;
	 default:
	    printf("Invalid selection. Please try again.\n");
      }

      choice = printMenu();
   }
   
   return 0;
}

// Removes new line character from any string input
void rmNewLine(char *str) {
   int length = strlen(str);
   if (length > 0 && str[length - 1] == '\n')
      str[length - 1] = '\0';
}

int printMenu() {
   int choice;
   
   printf("\n1) Display all sayings\n");
   printf("2) Enter a new saying\n");
   printf("3) List sayings containing search term\n");
   printf("4) Save sayings to new text file\n");
   printf("5) Quit the program\n\n");
   printf("Make a selection: ");
   scanf("%d", &choice);
   
   printf("\n");
   return choice;
}

void printSayings(char sayings[][MAX_LENGTH], int lineCount) {
   for (int i = 0; i < lineCount; i++) {
      printf("%s\n", sayings[i]);
   }
}

void addSaying(char sayings[][MAX_LENGTH], int *lineCount) {
   if (*lineCount < 30) {
      printf("Enter saying: ");

      // Remove new line character from buffer
      getchar();
      fgets(sayings[*lineCount], MAX_LENGTH, stdin);

      // Remove new line character
      rmNewLine(sayings[*lineCount]);

      printf("Saying added successfully.\n");

      (*lineCount)++;
   }
   else printf("Maximum number of sayings reached.\n");
}

void contains(char sayings[][MAX_LENGTH], int lineCount) {
   char substring[MAX_LENGTH];
   
   printf("Enter search term (lowercase): ");
   getchar();

   fgets(substring, MAX_LENGTH, stdin);
   rmNewLine(substring);
   
   // Loop, converting strings to lowercase; output original string if match
   for (int i = 0; i < lineCount; i++) {
      char lowerString[MAX_LENGTH] = {};
      for (int j = 0; j < strlen(sayings[i]); j++)
	 lowerString[j] = tolower(sayings[i][j]);
      
      if (strstr(lowerString, substring))
	 printf("%s\n", sayings[i]);
   }
}

void saveToFile(char sayings[][MAX_LENGTH], int lineCount) {
   char filename[31];
   
   printf("Enter a file name: ");
   scanf("%30s", filename);

   FILE *file = fopen(filename, "w");
   
   // Write to file line by line
   for (int i = 0; i < lineCount; i++)
      fprintf(file, "%s\n", sayings[i]);
   
   fclose(file);

   printf("Saved to %s successfully.\n", filename);
}
