using System;
using System.Linq;
using System.Text;
using System.Threading;

namespace Week1.MazeGeneration
{
	public class Screen
	{
		private const int RedrawRefreshRateMs = 10;
		private const int WalkRefreshRateMs = 100;

		private const int XOffset = 5;
		private const int YOffset = 3;

		private StringBuilder[] _screen;
		private int _previousDotPositionX = -1;
		private int _previousDotPositionY = -1;

		public Screen()
		{
			Console.OutputEncoding = Encoding.UTF8;

			CreateScreen();
			DrawMaze();
		}

		private void CreateScreen()
		{
			_screen = new StringBuilder[Maze.Rows * (YOffset - 1) + 1];

			for (int y = 0; y < _screen.Length; y++)
			{
				_screen[y] = new StringBuilder();
				for (int x = 0; x < Maze.Columns * (XOffset - 1) + 1; x++)
				{
					_screen[y].Append("┼");
				}
			}

			for (int y = 0; y < Maze.Rows * (YOffset - 1); y += YOffset - 1)
			{
				for (int x = 0; x < Maze.Columns * (XOffset - 1); x += XOffset - 1)
				{
					_screen[y].Remove(x, XOffset).Insert(x, "┼───┼");
					_screen[y + 1].Remove(x, XOffset).Insert(x, "│   │");
					_screen[y + 2].Remove(x, XOffset).Insert(x, "┼───┼");
				}
			}
		}

		public void RemoveEdgeFromMaze(Edge edgeToRemove)
		{
			int edgeX = CoordinateHelpers.ConvertToX(edgeToRemove.SecondIndex);
			int edgeY = CoordinateHelpers.ConvertToY(edgeToRemove.SecondIndex);

			int linePositionX;
			int linePositionY;
			if (edgeToRemove.HasRightEdge())
			{
				linePositionX = edgeX * (XOffset - 1);
				linePositionY = edgeY * (YOffset - 1) + 1;
				_screen[linePositionY].Remove(linePositionX, 1).Insert(linePositionX, " ");
			}
			else if (edgeToRemove.HasBottomEdge())
			{
				linePositionX = edgeX * (XOffset - 1) + 1;
				linePositionY = edgeY * (YOffset - 1);
				_screen[linePositionY].Remove(linePositionX, 3).Insert(linePositionX, "   ");
			}

			DrawMaze(RedrawRefreshRateMs);
		}

		private void RemovePreviousDot()
		{
			if (_previousDotPositionX != -1 && _previousDotPositionY != -1)
			{
				_screen[_previousDotPositionY].Remove(_previousDotPositionX, 1).Insert(_previousDotPositionX, " ");
			}
		}

		public void AddDotToTile(int x, int y, bool removePrevious = false)
		{
			if (removePrevious)
			{
				RemovePreviousDot();
			}
			
			_previousDotPositionX = x * (XOffset - 1) + XOffset / 2;
			_previousDotPositionY = y * (YOffset - 1) + YOffset / 2;
			_screen[_previousDotPositionY].Remove(_previousDotPositionX, 1).Insert(_previousDotPositionX, "o");

			DrawMaze(WalkRefreshRateMs);
		}

		public void DrawMaze(int refreshRateMs = 0)
		{
			if (refreshRateMs > 0)
			{
				Thread.Sleep(refreshRateMs);
			}

			Console.SetCursorPosition(0, 0);
			Console.WriteLine(this);
		}

		public override string ToString()
		{
			return string.Join("\n", _screen.Select(x => x.ToString()));
		}
	}
}