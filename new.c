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

typedef struct queue
{
    int sum;
    int indexes[4];
}	t_queue;

typedef struct move
{
    int 	index;
    int 	priority;
	t_queue queue[256];
}	t_move;

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

static void assess(int board[ROW_SIZE][COL_SIZE], int row, int col)
{
    int nrow;
    int ncol;

    for (int  i = 0; i < DIRECTIONS; i++)
    {
        nrow = row + directions[i][0];
        ncol = col + directions[i][1];
        if (nrow >= 0 && nrow < 3 && ncol >= 0 && ncol < 3 && board[nrow][ncol] > 0)
            printf("%d ", board[nrow][ncol]);
    }
    printf("\n");
}

static void recursion(int board[ROW_SIZE][COL_SIZE], int *ret, int depth)
{
    if (depth > 0)
    {
        for (int i = 0; i < ROW_SIZE; i++)
        {
            for (int  j = 0; j < COL_SIZE; j++)
            {
                if (board[i][j] == 0)
                    assess(board, i, j);
            }
        }
        recursion(board, ret, depth - 1);
    }
    *ret = 0;
}
//
int main(void)
{
	int	ret = 0;
    int depth = 0;
    int board[ROW_SIZE][COL_SIZE] = {0};

    get_input(&depth, board);

    print_grid(board);

    recursion(board, &ret, depth);

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
