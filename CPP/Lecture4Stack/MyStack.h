#ifndef MY_STACK_HEADER
#define MY_STACK_HEADER

struct Block
{
	int number;
	Block* next;
};

class MyStack
{
private:
	Block* top;

public:
	MyStack();
	~MyStack();

	bool is_empty();
	void print();
	void push(int value);
	int pop();
	int size();
	int size_recursive();
	int sum();
	int sum_recursive();
};



#endif