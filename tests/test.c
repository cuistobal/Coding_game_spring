#include <stdio.h>
#include <stdlib.h>

static void generateCombinations(int *nums, int start, int *combination, int combLen, int maxSum) {
    int sum = 0;

    // Calculer la somme actuelle des chiffres dans la combinaison
    for (int i = 0; i < combLen; i++) 
        sum += combination[i];

    if (sum <= maxSum)
    {
        for (int i = 0; i < 4; i++) 
            printf("%d ", combination[i]);
        printf("\n");
    }

    // Générer les combinaisons
    for (int i = start; i < 4; i++)
    {
        combination[combLen] = nums[i];
        generateCombinations(nums, i + 1, combination, combLen + 1, maxSum);
    }
}

int main(int argc, char **argv) {
    if (argc != 6) 
    {
        printf("Usage: %s maxSum num1 num2 num3 num4\n", argv[0]);
        return 1;
    }

    int nums[4];
    int combination[4] = {0};
    int maxSum = atoi(argv[1]);

    for (int i = 0; i < 4; i++)
        nums[i] = atoi(argv[i + 2]);

    generateCombinations(nums, 0, combination, 0, maxSum);

    return 0;
}

