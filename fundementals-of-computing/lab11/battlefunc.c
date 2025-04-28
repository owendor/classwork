// Author: Owen Dorweiler
// Class: Fundamentals of Computing
// Assignment: Final Project
// Due: 15 December 2024

#include "battlefunc.h"

void startMenu() {
    system("clear");  // Clear the screen
    printf("\n====== BATTLESHIP ------\n\n");
    printf("This is a two-player battleship game.\n");
    printf("When placing ships, don't let the other player see.\n");
    printf("Place this window side-by-side with the popup before continuing.\n\n");
    printf("Press [ENTER] to begin.\n");
    getchar();
}

void initBoard(char board[][14]) {
    for (int x = 0; x < 14; x++) {
        for (int y = 0; y < 14; y++) {
            board[x][y] = ' ';
        }
    }
}

void initShips(Ships ships[]) {
    strcpy(ships[0].type, "Aircraft Carrier");
    ships[0].length = 5;
    strcpy(ships[1].type, "Battleship");
    ships[1].length = 4;
    strcpy(ships[2].type, "Cruiser");
    ships[2].length = 3;
    strcpy(ships[3].type, "Submarine");
    ships[3].length = 3;
    strcpy(ships[4].type, "Destroyer");
    ships[4].length = 2;

    for (int i = 0; i < 5; i++) {
        ships[i].hitsLeft = ships[i].length;
        ships[i].sunk = false;
    }
}

void placeShips(Ships ships[], int player, char board[][14]) {
    printBoard();

    for (int i = 0; i < 5; i++) {
        system("clear");
        printf("Player %d: Place your ships.\n\n", player);
        printf("Ship: %s\nLength: %d\n\n", ships[i].type, ships[i].length);
        printf("Select a valid starting coordinate by clicking on the board.\n");

        // Get coordinates and save to ship struct
        int startX, startY;
        bool validVertical, validHorizontal;
        do {
            getCoordinates(&startX, &startY);
            validVertical = validPlacement(startX, startY, ships[i].length, 'v', board);
            validHorizontal = validPlacement(startX, startY, ships[i].length, 'h', board);
        } while (!validVertical && !validHorizontal); // Reject coordinate if no valid placement availabe

        // Tell user, draw point and save to struct if valid placement available
        printf("You selected coordinate %c%d.\n\n", 'A' + startY, startX + 1);
        drawAtPoint(startX, startY, 150, 150, 150);
        ships[i].startX = startX;
        ships[i].startY = startY;

        // If one position is not valid, place it as the other
        if (!validVertical) {
            ships[i].orientation = 'h';
            addShipToBoard(ships[i], i, board); // Add horizontally
            printf("The only valid placement is horizontal.\n");
        } else if (!validHorizontal) {
            ships[i].orientation = 'v';
            addShipToBoard(ships[i], i, board); // Add vertically
            printf("The only valid placement is vertical.\n");
        // If both are valid, let the user pick an orientation
        } else {
            char orientation;
            do {
                printf("Enter orientation [v/h]: ");
                scanf(" %c", &orientation);  // Note the space before %c
                orientation = tolower(orientation);
            } while (orientation != 'v' && orientation != 'h'); // Input validation
            ships[i].orientation = orientation;
            addShipToBoard(ships[i], i, board);
        }

        usleep(2000000); // Pause 2 secs
    }
}

