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

#define MAX 6

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
static bool check_position(int grid[ROW_SIZE][COL_SIZE], int row, int col)
{
	if ((row >= 0 && row < ROW_SIZE) && (col >= 0 && col < COL_SIZE))
		return (grid[row][col] != 0);
	return (false);
}

//
static void modify_grid(int grid[ROW_SIZE][COL_SIZE], int row, int col)
{
	int		sum = 0;
	bool	flag = false;
	
	if (grid[row][col] == 0)
	{
		//UP
		if (check_position(grid, row + 1, col))
		{
			if (sum + grid[row + 1][col] < MAX)
			{
				if (sum != 0)
					flag = true;	
				sum += grid[row +1][col];
				grid[row + 1][col] = 0;
			}
		}
		//RIGTH
		if (check_position(grid, row, col + 1))
		{
			if (sum + grid[row][col + 1] < MAX)
			{	
				if (sum != 0)
					flag = true;	
				sum += grid[row][col + 1];
				grid[row][col + 1] = 0;
			}
		}
		//DOWN
		if (check_position(grid, row - 1, col))
		{
			if (sum + grid[row - 1][col] < MAX)
			{
				if (sum != 0)
					flag = true;	
				sum += grid[row - 1][col];
				grid[row - 1][col] = 0;
			}
		}
		//LEFT
		if (check_position(grid, row, col - 1))
		{
			if (sum + grid[row][col - 1] < MAX)
			{
				if (sum != 0)
					flag = true;	
				sum += grid[row][col - 1];
				grid[row][col - 1] = 0;
			}
		}
		if (flag)
			grid[row][col] = sum;	
	}
}

//
static void	check_cell(int grid[ROW_SIZE][COL_SIZE], int *count, int row, int col)
{
	int sum = 0;

	if (grid[row][col] == 0)
	{
		//UP
		*count += check_position(grid, row + 1, col);
		//RIGTH
		*count += check_position(grid, row, col + 1);
		//DOWN
		*count += check_position(grid, row - 1, col);
		//LEFT
		*count += check_position(grid, row, col - 1);
	}
}

//Main
int main(void)
{
    int depth;
	int ret = 0;
	int count = 0;
	int	initial[ROW_SIZE][COL_SIZE];

	get_input(&depth, initial);

	print_grid(initial);

	for (int c = 0; c < depth; c++)
	{
		for (int i = 0; i < GRID_SIZE; i++)
		{
			count = 0;
			check_cell(initial, &count, i / ROW_SIZE, i % COL_SIZE);
			if (count > 1)
			{
				modify_grid(initial, i / ROW_SIZE, i % COL_SIZE);
				i = GRID_SIZE;
			}
		}	
	}

	print_grid(initial);

	printf("%d\n", ret);

    return 0;
}
/*


/home/chrleroy/Desktop/repos/42/so_long/sources/parsing/perform_flood_fill.c

//I use this function to check if the position falls within the defined limtis
static bool	check_position(int grid[ROW_SIZE][COL_SIZE], int row, int col)
{
	if (row >= 0 && row < ROW_SIZE)
	{
		if (col >= 0 && col < COL_SIZE)
			return (grid[row][col] == 0);				
	}
	return (false);
}

//I use this function to append my connection_tree. Ultimately, this allows me
//to identify wether we have a valid path or not.
static void	flood_fill(int grid[ROW_SIZE][COL_SIZE], int *count, int row, int col)
{
	if (check_position(grid, row, col))
	{
		//UP
		*count =+ flood_fill(grid, row + 1, col);
		//RIGTH
		*count =+ flood_fill(grid, row, col + 1);
		//DOWN
		*count =+ flood_fill(grid, row - 1, col);
		//LEFT
		*count =+ flood_fill(grid, row, col - 1);
	}
}
*/
