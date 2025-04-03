#include "test.h"

void	print_params(int *params, int depth)
{
	printf("%d\n", depth);
	for (int i =0; i < 9; i++)
		printf("%d ", params[i]);
	printf("\n");
}
