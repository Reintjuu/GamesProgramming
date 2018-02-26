using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace Week2
{
	public sealed class Form1 : Form
	{
		private readonly XAxis _xAxis;
		private readonly YAxis _yAxis;
		private readonly ZAxis _zAxis;
		private readonly Cube _cube;

		private Matrix _rotation;
		private Matrix _scale;
		private Matrix _translation;

		public Form1()
		{
			Width = 800;
			Height = 600;
			DoubleBuffered = true;
			
			KeyPreview = true;
			KeyDown += Form1_KeyDown;

			_scale = Matrix.Identity();
			_rotation = Matrix.Identity();
			_translation = Matrix.Identity();

			_xAxis = new XAxis(3);
			_yAxis = new YAxis(3);
			_zAxis = new ZAxis(3);
			_cube = new Cube(Color.Purple);
		}

		protected override void OnPaint(PaintEventArgs e)
		{
			// Lastly apply translation to avoid translation relative to the rotation or scale.
			var transformation = _translation * _rotation * _scale;

			base.OnPaint(e);

			// Draw X-Axis.
			var vb = ViewportTransformation3D(Width, Height, _xAxis.Vb);
			_xAxis.Draw(e.Graphics, vb.ToList());

			// Draw Y-Axis.
			vb = ViewportTransformation3D(Width, Height, _yAxis.Vb);
			_yAxis.Draw(e.Graphics, vb.ToList());

			// Draw Z-Axis.
			vb = ViewportTransformation3D(Width, Height, _zAxis.Vb);
			_zAxis.Draw(e.Graphics, vb.ToList());

			vb = _cube.Vb;
			vb = ApplyTransformation(transformation, vb);
			vb = ViewportTransformation3D(Width, Height, vb);

			_cube.Draw(e.Graphics, vb.ToList());
		}

		private static IEnumerable<Vector> ApplyTransformation(Matrix transformation, IEnumerable<Vector> vb)
		{
			return vb.Select(v => transformation * v);
		}

		private static IEnumerable<Vector> ViewportTransformation(float width, float height, IEnumerable<Vector> vb)
		{
			return vb.Select(v => new Vector(v.X + width / 2, height / 2 - v.Y, 0));
		}

		private static IEnumerable<Vector> ViewportTransformation3D(float width, float height, IEnumerable<Vector> vb)
		{
			return vb.Select(v =>
			{
				var viewMatrix = Matrix.View(10, -100, -10) * v;
				var projectionMatrix = Matrix.Projection(800, viewMatrix.Z) * viewMatrix;
				return new Vector(projectionMatrix.X + width / 2, projectionMatrix.Y + height / 2, 0);
			});
		}

		private void Form1_KeyDown(object sender, KeyEventArgs e)
		{
			int modifier = e.Modifiers == Keys.Shift ? -1 : 1;
			switch (e.KeyCode)
			{
				case Keys.Left:
					_translation *= Matrix.Translate(new Vector(0f, -.1f, 0f));
					break;
				case Keys.Right:
					_translation *= Matrix.Translate(new Vector(0f, .1f, 0f));
					break;
				case Keys.Up:
					_translation *= Matrix.Translate(new Vector(-.1f, 0f, 0f));
					break;
				case Keys.Down:
					_translation *= Matrix.Translate(new Vector(.1f, 0f, 0f));
					break;
				case Keys.PageUp:
					_translation *= Matrix.Translate(new Vector(0f, 0f, -.1f));
					break;
				case Keys.PageDown:
					_translation *= Matrix.Translate(new Vector(0f, 0f, .1f));
					break;
				case Keys.X:
					_rotation *= Matrix.RotateX(5 * modifier);
					break;
				case Keys.Y:
					_rotation *= Matrix.RotateY(5 * modifier);
					break;
				case Keys.Z:
					_rotation *= Matrix.RotateZ(5 * modifier);
					break;
				case Keys.S:
					var s = e.Modifiers == Keys.Shift ? .9f : 1.1f;
					_scale *= Matrix.Scale(s);
					break;
				case Keys.C:
					_translation = _rotation = _scale = Matrix.Identity();
					break;
			}

			Invalidate();
		}
	}
}