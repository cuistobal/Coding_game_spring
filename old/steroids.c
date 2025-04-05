#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROW_SIZE 3
#define COL_SIZE 3
#define MODULO 1073741824  // 2^30

typedef struct {
    int board[ROW_SIZE][COL_SIZE];
    int row;
    int col;
} State;

static const int neighbours[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// Function to compute the hash of the board state
int compute_hash(int board[ROW_SIZE][COL_SIZE]) {
    int hash = 0;
    for (int i = 0; i < ROW_SIZE; i++) {
        for (int j = 0; j < COL_SIZE; j++) {
            hash = (hash * 10) + board[i][j];
        }
    }
    return hash;
}

// Function to check if a position is within bounds
bool is_valid_position(int row, int col) {
    return (row >= 0 && row < ROW_SIZE && col >= 0 && col < COL_SIZE);
}

// Function to check for capturing placements
bool can_capture(int board[ROW_SIZE][COL_SIZE], int row, int col, int *capture_sum) {
    int sum = 0;
    int count = 0;
    for (int dir = 0; dir < 4; dir++) {
        int new_row = row + neighbours[dir][0];
        int new_col = col + neighbours[dir][1];
        if (is_valid_position(new_row, new_col) && board[new_row][new_col] > 0) {
            sum += board[new_row][new_col];
            count++;
        }
    }
    if (count >= 2 && sum <= 6) {
        *capture_sum = sum;
        return true;
    }
    return false;
}

// Function to simulate placing a die on the board
void simulate_moves(int initial_board[ROW_SIZE][COL_SIZE], int turns) {
    State stack[ROW_SIZE * COL_SIZE * turns];
    int stack_top = 0;
    int hash_sum = 0;

    // Initialize the stack with the initial board state
    for (int i = 0; i < ROW_SIZE; i++) {
        for (int j = 0; j < COL_SIZE; j++) {
            if (initial_board[i][j] == 0) {
                stack[stack_top].row = i;
                stack[stack_top].col = j;
                for (int r = 0; r < ROW_SIZE; r++) {
                    for (int c = 0; c < COL_SIZE; c++) {
                        stack[stack_top].board[r][c] = initial_board[r][c];
                    }
                }
                stack_top++;
            }
        }
    }

    while (stack_top > 0) {
        stack_top--;
        State current = stack[stack_top];
        int row = current.row;
        int col = current.col;

        if (current.board[row][col] == 0) {
            int capture_sum = 0;
            if (can_capture(current.board, row, col, &capture_sum)) {
                // Capturing placement
                current.board[row][col] = capture_sum;
                // Remove captured dice
                for (int dir = 0; dir < 4; dir++) {
                    int new_row = row + neighbours[dir][0];
                    int new_col = col + neighbours[dir][1];
                    if (is_valid_position(new_row, new_col) && current.board[new_row][new_col] > 0) {
                        current.board[new_row][new_col] = 0;
                    }
                }
            } else {
                // Non-capturing placement
                current.board[row][col] = 1;
            }

            // Compute hash and add to sum
            hash_sum = (hash_sum + compute_hash(current.board)) % MODULO;

            // Push new states onto the stack
            for (int i = 0; i < ROW_SIZE; i++) {
                for (int j = 0; j < COL_SIZE; j++) {
                    if (current.board[i][j] == 0) {
                        stack[stack_top].row = i;
                        stack[stack_top].col = j;
                        for (int r = 0; r < ROW_SIZE; r++) {
                            for (int c = 0; c < COL_SIZE; c++) {
                                stack[stack_top].board[r][c] = current.board[r][c];
                            }
                        }
                        stack_top++;
                    }
                }
            }
        }
    }

    printf("%d\n", hash_sum);
}

// Function to read input
void read_input(int board[ROW_SIZE][COL_SIZE], int *turns) {
    scanf("%d", turns);
    for (int i = 0; i < ROW_SIZE; i++) {
        for (int j = 0; j < COL_SIZE; j++) {
            scanf("%d", &board[i][j]);
        }
    }
}

int main() {
    int board[ROW_SIZE][COL_SIZE];
    int turns;
    read_input(board, &turns);
    simulate_moves(board, turns);
    return 0;
}

