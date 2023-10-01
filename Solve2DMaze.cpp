#include "Solve2DMaze.h"

int rows = 0, cols = 0;

int main()
{

	string inputFileName = "../maze_easy.txt"; //EASY
	//string inputFileName = "../maze_med.txt"; //MEDIUM
	//string inputFileName = "../maze_hard.txt"; //HARD

	getMazeSize(inputFileName);

	char** mazeArray;
	mazeArray = readMazeIntoArray(inputFileName);


	findMazePath(mazeArray);
	removeDeadEndPaths(mazeArray);

	writeMazeSolutionToFile(mazeArray);
	printMazeArray(mazeArray);

	return 0;

}


void getMazeSize(string inputFileName)
{
	ifstream inStream;
	inStream.open(inputFileName);

	if (inStream.fail())
	{
		cout << "ERROR! Opening input file " << inputFileName << " failed." << endl;
		exit(1);
	}

	char currentChar;
	inStream.get(currentChar);

	if (isdigit(currentChar))
	{
		inStream.putback(currentChar);
		inStream >> rows;
		inStream >> cols;
	}
	else
	{
		inStream.putback(currentChar);

		int r = 0, c = 0;
		while (!inStream.eof())
		{
			inStream.get(currentChar);

			if (currentChar != '\n')
			{
				c++;
			}
			else //if (currentChar == '\n')
			{
				c = 0;
				r++;
			}

		}

		rows = r + 1;
		cols = c - 1;
		cout << "rows: " << rows << ", columns: " << cols << endl;
	}


}


char** readMazeIntoArray(string inputFileName)
{
	ifstream inStream;
	inStream.open(inputFileName);

	if (inStream.fail())
	{
		cout << "ERROR! Opening input file " << inputFileName << " failed" << endl;
		exit(1);
	}

	char currentChar;
	inStream.get(currentChar);

	if (isdigit(currentChar))
	{
		while (currentChar != '\n')
		{
			inStream.get(currentChar);
		}

	}
	else
	{
		inStream.putback(currentChar);
	}

	char** mazeArray = new char*[rows]; //initialize the maze array

	for (int i = 0; i < rows; i++)
		mazeArray[i] = new char[cols];

	int i = 0, j = 0;
	while (!inStream.eof())
	{

		inStream.get(currentChar);
		if (currentChar != '\n')
		{
			if (j < cols)
			{
				mazeArray[i][j] = currentChar;
				j++;
			}

		}

		else //currentChar == '\n'
		{
			i++;
			j = 0;
		}

	}

	inStream.close();

	return mazeArray;
}


bool hasPathForward(int row, int col, int** visitedArray)
{

	bool rightNotVisited = notVisited(row, col + 1, visitedArray); 	// @suppress("Invalid arguments")
	bool leftNotVisited = notVisited(row, col - 1, visitedArray); 	// @suppress("Invalid arguments")
	bool upNotVisited = notVisited(row - 1, col, visitedArray);
	bool downNotVisited = notVisited(row + 1, col, visitedArray);

	if ((rightNotVisited || leftNotVisited || upNotVisited || downNotVisited))
	{
		return true;
	}
	else
		return false;
}


bool notVisited(int row, int col, int** visitedArray)
{
	if (visitedArray[row][col] != 0) // -1, 1, 2
		return false;
	else //visitedArray[row][col] == 0
		return true;

}


