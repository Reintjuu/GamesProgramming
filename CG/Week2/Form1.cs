using System;
using System.Collections.Generic;
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
			_xAxis.Draw(e.Graphics, vb.ToList());

			// Draw Y-Axis.
			vb = ViewportTransformation(Width, Height, _yAxis.Vb);
			_yAxis.Draw(e.Graphics, vb.ToList());
			
			// Set the buffer to a transformed square.
			vb = ApplyTransformation(transformation, _square.Vb); 
			
			// Update the buffer for displaying based on the current viewport.
			vb = ViewportTransformation(Width, Height, vb);
			_square.Draw(e.Graphics, vb.ToList());
		}

		private IEnumerable<Vector> ApplyTransformation(Matrix transformation, IEnumerable<Vector> vb)
		{
			return vb.Select(v => transformation * v);
		}
		
		private static IEnumerable<Vector> ViewportTransformation(float width, float height, IEnumerable<Vector> vb)
		{
			return vb.Select(v => new Vector(v.X + width / 2, height / 2 - v.Y, 0));
		}

		private static IEnumerable<Vector> ViewportTransformation3D(IEnumerable<Vector> vb)
		{
			throw new NotImplementedException();
		}
	}
}