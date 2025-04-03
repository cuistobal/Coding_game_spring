#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//#include "cdg.h"

/*
void	print_params(int *params, int depth)
{
	printf("%d\n", depth);
	for (int i =0; i < 9; i++)
		printf("%d ", params[i]);
	printf("\n");
}
*/

void	get_input(int *depth, int *initial)
{
    scanf("%d", depth);
	for (int i = 0; i < 3; i++)
	{
        for (int j = 0; j < 3; j++) 
            scanf("%d", &initial[i * 3 + j]);
    }
}

int main()
{
	int	ret;
    int depth;
	int	initial[9];

	ret = 0;

	get_input(&depth, initial);

//	print_params(initial, depth);

	printf("%d\n", ret);

    return 0;
}
