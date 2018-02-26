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

		public Matrix(
			float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44)
		{
			_matrix = new float[4, 4];
			_matrix[0, 0] = m11;
			_matrix[0, 1] = m12;
			_matrix[0, 2] = m13;
			_matrix[0, 3] = m14;

			_matrix[1, 0] = m21;
			_matrix[1, 1] = m22;
			_matrix[1, 2] = m23;
			_matrix[1, 3] = m24;

			_matrix[2, 0] = m31;
			_matrix[2, 1] = m32;
			_matrix[2, 2] = m33;
			_matrix[2, 3] = m34;

			_matrix[3, 0] = m41;
			_matrix[3, 1] = m42;
			_matrix[3, 2] = m43;
			_matrix[3, 3] = m44;
		}

		public Matrix(Vector v) : this(v.X, 0, 0, 0, v.Y, 0, 0, 0, v.Z, 0, 0, 0, v.W, 0, 0, 0)
		{
		}

		public Vector ToVector()
		{
			return new Vector(_matrix[0, 0], _matrix[1, 0], _matrix[2, 0]);
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
			return new Matrix(
				1f, 0f, 0f, 0f,
				0f, 1f, 0f, 0f,
				0f, 0f, 1f, 0f,
				0f, 0f, 0f, 1f);
		}

		public static Matrix Scale(float s)
		{
			return s * Identity();
		}

		public static Matrix RotateX(float degrees)
		{
			double radians = Math.PI / 180 * degrees;
			float cos = (float) Math.Cos(radians);
			float sin = (float) Math.Sin(radians);

			return new Matrix(
				1f, 0f, 0f, 0f,
				0f, cos, -sin, 0f,
				0f, sin, cos, 0f,
				0f, 0f, 0f, 1f);
		}

		public static Matrix RotateY(float degrees)
		{
			double radians = Math.PI / 180 * degrees;
			float cos = (float) Math.Cos(radians);
			float sin = (float) Math.Sin(radians);

			return new Matrix(
				cos, 0f, sin, 0f,
				0, 1, 0f, 0f,
				-sin, 0f, cos, 0f,
				0f, 0f, 0f, 1f);
		}

		public static Matrix RotateZ(float degrees)
		{
			double radians = Math.PI / 180 * degrees;
			float cos = (float) Math.Cos(radians);
			float sin = (float) Math.Sin(radians);

			return new Matrix(
				cos, -sin, 0f, 0f,
				sin, cos, 0f, 0f,
				0f, 0f, 1f, 0f,
				0f, 0f, 0f, 1f);
		}

		public static Matrix Translate(Vector t)
		{
			return new Matrix(
				1f, 0f, 0f, t.X,
				0f, 1f, 0f, t.Y,
				0f, 0f, 1f, t.Z,
				0f, 0f, 0f, 1f);
		}

		public static Matrix View(float r, float theta, float phi)
		{
			float cosTheta = (float) Math.Cos(theta);
			float sinTheta = (float) Math.Sin(theta);
			float cosPhi = (float) Math.Cos(phi);
			float sinPhi = (float) Math.Sin(phi);

			return new Matrix(
				-sinTheta, cosTheta, 0f, 0f,
				-cosTheta * cosPhi, -cosPhi * sinTheta, sinPhi, 0f,
				cosTheta * sinPhi, sinTheta * sinPhi, cosPhi, -r,
				0f, 0f, 0f, 1f);
		}

		public static Matrix Projection(float d, float z)
		{
			float p = -(d / z);
			return new Matrix(
				p, 0f, 0f, 0f,
				0f, p, 0f, 0f,
				0f, 0f, 0f, 0f,
				0f, 0f, 0f, 0f);
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