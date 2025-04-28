// Owen Dorweiler
// Fundamentals of Computing
// Lab 3, Quadrants and Polar Coordinates
// Finds quadrant and polar coordinates for an x, y coordinate

#include <stdio.h>
#include <math.h>

int get_quadrant(double, double);
double get_radius(double, double);
double get_angle(double, double);
void show_info(int, double, double);

int main () {
   int quadrant;
   double radius, angle;
   double x, y;

   // Get user input
   printf("Input x coordinate: ");
   scanf("%lf", &x);
   printf("Input y coordinate: ");
   scanf("%lf", &y);
   
   // Use funtions to get values for quadrant, radius, and angle
   quadrant = get_quadrant(x, y);
   radius = get_radius(x, y);
   angle = get_angle(x, y);

   show_info(quadrant, radius, angle);

   return 0;
}

int get_quadrant(double x, double y) {
   int quadrant;
   
   // Find quadrant
   if (x > 0) {
      if (y > 0)
	 quadrant = 1;
      else quadrant = 4;
   }
   else {
      if (y > 0)
	 quadrant = 2;
      else quadrant = 3;
   }

   return quadrant;
}

double get_radius(double x, double y) {
   double radius;
   
   // Find radius
   radius = sqrt((x*x) + (y*y));

   return radius;
}

double get_angle(double x, double y) {
   double angle;

   // Find angle
   angle = atan2(y, x) * (180/M_PI);

   return angle;
}

void show_info(int quadrant, double radius, double angle) {
   printf("The point is in quadrant %d with radius %lf and angle %.2lf degrees.\n", quadrant, radius, angle);
}
