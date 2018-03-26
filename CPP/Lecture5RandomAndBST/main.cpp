#include "BinarySearchTree.h"
#include <iostream>

using namespace std;


int main()
{
	int i;
	BST tree;
	int* pointer = permutation(20);
	for (i = 0; i < 20; i++)
		cout << pointer[i] << endl;

	for (i = 0; i < 20; i++)
		tree.insert(random_number());

	tree.traverse();
	if (tree.is_present(306))
		cout << "306 is present" << endl;
	else
		cout << "306 is NOT present" << endl;
	if (tree.is_present(305))
		cout << "305 is present" << endl;
	else
		cout << "305 is NOT present" << endl;
	tree.print();
	cout << "Depth: " << tree.depth() << endl;

	cin.get();
}