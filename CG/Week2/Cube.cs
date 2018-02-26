using System.Collections.Generic;
using System.Drawing;

namespace Week2
{
	public class Cube
	{
		//          3----------2
		//         /|         /|
		//        / |        / |                z
		//       /  7-------/--6                |
		//      4--/-------1  /                 ----x
		//      | /        | /                 /
		//      |/         |/                  y
		//      8----------5

		private const int Size = 1;
		private readonly Color _color;

		public List<Vector> Vb = new List<Vector>
		{
			new Vector(1.0f, 1.0f, 1.0f), //1
			new Vector(1.0f, -1.0f, 1.0f), //2
			new Vector(-1.0f, -1.0f, 1.0f), //3
			new Vector(-1.0f, 1.0f, 1.0f), //4

			new Vector(1.0f, 1.0f, -1.0f), //5
			new Vector(1.0f, -1.0f, -1.0f), //6
			new Vector(-1.0f, -1.0f, -1.0f), //7
			new Vector(-1.0f, 1.0f, -1.0f), //8

			new Vector(1.2f, 1.2f, 1.2f), //1
			new Vector(1.2f, -1.2f, 1.2f), //2
			new Vector(-1.2f, -1.2f, 1.2f), //3
			new Vector(-1.2f, 1.2f, 1.2f), //4

			new Vector(1.2f, 1.2f, -1.2f), //5
			new Vector(1.2f, -1.2f, -1.2f), //6
			new Vector(-1.2f, -1.2f, -1.2f), //7
			new Vector(-1.2f, 1.2f, -1.2f) //8
		};

		public Cube(Color c)
		{
			_color = c;
		}

		public void Draw(Graphics g, List<Vector> vb)
		{
			Pen pen = new Pen(_color, 3f);
			g.DrawLine(pen, vb[0].X, vb[0].Y, vb[1].X, vb[1].Y); //1 -> 2
			g.DrawLine(pen, vb[1].X, vb[1].Y, vb[2].X, vb[2].Y); //2 -> 3
			g.DrawLine(pen, vb[2].X, vb[2].Y, vb[3].X, vb[3].Y); //3 -> 4
			g.DrawLine(pen, vb[3].X, vb[3].Y, vb[0].X, vb[0].Y); //4 -> 1

			g.DrawLine(pen, vb[4].X, vb[4].Y, vb[5].X, vb[5].Y); //5 -> 6
			g.DrawLine(pen, vb[5].X, vb[5].Y, vb[6].X, vb[6].Y); //6 -> 7
			g.DrawLine(pen, vb[6].X, vb[6].Y, vb[7].X, vb[7].Y); //7 -> 8
			g.DrawLine(pen, vb[7].X, vb[7].Y, vb[4].X, vb[4].Y); //8 -> 5

			//pen.DashStYle = DashStYle.DashDot;
			g.DrawLine(pen, vb[0].X, vb[0].Y, vb[4].X, vb[4].Y); //1 -> 5
			g.DrawLine(pen, vb[1].X, vb[1].Y, vb[5].X, vb[5].Y); //2 -> 6
			g.DrawLine(pen, vb[2].X, vb[2].Y, vb[6].X, vb[6].Y); //3 -> 7
			g.DrawLine(pen, vb[3].X, vb[3].Y, vb[7].X, vb[7].Y); //4 -> 8

			Font font = new Font("Arial", 12, FontStyle.Bold);
			for (int i = 0; i < 8; i++)
			{
				PointF p = new PointF(vb[i + 8].X, vb[i + 8].Y);
				g.DrawString(i.ToString(), font, Brushes.Black, p);
			}
		}
	}
}