#pragma once
#include "Linked_List.h"

class Hash_Table
{
public:
	Hash_Table(int table_size);
	~Hash_Table();
	int hash_value(int value);
	void add(int value);
	void print();
private:
	int table_size;
	Linked_List *the_table;
};

