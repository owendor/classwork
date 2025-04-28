// Author: Owen Dorweiler
// Class: Fundementals of Computing
// Assignment: Lab 7
// Due: 5 November 2024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 40

void initBoard(char board[][SIZE]);
void interactiveMode(char board[][SIZE]);
void batchMode(char board[][SIZE], char *filename);
void printBoard(char board[][SIZE]);
void iterateBoard(char board[][SIZE]);
void runGame(char board[][SIZE]);
