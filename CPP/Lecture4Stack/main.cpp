#include "MyStack.h"
#include <iostream>

using namespace std;


void main()
{
	MyStack stack;
	stack.push(8);
	stack.push(6);
	stack.push(7);
	stack.push(5);
	stack.push(3);
	stack.push(0);
	stack.push(9);

	stack.print();
	cout << "The size is: " << stack.size() << endl;
	cout << "The sum is: " << stack.sum() << endl;

	cout << "Popping: " << stack.pop() << endl;
	cout << "Popping: " << stack.pop() << endl;
	cout << "Popping: " << stack.pop() << endl;

	stack.print();
	cout << "The size is: " << stack.size_recursive() << endl;
	cout << "The sum is: " << stack.sum_recursive() << endl;

	stack.push(11);
	stack.push(13);

	stack.print();

	cout << "Popping: " << stack.pop() << endl;
	cout << "Popping: " << stack.pop() << endl;
	cout << "Popping: " << stack.pop() << endl;
	cout << "Popping: " << stack.pop() << endl;
	cout << "Popping: " << stack.pop() << endl;
	cout << "Popping: " << stack.pop() << endl;
	cout << "Popping: " << stack.pop() << endl;
	cout << "Popping: " << stack.pop() << endl;
	cout << "Popping: " << stack.pop() << endl;

	stack.print();
	cout << "The size is: " << stack.size_recursive() << endl;
	cout << "The sum is: " << stack.sum_recursive() << endl;

}