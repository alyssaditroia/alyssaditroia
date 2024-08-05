/*
 * life.c
 *
 *  Created on: Jan 31, 2024
 *      Author: Alyssa Ditroia
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ROWS 5
#define COLS 5
#define NUMBER_OF_ENTRIES 7

enum State{
	LIVE = 1,
	DEAD = 0,
};

void playGameOfLife();
void getPlayerGrid(int grid[ROWS][COLS]);
int determineNeighbors(int grid[ROWS][COLS], int curRow, int curCol);
void neighborCountGrid(int grid[ROWS][COLS], int neighborCounts[ROWS][COLS]);
void generationLogic(int neighborCounts[ROWS][COLS], int grid[ROWS][COLS], int *currentGeneration);
void printGrid(int grid[ROWS][COLS]);


int main() {

  playGameOfLife();

  printf("Thanks for playing, bye!");

  return 0;
}


void playGameOfLife() {

  char playerInput;
  int currentGeneration;

  printf("Welcome to The Game Of Life! Enter any key to continue or enter 'q' to quit: \n");
  scanf(" %c", &playerInput);

  while (playerInput != 'q') {

	int grid[ROWS][COLS] = {{2,3,4,5,6},
						    {7,8,9,10,11},
						    {12,13,14,15,16},
						    {17,18,19,20,21},
						    {22,23,24,25,26}};

    int neighborCounts[ROWS][COLS];

    getPlayerGrid(grid);


    for (currentGeneration = 1; currentGeneration < 7; currentGeneration++) {

      neighborCountGrid(grid, neighborCounts);

      generationLogic(neighborCounts, grid, &currentGeneration);

    }

    printf("Good Life! \n");
    printf("Enter any key to continue or enter 'q' to quit: \n");
    scanf(" %c", &playerInput);

  }
}

//this function creates a grid based on the users inputs that can be used for further processing

void getPlayerGrid(int grid[ROWS][COLS]) {

  char userInput[50];
  int playerNumbers[NUMBER_OF_ENTRIES];

  printf("Please enter 7 numbers in the form of a list separated by commas: \n");
  scanf(" %[^\n]", userInput); //reads input until enter key is pressed. Reads a string that might have spaces.

  char *entryTokens = strtok(userInput, ",");  /* strtok is splitting the users input into tokens using the comma
  	  	  	  	  	  	  	  	  	  	  	 */
  int i = 0;

  while (entryTokens != NULL && i < NUMBER_OF_ENTRIES) {
    playerNumbers[i++] = atoi(entryTokens);
    entryTokens = strtok(NULL, ",");
  }
 //compares the players inputs with the numbered grid and creates a new grid of live and dead cells
  for (int k = 0; k < i; k++) {
    for (int m = 0; m < ROWS; m++) {
      for (int n = 0; n < COLS; n++) {
        if (grid[m][n] == playerNumbers[k] + 2) {
          grid[m][n] = LIVE;
        }
      }
    }
  }
  for (int m = 0; m < ROWS; m++) {
    for (int n = 0; n < COLS; n++) {
      if (grid[m][n] != LIVE) {
        grid[m][n] = DEAD;
      }
    }
  }
  printf("generation 0:\n");
  printGrid(grid);

}

//Creates a grid that has the count of each cells live neighbors
void neighborCountGrid(int grid[ROWS][COLS], int neighborCounts[ROWS][COLS]) {

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {

      neighborCounts[i][j] = determineNeighbors(grid, i, j);
    }
  }

}

//Determines the count of neighbors for each element in the grid for the Neighbor Count grid
int determineNeighbors(int grid[ROWS][COLS], int curRow, int curCol) {

  int neighborCount = 0;

  for (int i = curRow - 1; i <= curRow + 1; i++) {
    for (int j = curCol - 1; j <= curCol + 1; j++) {
      // Skips the current cell
      if ((i == curRow && j == curCol) || i < 0 || i >= ROWS || j < 0 || j >= COLS) {
        continue;
      }

      // Check if the neighbor is in proximity of the cell and is live
      if (grid[i][j] == LIVE) {
        neighborCount++;
      }
    }
  }

  return neighborCount;
}

//Executes the logic for each generation based on the game of life rules
void generationLogic(int neighborCounts[ROWS][COLS], int grid[ROWS][COLS], int *currentGeneration) {

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (neighborCounts[i][j] == 3 && grid[i][j] == DEAD) {

        grid[i][j] = LIVE;
      }
      if ((neighborCounts[i][j] > 3 || neighborCounts[i][j] < 2) && grid[i][j] == LIVE) {

        grid[i][j] = DEAD;
      }
    }
  }

  printf("Generation %d:\n", *currentGeneration);
  printGrid(grid);
}

//Prints the grid based on if the cell is live or dead
void printGrid(int grid[ROWS][COLS]) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (grid[i][j] == LIVE) {
        printf("*");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

