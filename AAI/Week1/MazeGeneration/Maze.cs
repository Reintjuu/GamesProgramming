using System;
using System.Collections.Generic;

namespace Week1.MazeGeneration
{
	public class Maze
	{
		private readonly Screen _screen;
		
		// 33 Rows and 40 Columns works quite well for 1920x1080 default Windows consoles.
		public const int Rows = 33;
		public const int Columns = 40;

		private List<Edge> _removedEdges;

		public Maze()
		{
			_screen = new Screen();
			
			GenerateMaze();
			var solver = new MazeSolver(_screen, _removedEdges);
			solver.Solve();
		}

		private void GenerateMaze()
		{
			var rand = new Random();
			var set = new DisjointSets(Rows * Columns);

			var edges = CalculateEdges();
			_removedEdges = new List<Edge>();

			while (set.HasMultipleSets())
			{
				var edgeToRemove = edges[rand.Next(0, edges.Count)];
				edges.Remove(edgeToRemove);

				if (set.Find(edgeToRemove.FirstIndex) != set.Find(edgeToRemove.SecondIndex))
				{
					set.Union(edgeToRemove.FirstIndex, edgeToRemove.SecondIndex);
					_screen.RemoveEdgeFromMaze(edgeToRemove);
					_removedEdges.Add(edgeToRemove);
				}
			}
			
			_screen.DrawMaze();
		}

		private List<Edge> CalculateEdges()
		{
			var result = new List<Edge>();
			int i = 0;
			for (int y = 0; y < Rows; y++)
			{
				for (int x = 0; x < Columns; x++)
				{
					if (x < Columns - 1)
					{
						result.Add(new Edge(i, i + 1));
					}

					if (y < Rows - 1)
					{
						result.Add(new Edge(i, i + Columns));
					}

					i++;
				}
			}

			return result;
		}
	}
}