#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define GRID_SIZE 9
#define	ROW_SIZE 3
#define	COL_SIZE 3

void	find_captures(int *initial, int pos)
{

	for (int i = 0; i < GRID_SIZE; i++)
	{
		// We found a 0	-> slot available

		if (pos & (1 << i))
		{
			printf("ACTIVATED\n");
		
			if (i - 3 >= 0)
				printf("UP	->	%d\n", initial[i - 3]);
				
			if (i + 3 < 9)
				printf("DOWN	->	%d\n", initial[i + 3]);
		
			if (i - 1 >= 0 && i % 3 > 0)
				printf("LEFT	->	%d\n", initial[i - 1]);

			if (i + 1 < 9 && i % 3 < 2)
				printf("RIGHT	->	%d\n", initial[i + 1]);
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
int main()
{
	int	ret;
    int depth;
	int	initial[GRID_SIZE];

	ret = 0;

	get_input(&depth, initial);

	find_empty(initial, &ret);

	find_captures(initial, ret);

	printf("%d\n", ret);

    return 0;
}
