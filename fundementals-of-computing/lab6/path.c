// Author: Owen Dorweiler
// Class: Fundamentals of Computing
// Assignment: Lab 6, Part 1
// Due: 20 October 2024

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 30

typedef struct {
  float x;
  float y;
} Point;

int readPoints(Point points[], char filename[]);
float findPathLength(Point points[], int pointCount);
float distanceCalc(Point a, Point b);
void printResult(Point points[], int pointCount, float pathLength);

int main() {
  char filename[31];
  Point points[MAX_POINTS];
  int pointCount;
  float pathLength = 0;
  
  printf("Enter file name: ");
  scanf("%99s", filename);
  
  // Read points, return line count
  pointCount = readPoints(points, filename);
  
  // Find path length
  pathLength = findPathLength(points, pointCount);
  
  // Print the output
  printResult(points, pointCount, pathLength);
  
  return 0;
}

int readPoints(Point points[], char filename[]) {
  // Open file, display error message if file does not exist
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("\nError: File '%s' does not exist. Please restart the program and try again.\n\n", filename);
    return 1;
  }
  
  // Read from file and save to struct
  int line = 0;
  while (fscanf(file, "%f %f", &points[line].x, &points[line].y) == 2 && line < MAX_POINTS) {
    line++;
  }
  fclose(file);
  
  return line;
}

float findPathLength(Point points[], int pointCount) {
  float length = 0;
  
  // Add distance between each set of points by calling distanceCalc()
  for (int i = 0; i < pointCount - 1; i++) {
    length = length + distanceCalc(points[i], points[i+1]);
  }
  
  return length;
}

float distanceCalc(Point a, Point b) {
  return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
}

void printResult(Point points[], int pointCount, float pathLength) {
  printf("Number of points: %d\n\n", pointCount);
  printf("  x   |   y  \n");
  printf("------+------\n");
  
  // Print points in the table
  for (int i = 0; i < pointCount; i++) {
    printf("%5.1f | %5.1f\n", points[i].x, points[i].y);
  }
  
  printf("\nTotal path length is %.2f\n", pathLength);
}
