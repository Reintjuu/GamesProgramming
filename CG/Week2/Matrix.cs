using System;
using System.Linq;

namespace Week2
{
	public class Matrix
	{
		private readonly float[,] _matrix;

		public int Height => _matrix.GetLength(0);
		public int Width => _matrix.GetLength(1);

		public float this[int y, int x]
		{
			get => _matrix[y, x];
			set => _matrix[y, x] = value;
		}

		public Matrix()
		{
			_matrix = Identity()._matrix;
		}

		public Matrix(float[,] matrix)
		{
			_matrix = matrix;
		}

		public Matrix(float m11, float m12, float m21, float m22)
		{
			_matrix = new float[2, 2];
			_matrix[0, 0] = m11;
			_matrix[0, 1] = m12;
			_matrix[1, 0] = m21;
			_matrix[1, 1] = m22;

			Console.WriteLine(this);
		}

		public Matrix(Vector v) : this(v.X, 0, v.Y, 0)
		{
		}

		public Vector ToVector()
		{
			return new Vector(_matrix[0, 0], _matrix[1, 0]);
		}

		public static Matrix operator +(Matrix m1, Matrix m2)
		{
			if (m1.Height != m2.Height ||
			    m1.Width != m2.Width)
			{
				throw new ArgumentException("Inconsistent matrix dimension.");
			}

			var result = new float[m1.Height, m1.Width];
			for (int row = 0; row < m1.Height; row++)
			{
				for (int column = 0; column < m1.Width; column++)
				{
					result[row, column] = m1[row, column] + m2[row, column];
				}
			}

			return new Matrix(result);
		}

		public static Matrix operator -(Matrix m1, Matrix m2)
		{
			if (m1.Height != m2.Height ||
			    m1.Width != m2.Width)
			{
				throw new ArgumentException("Inconsistent matrix dimension.");
			}

			var result = new float[m1.Height, m1.Width];
			for (int row = 0; row < m1.Height; row++)
			{
				for (int column = 0; column < m1.Width; column++)
				{
					result[row, column] = m1[row, column] + m2[row, column];
				}
			}

			return new Matrix(result);
		}

		public static Matrix operator *(Matrix m1, float f)
		{
			var result = new float[m1.Width, m1.Height];
			for (int x = 0; x < m1.Width; x++)
			{
				for (int y = 0; y < m1.Height; y++)
				{
					result[y, x] = m1[y, x] * f;
				}
			}

			return new Matrix(result);
		}

		public static Matrix operator *(float f, Matrix m1)
		{
			return m1 * f;
		}

		public static Matrix operator *(Matrix m1, Matrix m2)
		{
			if (m1.Width != m2.Height)
			{
				throw new ArgumentException(
					"Number of columns in First Matrix should be equal to Number of rows in Second Matrix.");
			}

			var result = new float[m1.Height, m2.Width];
			for (int i = 0; i < result.GetLength(0); i++)
			{
				for (int j = 0; j < result.GetLength(1); j++)
				{
					result[i, j] = 0;
					for (int k = 0; k < m1.Width; k++)
					{
						result[i, j] = result[i, j] + m1[i, k] * m2[k, j];
					}
				}
			}

			return new Matrix(result);
		}

		public static Vector operator *(Matrix m1, Vector v)
		{
			return (m1 * new Matrix(v)).ToVector();
		}

		public static Matrix Identity()
		{
			return new Matrix(1f, 0f, 0f, 1f);
		}

		public static Matrix Scale(float s)
		{
			return s * Identity();
		}

		public static Matrix Rotate(float degrees)
		{
			var rad = Math.PI / 180 * degrees;
			return new Matrix(
				(float) Math.Cos(rad), -(float) Math.Sin(rad),
				(float) Math.Sin(rad), (float) Math.Cos(rad));
		}

		public override string ToString()
		{
			return string.Join(Environment.NewLine, _matrix
				.OfType<float>()
				.Select((value, index) => new {value, index})
				.GroupBy(x => x.index / Width, x => x.value, (i, floats) => $"{{{string.Join(",", floats)}}}"));
		}
	}
}