void printBoard() {
    gfx_clear();
    int xRef, yRef;

    // Draw grid lines
    gfx_color(0, 255, 0);
    for (int a = 0; a < 15; a++) {
        xRef = WIN_WIDTH/2 - BOARD_SIDE/2;
        yRef = WIN_HEIGHT/2 - BOARD_SIDE/2;
        gfx_line(xRef + (BOARD_SIDE/14)*a, yRef, xRef + (BOARD_SIDE/14)*a, yRef + BOARD_SIDE);
        gfx_line(xRef, yRef + (BOARD_SIDE/14)*a, xRef + BOARD_SIDE, yRef + (BOARD_SIDE/14)*a);
    }

    gfx_color(255, 255, 255);

    // Draw row labels (0-14)
    for (int i = 0; i < 14; i++) {
        char label[2];
        sprintf(label, "%d", i + 1);
        gfx_text(xRef + (BOARD_SIDE/14)*i + 25, yRef + BOARD_SIDE + 30, label);
    }

    // Draw column labels (A-N)
    for (int i = 0; i < 14; i++) {
        char label[2];
        label[0] = 'A' + i;
        label[1] = '\0';
        gfx_text(xRef - 30, yRef + (BOARD_SIDE/14)*i + 30, label);
    }

    gfx_flush();
}

// Function to get the coordinates of the board
void getCoordinates(int *startX, int *startY) {
    int xRef = WIN_WIDTH/2 - BOARD_SIDE/2;
    int yRef = WIN_HEIGHT/2 - BOARD_SIDE/2;

    // Get a valid click within the borders of the grid
    int inpt, xPos, yPos;
    do {
        inpt = gfx_wait();

        if (inpt == 1) {
            xPos = gfx_xpos();
            yPos = gfx_ypos();
        }
    } while (xPos < xRef || xPos > xRef + BOARD_SIDE || yPos < yRef || yPos > yRef + BOARD_SIDE);

    // Convert from screen coordinates to board coordinates
    *startX = (xPos - xRef) / (BOARD_SIDE/14);
    *startY = (yPos - yRef) / (BOARD_SIDE/14);
}

void drawAtPoint(int xCoor, int yCoor, int red, int green, int blue) {
    gfx_color(red, green, blue);

    // Convert grid coordintes to screen coordinates
    int xRef = WIN_WIDTH/2 - BOARD_SIDE/2;
    int yRef = WIN_HEIGHT/2 - BOARD_SIDE/2;
    int x = xRef + (BOARD_SIDE/14)*xCoor + BOARD_SIDE/28;
    int y = yRef + (BOARD_SIDE/14)*yCoor + BOARD_SIDE/28;
    int radius = (BOARD_SIDE / 28) - 10;

    gfx_fill_circle(x, y, radius); // Draw a filed circle
    gfx_flush();
}

bool validPlacement(int startX, int startY, int length, char orientation, char board[][14]) {
    if (orientation == 'v') {
        if (startY + length - 1 > 13) return false; // Check out of bounds
        for (int y = startY; y < startY + length; y++) {
            if (board[startX][y] != ' ') return false; // Check for ships
        }
    } else {
        if (startX + length - 1 > 13) return false; // Check out of bounds
        for (int x = startX; x < startX + length; x++) {
            if (board[x][startY] != ' ') return false; // Check for ships
        }
    }

    return true;
}

void addShipToBoard(Ships ship, int index, char board[][14]) {
    if (ship.orientation == 'v') {
        for (int y = ship.startY; y < ship.startY + ship.length; y++) {
            board[ship.startX][y] = '0' + index;
        }
    } else {
        for (int x = ship.startX; x < ship.startX + ship.length; x++) {
            board[x][ship.startY] = '0' + index;
        }
    }

    drawShip(ship, 150, 150, 150);
}

