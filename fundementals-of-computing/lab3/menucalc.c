// Owen Dorweiler
// Fundamentals of Computing
// Lab 3, Text Menu Calculator
// Program to help 3rd graders verify math skills; does user selected operations on two integers

#include <stdio.h>
#include <math.h>

int menu();
void decide(int, double, double);
void add(double, double);
void subtract(double, double);
void multiply(double, double);
void divide(double, double);

int main() {
   int select;
   double num1, num2;
   
   // Run function to display menu and get selection
   select = menu();
   
   // Run loop while selection is not 5
   while (select != 5) {
      // Get user input
      printf("Enter number 1: ");
      scanf("%lf", &num1);
      printf("Enter number 2: ");
      scanf("%lf", &num2);
      
      // Run decision function, which calls other functions
      decide(select, num1, num2);
      
      // Display menu again and get selection
      select = menu();
   }

   return 0;
}

int menu() {
   int select;
   
   // Display menu
   printf("What would you like to do?");
   printf("\n1 - Addition");
   printf("\n2 - Subtraction");
   printf("\n3 - Multiplication");
   printf("\n4 - Division");
   printf("\n5 - Quit");

   // Get selection
   printf("\n\nEnter selection: ");
   scanf("%d", &select);

   return select;
}

void decide(int select, double num1, double num2) {
   // Call functions based on selection, checking for errors
   if (select == 1)
      add(num1, num2);
   else if (select == 2)
      subtract(num1, num2);
   else if (select == 3)
      multiply(num1, num2);
   else if (select == 4) {
      if (num2 != 0)
         divide(num1, num2);
      else printf("\nError: divide by zero.\n\n");
   }
   else printf("\nError: invalid menu selection.\n\n");
}

void add(double x, double y) {
   printf("\n(%g) + (%g) = %g\n\n", x, y, x+y);
}

void subtract(double x, double y) {
   printf("\n(%g) - (%g) = %g\n\n", x, y, x-y);
}

void multiply(double x, double y) {
   printf("\n(%g) * (%g) = %g\n\n", x, y, x*y);
}

void divide(double x, double y) {
   printf("\n(%g) / (%g) = %g\n\n", x, y, x/y);
}
