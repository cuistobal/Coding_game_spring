#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define COMBINATIONS 256

#define GRID_SIZE 9
#define ROW_SIZE 3
#define COL_SIZE 3

#define HASH 1073741824

#define MAX 6
#define STOP -1

#define DIRECTIONS 4
#define ITOT 2
#define IROW 0
#define ICOL 1

#define COMBINATIONS 256

#define CAP_HEURISTIC 10

typedef	struct combs
{
	int	depth;
	int	board[ROW_SIZE][COL_SIZE];
}	t_comb;

static const int directions[DIRECTIONS][ITOT] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

//
void print_grid(int initial[ROW_SIZE][COL_SIZE])
{
    printf("\n");
    for (int i = 0; i < ROW_SIZE; i++)
	{
        for (int j = 0; j < COL_SIZE; j++)
            j == 2 ? printf("%d\n", initial[i][j]) : printf("%d ", initial[i][j]);
    }
    printf("\n");
}

static inline long hash(int board[ROW_SIZE][COL_SIZE])
{
	long ret = 0;

	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
			ret = ret * 10 + board[i][j];
	}
	return ret;
}


/*
int compare(const void *a, const void *b)
{
    t_move *moveA = (t_move *)a;
    t_move *moveB = (t_move *)b;
    return moveB->priority - moveA->priority;
}
*/

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
static void	explore(int board[ROW_SIZE][COL_SIZE], int row, int col)
{
	int	new_row;
	int	new_col;
	int combinations[4];
	int nums[DIRECTIONS];

	for (int  i = 0; i < DIRECTIONS; i++)
	{
        new_row = row + directions[i][IROW];
	    new_col = col + directions[i][ICOL];
   		if (check_position(board, new_row, new_col)) 
			nums[i] = board[new_row][new_col];
    }
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

	if (board[row][col] == 0)
	{
    	for (int i = 0; i < DIRECTIONS; i++)
		{
    	    temp = check_position(board, row + directions[i][IROW], col + directions[i][ICOL]); 
			if (temp > 0)
			{
    	        sum += temp;
    	        captures++;
    	    }
    	}
	}

//	printf("heuristic %d @ index %d\n", captures > 1 ? sum <= 6 ? (row + col + CAP_HEURISTIC) : 0 : (row + col), row * 3 + col);

	if (captures > 1)
		return (sum <= 6) ? (row * ROW_SIZE + col + CAP_HEURISTIC + captures) : 0;
	return board[row][col] == 0 ? (GRID_SIZE - (row * ROW_SIZE + col)) : 0;
   // return captures > 1 ? sum <= 6 ? (row + col + CAP_HEURISTIC) : 0 : (row + col);
}

//
static bool is_safe(int board[ROW_SIZE][COL_SIZE], int row, int col)
{
	int sum = 0;
    int save[ROW_SIZE][COL_SIZE];

    if (board[row][col] == 0)
	{
        memcpy(save, board, sizeof(int) * GRID_SIZE);
        if (capture(board, &sum, row, col))
            board[row][col] = sum;
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
static void	recursion(t_comb combs[50], int *index, int board[ROW_SIZE][COL_SIZE], int *ret, int depth)
{
    int row;
    int col;
    
	if (depth > 0)
	{
		//Find possible moves && assess their priority

	    for (int i = 0; i < GRID_SIZE; i++)
		{
	        row = i / COL_SIZE;
	        col = i % COL_SIZE;



			if (is_safe(board, row, col))
			{
				combs[*index].depth = depth;
				memcpy(combs[*index].board, board, sizeof(int) * GRID_SIZE);
				recursion(combs, index, board, ret, depth - 1);
			}
		}	
	}
	*ret = (*ret + hash(board)) % HASH; 
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
	int	ret = 0;
    int depth = 0;
	int	combindex = 0;
	t_comb	combinations[50];
    int board[ROW_SIZE][COL_SIZE] = {0};

    get_input(&depth, board);

    print_grid(board);

    recursion(combinations, &combindex, board, &ret, depth);

    print_grid(board);

    printf("%d\n", ret);

    return 0;
}

/*

// Function to generate combinations
void	generateCombinations(t_queue *queue, int *nums, int len, int start, int *combination, int *originalIndexes, int combLen, int *queueIndex)
{
    int sum = 0;

    if (combLen > 0 && combLen <= 4)
    {
        for (int i = 0; i < combLen; i++)
            sum += combination[i];
        if (sum < MAX)
        {
            queue[*queueIndex].sum = sum;
            memcpy(queue[*queueIndex].indexes, originalIndexes, sizeof(int) * len);
            (*queueIndex)++;
        }
    }

    for (int i = start; i < len; i++)
    {
        combination[combLen] = nums[i];
        originalIndexes[i] = nums[i];
        generateCombinations(queue, nums, len, i + 1, combination, originalIndexes, combLen + 1, queueIndex);
        originalIndexes[i] = 0;
	}
}
*/
