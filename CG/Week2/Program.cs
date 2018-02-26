using System;
using System.Windows.Forms;

namespace Week2
{
	internal class Program
	{
		public static void Main(string[] args)
		{
			var v = new Vector(2, 5);
			var m = new Matrix(v);
			Console.WriteLine(m.ToVector());

			var f = new Form1();
			Application.Run(f);
		}
	}
}