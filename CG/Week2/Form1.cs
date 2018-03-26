using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace Week2
{
	public sealed class Form1 : Form
	{
		public const float StartR = 10;
		public const float StartTheta = -100f;
		public const float StartPhi = -10f;

		public float R;
		public float D;
		public float Theta;
		public float Phi;

		public Matrix RotationMatrix;
		public Matrix ScaleMatrix;
		public Matrix TranslationMatrix;

		private readonly XAxis _xAxis;
		private readonly YAxis _yAxis;
		private readonly ZAxis _zAxis;
		private readonly Cube _cube;
		private readonly Animator _animator;
		private float _currentScale;

		public Form1()
		{
			Text = "Reinier";
			Width = 800;
			Height = 600;
			DoubleBuffered = true;

			KeyPreview = true;
			KeyDown += OnKeyDown;

			_xAxis = new XAxis(3);
			_yAxis = new YAxis(3);
			_zAxis = new ZAxis(3);
			_cube = new Cube(Color.Purple);

			_animator = new Animator(this);

			SetInitialValues();
		}

		private void SetInitialValues()
		{
			ScaleMatrix = Matrix.Identity();
			RotationMatrix = Matrix.Identity();
			TranslationMatrix = Matrix.Identity();
			_currentScale = 1;

			R = StartR;
			D = 800;
			Theta = StartTheta;
			Phi = StartPhi;
		}

		protected override void OnPaint(PaintEventArgs e)
		{
			// Lastly apply translation to avoid translation relative to the rotation or scale.
			var transformation = TranslationMatrix * RotationMatrix * ScaleMatrix;

			base.OnPaint(e);
			e.Graphics.DrawString(ToString(), new Font("Comic Sans MS", 16), Brushes.Chocolate, 10, 10);

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

		private IEnumerable<Vector> ViewportTransformation3D(float width, float height, IEnumerable<Vector> vb)
		{
			return vb.Select(v =>
			{
				Vector view = Matrix.View(R, Theta, Phi) * v;
				Vector projectionView = Matrix.Projection(D, view.Z) * view;
				return new Vector(projectionView.X + width / 2, -projectionView.Y + height / 2, 0);
			});
		}

		private void OnKeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.C)
			{
				SetInitialValues();
				_animator.ResetAnimation();
			}

			if (_animator.IsAnimating)
			{
				return;
			}

			int modifier = e.Modifiers == Keys.Shift ? -1 : 1;
			switch (e.KeyCode)
			{
				case Keys.Left:
					TranslationMatrix *= Matrix.Translate(new Vector(-.1f, 0f, 0f));
					break;
				case Keys.Right:
					TranslationMatrix *= Matrix.Translate(new Vector(.1f, 0f, 0f));
					break;
				case Keys.Up:
					TranslationMatrix *= Matrix.Translate(new Vector(0, .1f, 0f));
					break;
				case Keys.Down:
					TranslationMatrix *= Matrix.Translate(new Vector(0f, -.1f, 0f));
					break;
				case Keys.PageUp:
					TranslationMatrix *= Matrix.Translate(new Vector(0f, 0f, -.1f));
					break;
				case Keys.PageDown:
					TranslationMatrix *= Matrix.Translate(new Vector(0f, 0f, .1f));
					break;
				case Keys.X:
					RotationMatrix *= Matrix.RotateX(5 * modifier);
					break;
				case Keys.Y:
					RotationMatrix *= Matrix.RotateY(5 * modifier);
					break;
				case Keys.Z:
					RotationMatrix *= Matrix.RotateZ(5 * modifier);
					break;
				case Keys.S:
					_currentScale += modifier * .01f;
					ScaleMatrix = Matrix.Scale(_currentScale);
					break;
				case Keys.A:
					SetInitialValues();
					_animator.StartAnimation();
					break;
				case Keys.R:
					R += modifier * 1;
					break;
				case Keys.D:
					D += modifier * 1;
					break;
				case Keys.P:
					Phi += modifier * 1;
					break;
				case Keys.T:
					Theta += modifier * 1;
					break;
			}

			Invalidate();
		}

		public override string ToString()
		{
			return $"r:\t{R}\n" +
			       $"d:\t{D}\n" +
			       $"phi:\t{Phi}\n" +
			       $"theta:\t{Theta}\n\n" +
			       $"Phase:\t{_animator.Phase / 2 + 1}";
		}
	}
}