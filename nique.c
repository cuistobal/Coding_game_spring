
static void method(int board[ROW_SIZE][COL_SIZE], int depth)
{
	int	row;
	int	col;

	if (depth > 0)
	{
		for (int i = 0; i < GRID_SIZE; i++)
		{
			row = i / ROW_SIZE;				
			col = i % COL_SIZE;				
			if (board[row][col] == 0)
			{
				try_capture();
			}
		}
	}
}

int main()
{

}
