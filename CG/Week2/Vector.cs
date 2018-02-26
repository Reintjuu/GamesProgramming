using System;

namespace Week2
{
	public class Vector
	{
		public float X { get; set; }
		public float Y { get; set; }
		public float Z { get; set; }
		public float W { get; set; }

		public Vector(float x, float y, float z)
		{
			X = x;
			Y = y;
			Z = z;
			W = 1;
		}

		public static Vector operator +(Vector first, Vector second)
		{
			return new Vector(first.X + second.X, first.Y + second.Y, first.Z + second.Z);
		}

		public override string ToString()
		{
			return $"X: {X}, Y: {Y}, Z: {Z}, W: {W}";
		}

		public double Theta()
		{
			return Math.Atan2(Y, X);
		}
	}
}