void findMazePath(char** mazeArray)
{

	int** visitedArray;
	visitedArray = initiateVisitedArray(mazeArray);

	int row = 1, col = 1, count = 1;

	char *currentPosMaze = &mazeArray[row][col];
	int *currentPosVisited = &visitedArray[row][col];


	char *endPosMaze = &mazeArray[rows - 2][cols - 2];
	//*endPosMaze = '!';

	while (currentPosMaze != endPosMaze)
	{

		bool rightNotVisited = notVisited(row, col + 1, visitedArray);
		bool leftNotVisited = notVisited(row, col - 1, visitedArray);
		bool upNotVisited = notVisited(row - 1, col, visitedArray);
		bool downNotVisited = notVisited(row + 1, col, visitedArray);

		int *rightPosVisit = &visitedArray[row][col + 1];
		int *leftPosVisit = &visitedArray[row][col - 1];
		int *upPosVisit = &visitedArray[row - 1][col];
		int *downPosVisit = &visitedArray[row + 1][col];

		char *rightPosMaze = &mazeArray[row][col + 1];
		char *leftPosMaze = &mazeArray[row][col - 1];
		char *upPosMaze = &mazeArray[row - 1][col];
		char *downPosMaze = &mazeArray[row + 1][col];


		if (rightNotVisited || leftNotVisited || upNotVisited || downNotVisited)
		{
			if (rightNotVisited)
			{
				mazeArray[row][col] = '.';
				visitedArray[row][col] = count;
				count++;
				col = col + 1;

				currentPosMaze = rightPosMaze;
				currentPosVisited = rightPosVisit;

			}
			else if (leftNotVisited)
			{
				mazeArray[row][col] = '.';
				visitedArray[row][col] = count;
				count++;
				col = col - 1;

				currentPosMaze = leftPosMaze;
				currentPosVisited = leftPosVisit;

			}
			else if (upNotVisited)
			{
				mazeArray[row][col] = '.';
				visitedArray[row][col] = count;
				count++;
				row = row - 1;

				currentPosMaze = upPosMaze;
				currentPosVisited = upPosVisit;

			}
			else if (downNotVisited)
			{

				mazeArray[row][col] = '.';
				visitedArray[row][col] = count;
				count++;
				row = row + 1;

				currentPosMaze = downPosMaze;
				currentPosVisited = downPosVisit;

			}
		}
		else
		{

			if ((*rightPosVisit != 0 && *leftPosVisit != 0 && *upPosVisit != 0 && *downPosVisit != 0))
			{


				if (*rightPosVisit == count - 1)
				{
					visitedArray[row][col] = -2;
					mazeArray[row][col] = 'X';


					count = count - 1;
					col = col + 1;
					currentPosVisited = rightPosVisit;

				}
				else if (*leftPosVisit == count - 1)
				{
					visitedArray[row][col] = -2;
					mazeArray[row][col] = 'X';


					count = count - 1;
					col = col - 1;
					currentPosVisited = leftPosVisit;

				}
				else if (*upPosVisit == count - 1)
				{
					visitedArray[row][col] = -2;
					mazeArray[row][col] = 'X';


					count = count - 1;
					row = row - 1;
					currentPosVisited = upPosVisit;

				}
				else if (*downPosVisit == count - 1)
				{
					visitedArray[row][col] = -2;
					mazeArray[row][col] = 'X';

					currentPosVisited = downPosVisit;

					count = count - 1;
					row = row + 1;

				}


			}


		}

	}

	*endPosMaze = '.';

}


void removeDeadEndPaths(char** mazeArray)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (mazeArray[i][j] == 'X')
			{
				mazeArray[i][j] = ' ';
			}
		}
	}
}


int** initiateVisitedArray(char** mazeArray)
{
	int** visitedArray = new int*[rows];

	for (int i = 0; i < rows; i++)
		visitedArray[i] = new int[cols];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (mazeArray[i][j] == '*')
			{
				visitedArray[i][j] = -1; 	// -1 == WALL
			}
			else if (mazeArray[i][j] == ' ')
			{
				visitedArray[i][j] = 0; 	// 0 == SPACE NOT VISITED
			}
		}
	}

	return visitedArray;
}


void writeMazeSolutionToFile(char** mazeArray)
{
	string outputFileName = "../maze_SOLUTION.txt";

	ofstream fout;
	fout.open(outputFileName);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			fout << mazeArray[i][j];
		}
		fout << endl;
	}

}


void printMazeArray(char** mazeArray)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << mazeArray[i][j];
		}
		cout << endl;
	}
}


void printMazeArray(int** mazeArray)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (mazeArray[i][j] == -1)
				cout << mazeArray[i][j];
			else
				cout << setw(2) << mazeArray[i][j];
		}
		cout << endl;
	}
}


