#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define GRID_SIZE 9
#define	ROW_SIZE 3
#define	COL_SIZE 3

// TESTS && UTILS

void print_bits(void *ptr, size_t num_bits)
{
    char buffer[256] = {0};

    memcpy(buffer, ptr, (num_bits + 7) / 8);
    for (size_t i = 0; i < num_bits; ++i)
	{
        size_t byte_offset = i / 8;
        size_t bit_offset = i % 8;
        if (i > 0 && i % 4 == 0)
            printf(" ");
        (buffer[byte_offset] & (1 << (7 - bit_offset))) ? printf("1") : printf("0");
    }
    printf("\n");
}

// PROGRAMM

static void	try_position(int initial[ROW_SIZE][COL_SIZE], unsigned char adjacent, int index)
{
	int	sum = 0;

	printf("\n");
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			if (adjacent & (1 << (i * ROW_SIZE + j)))
				sum += initial[i][j];
			printf("%d ", initial[i][j]);	
		}
		printf("\n");
	}
	printf("\nSUM	->	%d\n", sum);
}
// This fucntion checks if we have at least 2 non 0 adjacent cells and increments
// the buffer's value with those adjacent positions.
static int check_adjacent_cells(int initial[ROW_SIZE][COL_SIZE], unsigned char *adjacent, int index) {
    int count = 0;
    int row = index / ROW_SIZE;
    int col = index % COL_SIZE;

    if (row > 0 && initial[row - 1][col] != 0)
	{
        *adjacent |= (1 << ((row - 1) * ROW_SIZE + col));
        count++;
    }
    if (row < ROW_SIZE - 1 && initial[row + 1][col] != 0)
	{
        *adjacent |= (1 << ((row + 1) * ROW_SIZE + col));
        count++;
    }
    if (col > 0 && initial[row][col - 1] != 0)
	{
        *adjacent |= (1 << (row * ROW_SIZE + (col - 1)));
        count++;
    }
    if (col < COL_SIZE - 1 && initial[row][col + 1] != 0)
	{
        *adjacent |= (1 << (row * ROW_SIZE + (col + 1)));
        count++;
    }
	return (count < 2) ? (*adjacent = '\0', count) : count;
}

void	find_captures(int initial[ROW_SIZE][COL_SIZE], int *captures, int pos)
{
	int				index;
	unsigned char	adjacent[GRID_SIZE] = {'\0'};

	for (int i = 0; i < ROW_SIZE; i++)
	{
		// We found a 0	-> slot available

		for (int j = 0; j < COL_SIZE; j++)
		{
			index = i * ROW_SIZE + j;
			if (pos & (1 << (i * ROW_SIZE + j)))
			{
				check_adjacent_cells(initial, &adjacent[index], index);

				if (adjacent[index] != '\0')
				{
				// We've got at least to valid neighbours

					try_position(initial, index, adjacent[index]);

					printf("@ %d	->	", i);
					print_bits(&adjacent[i], 8);
				}
			}
		}
	}
}

//Find empty spaces within the the current grid
void	find_empty(int initial[3][3], int *pos)
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			if (initial[i][j] == 0)
        		*pos |= (1 << i);
		}
	}
}

//Gets input from the stdin
void	get_input(int *depth, int initial[3][3])
{
    scanf("%d", depth);
	for (int i = 0; i < ROW_SIZE; i++)
	{
        for (int j = 0; j < COL_SIZE; j++) 
            scanf("%d", &initial[i][j]);
    }
}

//Main
int main(void)
{
	int	ret;
    int depth;
	int	captures;
	int	initial[ROW_SIZE][COL_SIZE];

	ret = 0;

	captures = 0;

	get_input(&depth, initial);

	find_empty(initial, &ret);

	find_captures(initial, &captures, ret);

	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < ROW_SIZE; j++)
		{
			if (captures & (1 << (i * ROW_SIZE + j)))
				printf("%d	@	%d\n", initial[i][j], i);
		}
	}

	printf("%d\n", ret);

    return 0;
}
