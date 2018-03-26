#include "MyStack.h"
#include <iostream>

using namespace std;


MyStack::MyStack()
{
	top = NULL;
}


MyStack::~MyStack()
{
	Block* pointer = top;
	while (top != NULL)
	{
		top = top->next;
		delete pointer;
		pointer = top;
	}
}


bool MyStack::is_empty()
{
	return (top == NULL);
}


void MyStack::print()
{
	Block* pointer = top;
	cout << "* * * The Stack * * *" << endl;
	while (pointer != NULL)
	{
		cout << pointer->number << endl;
		pointer = pointer->next;
	}
}


void MyStack::push(int value)
{
	Block* pointer = new Block;
	pointer->number = value;
	pointer->next = top;
	top = pointer;
}


int MyStack::pop()
{
	if (is_empty())
		return 0;
	int result = top->number;
	Block* pointer = top;
	top = top->next;
	return result;
}


int MyStack::size()
{
	int size = 0;
	Block* pointer = top;
	while (pointer != NULL)
	{
		size++;
		pointer = pointer->next;
	}
	return size;
}


int calculate_size(Block* pointer)
{
	if (pointer == NULL)
		return 0;
	return 1 + calculate_size(pointer->next);
}


int MyStack::size_recursive()
{
	return (calculate_size(top));
}


int MyStack::sum()
{
	int sum = 0;
	Block* pointer = top;
	while (pointer != NULL)
	{
		sum += pointer->number;
		pointer = pointer->next;
	}
	return sum;
}


int calculate_sum(Block* pointer)
{
	if (pointer == NULL)
		return 0;
	return pointer->number + calculate_sum(pointer->next);
}


int MyStack::sum_recursive()
{
	return (calculate_sum(top));
}

