using System.Collections.Generic;
using System.Data.SqlTypes;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace Week2
{
	public class Form1 : Form
	{
		private readonly AxisX _xAxis;
		private readonly AxisY _yAxis;
		private readonly Square _square;

		public Form1()
		{
			Width = 800;
			Height = 600;

			_xAxis = new AxisX(200);
			_yAxis = new AxisY(200);
			_square = new Square(Color.Purple, 100);
		}

		protected override void OnPaint(PaintEventArgs e)
		{
			var rotateMatrix = Matrix.Rotate(20);
			var scaleMatrix = Matrix.Scale(1.5f);
			
			base.OnPaint(e);

			var vb = ViewportTransformation(Width, Height, _xAxis.Vb);
			_xAxis.Draw(e.Graphics, vb);

			vb = ViewportTransformation(Width, Height, _yAxis.Vb);
			_yAxis.Draw(e.Graphics, vb);

			vb = ViewportTransformation(Width, Height, _square.Vb);
			_square.Draw(e.Graphics, vb);

			vb = new List<Vector>();
			foreach (var v in _square.Vb)
			{
				vb.Add(rotateMatrix * v);
			}
			
			vb = ViewportTransformation(Width, Height, vb);
			_square.Draw(e.Graphics, vb);
			
			vb = new List<Vector>();
			foreach (var v in _square.Vb)
			{
				vb.Add(scaleMatrix * v);
			}
			
			vb = ViewportTransformation(Width, Height, vb);
			_square.Draw(e.Graphics, vb);
		}

		private static List<Vector> ViewportTransformation(float width, float height, IEnumerable<Vector> vb)
		{
			float cx = width / 2;
			float cy = height / 2;
			return vb
				.Select(v => new Vector(v.X + cx, cy - v.Y))
				.ToList();
		}
	}
}