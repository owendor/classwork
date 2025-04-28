// Owen Dorweiler
// Fundamentals of Computing
// Lab 3, Multiple Quadratics
// Calculates zeros using the quadratic formula given a, b, c inputs, using a function to find the discriminant and going in a loop

#include <stdio.h>
#include <math.h>

double findDisc(double, double, double);

int main() {
   // Initialize variables
   double a, b, c;
   double disc;
   double zero1, zero2;

   // Print title and get a input
   printf("Quadratic Roots Calculator");
   printf("\nEnter A (0 to quit): ");
   scanf("%lf", &a);

   while (a != 0) {
      //Get b and c inputs
      printf("Enter B: ");
      scanf("%lf", &b);
  
      printf("Enter C: ");
      scanf("%lf", &c);
  
      // Calculate discriminant
      disc = findDisc(a, b, c);
  
      if (disc > 0) {
         // Calculate zeros
         zero1 = (-b + sqrt(disc)) / (2*a);
         zero2 = (-b - sqrt(disc)) / (2*a);

         // Print result
         printf("The first zero is %.4lf\n", zero1);
         printf("The second zero is: %.4lf\n", zero2);
      }

      else if (disc == 0) {
         // Calculate zero
         zero1 = -b / (2*a);

         // Print result
         printf("The zero is %.4lf\n", zero1);
      }
      // If roots are imaginary, print message
      else printf("The roots are imaginary.\n");

      // Get a input
      printf("\nEnter A (0 to quit): ");
      scanf("%lf", &a);
   }

   return 0;
}

double findDisc(double a, double b, double c) {
   double disc;
   disc = (b*b) - (4*a*c);
   return disc;
}
