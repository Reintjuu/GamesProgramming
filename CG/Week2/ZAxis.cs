using System.Collections.Generic;
using System.Drawing;

namespace Week2
{
	public class ZAxis
	{
		public List<Vector> Vb { get; set; }

		public ZAxis(int size = 100)
		{
			Vb = new List<Vector>
			{
				new Vector(0, 0, 0),
				new Vector(0, 0, size)
			};
		}

		public void Draw(Graphics g, List<Vector> vb)
		{
			Pen pen = new Pen(Color.Blue, 2f);
			g.DrawLine(pen, vb[0].X, vb[0].Y, vb[1].X, vb[1].Y);
			Font font = new Font("Arial", 10);
			PointF p = new PointF(vb[1].X, vb[1].Y);
			g.DrawString("z", font, Brushes.Blue, p);
		}
	}
}