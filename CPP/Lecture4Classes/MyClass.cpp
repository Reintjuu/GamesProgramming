#include "MyClass.h"
#include <iostream>

using namespace std;


MyClass::MyClass()
{
	x = 0;
	p = NULL;
}


MyClass::MyClass(int a)
{
	x = a;
	p = NULL;
}


MyClass::MyClass(int a, int b)
{
	x = a;
	p = new int;
	*p = b;
}


MyClass::~MyClass()
{
	if (p != NULL)
		delete p;
}


void MyClass::print()
{
	cout << "(" << x << ", ";
	if (p == NULL)
		cout << "-";
	else
		cout << *p;
	cout << ")" << endl;
}


void MyClass::setX(int x)
{
	this->x = x;
}


void MyClass::setP(int value)
{
	if (p == NULL)
		p = new int;
	*p = value;
}


void MyClass::clearP()
{
	if (p != NULL)
	{
		delete p;
		p = NULL;
	}
}