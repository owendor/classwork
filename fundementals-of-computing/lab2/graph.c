// Author: Owen Dorweiler
// Class: Fundementals of Computing
// Assignment: Lab 2, Part 3
// Description: Computes and prints graph of equation using x and y

#include <stdio.h>
#include <math.h>

int main() {
  // Initialize variables
  double minX, minY, maxX, maxY;
  double startX = 0.0, endX = 10.0, step = 0.2;

  
  // Print plot title
  printf("\nPlot for y = 12+(5*sin(2*x))+(6*cos(3*x)) for x from %.1f to %.1f", startX, endX);
  printf("\nX\tY");
  
  // Define starting max and min
  double y;
  y = 12+(5*sin(2*startX))+(6*cos(3*startX));
  minY = y;
  maxY = y;
  minX = startX;
  maxX = startX;

  // Calculate y, check if max or min
  for (double x = startX; x <= endX; x = x + step) {
    y = 12+(5*sin(2*x))+(6*cos(3*x));
    if (minY > y) {
      minY = y;
      minX = x;
    }
    if (maxY < y) {
      maxY = y;
      maxX = x;
    }

    // Print line of plot
    printf("\n%.2f\t%.2f\t", x, y);
    int roundY = (int)floor(y);
    for (int a = 1; a <= roundY; a++)
      printf("#");
  } 
  
  // Print max and min
  printf("\nThe maximum of %.2f was at %.2f", maxY, maxX);
  printf("\nThe minimum of %.2f was at %.2f\n", minY, minX);
}
