// Author: Owen Dorweiler
// Class: Fundamentals of Computing
// Assignment: Lab 6, Part 1
// Due: 20 October 2024

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_STATES 100
#define MAX_LENGTH 50

typedef struct {
  char abbr[3];
  char name[MAX_LENGTH];
  char capital[MAX_LENGTH];
  int year;
} States;

int readStates(States states[], char filename[]);
int printMenu();
void printData(States states[], int stateCount);
void abbrFind(States states[], int stateCount);
void foundedRange(States states[], int stateCount);
void longerThan(States states[], int stateCount);

int main() {
  char filename[31];
  States states[MAX_STATES];
  int stateCount;
  int choice;
  
  printf("Enter file name: ");
  scanf("%99s", filename);
  
  // Read csv file into struct by calling readStates(), return num of states
  stateCount = readStates(states, filename);
  
  choice = printMenu();
  
  // Loop until user exits, call functions to perform selections
  while (choice != 5) {
    printf("\n");
    switch (choice) {
      case 1:
        printData(states, stateCount);
        break;
      case 2:
        abbrFind(states, stateCount);
        break;
      case 3:
        foundedRange(states, stateCount);
        break;
      case 4:
        longerThan(states, stateCount);
        break;
      default:
        printf("Invalid selection. Please try again.\n");
    }
    
    choice = printMenu();
  }
  
  return 0;
}

int readStates(States states[], char filename[]) {
  // Read file, if no file present output error message
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("\nError: File '%s' does not exist. Please exit the program and try again.\n", filename);
    return 1;
  }
  
  // Read csv file into struct
  int state = 0;
  while (state < MAX_STATES && fscanf(file, "%2[^,],%49[^,],%49[^,],%d\n", states[state].abbr, states[state].name, states[state].capital, &states[state].year) == 4) {
    state++;
  }
  
  return state;
}

int printMenu() {
  int choice;
  
  // Print choices
  printf("\n1) List all data\n");
  printf("2) Find state info from abbreviation\n");
  printf("3) List states founded within year range\n");
  printf("4) List state names at least _ letters long\n");
  printf("5) Exit\n\n");
  
  printf("Enter selection: ");
  scanf("%d", &choice);
  
  return choice;
}

void printData(States states[], int stateCount) {
  printf("Abbr. | State              | Capital            | Year \n");
  printf("------+--------------------+--------------------+------\n");
  for (int i = 0; i < stateCount; i++) {
    printf("%-5s | %-18s | %-18s | %-4d\n", states[i].abbr, states[i].name, states[i].capital, states[i].year);
  }
}

void abbrFind(States states[], int stateCount) {
  char abbreviation[3];
  
  printf(">> Enter abbreviation (uppercase): ");
  scanf("%3s", &abbreviation);
  printf("\n");
  
  // Loop through struct and output state info if if there is a match
  bool stateFound = false;
  int state = 0;
  while (!stateFound && state < stateCount) {
    if (strcmp(states[state].abbr, abbreviation) == 0) {
      printf(">> %s is the abbreviation for %s, whose capital is %s and was founded in %d.\n", states[state].abbr, states[state].name, states[state].capital, states[state].year);
      stateFound = true;
    }
    state++;
  }
  
  // Print error message if no match
  if (!stateFound)
    printf(">> No state has the abbreviation '%s'.", abbreviation);    
}

void foundedRange(States states[], int stateCount) {
  int startYear, endYear;
  
  printf(">> Enter start year: ");
  scanf("%d", &startYear);
  printf(">> Enter end year: ");
  scanf("%d", &endYear);
  printf("\n");
  
  // Loop through struct, output all states within range
  bool stateFound = false;
  for (int i = 0; i < stateCount; i++) {
    if (states[i].year >= startYear && states[i].year <= endYear) {
      printf(">> %s (%d)\n", states[i].name, states[i].year);
      stateFound = true;
    }
  }
  
  if (!stateFound)
    printf(">> No state was founded between %d and %d.\n", startYear, endYear);
}

void longerThan(States states[], int stateCount) {
  int maxLength;
  
  printf(">> Enter name length: ");
  scanf("%d", &maxLength);
  printf("\n");
  
  // Loop through struct, output all states at least maxLength letters long
  bool stateFound = false;
  for (int i = 0; i < stateCount; i++) {
    if (strlen(states[i].name) >= maxLength) {
    printf(">> %s\n", states[i].name);
    stateFound = true;
    }
  }
  
  if (!stateFound)
    printf(">> No state name is at least %d letters long.", maxLength); 
}

