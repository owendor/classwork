// Author: Owen Dorweiler
// Class: Fundementals of Computing
// Assignment: Lab 2, Part 1
// Description: Gets two numerical inputs and outputs a multiplication table

#include <stdio.h>

int main() {
  // Declare variables
  int num1, num2;

  // Get inputs	
  printf("Input first number: ");
  scanf("%d", &num1);
  printf("Input second number: ");
  scanf("%d", &num2);

  // Print table header
  printf("*");
  for (int a = 1; a <= num1; a++) {
    printf("\t%d", a);
  }
  
  // Print table
  for (int b = 1; b <= num2; b++) {
    printf("\n%d |", b);
    for (int c = 1; c <= num1; c++) {
      printf("\t%d", b * c);
    }
  }
  printf("\n");
}
