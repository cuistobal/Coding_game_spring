#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // For memcpy

#define BOARD_SIZE 3
#define MODULO 1073741824 // 2^30

// Directions for adjacent cells (up, down, left, right)
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// Function to compute the hash of the board
unsigned int computeHash(int board[BOARD_SIZE][BOARD_SIZE]) {
    unsigned int hash = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            hash = (hash << 3) | board[i][j];
        }
    }
    return hash;
}

// Function to check if a move is a capturing move
bool isCapturingMove(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int *sumValue)
{
    int sums[4] = {0};
    int count = 0;

    for (int d = 0; d < 4; d++)
    {
        int nx = x + directions[d][0];
        int ny = y + directions[d][1];
        if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && board[nx][ny] != 0)
            sums[count++] = board[nx][ny];
    }

    for (int i = 0; i < count; i++) 
    {
        for (int j = i + 1; j < count; j++) 
        {
            if (sums[i] + sums[j] <= 6) 
                return *sumValue = sums[i] + sums[j], true;
        }
    }

    return false;
}

// Function to handle capturing moves
void handleCapturingMove(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int sumValue)
{
    for (int d = 0; d < 4; d++)
    {
        int nx = x + directions[d][0];
        int ny = y + directions[d][1];
        if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && board[nx][ny] != 0)
            board[nx][ny] = 0;
    }
    board[x][y] = sumValue;
}

// Function to simulate all possible moves
void simulateMoves(int board[BOARD_SIZE][BOARD_SIZE], int turns, unsigned int *finalSum) {
    if (turns == 0) {
        *finalSum = (*finalSum + computeHash(board)) % MODULO;
        return;
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                int newBoard[BOARD_SIZE][BOARD_SIZE];
                memcpy(newBoard, board, sizeof(newBoard));

                int sumValue = 0;
                if (isCapturingMove(board, i, j, &sumValue))
                    handleCapturingMove(newBoard, i, j, sumValue);
                else  
                    newBoard[i][j] = 1;

                simulateMoves(newBoard, turns - 1, finalSum);
            }
        }
    }
}

int main() {
    int turns;
    int board[BOARD_SIZE][BOARD_SIZE];
    unsigned int finalSum = 0;

    // Read input
    scanf("%d", &turns);
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    // Simulate all possible moves
    simulateMoves(board, turns, &finalSum);

    // Output the result
    printf("%u\n", finalSum);

    return 0;
}

