using System.Collections.Generic;
using System.Linq;

namespace Week1.MazeGeneration
{
	public class MazeSolver
	{
		private readonly IEnumerable<Edge> _removedEdges;
		private readonly Screen _screen;

		private readonly bool[,] _visited;
		private readonly bool[,] _correctPath;
		private readonly int _startX, _startY, _endX, _endY;

		public MazeSolver(Screen screen, IEnumerable<Edge> removedEdges)
		{
			_screen = screen;
			_removedEdges = removedEdges;

			// Start at the end to prevent the animation from running backwards.
			_startX = Maze.Columns - 1;
			_startY = Maze.Rows - 1;
			_endX = 0;
			_endY = 0;

			_visited = new bool[Maze.Rows, Maze.Columns];
			_correctPath = new bool[Maze.Rows, Maze.Columns];
		}

		public bool Solve()
		{
			return RecursiveSolve(_startX, _startY);
		}

		private bool RecursiveSolve(int x, int y)
		{
			// If you've reached the end.
			if (x == _endX && y == _endY)
			{
				_screen.AddDotToTile(x, y);
				return true;
			}

			if (_visited[y, x])
			{
				return false;
			}

			// Mark current location.
			_visited[y, x] = true;

			// Checks if we're not on the left edge and checks if there is a removed edge left from this tile.
			if (x != 0 && HasRemovedRightEdge(x - 1, y))
			{
				// Recalls method one to the left.
				if (RecursiveSolve(x - 1, y))
				{
					_correctPath[y, x] = true;
					_screen.AddDotToTile(x, y);
					return true;
				}
			}

			// Checks if we're not on the right edge and checks if there is a removed edge right from this tile.
			if (x != Maze.Columns - 1 && HasRemovedRightEdge(x, y))
			{
				// Recalls method one to the right.
				if (RecursiveSolve(x + 1, y))
				{
					_correctPath[y, x] = true;
					_screen.AddDotToTile(x, y);
					return true;
				}
			}

			// Checks if we're not on the top edge and checks if there is a removed edge above this tile.
			if (y != 0 && HasRemovedBottomEdge(x, y - 1))
			{
				// Recalls method one up.
				if (RecursiveSolve(x, y - 1))
				{
					_correctPath[y, x] = true;
					_screen.AddDotToTile(x, y);
					return true;
				}
			}

			// Checks if we're not on the bottom edge and checks if there is a removed edge beneath this tile.
			if (y != Maze.Rows - 1 && HasRemovedBottomEdge(x, y))
			{
				// Recalls method one down.
				if (RecursiveSolve(x, y + 1))
				{
					_correctPath[y, x] = true;
					_screen.AddDotToTile(x, y);
					return true;
				}
			}

			return false;
		}

		private bool HasRemovedRightEdge(int x, int y)
		{
			int index = CoordinateHelpers.ConvertToIndex(x, y);
			return HasRemovedRightEdge(index);
		}

		private bool HasRemovedBottomEdge(int x, int y)
		{
			int index = CoordinateHelpers.ConvertToIndex(x, y);
			return HasRemovedBottomEdge(index);
		}

		private bool HasRemovedRightEdge(int index)
		{
			return _removedEdges
				.Where(e => e.FirstIndex == index)
				.Any(e => e.HasRightEdge());
		}

		private bool HasRemovedBottomEdge(int index)
		{
			return _removedEdges
				.Where(e => e.FirstIndex == index)
				.Any(e => e.HasBottomEdge());
		}
	}
}