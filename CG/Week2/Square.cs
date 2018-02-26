using System.Collections.Generic;
using System.Drawing;

namespace Week2
{
	// Added in Lecture 3.1
	public class Square
	{
		public List<Vector> Vb { get; set; }
		
		private readonly Color _color;
		private readonly float _weight;

		public Square(Color color, int size = 100, float weight = 3)
		{
			_color = color;
			_weight = weight;

			Vb = new List<Vector>
			{
				new Vector(-size, -size),
				new Vector(size, -size),
				new Vector(size, size),
				new Vector(-size, size)
			};
		}

		public void Draw(Graphics g, List<Vector> vb)
		{
			var pen = new Pen(_color, _weight);
			g.DrawLine(pen, vb[0].X, vb[0].Y, vb[1].X, vb[1].Y);
			g.DrawLine(pen, vb[1].X, vb[1].Y, vb[2].X, vb[2].Y);
			g.DrawLine(pen, vb[2].X, vb[2].Y, vb[3].X, vb[3].Y);
			g.DrawLine(pen, vb[3].X, vb[3].Y, vb[0].X, vb[0].Y);
		}
	}
}