#pragma once
#include <iostream>

using namespace std;

struct List_Node
{
	int data;
	List_Node *next;
};

class Linked_List
{
public:
	Linked_List();
	~Linked_List();
	void delete_next(List_Node* pointer);
	void add(int value);
	void remove(int value);
	void print();
	List_Node * tail;
private:
	List_Node * head;
};

