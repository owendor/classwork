// Author: Owen Dorweiler
// Class: Fundementals of Computing
// Assignment: Lab 4, Part 1
// Due: 29 September 2024

#include <stdio.h>
#include <math.h>

float getAverage(int size, int grades[]);
float getStDev(int size, float average, int grades[]);

int main() {
   float average;
   float stdev;
   int size;
   
   int grades[] =
     { 96,73,62,87,80,63,93,79,71,99,
       82,83,80,97,89,82,93,92,95,89,
       71,97,91,95,63,81,76,98,64,86,
       74,79,98,82,77,68,87,70,75,97,
       71,94,68,87,79 };
   
   // Compute size, average, and standard deviation
   size = sizeof(grades) / sizeof(grades[0]);
   average = getAverage(size, grades);
   stdev = getStDev(size, average, grades);
 
   // Print result
   printf("Number of grades: %d\n", size);
   printf("Average grade: %.2lf\n", average);
   printf("Standard deviation: %.2lf\n", stdev);
  
   return 0;
}

float getAverage(int size, int grades[]) {
   float average;
   float sum = 0;

   // Loop through array to create sum
   for (int i = 0; i < size; i++)
      sum = sum + grades[i];
   
   average = sum / size;
   return average;
}

float getStDev(int size, float average, int grades[]) {
   float stdev;
   float sum = 0;
   
   // Loop through array, create sum of squares of difference between grades and the mean
   for (int i = 0; i < size; i++) {
      sum = sum + pow(grades[i] - average, 2);
   }
   
   stdev = sqrt(sum / (size - 1));

   return stdev;
}
