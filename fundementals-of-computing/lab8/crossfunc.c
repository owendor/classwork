// Author: Owen Dorweiler
// Class: Fundamentals of Computing
// Assignment: Lab 8
// Due: 17 November 2024

#include "crossfunc.h"

void initBoard(char solBoard[][BOARD_SIZE]) {
   for (int j = 0; j < BOARD_SIZE; j++) {
      for (int i = 0; i < BOARD_SIZE; i++)
	 solBoard[i][j] = '.';
   }
}

int getUserWords(Wordstruct words[]) {
   char userWord[MAX_LENGTH + 1];
   int wordCount = 0;
   
   printf("Enter word list:\n");
   
   // Read in words until '.' is read or there are 20 words
   scanf("%s", userWord);
   do {
      // Check validity of words and add them to array if valid
      if (validWord(userWord)) {
	 strcpy(words[wordCount].word, userWord);
	 wordCount++;
      }
      else printf("^ Word is invalid and will be ignored.\n"); 
	 
      scanf("%s", userWord);
   } while (strcmp(userWord, ".") != 0 && wordCount != MAX_WORDS);

   return wordCount;
}

int getFileWords(Wordstruct words[], char *filename) {
   FILE *file = fopen(filename, "r");
   if (file == NULL) {
      printf("File could not be opened. Exiting...\n");
      return 0;
   }
   
   char fileWord[100];
   int wordCount = 0;
   
   // Read words until "." is read or there are 20 words
   while (fgets(fileWord, 100, file) != NULL) {
      fileWord[strcspn(fileWord, "\n")] = 0;
      
      // Check validity of words and add them to array if valid
      if (strcmp(fileWord, ".") != 0 && wordCount != MAX_WORDS) {
	 if (validWord(fileWord)) {
	    strcpy(words[wordCount].word, fileWord);
	    wordCount++;
	 }
	 else printf("\"%s\" is invalid and will be ignored.\n", fileWord);
      }
      else break;
   }
   
   return wordCount;
}

bool validWord(char word[]) {
   bool allLetters = true;
   for (int a = 0; a < strlen(word); a++) {
      if (!isalpha(word[a]))
	 allLetters = false;
   }

   bool correctLength = true;
   if (strlen(word) < 2 || strlen(word) > MAX_LENGTH)
      correctLength = false;

   if (allLetters && correctLength)
      return true;
   else return false;
}

void processWords(Wordstruct words[], int numWords) {
   int wordLength[numWords];
   
   // Capitalize all words, set placed variables to false
   for (int a = 0; a < numWords; a++) {
      for (int b = 0; b < strlen(words[a].word); b++) {
	 words[a].word[b] = toupper(words[a].word[b]);
      }
      words[a].placed = false;
   }

   // Sort the words list longest to shortest
   bool swapped;
   char temp[16];
   do {
      swapped = false;
      for (int a = 0; a < numWords - 1; a++) {
	 if (strlen(words[a].word) < strlen(words[a+1].word)) {
	    strcpy(temp, words[a].word);
	    strcpy(words[a].word, words[a+1].word);
	    strcpy(words[a+1].word, temp);
	    swapped = true;
         }
      }
   } while (swapped);
}

void placeWords(char board[][BOARD_SIZE], Wordstruct words[], int numWords) {
   
   // Place the first word
   strcpy(words[0].direc, "Across");
   words[0].x = ceil(BOARD_SIZE / 2) - ceil(strlen(words[0].word) / 2);
   words[0].y = ceil(BOARD_SIZE / 2);
   updateBoard(board, words[0]);
   words[0].placed = true;

   // If crossword only has one word, break
   if (numWords == 1) return;
   
   // Define variables
   int numPlaced = 1;
   char prevDirec[7] = "Across";
   bool wordPlaced;

   // Loop through words 2-end; continue while at least one word is placed per cycle
   do {
      wordPlaced = false;
      for (int currentWord = 1; currentWord < numWords; currentWord++) {
	 // If word has not been placed, start the process to place it
	 if (!words[currentWord].placed) {
            // Define direction based on direction of previous placed word
            if (strcmp(prevDirec, "Across") == 0)
	       strcpy(words[currentWord].direc, "Down");
            else strcpy(words[currentWord].direc, "Across");
	    
	    // Call search function, which will place word if possible
	    if (search(board, &words[currentWord])) {
	       words[currentWord].placed = true;
	       wordPlaced = true;
	       strcpy(prevDirec, words[currentWord].direc);
	       numPlaced++;
	    }
	 }
      }
      // If all words have been placed, break the loop
      if (numWords == numPlaced)
	 break;
   } while (wordPlaced);
}

bool search(char board[][BOARD_SIZE], Wordstruct *word) {  
   for (int letterIndex = 0; letterIndex < strlen((*word).word); letterIndex++) {
      for (int y = 0; y < BOARD_SIZE; y++) {
	 for (int x = 0; x < BOARD_SIZE; x++) {
	    if ((*word).word[letterIndex] == board[x][y]) {
	       // Try to place word if match is found
	       if (attemptPlace(board, word, letterIndex, x, y))
		  return true;
            }
	 }
      }
   }

   return false;
}

