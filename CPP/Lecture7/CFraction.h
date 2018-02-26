#pragma once

using namespace std;
#include <iostream>
#include "Functions.h"

class CFraction
{
public:
	int numerator;
	int denumerator;

	CFraction();
	CFraction(int n, int d);
	~CFraction();
	CFraction operator*(const CFraction &f);
	friend CFraction operator * (const CFraction &f1, const CFraction f2);
	void Simplify(int &n, int &d);
};

ostream & operator<< (ostream & os, const CFraction & f);