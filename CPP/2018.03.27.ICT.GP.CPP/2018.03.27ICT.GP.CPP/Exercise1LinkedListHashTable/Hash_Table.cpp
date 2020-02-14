#include "Hash_Table.h"



Hash_Table::Hash_Table(int size)
{
	if (size == 0)
	{
		cout << "Please specify a table_size bigger than 0." << endl;
	}

	table_size = size;
	the_table = new Linked_List[table_size];
}


Hash_Table::~Hash_Table()
{
	delete[] the_table;
}

int Hash_Table::hash_value(int value)
{
	return value % table_size;
}

void Hash_Table::add(int value)
{
	the_table[hash_value(value)].add(value);
}

void Hash_Table::print()
{
	for (int i = 0; i < table_size; i++)
	{
		cout << i << " : ";
		the_table[i].print();
	}
}
