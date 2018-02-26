using System;
using System.Linq;

namespace Week1
{
	class NQueens
	{
		private readonly bool[][] _board;
		private readonly int _n;

		public NQueens(int n)
		{
			_board = new bool[n][];
			for (int i = 0; i < n; i++)
			{
				_board[i] = new bool[n];
			}

			_n = n;

			SolveBacktracking();
		}

		private void SolveBacktracking(int row = 0)
		{
			if (CheckBoard())
			{
				if (CountQueens() == _n)
				{
					Print();
					return;
				}

				for (int i = 0; i < _n; i++)
				{
					_board[row][i] = true;
					SolveBacktracking(row + 1);
					_board[row][i] = false;
				}
			}
		}

		private int CountQueens()
		{
			return _board.Sum(line => line.Count(q => q));
		}

		private bool CheckBoard()
		{
			// iterate through all rows
			for (int r = 0; r < _n; r++)
			{
				int queenCol = -1;
				int nrOfQueens = 0;

				// check horizontally
				for (int c = 0; c < _n; c++)
				{
					if (_board[r][c])
					{
						nrOfQueens++;
						queenCol = c;
					}

					if (nrOfQueens > 1)
					{
						return false;
					}

					if (nrOfQueens > 0)
					{
						// check column
						for (int qr = r + 1; qr < _n; qr++) //start from next row
						{
							if (_board[qr][queenCol])
							{
								return false; // there is another queen on this column
							}
						}

						// check diagonal -> r
						int dc = queenCol + 1;
						for (int qr = r + 1; qr < _n && dc < _n; qr++) //start from next row
						{
							if (_board[qr][dc])
							{
								return false; // there is another queen on this column
							}

							dc++;
						}

						// check diagonal -> l
						dc = queenCol - 1;
						for (int qr = r + 1; qr < _n && dc >= 0; qr++) //start from next row
						{
							if (_board[qr][dc])
							{
								return false; // there is another queen on this column
							}

							dc--;
						}
					}
				}
			}

			return true;
		}

		private void Print()
		{
			for (int i = 0; i < _n; i++)
			{
				for (int j = 0; j < _n; j++)
				{
					string s = _board[i][j] ? "Q " : "- ";
					Console.Write(s);
				}

				Console.WriteLine();
			}

			Console.WriteLine();
		}
	}
}