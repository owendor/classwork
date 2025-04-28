// Author: Owen Dorweiler
// Class: Fundementals of Computing
// Assignment: Lab 9, Part 3
// Due: 26 November 2024

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
 
#include "gfx.h"

#define WIN_LENGTH 1200
#define WIN_HEIGHT 1000
#define HOOP_RADIUS 75
#define BALL_RADIUS 50
#define HOOP_SPEED 400 // pixels/sec
#define BALL_SPEED_MULT 300
#define BALL_NUM 5
#define REF_RATE 30 // frames/sec

void startScreen();
void nextFrame(int*, int, int*, int*, int*);
void drawShootingLine();
void drawHoop(int);
void drawBall(int, int);
bool scored(int, int, int);
void printStats(int, int);

int main() {
   gfx_open(WIN_LENGTH, WIN_HEIGHT, "Ball Toss");

   int ballsLeft = BALL_NUM;
   int ballXPos, ballYPos;
   int ballSpeed = 0;
   int hoopXPos = 75;
   int hoopSpeed = HOOP_SPEED;
   int score = 0;

   // Draw shooting line, hoop and ball and flush
   drawShootingLine();
   drawHoop(hoopXPos);
   gfx_flush();
   
   // Call the start screen
   startScreen();

   while (1) {
      usleep(1000000 / REF_RATE);
      
      // Iterate to the next frame, performing calculations
      nextFrame(&hoopXPos, ballXPos, &ballYPos, &hoopSpeed, &ballSpeed);
      printStats(score, ballsLeft);
      gfx_flush();
      
      // If scored, add to score
      if (scored(hoopXPos, ballXPos, ballYPos)) {
	 score += 1100 - (100 * ballSpeed / BALL_SPEED_MULT);
	 ballSpeed = 0;
	 ballYPos = -100;
      }
      
      // If no balls left, display score and exit
      if (ballsLeft == 0 && ballSpeed == 0) {
	 char finalScore[25];
	 sprintf(finalScore, "Final Score: %d", score);
	 gfx_text(WIN_LENGTH / 2, WIN_HEIGHT / 2, finalScore);
	 gfx_flush();
	 usleep(3000000);
	 break;
      }
      
      // Check for user input 1-9 and esc
      if (gfx_event_waiting()) {
	 int input = gfx_wait();
	 if (input == 27) break;
	 else if (input >= '1' && input <= '9' && ballSpeed == 0) {
	    ballXPos = gfx_xpos();
	    ballYPos = WIN_HEIGHT - BALL_RADIUS;
	    ballSpeed = (input - '0') * BALL_SPEED_MULT;
	    ballsLeft--;
	 }
      }
   }

   return 0;
}

void startScreen() {   
   // Print instructions on how to play
   gfx_color(0, 255, 0);
   gfx_text(WIN_LENGTH / 2 - 200, WIN_HEIGHT / 2 - 20, "Shoot balls by placing mouse horizontally, then hit keys 1-9. Higher number = faster ball.");
   gfx_text(WIN_LENGTH / 2 - 200, WIN_HEIGHT / 2, "If you score with a slower ball, you get more points.");
   gfx_text(WIN_LENGTH / 2 - 200, WIN_HEIGHT / 2 + 20, "Press [Enter] to begin.");

   gfx_flush();
   
   // Wait until user hits enter to continue
   int input;
   while (1) {
      input = gfx_wait();
      if (input == 13) break;
   }
}

void nextFrame(int* hoopXPos, int ballXPos, int* ballYPos, int* hoopSpeed, int* ballSpeed) {
   // Update hoop x position
   *hoopXPos = *hoopXPos + (*hoopSpeed / REF_RATE);   
   if (*hoopXPos + HOOP_RADIUS >= WIN_LENGTH || *hoopXPos - HOOP_RADIUS <= 0) *hoopSpeed = -(*hoopSpeed);
   
   // Update ball y position
   if (ballSpeed > 0) {
      *ballYPos = *ballYPos - (*ballSpeed / REF_RATE);
      if (*ballYPos + BALL_RADIUS < 0) *ballSpeed = 0;
   }
   
   // Clear screen and draw elements
   gfx_clear();
   drawShootingLine();
   drawHoop(*hoopXPos);
   if (ballSpeed > 0 && ballXPos != 0) drawBall(ballXPos, *ballYPos);
}

void drawShootingLine() {
   gfx_color(255, 255, 255);
   gfx_line(50, WIN_HEIGHT - BALL_RADIUS * 2, WIN_LENGTH - 50, WIN_HEIGHT - BALL_RADIUS * 2);
}

void drawHoop(int xPos) {
   gfx_color(255, 0, 0);
   gfx_circle(xPos, HOOP_RADIUS, HOOP_RADIUS);
}

void drawBall(int xPos, int yPos) {
   gfx_color(255, 165, 0);
   gfx_circle(xPos, yPos, BALL_RADIUS);
}

bool scored(int hoopXPos, int ballXPos, int ballYPos) {
    // Return true if ball is within hoop
    return abs(HOOP_RADIUS - ballYPos) <= HOOP_RADIUS - BALL_RADIUS &&
           abs(hoopXPos - ballXPos) <= HOOP_RADIUS - BALL_RADIUS;
}

void printStats(int score, int ballsLeft) {   
   char scoreString[20], ballString[20];
   sprintf(scoreString, "Score: %d", score);
   sprintf(ballString, "Balls left: %d", ballsLeft);
   
   // Print current score and balls remaining
   gfx_color(0, 255, 0);
   gfx_text(WIN_LENGTH - 100, WIN_HEIGHT - 300, scoreString);
   gfx_text(WIN_LENGTH - 100, WIN_HEIGHT - 250, ballString);
}
