#include <stdbool.h>
#include <stdio.h>

#define ROW_SIZE 3
#define COL_SIZE 3
#define MAX 6

static const int neighbours[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void print_grid(int grid[ROW_SIZE][COL_SIZE])
{
    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
        {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

static bool check_position(int grid[ROW_SIZE][COL_SIZE], int row, int col)
{
    return (row >= 0 && row < ROW_SIZE && col >= 0 && col < COL_SIZE && grid[row][col] != 0);
}

static bool can_modify(int grid[ROW_SIZE][COL_SIZE], int row, int col)
{
    int sum = 0;
    int adjacent_count = 0;

    for (int dir = 0; dir < 4; dir++)
    {
        int new_row = row + neighbours[dir][0];
        int new_col = col + neighbours[dir][1];

        if (check_position(grid, new_row, new_col))
        {
            sum += grid[new_row][new_col];
            adjacent_count++;
        }
    }
    return (adjacent_count >= 2 && sum <= MAX);
}

static void try_modify(int grid[ROW_SIZE][COL_SIZE], int row, int col, bool *modified, int *count)
{
    if (can_modify(grid, row, col))
    {
        int original_value = grid[row][col];
        grid[row][col] = 0;
        *modified = true;
        for (int i = 0; i < ROW_SIZE; i++)
        {
            for (int j = 0; j < COL_SIZE; j++)
            {
                if (grid[i][j] != 0)
                {
                    bool new_modified = false;
                    try_modify(grid, i, j, &new_modified, count);
                    if (new_modified)
                    {
                        (*count)++;
                        print_grid(grid);
                    }
                }
            }
        }
        grid[row][col] = original_value;
    }
}

void explore_possibilities(int grid[ROW_SIZE][COL_SIZE], int *count, int depth)
{
	bool	modified = false;
	
	for (int c = 0; c < depth; c++)
	{
		for (int i = 0; i < ROW_SIZE; i++)
	    {
	        for (int j = 0; j < COL_SIZE; j++)
	        {
	            if (grid[i][j] != 0)
	            {
	                modified = false;
	                try_modify(grid, i, j, &modified, count);
	                if (modified)
	                {
	                    (*count)++;
	                    print_grid(grid);
	                }
	            }
	        }
	    }
	}
}

void get_input(int *depth, int initial[ROW_SIZE][COL_SIZE])
{
    scanf("%d", depth);
    for (int i = 0; i < ROW_SIZE; i++)
    {
        for (int j = 0; j < COL_SIZE; j++)
            scanf("%d", &initial[i][j]);
    }
}

int main(void)
{
    int depth;
    int count = 0;
    int initial[ROW_SIZE][COL_SIZE];

    get_input(&depth, initial);

    print_grid(initial);

    explore_possibilities(initial, &count, depth);

    print_grid(initial);

    printf("Total possibilities: %d\n", count);

    return 0;
}

