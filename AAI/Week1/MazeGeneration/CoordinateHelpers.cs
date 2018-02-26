namespace Week1.MazeGeneration
{
	public static class CoordinateHelpers
	{
		public static int ConvertToX(int index)
		{
			return index % Maze.Columns;
		}

		public static int ConvertToY(int index)
		{
			return index / Maze.Columns;
		}

		public static int ConvertToIndex(int x, int y)
		{
			return Maze.Columns * y + x;
		}
	}
}