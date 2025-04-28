// Owen Dorweiler
// Fundamentals of Computing
// Lab 1, Formula Calculator
// Calculates zeros using the quadratic formula given a, b, c inputs

#include <stdio.h>
#include <math.h>

int main () {
  // Initialize variables
  double a, b, c;
  double disc;
  double zero1, zero2;
  
  //Print title
  printf("Quadratic Formula Calculator\n");
  
  // Get inputs
  printf("Enter A: ");
  scanf("%lf", &a);
  
  printf("Enter B: ");
  scanf("%lf", &b);
  
  printf("Enter C: ");
  scanf("%lf", &c);
  
  // Calculate discriminant
  disc = (b*b) - (4*a*c);
  
  if (disc > 0) {
    // Calculate zeros
    zero1 = (-b + sqrt(disc)) / (2*a);
    zero2 = (-b - sqrt(disc)) / (2*a);

    // Print result
    printf("The first zero is %.4lf\n", zero1);
    printf("The second zero is: %.4lf\n", zero2);
    }
  // Print error message if discriminant is not greater than 0
  else printf("Result does not yield two real and distinct zeros. Try again.\n");
}
