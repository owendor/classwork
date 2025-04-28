// Author: Owen Dorweiler
// Class: Fundamentals of Computing
// Assignment: Lab 8
// Due: 17 November 2024

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define BOARD_SIZE 15
#define MAX_WORDS 20
#define MAX_LENGTH 15

typedef struct {
   char word[MAX_LENGTH];
   char scrambled[MAX_LENGTH];
   char direc[7];
   int x;
   int y;
   bool placed;
} Wordstruct;

void initBoard(char [][BOARD_SIZE]);
int getUserWords(Wordstruct words[]);
int getFileWords(Wordstruct words[], char []);
bool validWord(char []);
void processWords(Wordstruct words[], int);

void placeWords(char [][BOARD_SIZE], Wordstruct words[], int);
bool search(char [][BOARD_SIZE], Wordstruct *word);
bool attemptPlace (char [][BOARD_SIZE], Wordstruct *word, int, int, int);
bool validPlace(char [][BOARD_SIZE], Wordstruct word);
void updateBoard(char [][BOARD_SIZE], Wordstruct word);

void printBoards(char [][BOARD_SIZE]);
void printBorder();
void randomize(Wordstruct words[], int);
void printClues(Wordstruct words[], int);
