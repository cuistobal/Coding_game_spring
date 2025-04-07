#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Fonction pour vérifier si la somme des nombres non nuls est inférieure ou égale à 6
static bool check_sum(int *combinaison, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (combinaison[i] > 0 && combinaison[i] < 6)
            sum += combinaison[i];
    }
    return sum <= 6;
}

// Fonction pour compter le nombre de chiffres non nuls
static bool valid_die(int *combinaison, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        
		if (combinaison[i] > 0 && combinaison[i] < 6)
            count++;
    }
    return count > 1;
}

// Fonction récursive pour générer les combinaisons
static void combinaisons(int *nombres, int set[50][4], int *index, bool *hash, int start, int size) 
{
    if (size > 1) 
	{
        if (check_sum(set[*index], size) && valid_die(set[*index], size)) 
            (*index)++;
    }

    for (int i = start; i < 4; i++) 
	{
        if (!hash[i]) 
		{
            hash[i] = true;
            set[*index][size] = nombres[i];
            combinaisons(nombres, set, index, hash, i + 1, size + 1);
            hash[i] = false;
            set[*index][size] = 0; 
        }
    }
}

int main(int argc, char *argv[]) {


    int set[50][4] = {0}; // Initialiser le tableau à zéro
    int index = 0;
    int nombres[4];
    bool hash[4] = {false};

    for (int i = 0; i < 4; i++) 
        nombres[i] = atoi(argv[i + 1]);

    combinaisons(nombres, set, &index, hash, 0, 0);

    // Afficher les combinaisons valides
    for (int i = 0; i < index; i++) 
	{
        for (int j = 0; j < 4; j++) 
		{
            printf("%d", set[i][j]);
            if (j < 3) 
				printf(" ");
        }
        printf("\n");
    }

    return 0;
}

