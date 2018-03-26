#include "BinarySearchTree.h"
#include <iostream>

using namespace std;


void main()
{
	BST<int> tree;

	tree.insert(8);
	tree.insert(4);
	tree.insert(2);
	tree.insert(1);
	tree.insert(3);
	tree.insert(6);
	tree.insert(5);
	tree.insert(7);
	tree.insert(12);
	tree.insert(10);
	tree.insert(9);
	tree.insert(11);
	tree.insert(14);
	tree.insert(13);
	tree.insert(15);
	tree.print();

	tree.remove(1);
	tree.print();
	tree.remove(2);
	tree.print();
	tree.remove(12);
	tree.print();
	tree.remove(9);
	tree.print();
	tree.remove(13);
	tree.print();
	tree.remove(8);
	tree.print();
	tree.remove(6);
	tree.print();
	tree.remove(14);
	tree.print();
	tree.remove(10);
	tree.print();
	tree.remove(4);
	tree.print();
	tree.remove(5);
	tree.print();
	tree.remove(11);
	tree.print();
	tree.remove(7);
	tree.print();
	tree.remove(15);
	tree.print();
	tree.remove(3);
	tree.print();

	cin.get();
}