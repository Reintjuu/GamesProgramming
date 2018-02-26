﻿using System;

namespace Week2
{
	public class Vector
	{
		public float X { get; set; }
		public float Y { get; set; }

		public Vector(float x, float y)
		{
			X = x;
			Y = y;
		}

		public static Vector operator +(Vector first, Vector second)
		{
			return new Vector(first.X + second.X, first.Y + second.Y);
		}

		public override string ToString()
		{
			return $"X: {X}, Y: {Y}";
		}

		public double Theta()
		{
			return Math.Atan2(Y, X);
		}
	}
}