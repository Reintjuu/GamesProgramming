#include <iostream>
#include "MyClass.h"

using namespace std;


int main()
{
	int i;

	// first, create two instances of MyClass, one with the default constructor
	// and one with the overloaded constructor
	MyClass thing1;
	MyClass thing2(2, 3);
	// and print them to see they are fine
	cout << "Two instances: " << endl;
	thing1.print();
	thing2.print();



	// it is also possible to create an array of MyClass elements:
	MyClass list[3];
	for (i = 0; i < 3; i++)
	{
		list[i].setX(i);
		list[i].setP(i * 2);
	}

	// One can call the members of each instance in the array 
	// by using the dot-operator. See the next code as an example
	// to print each element in the array.
	// Notice they are all set with the default constructor (0,0)
	cout << endl << "Print each element of the array:" << endl;
	for (i = 0; i < 3; i++)
		list[i].print();



	// It is also possible to create a pointer to a MyClass object:
	MyClass* pointer;
	
	// This pointer does not yet point to an object. You need to 
	// create that first, by allocating space for it. You can use
	// any constructor that you like:
	pointer = new MyClass(4, 5);

	// Now, to access a member through a pointer, you cannot use the 
	// dot operator. You need to use the arrow operator: 
	pointer->clearP();
	cout << endl << "Print the element where the pointer points at:" << endl;
	pointer->print();

	// When you're done with such object, you need to delete it:
	delete pointer;



	// Finally, it is possible to use the pointer to create an array 
	// of MyClass elements:
	pointer = new MyClass[4];

	// Now, pay close attention. The elements in this array are
	// actual instances and not pointers to instances. Thus, to reach 
	// a member of such element, one needs to use the dot operator:
	cout << endl << "Print the array elements of the pointer:" << endl; 
	for (i = 0; i < 4; i++)
		pointer[i].print();

	// To clean up an array of elements created from a pointer,
	// one needs to use the 'delete[]' command:
	delete[] pointer;

	cin.get();
}