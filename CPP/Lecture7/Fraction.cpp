#include "Fraction.h"
#include <iostream>
#include <string>

using namespace std;


Fraction::Fraction()
{
	numerator = 0;
	denumerator = 1;
}

Fraction::Fraction(int n, int d)
{
	numerator = n;
	if (d != 0)
		denumerator = d;
	else
		denumerator = 1;
}

Fraction::~Fraction()
{}

string Fraction::to_string() const
{
	string result = std::to_string(numerator) + " / " + std::to_string(denumerator);
	return result;
}


int gcd(int a, int b)
{
	int temp;
	while (b != 0)
	{
		temp = a%b;
		a = b;
		b = temp;
	}
	return a;
}


void Fraction::simplify()
{
	int factor = gcd(numerator, denumerator);
	numerator /= factor;
	denumerator /= factor;
}

void Fraction::multiply(const Fraction f)
{
	numerator *= f.numerator;
	denumerator *= f.denumerator;
	simplify();
}

void Fraction::multiply(const Fraction f1, const Fraction f2)
{
	numerator = f1.numerator * f2.numerator;
	denumerator = f1.denumerator * f2.denumerator;
	simplify();
}

void Fraction::add(const Fraction f)
{
	numerator = numerator * f.denumerator + f.numerator * denumerator;
	denumerator *= f.denumerator;
	simplify();
}


void Fraction::add(const Fraction f1, const Fraction f2)
{
	numerator = f1.numerator * f2.denumerator + f2.numerator * f1.denumerator;
	denumerator *= f1.denumerator * f2.denumerator;
	simplify();
}



Fraction & Fraction::operator= (const Fraction & f)
{
	if (this == &f)
		return *this;
	this->numerator = f.numerator;
	this->denumerator = f.denumerator;

	return *this;
}

Fraction& Fraction::operator*=(const Fraction & f)
{
	multiply(f);
	return *this;
}

Fraction operator* (const Fraction &f1, const Fraction & f2)
{
	Fraction result;
	result.multiply(f1, f2);
	return result;
}

Fraction& Fraction::operator+=(const Fraction & f)
{
	add(f);
	return *this;
}

Fraction operator+ (const Fraction &f1, const Fraction & f2)
{
	Fraction result;
	result.add(f1, f2);
	return result;
}

ostream & operator<< (ostream & os, const Fraction & f)
{
	os << f.to_string();
	return os;
}

