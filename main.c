#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define GRID_SIZE 9
#define	ROW_SIZE 3
#define	COL_SIZE 3

#define ADJACENT 4
#define RINDEX 1
#define CINDEX 1

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

#define MAX 6
#define STOP -1

/******************************************************************************/
/* ****************************** UTILITIES ********************************* */
/******************************************************************************/

//
void	print_grid(int initial[ROW_SIZE][COL_SIZE])
{
	printf("\n");
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
			j == 2 ? printf("%d\n", initial[i][j]) : printf("%d ", initial[i][j]);	
	}
	printf("\n");
}

/******************************************************************************/
/* ****************************** PROGRAM *********************************** */
/******************************************************************************/

//
static int	check_position(int grid[ROW_SIZE][COL_SIZE], int row, int col)
{
	if (row >= 0 && row < ROW_SIZE)
	{
		if (col >= 0 && col < COL_SIZE)
			return grid[row][col];				
	}
	return 0;
}

//
static inline void	captured(int *board, int *sum, int *captures, int temp)
{
	*sum += temp;
	(*captures)++;
	*board = 0;
}

//
static bool capture(int board[ROW_SIZE][COL_SIZE], int *sum, int row, int col)
{
	int	temp = 0;
	int	captures = 0;

	temp = check_position(board, row - 1, col);
	if (temp > 0 && *sum + temp <= MAX)
		captured(&board[row - 1][col], sum, &captures, temp);
	temp = check_position(board, row, col + 1);
	if (temp > 0 && *sum + temp <= MAX)
		captured(&board[row][col + 1], sum, &captures, temp);
	temp = check_position(board, row + 1, col);
	if (temp > 0 && *sum + temp <= MAX)
		captured(&board[row + 1][col], sum, &captures, temp);
	temp = check_position(board, row, col - 1);
	if (temp > 0 && *sum + temp <= MAX)
		captured(&board[row][col + 1], sum, &captures, temp);

	printf("Scored %d for %d captures\n", *sum, captures);

	return (captures > 1);
}

//
static bool	is_safe(int board[ROW_SIZE][COL_SIZE], int *pos)
{
	int sum = 0;
	int	row = *pos / ROW_SIZE;
	int	col = *pos % COL_SIZE;
	int	save[ROW_SIZE][COL_SIZE];

	if (board[row][col] == 0)
	{
		memcpy(save, board, sizeof(int) * GRID_SIZE);
		if (capture(board, &sum, row, col))
			(board[row][col] = sum);
		else
		{
			memcpy(board, save, sizeof(int) * GRID_SIZE);
			(board[row][col] = 1);
		}
		(*pos)++;
		return (true);
	}
	return (false);
}

/*
static bool	capture_is_possible(int board[ROW_SIZE][COL_SIZE], int *pos)
{
			
}
*/

//
static void	recursion(int board[ROW_SIZE][COL_SIZE], int *count, int *pos, int depth)
{
	int		calls = 0;

	if (depth < 0)
	{
		(*count)++;
		return ;
	}
	while (*pos < GRID_SIZE)
	{
//		if (!capture_is_possible(board, pos))
//		{
			if (is_safe(board, pos))
			{
				print_grid(board);
				recursion(board, count, pos, depth - 1);
			}
//		}
		(*pos)++;
	}

	//No more possibilities -> time to stop
	recursion(board, count, pos, STOP);
}

//Gets input from the stdin
void	get_input(int *depth, int initial[ROW_SIZE][COL_SIZE])
{
    scanf("%d", depth);
	for (int i = 0; i < ROW_SIZE; i++)
	{
        for (int j = 0; j < COL_SIZE; j++) 
            scanf("%d", &initial[i][j]);
    }
}

//
int main(void)
{
	int	pos = 0;
	int	count = 0;
	int	depth = 0;
	int	board[ROW_SIZE][COL_SIZE] = {0};

	get_input(&depth, board);

	print_grid(board);

	recursion(board, &count, &pos, depth);

	print_grid(board);

	printf("%d\n", count);

	return 0;
}
