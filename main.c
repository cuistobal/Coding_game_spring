#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define GRID_SIZE 9
#define	ROW_SIZE 3
#define	COL_SIZE 3

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

static void	try_position(int *initial, unsigned char adjacent, int i)
{
	int	sum = 0;

	for (int j = 0; j < 9; j++)
	{
		if (adjacent & (1 << j))
			sum += initial[j];
	}
	printf("SUM	->	%d\n", sum);
}
// This fucntion checks if we have at least 2 non 0 adjacent cells and increments
// the buffer's value with those adjacent positions.
static int	check_adjacent_cells(int *initial, unsigned char *adjacent, int i)
{
	int	count = 0;

	if (i - ROW_SIZE >= 0 && initial[i - ROW_SIZE] != 0)
	{
		*adjacent |= (1 << (i - ROW_SIZE));	
		count++;
	}
	if (i + ROW_SIZE < GRID_SIZE && initial[i + ROW_SIZE] != 0)
	{
		*adjacent |= (1 << (i + ROW_SIZE));
		count++;
	}
	if (i - 1 >= 0 && i % COL_SIZE > 0 && initial[i - 1] != 0)
	{
		*adjacent |= (1 << (i - 1));
		count++;
	}
	if (i + 1 < GRID_SIZE && i % COL_SIZE < 2 && initial[i + 1] != 0)
	{
		*adjacent |= (1 << (i + 1));
		count++;
	}
	return (count < 2) ? (*adjacent = '\0', count) : count;
}

void	find_captures(int *initial, int *captures, int pos)
{
	unsigned char	adjacent[9] = {'\0'};

	for (int i = 0; i < GRID_SIZE; i++)
	{
		// We found a 0	-> slot available

		if (pos & (1 << i))
		{
			check_adjacent_cells(initial, &adjacent[i], i);

			if (adjacent[i] != '\0')
			{
				// We've got at least to valid neighbours

				try_position(initial, i, adjacent[i]);

				printf("@ %d	->	", i);
				print_bits(&adjacent[i], 8);
			}
		}
	}
}

//Find empty spaces within the the current grid
void	find_empty(int *initial, int *pos)
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		if (initial[i] == 0)
        	*pos |= (1 << i);
	}
}

//Gets input from the stdin
void	get_input(int *depth, int *initial)
{
    scanf("%d", depth);
	for (int i = 0; i < ROW_SIZE; i++)
	{
        for (int j = 0; j < COL_SIZE; j++) 
            scanf("%d", &initial[i * COL_SIZE + j]);
    }
}

//Main
int main(void)
{
	int	ret;
    int depth;
	int	captures;
	int	initial[GRID_SIZE];

	ret = 0;

	captures = 0;

	get_input(&depth, initial);

	find_empty(initial, &ret);

	find_captures(initial, &captures, ret);

	for (int i = 0; i < GRID_SIZE; i++)
	{
		if (captures & (1 << i))
			printf("%d	@	%d\n", initial[i], i);
	}

	printf("%d\n", ret);

    return 0;
}
