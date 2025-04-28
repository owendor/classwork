// Author: Owen Dorweiler
// Class: Fundamentals of Computing
// Assignment: Lab 10
// Due: 8 December 2024

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "gfx.h"

void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void shrinkingSquares(int x, int y, int sideRadius);
void spiralSquares(int centerX, int centerY, int radius, float angle, int sideRadius);
void square(int x, int y, int sideRadius);
void lace(int x, int y, int radius);
void snowflake(int x, int y, int radius, float angle);
void tree(int x, int y, int length, float angle, float branchAngle);
void fern(int x, int y, int length, float angle, float branchAngle);
void spiralSpirals(int x, int y, int radius, double angle);

int main() {
  int width = 1000, height = 1000, mrgn = 20;
  gfx_open(width, height, "Fractals");

  char inpt;
  
  bool loop = true;
  while(loop) {
    inpt = gfx_wait();
    gfx_clear();

    switch (inpt) {
      case '1':
	sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
	break;
      case '2':
        shrinkingSquares(height/2, height/2, height/4);
        break;
      case '3':
        spiralSquares(width/2, height/2, width/2, 0, height/10);
        break;
      case '4':
        lace(width/2, height/2, height*1/3);
        break;
      case '5':
        snowflake(width/2, height/2, height/3, M_PI/2);
        break;
      case '6':
        tree(width/2, height-20, height/3.2, -M_PI/2, M_PI/6);
        break;
      case '7':
        fern(width/2, height-20, height/1.5, -M_PI/2, M_PI/4);
        break;
      case '8':
        spiralSpirals(width/2, height/2, width, 0);
        break;
      case 'q':
        loop = false;
	break;
      default:
        break;
    }
  }
}

void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3) {
  // Base case 
  if (abs(x2-x1) < 5) return;

  // Draw a triangle
  drawTriangle(x1, y1, x2, y2, x3, y3);

  // Recursive calls
  sierpinski(x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2);
  sierpinski((x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2);
  sierpinski((x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3);
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
  gfx_line(x1, y1, x2, y2);
  gfx_line(x2, y2, x3, y3);
  gfx_line(x3, y3, x1, y1);
}

void shrinkingSquares(int x, int y, int sideRadius) {
  // Base case
  if (sideRadius < 2) return;
  
  // Draw a square
  square(x, y, sideRadius);
  
  // Recursive calls
  shrinkingSquares(x-sideRadius, y-sideRadius, sideRadius/2.1);
  shrinkingSquares(x+sideRadius, y-sideRadius, sideRadius/2.1);
  shrinkingSquares(x+sideRadius, y+sideRadius, sideRadius/2.1);
  shrinkingSquares(x-sideRadius, y+sideRadius, sideRadius/2.1);
}

void spiralSquares(int centerX, int centerY, int radius, float angle, int sideRadius) {
  // Base case
  if (sideRadius < 2) return;
  
  // Draw a square
  square(centerX + radius*cos(angle), centerY + radius*sin(angle), sideRadius);
  
  // Recursive call
  spiralSquares(centerX, centerY, radius*0.9, angle+M_PI*0.2, sideRadius*0.9);
}

void square(int x, int y, int sideRadius) {
  gfx_line(x-sideRadius, y-sideRadius, x+sideRadius, y-sideRadius);
  gfx_line(x+sideRadius, y-sideRadius, x+sideRadius, y+sideRadius);
  gfx_line(x+sideRadius, y+sideRadius, x-sideRadius, y+sideRadius);
  gfx_line(x-sideRadius, y+sideRadius, x-sideRadius, y-sideRadius);
}

void lace(int x, int y, int radius) {
  // Base case
  if (radius < 2) return;
  
  // Draw a circle
  gfx_circle(x, y, radius);
  
  // Recursive calls
  for (float i = 0; i < 2; i += 1.0f/3.0f) {
    lace(x + radius*cos(M_PI*i), y + radius*sin(M_PI*i), radius/3);
  }
}

void snowflake(int x, int y, int radius, float angle) {
  // Base case
  if (radius < 2) return;
 
  // Recursive calls with drawing
  int numLines = 5;
  float angleStep = 2 * M_PI / numLines;
  for (int i = 0; i < numLines; i++) {
    float newAngle = angle + i * angleStep;
    int newX = x + radius * cos(newAngle);
    int newY = y + radius * sin(newAngle);
    gfx_line(x, y, newX, newY);
    snowflake(newX, newY, radius / 3, newAngle);
  }
}

void tree(int x, int y, int length, float angle, float branchAngle) {
  // Base case
  if (length < 5) return;

  // Draw a line
  int newX = x + length * cos(angle);
  int newY = y + length * sin(angle);
  gfx_line(x, y, newX, newY);

  // Recursive calls
  tree(newX, newY, length * 0.7, angle - branchAngle, branchAngle);
  tree(newX, newY, length * 0.7, angle + branchAngle, branchAngle);
}

void fern(int x, int y, int length, float angle, float branchAngle) {
  // Base case
  if (length < 5) return;

  // Draw a line
  int endX = x + length * cos(angle);
  int endY = y + length * sin(angle);
  gfx_line(x, y, endX, endY);

  // Calculate new points along the line
  int numPoints = 4;
  int pointsX[numPoints];
  int pointsY[numPoints];
  for (int i = 0; i < numPoints; i++) {
    pointsX[i] = x + (i * length / numPoints + length / numPoints) * cos(angle);
    pointsY[i] = y + (i * length / numPoints + length / numPoints) * sin(angle);
  }

  // Recursive calls
  for (int i = 0; i < numPoints; i++) {
    fern(pointsX[i], pointsY[i], length / 3, angle - branchAngle, branchAngle);
    fern(pointsX[i], pointsY[i], length / 3, angle + branchAngle, branchAngle);
  }
}

void spiralSpirals(int x, int y, int radius, double angle) {
  // Base case
  if (radius < 2) return;
  
  // Draw point with new coordinates
  int newX = x + radius * cos(angle);
  int newY = y + radius * sin(angle);
  gfx_point(newX, newY);
  
  // Recursive cases
  spiralSpirals(x, y, radius*0.9, angle + M_PI*0.2);
  spiralSpirals(newX, newY, radius*0.35, angle);
}
