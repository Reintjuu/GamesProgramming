#include <iostream>

using namespace std;

void printArray(int a[]);
int sum(int a, int b);
void printIsEven(int x);
int power(int base, int exponent);
bool isPrime(int x);
int indexOf(int a[], int value);
void bubbleSort(int * a, int size);
int greatestCommonDivisor(int a, int b);
int leastCommonMultiple(int a, int b);

int main()
{
	// 1.
	cout << sum(1, 2) << endl;

	// 2.
	printIsEven(1);
	printIsEven(2);

	// 3.
	cout << power(3, 2) << endl;

	// 4.
	cout << isPrime(15) << endl;

	// 5.
	int a[] = { 4, 3, 1, 2 };
	cout << indexOf(a, 3) << endl;

	// 6.
	bubbleSort(a, 4);
	printArray(a);

	// 7.
	cout << greatestCommonDivisor(1, 2) << endl;

	// 8.
	cout << leastCommonMultiple(1, 2) << endl;

	cin.get();
	return 0;
}

void printArray(int a[])
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

int sum(int a, int b)
{
	return a + b;
}

void printIsEven(int x)
{
	cout << x << " is " << ((x % 2 != 0) ? "un" : "") << "even" << endl;
}

int power(int base, int exponent)
{
	if (exponent > 1)
	{
		return power(base * base, exponent - 1);
	}

	return base;
}

bool isPrime(int x)
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

int indexOf(int a[], int value)
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

void bubbleSort(int* a, int size)
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

int greatestCommonDivisor(int a, int b)
{
	if (b == 0)
	{
		return a;
	}

	return greatestCommonDivisor(b, a % b);

}

int leastCommonMultiple(int a, int b)
{
	int temp = greatestCommonDivisor(a, b);

	return temp ? (a / temp * b) : 0;
}