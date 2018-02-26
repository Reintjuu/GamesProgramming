using System.Collections.Generic;
using System.Data.SqlTypes;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace Week2
{
	public class Form1 : Form
	{
		private readonly XAxis _xAxis;
		private readonly YAxis _yAxis;
		private readonly Square _square;

		public Form1()
		{
			Width = 800;
			Height = 600;

			_xAxis = new XAxis(200);
			_yAxis = new YAxis(200);
			_square = new Square(Color.Purple);
		}

		protected override void OnPaint(PaintEventArgs e)
		{
			var t = Matrix.Translate(new Vector(100, 0, 0));
			var r = Matrix.RotateZ(20);
			var s = Matrix.Scale(1.5f);

			// First apply translation to avoid translation relative to the rotation or scale.
			var transformation = s * r * t;
			
			base.OnPaint(e);

			// Draw X-Axis.
			var vb = ViewportTransformation(Width, Height, _xAxis.Vb);
			_xAxis.Draw(e.Graphics, vb);

			// Draw Y-Axis.
			vb = ViewportTransformation(Width, Height, _yAxis.Vb);
			_yAxis.Draw(e.Graphics, vb);
			
			// Clear the buffer and apply transformation.
			vb = new List<Vector>();
			vb = ApplyTransformation(transformation, vb); 
			
			// Update the buffer for displaying based on the current viewport.
			vb = ViewportTransformation(Width, Height, vb);
			
			// Draw the square.
			_square.Draw(e.Graphics, vb);
		}

		private List<Vector> ApplyTransformation(Matrix transformation, List<Vector> vb)
		{
			foreach (var v in _square.Vb)
			{
				vb.Add(transformation * v);
			}

			return vb;
		}
		
		private static List<Vector> ViewportTransformation(float width, float height, IEnumerable<Vector> vb)
		{
			float cx = width / 2;
			float cy = height / 2;
			return vb
				.Select(v => new Vector(v.X + cx, cy - v.Y, 1))
				.ToList();
		}
	}
}