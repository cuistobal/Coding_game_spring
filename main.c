#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void	find_empty(int *initial, int *pos)
{
	for (int i = 0; i<9; i++)
	{
		if (initial[i] == 0)
        	*pos |= (1 << i);
	}
}

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

	find_empty(initial, &ret);

//	print_params(initial, depth);

	printf("%d\n", ret);

    return 0;
}
