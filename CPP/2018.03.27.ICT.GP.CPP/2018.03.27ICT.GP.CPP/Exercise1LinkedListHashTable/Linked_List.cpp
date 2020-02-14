#include "Linked_List.h"


Linked_List::Linked_List()
{
	head = NULL;
	tail = NULL;
}


Linked_List::~Linked_List()
{
	delete_next(head);
}

void Linked_List::delete_next(List_Node* pointer)
{
	if (pointer != NULL)
	{
		delete_next(pointer->next);
		delete pointer;
	}
}

void Linked_List::add(int value)
{
	List_Node *temp = new List_Node;
	temp->data = value;
	temp->next = NULL;
	if (head == NULL)
	{
		head = temp;
		tail = temp;
		temp = NULL;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}
}

void Linked_List::remove(int value)
{
	List_Node *temp = head;
	List_Node *previous = new List_Node;

	if (temp != NULL && temp->data == value)
	{
		head = temp->next;
	}

	while (temp != NULL && temp->data != value)
	{
		previous = temp;
		temp = temp->next;
	}

	if (temp == NULL)
	{
		return;
	}

	// Set tail if last node is removed.
	if (previous->next == tail)
	{
		tail = previous;
	}

	// Remove node from the linked list.
	previous->next = temp->next;

	delete temp;
}

void Linked_List::print()
{
	if (head == NULL)
	{
		cout << "-" << endl;
		return;
	}

	List_Node *temp = head;
	while (temp != NULL)
	{
		cout << (temp != head ? " -> " : "") << temp->data;
		temp = temp->next;
	}
	cout << endl;

	delete temp;
}