bool attemptPlace(char board[][BOARD_SIZE], Wordstruct *word, int letterIndex, int x, int y) {
   // Find potential start and end coordinates
   if (strcmp((*word).direc, "Across") == 0) {
      (*word).x = x - letterIndex;
      (*word).y = y;
   }  
   else if (strcmp((*word).direc, "Down") == 0) {
      (*word).x = x;
      (*word).y = y - letterIndex;
   }  
       
   // Check if word has valid placement; if so, add to board, if not, keep searching
   if (validPlace(board, *word)) {
      updateBoard(board, *word); 
      return true;
   }

   return false;
}

bool validPlace(char board[][BOARD_SIZE], Wordstruct word) {
   // Check horizontal words
   if (strcmp(word.direc, "Across") == 0) {
      // Check if word would fit on board
      if (word.x < 0 || word.x + strlen(word.word) - 1 > BOARD_SIZE)
	 return false;
      
      // Check to the left and right of the word
      if (word.x - 1 >= 0 && board[word.x - 1][word.y] != '.')
	 return false;
      if (word.x + strlen(word.word) <= BOARD_SIZE && board[word.x + strlen(word.word)][word.y] != '.')
	 return false;
      
      // Check above and below word
      for (int a = 0; a < strlen(word.word); a++) {
         // Check above and below only if letter is not already on board
	 if (word.word[a] != board[word.x + a][word.y]) {
            if (word.y - 1 >= 0 && board[word.x + a][word.y - 1] != '.')
	       return false;
	    if (word.y + 1 <= BOARD_SIZE && board[word.x + a][word.y + 1] != '.')
	       return false;
	 }
      }

   }
   // Check vertical words
   else if (strcmp(word.direc, "Down") == 0) {
      // Check if word would fit on board
      if (word.y < 0 || word.y + strlen(word.word) - 1 > BOARD_SIZE)
	 return false;

      // Check above and below word
      if (word.y - 1 >= 0 && board[word.x][word.y - 1] != '.')
	 return false;
      if (word.y + strlen(word.word) <= BOARD_SIZE && board[word.x][word.y + strlen(word.word)] != '.')
	 return false;
      
      // Check to the left and right of the word
      for (int a = 0; a < strlen(word.word); a++) {
         // Check to the left and right only if letter is not already on board
	 if (word.word[a] != board[word.x][word.y + a]) {
	    if (word.x - 1 >= 0 && board[word.x - 1][word.y + a] != '.')
	       return false;
	    if (word.x + 1 <= BOARD_SIZE && board[word.x + 1][word.y + a] != '.')
	       return false;
	 }
      }
   }

   return true;
}

void updateBoard(char board[][BOARD_SIZE], Wordstruct word) {
   // Place words horizontally or vertically depending on direction
   if (strcmp(word.direc, "Across") == 0) {
      for (int a = 0; a < strlen(word.word); a++)
         board[word.x + a][word.y] = word.word[a];
   }
   else if (strcmp(word.direc, "Down") == 0) {
      for (int a = 0; a < strlen(word.word); a++)
	 board[word.x][word.y + a] = word.word[a];
   }
}

void printBoards(char board[][BOARD_SIZE]) {
   printf("\nSolution:\n");
   
   // Print solution board within border
   printBorder();
   for (int y = 0; y < BOARD_SIZE; y++) {
      printf("|");
      for (int x = 0; x < BOARD_SIZE; x++)
	 printf("%c", board[x][y]);
      printf("|\n");
   }
   printBorder();

   printf("\nCrossword puzzle:\n");
   
   // Print puzzle board within border
   printBorder();
   for (int y = 0; y < BOARD_SIZE; y++) {
      printf("|");
      for (int x = 0; x < BOARD_SIZE; x++) {
	 if (board[x][y] == '.')
	    printf("#");
	 else printf(" ");
      }
      printf("|\n");
   }
   printBorder();
}

void printBorder() {
   for (int i = 0; i < BOARD_SIZE + 2; i++)
      printf("-");
   printf("\n");
}

void randomize(Wordstruct words[], int numWords) {
   srand(time(NULL));

   // Generate a scrambled version of each word
   for (int a = 0; a < numWords; a++) {
      strcpy(words[a].scrambled, words[a].word);
      for (int i = strlen(words[a].scrambled) - 1; i > 0; i--) {
	 int j = rand() % (i + 1);
	 char temp = words[a].scrambled[i];
	 words[a].scrambled[i] = words[a].scrambled[j];
	 words[a].scrambled[j] = temp;
      }
   }

   // Rearrange word struct randomly
   for (int i = numWords - 1; i > 0; i--) {
      int j = rand() % (i + 1);
      Wordstruct temp = words[i];
      words[i] = words[j];
      words[j] = temp;
   }
}

void printClues(Wordstruct words[], int numWords) {
   printf("\nClues:\n");
   
   for (int a = 0; a < numWords; a++)
      if (words[a].placed)
	 printf("%2d %2d  %-6s  %s\n", words[a].x, words[a].y, words[a].direc, words[a].scrambled);

   printf("\n");
}
