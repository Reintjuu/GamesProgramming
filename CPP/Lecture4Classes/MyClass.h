#ifndef MY_CLASS_HEADER
#define MY_CLASS_HEADER

class MyClass
{
private:
	int x;
	int* p;

public:
	MyClass();
	MyClass(int a);
	MyClass(int a, int b);
	~MyClass();

	void print();
	void setX(int x);
	void setP(int value);
	void clearP();

};

#endif