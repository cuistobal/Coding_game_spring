#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int	grid[9] = {0};

	for (int k = 1; k < argc; k++)
	{
		for (int i = 0; i < 9; i++)
			grid[i]	= argv[k][i] - '0';
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				printf("%d", grid[i * 3 + j]);
				(j == 2) ? printf("\n") : printf(" ");
			}
		}
		argv++;
	}
	return 0;
}
