using System;
using Week1.MazeGeneration;

namespace Week1
{
	class Program
	{
		static void Main(string[] args)
		{
			// new NQueens(4);
			
			Console.CursorVisible = false;
			new Maze();
			Console.CursorVisible = true;
		}
	}
}