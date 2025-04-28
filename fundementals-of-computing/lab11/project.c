// Author: Owen Dorweiler
// Class: Fundamentals of Computing
// Assignment: Final Project
// Due: 15 December 2024

#include "battlefunc.h"

int main() {
    int selection;

    // Create gameboard and ship structs
    char board1[14][14], board2[14][14];
    Ships ships1[5];
    Ships ships2[5];

    gfx_open(WIN_WIDTH, WIN_HEIGHT, "Battleship"); // Open the window
    startMenu();

    // Initialize gameboards and ships
    initBoard(board1);
    initBoard(board2);
    initShips(ships1);
    initShips(ships2);

    // Have both players place their ships
    placeShips(ships1, 1, board1);
    placeShips(ships2, 2, board2);

    int player = 1, p1hits = 0, p2hits = 0;
    bool win = false; // Set up a win variable

    // Start the game
    do {
        system("clear");
        gfx_clear();
        printBoard();

        printHits(p1hits, p2hits);

        if (player == 1) {
            drawShots(ships2, board2); // Draw the previous shots and sunk ships on the screen
            if (fire(player, ships2, board2, &p1hits)) { // If fire returns true, ship was sunk
                if (allSunk(ships2)) win = true; // If all ships are sunk, set win to true
            }
        } else {
            drawShots(ships1, board1);
            if (fire(player, ships1, board1, &p2hits)) {
                if (allSunk(ships1)) win = true;
            }
        }

        usleep(2000000); // Pause 2 secs

        // If win, display message and end the game
        if (win) {
            system("clear");
            printf("Player %d wins. Congratulations, Commander.\n\n", player);
        }
        // If no win, switch whose turn it is
        else if (player == 1) player = 2;
        else player = 1;
    } while (!win);

    return 0;
}
