// Owen Dorweiler
// Fundamentals of Computing
// Lab 1, Football Score Formula
// Calculates final team score from user inputs

#include <stdio.h>

int main() {
	// Initialize variables
	int touchdowns, extraPoints, fieldGoals, safeties;
	int total;
	
	// Get inputs
	printf("Enter number of touchdowns: ");
	scanf("%d", &touchdowns);

	printf("Enter number of extra points: ");
	scanf("%d", &extraPoints);

	printf("Enter number of field goals: ");
	scanf("%d", &fieldGoals);

	printf("Enter number of safeties: ");
	scanf("%d", &safeties);

	// Calculate total
	total = (touchdowns*6) + (extraPoints*1) + (fieldGoals*3) + (safeties*2);

	// Display total
	printf("Total points scored: %d\n", total);	
}
