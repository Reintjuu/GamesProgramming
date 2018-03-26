#ifndef FRACTION_HEADER
#define FRACTION_HEADER

#include <string>
#include <iostream>
using namespace std;



class Fraction
{
private:
	int numerator;
	int denumerator;

public:
	Fraction();
	Fraction(int n, int d);
	~Fraction();

	string to_string() const;
	void simplify();
	void multiply(const Fraction f);
	void multiply(const Fraction f1, const Fraction f2);
	void add(const Fraction f);
	void add(const Fraction f1, const Fraction f2);

	Fraction & operator= (const Fraction & f);
	Fraction & operator*=(const Fraction & f);
	friend Fraction operator* (const Fraction &f1, const Fraction & f2);
	Fraction & operator+=(const Fraction & f);
	friend Fraction operator+ (const Fraction &f1, const Fraction & f2);
};


ostream & operator<< (ostream & os, const Fraction & f);


#endif