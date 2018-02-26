#include "stdafx.h"
#include "Functions.h"
#include <iostream>

using namespace std;

void Functions::PrintArray(int a[])
{
	int size = sizeof(a);
	for (int i = 0; i < size; i++)
	{
		if (i != 0)
		{
			cout << ", ";
		}

		cout << a[i];
	}
	cout << endl;
}

int Functions::Sum(int a, int b)
{
	return a + b;
}

void Functions::PrintIsEven(int x)
{
	cout << x << " is " << ((x % 2 != 0) ? "un" : "") << "even" << endl;
}

int Functions::Power(int base, int exponent)
{
	if (exponent > 1)
	{
		return Power(base * base, exponent - 1);
	}

	return base;
}

bool Functions::IsPrime(int x)
{
	for (int i = x - 1; i > 1; i--)
	{
		if (x % i == 0)
		{
			return false;
		}
	}

	return true;
}

int Functions::IndexOf(int a[], int value)
{
	int size = sizeof(a);
	for (int i = 0; i < size; i++)
	{
		if (a[i] == value)
		{
			return i;
		}
	}

	return -1;
}

void Functions::BubbleSort(int* a, int size)
{
	int i, j;
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
			}
		}
	}
}

int Functions::GreatestCommonDivisor(int a, int b)
{
	if (b == 0)
	{
		return a;
	}

	return GreatestCommonDivisor(b, a % b);
}

int Functions::LeastCommonMultiple(int a, int b)
{
	int temp = GreatestCommonDivisor(a, b);

	return temp ? (a / temp * b) : 0;
}