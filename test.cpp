#include <vector>
#include <iostream>

#define COMBINATIONS 256

#define GRID_SIZE 9
#define ROW_SIZE 3
#define COL_SIZE 3

#define HASH 1073741824

#define MAX 6
#define STOP -1

#define DIRECTIONS 4
#define ITOT 2
#define IROW 0
#define ICOL 1

#define COMBINATIONS 256

#define CAP_HEURISTIC 10

//
void get_input(int *depth, std::vector<std::vector<int>>& board) 
{
    std::cin >> *depth;
    for (int i = 0; i < ROW_SIZE; i++)
	{
        for (int j = 0; j < COL_SIZE; j++)
            std::cin >> board[i][j];
    }
}

// CPP Implementation
int main()
{
    int turns;
    std::vector<std::vector<int>> board(ROW_SIZE, std::vector<int>(COL_SIZE));

    get_input(&turns, board);

    for (int i = 0; i < ROW_SIZE; i++)
	{
        for (int j = 0; j < COL_SIZE; j++)
		{
            std::cout << "Element at [" << i << "][" << j << "]: " << board[i][j] << std::endl;
            board[i][j] = 0;
        }
    }

    return 0;
}

