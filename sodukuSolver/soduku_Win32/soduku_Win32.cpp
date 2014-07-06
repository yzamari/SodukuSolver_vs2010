// soduku_Win32.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include  <stdio.h>
#include  <math.h>

#define EMPTY_CELL 0
#define E EMPTY_CELL

#define BOARD_SIZE 9
#define N BOARD_SIZE

#define PRINT_TO_FILE
#define PRINT_TO_STD
/** flag to check if the file has already created once **/
static bool wasFileOpened = false;

/** counts the number of boards - will easily be overflown **/
/** this counter is just for indexing the solutions        **/
static long long int boardCounter = 0;

/** Find the next empty place on board (row,col) **/
/** Input: board - Soduku board				    **/
/** Output: row, column							**/
/**         false if no more empty places       **/
bool findNextEmptyLocation(int board[N][N], int &row, int &col);

/** Check if puting val on row,column is legal move  **/
/** Input: board         - Soduku board               **/
/**        row, column  - coardinates on board       **/
/**        val          - value                      **/
bool isLegal(int board[N][N], int row, int col, int val);


bool findNextEmptyLocation(int board[N][N], int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (board[row][col] == EMPTY_CELL)
                return true;
    return false;
}

/** Checks if val is already exists in this row      **/
/** Input: board         - Soduku board               **/
/**        row, column  - coardinates on board       **/
/**        val          - value                      **/
/** Output: TRUE if already exists false else        **/
bool existInRow(int board[N][N], int row, int val)
{
	int col = 0;
	for (col = 0; col < N; col++)
	{
      if (board[row][col] == val)
            return true;
	}
	return false;
}

/** Checks if val is already exists in 3x3 square										  **/
/** Input: board         - Soduku board													  **/
/**        squareStartRow, squareStartCol  - coardinates on board  of starting square     **/
/**        val          - value															  **/
/** Output: TRUE if already exists false else											  **/

bool existIn3x3Square(int board[N][N], int squareStartRow, int squareStartCol, int val)
{
    for (int row = 0; row < 3; row++)
	{
        for (int col = 0; col < 3; col++)
		{
            if (board[row+squareStartRow][col+squareStartCol] == val)
			{
                return true;
			}
		}
	}
    return false;
}

/** Checks if val is already exists in this col      **/
/** Input: board         - Soduku board               **/
/**        row, column  - coardinates on board       **/
/**        val          - value                      **/
/** Output: TRUE if already exists false else        **/

bool existInCol(int board[N][N], int col, int val)
{
	int row = 0;
	for (row = 0; row < N; row++)
	{
      if (board[row][col] == val)
            return true;
	}
	return false;
}


bool isLegal(int board[N][N], int row, int col, int val)
{
	/** move is legal iff it doesn't already exist in row and col**/
	/** and in sqaure of 3x3**/
	int sqrtN = sqrt((double)N);
    return !existInRow(board, row, val) &&
           !existInCol(board, col, val) &&
		   !existIn3x3Square(board, row - (row % sqrtN) , col - (col % sqrtN), val);
}

/** printing the board (board) to std output**/
void printboardToStdOutput(int board[N][N])
{	
#ifdef PRINT_TO_STD
	printf("Board number: %ld \n" , boardCounter);
	printf("--------------------------------------------- \n");

    for (int row = 0; row < N; row++)
    {
       for (int col = 0; col < N; col++)
             printf("%3d", board[row][col]);
        printf("\n");
    }	
	printf("--------------------------------------------- \n");
#endif
}

/** printing the board (board) to output file**/
void printboardToFile(int board[N][N])
{
#ifdef PRINT_TO_FILE
	FILE *f;

	if (!wasFileOpened)
	{		
		f = fopen("yahavSoduku.txt","w");
		wasFileOpened = true;
	}
	else
	{
		f= fopen("yahavSoduku.txt","a");
	}

	fprintf(f,"Board number: %ld \n" , boardCounter);
	fprintf(f,"--------------------------------------------- \n");
    for (int row = 0; row < N; row++)
    {
       for (int col = 0; col < N; col++)
	   {
             fprintf(f,"%3d", board[row][col]);
	   }
        fprintf(f,"\n");
    }
	fprintf(f,"--------------------------------------------- \n");
	fclose(f);
#endif
}

/** Recursivley solve the board					    **/
/** Take a board with some values somewhere and try  **/
/** to solve it										**/
bool solveSudoku(int board[N][N])
{
    int row, col;
 
	/** If no more empty cells in board we were done**/
    if (!findNextEmptyLocation(board, row, col))
       return true;
 
    for (int num = 1; num <= N; num++)
    {        
        if (isLegal(board, row, col, num))
        {
            
            board[row][col] = num;
 
            // on success print the board
            if (solveSudoku(board))
			{	
				printboardToStdOutput(board);
				printboardToFile(board);				
				boardCounter++;
			}
            // if didn't succeed make this place in board empty without printing the board
            board[row][col] = E;
        }
    }
    return false;
}



int _tmain(int argc, _TCHAR* argv[])
{
   int board1[N][N] ={{9, E, E, E, E, E, E, E, E},
                      {E, 8, E, E, E, E, E, E, E},
                      {E, E, 7, E, E, E, E, E, E},
                      {E, E, E, E, E, E, E, E, E},
                      {E, E, E, E, E, E, E, E, E},
                      {E, E, E, E, E, E, E, E, E},
                      {E, E, E, E, E, E, E, E, E},
                      {E, E, E, E, E, E, E, E, E},
                      {E, E, E, E, E, E, E, E, E}};

    if (solveSudoku(board1) == true)
	{
          printf("There are solutions");
	}
    else
	{
         printf("No solution exists");
	}
 
    return 0;
}