void drawShip(Ships ship, int red, int green, int blue) {
    int xRef = WIN_WIDTH/2 - BOARD_SIDE/2;
    int yRef = WIN_HEIGHT/2 - BOARD_SIDE/2;

    // Draw the end coordinates
    drawAtPoint(ship.startX, ship.startY, red, green, blue);
    if (ship.orientation == 'v') {
        drawAtPoint(ship.startX, ship.startY + ship.length - 1, red, green, blue);
    } else {
        drawAtPoint(ship.startX + ship.length - 1, ship.startY, red, green, blue);
    }

    int x = (xRef + (BOARD_SIDE/14)*ship.startX + BOARD_SIDE/28);
    int y = (yRef + (BOARD_SIDE/14)*ship.startY + BOARD_SIDE/28);

    // Draw a rectangle between them
    gfx_color(red, green, blue);
    if (ship.orientation == 'v') {
        int height = (BOARD_SIDE/14)*(ship.length - 1);
        gfx_fill_rectangle(x - (BOARD_SIDE/28) + 6, y, (BOARD_SIDE/14) - 12, height);
    } else {
        int width = (BOARD_SIDE/14)*(ship.length - 1);
        gfx_fill_rectangle(x, y - (BOARD_SIDE/28) + 6, width, (BOARD_SIDE/14) - 12);
    }
    gfx_flush();
}

void drawShots(Ships ships[], char board[][14]) {
    for (int y = 0; y < 14; y++) {
        for (int x = 0; x < 14; x++) {
            if (board[x][y] == 'M')
                drawAtPoint(x, y, 255, 255, 0); // Draw yellow if miss
            else if (board[x][y] == 'H')
                drawAtPoint(x, y, 255, 0, 0); // Draw red if hit
        }
    }

    // Draw sunk ships
    for (int i = 0; i < 5; i++) {
        if (ships[i].sunk)
            drawShip(ships[i], 255, 0, 0);
    }
}

int fire(int player, Ships ships[], char board[][14], int *hits) {
    int xCoor, yCoor;
    char value;

    printf("Player %d: Fire when ready.\n\n", player);
    printf("Select a square on the board to fire.\n\n");

    // Get a shot from the user
    do {
        getCoordinates(&xCoor, &yCoor);
        value = board[xCoor][yCoor];
    } while (value == 'H' || value == 'M'); // Reject if already tried previously

    // If it's a hit, tell the user, put on board, increment hits, and return the value to runGame()
    if (value >= '0' && value <= '4') {
        drawAtPoint(xCoor, yCoor, 255, 0, 0);
        gfx_flush();
        (*hits)++;
        printf("HIT CONFIRMED at %c%d.\n", 'A' + yCoor, xCoor + 1);
        board[xCoor][yCoor] = 'H';
        if (shipSunk(&ships[value - '0'])) {
            drawShip(ships[value - '0'], 255, 0, 0);
            printf("%s SUNK.\n", ships[value - '0'].type); // Print message saying ship has been hit
            return true; // Id ship is sunk, return true;
        }
    // Otherwise, record it as a miss
    } else {
        drawAtPoint(xCoor, yCoor, 255, 255, 0);
        gfx_flush();
        printf("MISS at %c%d.\n", 'A' + yCoor, xCoor + 1);
        board[xCoor][yCoor] = 'M';
    }

    return false; // If ship is not sunk, return false;
}

void printHits(int p1hits, int p2hits) {
    printf("Confirmed Hits:\n");

    // Print Player 1 hits
    printf("Player 1: [");
    for (int i = 0; i < p1hits; i++) {
        printf("#");
    }
    for (int i = 0; i < 17 - p1hits; i++) {
        printf(" ");
    }
    printf("]\n");

    // Print Player 2 hits
    printf("Player 2: [");
    for (int i = 0; i < p2hits; i++) {
        printf("#");
    }
    for (int i = 0; i < 17 - p2hits; i++) {
        printf(" ");
    }
    printf("]\n\n");
}

bool shipSunk(Ships *ship) {
    ship->hitsLeft--; // Decrement the life counter
    if (ship->hitsLeft == 0) {
        ship->sunk = true;
        return true; // If ship is sunk, return true
    }

    return false; // Otherwise return false
}

bool allSunk(Ships ships[]) {
    // If every ship is sunk, return true
    if (ships[0].sunk && ships[1].sunk && ships[2].sunk && ships[3].sunk && ships[4].sunk) return true;

    return false; // Otherwise return false
}
