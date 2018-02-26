using System;
using System.Collections.Generic;
using System.Linq;

namespace Week1.MazeGeneration
{
	public class DisjointSets
	{
		private readonly int[] _setArray;

		public DisjointSets(int elementAmount = 10)
		{
			_setArray = new int[elementAmount];
			for (int i = 0; i < elementAmount; i++)
			{
				_setArray[i] = -1;
			}
		}

		public bool HasMultipleSets()
		{
			return _setArray.Count(x => x < 0) > 1;
		}

		public void Union(int first, int second)
		{
			int firstRoot = Find(first);
			int secondRoot = Find(second);

			// If second root is deeper.
			if (_setArray[secondRoot] < _setArray[firstRoot])
			{
				// Make the second root the new root.
				_setArray[firstRoot] = secondRoot;
			}
			else
			{
				// If the height is the same.
				if (_setArray[firstRoot] == _setArray[secondRoot])
				{
					// Decrease the first root's height.
					_setArray[firstRoot]--;
				}

				// Make the first root the new root.
				_setArray[secondRoot] = firstRoot;
			}
		}

		public int Find(int i)
		{
			if (i < 0 || i > _setArray.Length - 1)
			{
				throw new IndexOutOfRangeException();
			}

			if (_setArray[i] < 0)
			{
				return i;
			}

			return _setArray[i] = Find(_setArray[i]);
		}

		public override string ToString()
		{
			return string.Join("\t", _setArray.Select((value, index) => $"{index}: {value}"));
		}
	}
}