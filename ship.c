#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define GRID_SIZE 9
#define ROW_SIZE 3
#define COL_SIZE 3

#define MAX 6
#define STOP -1

#define DIRECTIONS 4
#define ITOT 2
#define IROW 0
#define ICOL 1

#define CAP_HEURISTIC 10

typedef struct move
{
    int priority;
    int index;
}	t_move;

static const int directions[DIRECTIONS][ITOT] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

//
int compare(const void *a, const void *b)
{
    t_move *moveA = (t_move *)a;
    t_move *moveB = (t_move *)b;
    return moveB->priority - moveA->priority;
}

//
static inline int check_position(int grid[ROW_SIZE][COL_SIZE], int row, int col) 
{
    if (row >= 0 && row < ROW_SIZE && col >= 0 && col < COL_SIZE)
        return grid[row][col];
    return 0;
}

//
static inline void captured(int *board, int *sum, int *captures, int temp) 
{

    *sum += temp;
    (*captures)++;
    *board = 0;
}

//
static bool capture(int board[ROW_SIZE][COL_SIZE], int *sum, int row, int col) 
{
    int new_row;
    int new_col;
    int temp = 0;
    int captures = 0;

    for (int i = 0; i < 4; i++)
	{
        new_row = row + directions[i][IROW];
        new_col = col + directions[i][ICOL];
        temp = check_position(board, new_row, new_col);
        if (temp > 0 && *sum + temp <= MAX) 
            captured(&board[new_row][new_col], sum, &captures, temp);
    }

    return (captures > 1);
}

//
static int evaluate_capture(int board[ROW_SIZE][COL_SIZE], int row, int col)
{
    int sum = 0;
    int captures = 0;
    int temp = 0;

    for (int i = 0; i < DIRECTIONS; i++)
	{
        temp = check_position(board, row + directions[i][IROW], col + directions[i][ICOL]);
        if (temp > 0)
		{
            sum += temp;
            captures++;
        }
    }

    return sum <= 6 ? captures * CAP_HEURISTIC + sum : 0;
}

//
static bool is_safe(int board[ROW_SIZE][COL_SIZE], int *pos, int *sum)
{
    int row = *pos / COL_SIZE;
    int col = *pos % COL_SIZE;
    int save[ROW_SIZE][COL_SIZE];

    if (board[row][col] == 0)
	{
        memcpy(save, board, sizeof(int) * GRID_SIZE);
        if (capture(board, sum, row, col))
            board[row][col] = *sum;
        else
		{
            memcpy(board, save, sizeof(int) * GRID_SIZE);
            board[row][col] = 1;
        }
        return true;
    }
    return false;
}

//
static void recursion(int board[ROW_SIZE][COL_SIZE], int *count, int depth)
{
    int row;
    int col;
	int	pos = 0;
	int sum = 0;
    t_move	temp;
    t_move	moves[GRID_SIZE];
    
	if (depth > 0)
	{
	    for (int i = 0; i < GRID_SIZE; i++)
		{
	        row = i / COL_SIZE;
	        col = i % COL_SIZE;
	        moves[i].priority = evaluate_capture(board, row, col);
	        moves[i].index = i;
	    }

	    // Sort moves based on priority (simple bubble sort for demonstration)
    
		qsort(moves, GRID_SIZE, sizeof(t_move), compare);

	    // Try captures in order of priority
	    for (int i = 0; i < GRID_SIZE; i++)
		{
	        pos = moves[i].index;
	
	        if (is_safe(board, &pos, &sum))
	            recursion(board, count, depth - 1);
	    }
	}
}

//
void get_input(int *depth, int initial[ROW_SIZE][COL_SIZE])
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
    int count = 0;
    int depth = 0;
    int board[ROW_SIZE][COL_SIZE] = {0};

    get_input(&depth, board);

    recursion(board, &count, depth);

    printf("%d\n", count);

    return 0;
}
