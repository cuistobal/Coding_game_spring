#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
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

static const int	neighbours[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};

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

// PROGRAMM


/*
static void	modify_grid(int initial[ROW_SIZE][COL_SIZE], int index, uint8_t adjacent)
{
	int	sum = 0;

	for (int i = 0; i < ADJACENT; i++)
	{
		if (adjacent & (1 << i))
			sum += initial[] 
	}
}
*/

static void modify_grid(int initial[ROW_SIZE][COL_SIZE], int index, uint8_t adjacent)
{
    int sum = 0;
    int row = index / ROW_SIZE;
    int col = index % COL_SIZE;

    for (int i = 0; i < ADJACENT; i++) 
	{
    	if (adjacent & (1 << i)) 
		{
            int newRow = row + neighbours[i][0];
            int newCol = col + neighbours[i][1];

            if (newRow >= 0 && newRow < ROW_SIZE && newCol >= 0 && newCol < COL_SIZE)
                sum += initial[newRow][newCol];
        }
    }

    initial[row][col] = sum;
}

static void	activate_bits(void *container, int bits)
{
	*(int *)container |= bits;
}

// This fucntion checks if we have at least 2 non 0 adjacent cells and increments
// the buffer's value with those adjacent positions.
static void check_adjacent_cells(int initial[ROW_SIZE][COL_SIZE], uint8_t *adjacent, int index) 
{
    int 	row = index / ROW_SIZE;
    int 	col = index % COL_SIZE;
	
	// UP
    if (row > 0 && initial[row - 1][col] != 0)
		activate_bits(adjacent, UP | (1 << 4));
	// LEFT
	if (row < ROW_SIZE - 1 && initial[row + 1][col] != 0)
		activate_bits(adjacent, LEFT | (1 << 5));
    // DOWN
	if (col > 0 && initial[row][col - 1] != 0)
		activate_bits(adjacent, DOWN | (1 << 6));
	// RIGHT
    if (col < COL_SIZE - 1 && initial[row][col + 1] != 0)
		activate_bits(adjacent, RIGHT | (1 << 7));
	if (*adjacent < 15) 
		*adjacent = 0;
}

void	find_captures(int initial[ROW_SIZE][COL_SIZE], int *captures, int pos)
{
	int				index;
	uint8_t			adjacent;

	for (int i = 0; i < ROW_SIZE; i++)
	{
		// We found a 0	-> slot available

		for (int j = 0; j < COL_SIZE; j++)
		{
			index = (i * ROW_SIZE) + j;
			printf("%d\n", index);
			if (pos & (1 << index))
			{
				adjacent = 0;

				printf("index -> %d\n", pos & (1 << index));
				
				check_adjacent_cells(initial, &adjacent, index);

				if (adjacent != 0)
				{
					
				// We've got at least two valid neighbours
					
					print_grid(initial);

				//	try_position(initial, index, adjacent);

					modify_grid(initial, pos & (1 << index), adjacent);

					print_grid(initial);

/*
					printf("@ %d	->	", i);
					print_bits(&adjacent[i], 8);
*/
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
        		*pos |= (1 << (i * ROW_SIZE + j));
		}
		print_bits(pos, i * 4 + 4);
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

	print_bits(&ret, 64);

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
