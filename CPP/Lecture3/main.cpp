#include <iostream>

using namespace std;

// make sure that 'p' is call by reference
// the address changes in the function and should change 
// in main() as well (comment from solution).
void create_array(int* &p, int n)
{
	p = new int[n];
	for (int i = 0; i < n; i++)
	{
		p[i] = i + 1;
	}
}

void pascals_triangle(int** &p, int n)
{
	int i, j;
	p = new int*[n];
	for (i = 0; i < n; i++)
	{
		p[i] = new int[i + 1];
		p[i][0] = 1;
		p[i][i] = 1;
		for (j = 1; j < i; j++)
			p[i][j] = p[i - 1][j - 1] + p[i - 1][j];
	}
}

int main()
{
	int *p, *q, *r;
	p = new int;
	q = new int;

	*p = 2;
	*q = 3;

	cout << *p << ", " << *q << endl;

	r = p;
	p = q;
	q = r;

	cout << *p << ", " << *q << endl;

	delete p;
	delete q;

	create_array(p, 5);
	for (int i = 0; i < 5; i++)
	{
		cout << p[i];
	}
	cout << endl;

	cin.get();
}