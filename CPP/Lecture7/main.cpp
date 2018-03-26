#include "Fraction.h"
#include <iostream>

using namespace std;


void main()
{
	Fraction f1(3, 8), f2(4, 9), f3;
	cout << "* * *" << endl;
	cout << "f1: " << f1 << endl;
	cout << "f2: " << f2 << endl;
	cout << "f3: " << f3 << endl;

	f3.multiply(f1, f2);
	cout << "* * *   f3.multiply(f1, f2)" << endl;
	cout << "f1: " << f1 << endl;
	cout << "f2: " << f2 << endl;
	cout << "f3: " << f3 << endl;

	f3.add(f2);
	cout << "* * *   f3.add(f2)" << endl;
	cout << "f1: " << f1 << endl;
	cout << "f2: " << f2 << endl;
	cout << "f3: " << f3 << endl;

	f3 = f2;
	cout << "* * *   f3 = f2" << endl;
	cout << "f1: " << f1 << endl;
	cout << "f2: " << f2 << endl;
	cout << "f3: " << f3 << endl;

	f3 = f1*f2;
	cout << "* * *   f3 = f1*f2" << endl;
	cout << "f1: " << f1 << endl;
	cout << "f2: " << f2 << endl;
	cout << "f3: " << f3 << endl;

	f1 *= f3;
	cout << "* * *   f1 *= f3" << endl;
	cout << "f1: " << f1 << endl;
	cout << "f2: " << f2 << endl;
	cout << "f3: " << f3 << endl;

	f1 = f2 + f3;
	cout << "* * *   f1 = f2 + f3" << endl;
	cout << "f1: " << f1 << endl;
	cout << "f2: " << f2 << endl;
	cout << "f3: " << f3 << endl;

	f3 += f1;
	cout << "* * *   f3 += f1" << endl;
	cout << "f1: " << f1 << endl;
	cout << "f2: " << f2 << endl;
	cout << "f3: " << f3 << endl;

	cin.get();
}