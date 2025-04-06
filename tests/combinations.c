#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void	generateCombinations(int *nums, int start, int *combination, int combLen)
{
    int sum = 0;

    if (combLen > 1 && combLen <= 4)
    {
        for (int i = 0; i < combLen; i++)
            sum += combination[i];
        if (sum < 6)
        {
            for (int i = 0; i < 4; i++)
                printf("%d ", combination[i]);
            printf("\n");
        }
    }

    for (int i = start; i < 4; i++)
    {
        combination[combLen] = nums[i];
        generateCombinations(nums, i + 1, combination, combLen + 1);
	}
}

int main(int argc, char **argv)
{
    int max;
    int nums[4] = {0};
    int combination[4] = {0};

    max = atoi(argv[1]);
    for (int i = 0; i < 4; i++)
        nums[i] = atoi(argv[i + 2]);
    generateCombinations(nums, 0, combination, 0);
    for (int i = 0; i < 4; i++)
        printf("%d ", combination[i]);
}
