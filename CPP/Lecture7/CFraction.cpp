#include "CFraction.h"

CFraction::CFraction()
{
	numerator = 0;
	denumerator = 1;
}

CFraction::CFraction(int n, int d)
{
	numerator = n;
	denumerator = d;
}

CFraction::~CFraction()
{
}

CFraction CFraction::operator*(const CFraction & f)
{
	int newNumerator = numerator * f.numerator;
	int newDenumerator = denumerator * f.denumerator;
	Simplify(newNumerator, newDenumerator);
	return CFraction(newNumerator, newDenumerator);
}

void CFraction::Simplify(int &n, int &d)
{
	int gcd = Functions::GreatestCommonDivisor(n, d);
	n /= gcd;
	d /= gcd;
}

CFraction operator*(const CFraction & f1, const CFraction f2)
{
	return CFraction();
}

ostream & operator<< (ostream & os, const CFraction & f)
{
	os << f.numerator << "/" << f.denumerator;
	return os;
}