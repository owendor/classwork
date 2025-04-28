// Author: Owen Dorweiler
// Class: Fundamentals of Computing
// Assignment: Final Project
// Due: 15 December 2024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

#include "gfx2.h"

#define WIN_WIDTH 1200
#define WIN_HEIGHT 1000
#define BOARD_SIDE 770

typedef struct {
    char type[16];
    int length;
    int startX;
    int startY;
    char orientation;
    int hitsLeft;
    bool sunk;
} Ships;

void startMenu();
void initBoard(char [][14]);
void initShips(Ships []);
void placeShips(Ships [], int, char [][14]);
void printBoard();
void getCoordinates(int*, int*);
void drawAtPoint(int, int, int, int, int);
bool validPlacement(int, int, int, char, char [][14]);
void addShipToBoard(Ships, int, char [][14]);
void drawShip(Ships, int, int, int);
void drawShots(Ships [], char board[][14]);
int fire(int, Ships [], char [][14], int*);
void printHits(int, int);
bool shipSunk(Ships*);
bool allSunk(Ships []);
