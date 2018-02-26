namespace Week1.MazeGeneration
{
	public class Edge
	{
		public int FirstIndex { get; }
		public int SecondIndex { get; }

		public Edge(int firstIndex, int secondIndex)
		{
			FirstIndex = firstIndex;
			SecondIndex = secondIndex;
		}

		public override string ToString()
		{
			return $"{FirstIndex}, {SecondIndex}";
		}
		
		public bool HasRightEdge()
		{
			return CoordinateHelpers.ConvertToY(FirstIndex) == CoordinateHelpers.ConvertToY(SecondIndex);
		}
		
		public bool HasBottomEdge()
		{
			return CoordinateHelpers.ConvertToX(FirstIndex) == CoordinateHelpers.ConvertToX(SecondIndex);
		}
	}
}