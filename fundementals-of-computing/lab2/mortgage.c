// Author: Owen Dorweiler
// Class: Fundementals of Computing
// Assignment: Lab 2, Part 2
// Description: Calculates time it takes to pay off a mortgage given the principal, interest rate, and monthly payment

#include <stdio.h>
#include <math.h>

int main() {
  // Initialize user defined variables
  double principal, payment, rate;

  // Get inputs from user
  printf("Enter principal (initial amount): ");
  scanf("%lf", &principal);
  printf("Enter yearly interest rate (%): ");
  scanf("%lf", &rate);
  printf("Enter monthly payment: ");
  scanf("%lf", &payment);

  // Initialize variables
  double balance = principal, interest, totalPaid = 0, monthRate = rate/12;
  int totalMonths = 0;

  // Check to if payment is less than interest; if so, display error
  if (payment < balance * monthRate / 100)
    printf("You cannot pay off your mortgage because your monthly payment is less than your initial monthly interest.\n");
  
  else {
    // Print header
    printf("\nMonth\tPayment\t\tInterest\tBalance");

    // Calculate and display table
    for (int month = 1; balance > 0; month++) {
    
      // Calculate interest
      interest = balance * monthRate / 100;
    
      // Check if balance is 0, and calculate balance
      if (payment > balance) {
        payment = balance;
        balance = 0;
      }
      else balance = balance + interest - payment;

      // Sum totals
      totalPaid += payment;
      totalMonths++;
    
      printf("\n%d\t$%.2f\t\t$%.2f\t\t$%.2f", month, payment, interest, balance);
    }

    // Calculate and print total stats
    int years = totalMonths / 12;
    int months = totalMonths % 12;
    printf("\n\nYou paid a total of $%.2f over %d years and %d months.\n\n", totalPaid, years, months);
  }
}
