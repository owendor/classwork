 // Author: Owen Dorweiler
 // Class: Fundementals of Computing
 // Assignment: Lab 9, Part 2
 // Due: 26 November 2024

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "gfx.h"

#define WIN_LENGTH 1200
#define WIN_HEIGHT 1000
#define BALL_SIZE 200
#define REF_RATE 30 // frames/sec
#define MAX_VEL 200 // pixels/sec
#define MIN_VEL 50

int randVel();

int main() {
   srand(time(NULL));

   int keyPress;
   int xVel = randVel();
   int yVel = randVel();
   int xPos = WIN_LENGTH / 2;
   int yPos = WIN_HEIGHT / 2;
   
   // Open new window, set color and draw first frame
   gfx_open(WIN_LENGTH, WIN_HEIGHT, "Bounce");
   gfx_color(255, 255, 255);
   gfx_circle(xPos, yPos, BALL_SIZE / 2);
   gfx_flush();

   while (1) {     
      usleep(100000 / REF_RATE);
      xPos = xPos + (xVel / REF_RATE);
      yPos = yPos + (yVel / REF_RATE);
      
      // Change the direction of the velocity vectors if ball hits wall
      if (abs(xPos) - BALL_SIZE / 2 < 0 || abs(xPos) + BALL_SIZE / 2 > WIN_LENGTH) xVel = -xVel;
      if (abs(yPos) - BALL_SIZE / 2 < 0 || abs(yPos) + BALL_SIZE / 2 > WIN_HEIGHT) yVel = -yVel;
      
      // Draw the next frame
      gfx_clear();
      gfx_circle(xPos, yPos, BALL_SIZE / 2);
      gfx_flush();

      // Check if user has pressed key
      if (gfx_event_waiting()) {
	 keyPress = gfx_wait();
	 // Update position and generate random velocity if left click
	 if (keyPress == 1) {
	    xPos = gfx_xpos();
	    yPos = gfx_ypos();
	    xVel = randVel();
	    yVel = randVel();
	 }
	 // If user hit escape, exit
	 else if (keyPress == 27) break;
      }
   }

   return 0;
}

int randVel() {
   srand(time(NULL) + rand());
   int randNum = 1;
   // Generate a random number in range, if zero repeat until nonzero
   do {
      randNum = -MAX_VEL + rand() % (2 * MAX_VEL + 1);
   } while (abs(randNum) < MIN_VEL);
   return randNum;
}
