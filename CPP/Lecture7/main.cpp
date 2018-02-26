#include <iostream>
#include "CFraction.h"

using namespace std;

int main()
{
	CFraction f1 = CFraction(50, 100);
	CFraction f2 = CFraction(100, 2000);
	cout << f1 << endl;
	cout << f2 << endl;

	f1 = f1 * f2;
	cout << f1 << endl;


	cin.get();
	return 0;
}