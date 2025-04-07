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


//
void get_input(int *depth, int initial[GRID_SIZE])
{
    scanf("%d", depth);
    for (int i = 0; i < GRID_SIZE; i++)
		scanf("%d", &initial[i]);
}

static void	check_adjacent(int board[GRID_SIZE], int index)
{
	if (index & 1 && !(index & 2))
	{
		//	2 max, sauf le 4
	}
	else if (!(index & 1))
	{
		//	3 max
	}
	else
	{
		//	4 max
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
			printf("%d ", new[index][i]);
/*
			if (board[i] == 0)
				explore(new, &index, i);
*/		}
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
