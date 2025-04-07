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

int	adjacent[4] = {-ROW_SIZE, 1, ROW_SIZE, -1};
//
void get_input(int *depth, int initial[GRID_SIZE])
{
    scanf("%d", depth);
    for (int i = 0; i < GRID_SIZE; i++)
		scanf("%d", &initial[i]);
}

static inline bool	check_index(int board[GRID_SIZE], int *value, int index)
{
	return (board[index] > 0 && board[index] < 6) ? (*value = board[index], true) : false;
}

static inline int	get_value(int board[GRID_SIZE], int *count, int pos)
{
	(pos >= 0 && pos < 9) && (board[pos] > 0 && board[pos] < 6) ? board[pos] : -1;
}

static void	explore(int new[][GRID_SIZE], int board[GRID_SIZE], int *index, int pos)
{
	int count = 0;
	int	adjacent[4] = {-1};

	for (int i = 0; i < 4; i++)
	{
		adjacent[i] = get_value(board, &count, pos + adjacent[i]);
	}
	if (count == 2)
	{
			
	}
	else if (count > 2)
	{

	}
}

//
static void	recursion(int board[GRID_SIZE], int *ret, int depth)
{
	int	index = 0;
	int	new[500][GRID_SIZE];
	int	zeros[GRID_SIZE] = {0};

	if (depth > 0)
	{
		memcpy(new[index], board, sizeof(int) * GRID_SIZE);
		for (int  i = 0; i < GRID_SIZE; i++)
		{
			if (board[i] == 0)
			{
				explore(new + index, new[index], &index, i);
			
			}
	}
}
//
int main(void)
{
	int	ret = 0;
    int depth = 0;
    int board[GRID_SIZE] = {0};

    get_input(&depth, board);

    recursion(board, &ret, depth);

    printf("%d\n", ret);

    return 0;
}
