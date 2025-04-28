// Author: Owen Dorweiler
// Class: Fundementals of Computing
// Assignment: Lab 4, Part 2
// Due: 29 September 2024

#include <stdio.h>
#include <stdbool.h>

void findPrimes(int max, bool* isPrime);
void printPrimes(int max, bool* isPrime);

int main() {
   int max = 1000;
   bool isPrime[max];
   
   // Fill array with 1s
   for (int i = 0; i < 1000; i++)
      isPrime[i] = true;
   
   // Set 0 and 1 to 0
   isPrime[0] = isPrime[1] = false;
   
   // Call functions to find and print primes
   findPrimes(max, isPrime);
   printPrimes(max, isPrime);
   return 0;
}

void findPrimes(int max, bool* isPrime) {
   for (int i = 2; i <= max; i++) {
      // If number is prime, test all higher numbers
      if (isPrime[i] == true) {
	 for (int j = i + 1; j <= max; j++) {
	    // If i is factor of j, j is not prime
	    if (j % i == 0)
	       isPrime[j] = false;
	 }
      }
   }
}

void printPrimes(int max, bool* isPrime) {
   int rowPrinted = 0;
   for (int i = 2; i <= max; i++) {
      if (isPrime[i] == true) {
         printf("%d ", i);
	 rowPrinted++;
      }
      
      // If the number of printed values is 10, start a new line
      if (rowPrinted == 10){
	 printf("\n");
	 rowPrinted = 0;
      }
   }
   printf("\n");
}


