// Author: Owen Dorweiler
// Class: Fundementals of Computing
// Assignment: Lab 9, Part 1
// Due: 24 November 2024

#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "gfx.h"

#define SIZE 100

void poly(int x, int y, int numSides);
void triangle(int x, int y);
void square(int x, int y);

int main() {
   int inpt;
   int x, y;

   gfx_open(600, 600, "Symbolic Typewriter"); 
   

   while(1) {
      inpt = gfx_wait();
      x = gfx_xpos();
      y = gfx_ypos();
      
      switch (inpt) {
	 // Check for letter inputs
	 case 'c':
	    gfx_color(255, 255, 255);
	    gfx_circle(x, y, SIZE / 2);
	    break;
	 case 't':
	    gfx_color(0, 255, 0);
	    triangle(x, y);
	    break;
	 case 'q':
	    goto end;
	    break;
	 default:
	    // Check for number inputs
	    if (isdigit(inpt)) {
	       if (inpt == '1') { 
		  gfx_color(0, 0, 255);
		  square(x, y);
	       }
               else if (inpt >= '3' && inpt <= '9') {
                  gfx_color(255, 0, 255);
                  poly(x, y, inpt - '0');
               }
            }
	    else {
	       // Check for left click and esc
	       if (inpt == 1) {
		  gfx_color(0, 0, 255);
		  square(x, y);
	       }
	       else if (inpt == 27) gfx_clear();
	    }
	    break;
      }
   }

   end: return 0;
}

void poly(int x, int y, int numSides) {
   int radius = SIZE / 2;
   float angleStep = 360.0 / numSides;
   int x1 = x + radius;
   int y1 = y;
   int x2, y2;
   float angle;

   // Draw lines based on number of sides
   for (int i = 1; i < numSides + 1; i++) {
      angle = angleStep * i;     
      x2 = x + radius * cos(angle * M_PI / 180);
      y2 = y + radius * sin(angle * M_PI / 180);
      gfx_line(x1, y1, x2, y2);
      
      x1 = x2;
      y1 = y2;
   }
}

void square(int x, int y) {
   int halfSide = SIZE / 2;
   
   // Draw the square
   gfx_line(x + halfSide, y - halfSide, x + halfSide, y + halfSide);
   gfx_line(x + halfSide, y + halfSide, x - halfSide, y + halfSide);
   gfx_line(x - halfSide, y + halfSide, x - halfSide, y - halfSide);
   gfx_line(x - halfSide, y - halfSide, x + halfSide, y - halfSide);
}

void triangle(int x, int y) {
   int height = SIZE;
   int halfWidth = SIZE / 2;
   
   // Draw the triangle with the top at (x, y)
   gfx_line(x - halfWidth, y + height, x + halfWidth, y + height);
   gfx_line(x - halfWidth, y + height, x, y);
   gfx_line(x + halfWidth, y + height, x, y);
}
