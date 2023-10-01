#ifndef Solve2DMaze_H_
#define Solve2DMaze_H_
#endif /* Solve2DMaze_H_ */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std; // @suppress("Symbol is not resolved")

// -------------------------------------------------------

//1. READ MAZE FROM FILE INTO 2D ARRAY
char** readMazeIntoArray(string inputFileName);

//2. FIND AND MARK PATH
void findMazePath(char** mazeArray);


//3. PRINT SOLVED MAZE TO OUTPUT FILE
void writeMazeSolutionToFile(char** mazeArray);

// -------------------------------------------------------


//HELPER METHODS - START
void printMazeArray(char** mazeArray);


void printMazeArray(int** mazeArray);


void getMazeSize(string inputFileName);


bool hasPathForward(int row, int col, int** visitedArray);


bool notVisited(int row, int col, int** visitedArray);


void removeDeadEndPaths(char** mazeArray);


int** initiateVisitedArray(char** mazeArray);
//HELPER METHODS - END
