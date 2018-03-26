#include "BinarySearchTree.h"
#include <iostream>

using namespace std;


int random_number()
{
	static int number = 1;
	number = (221 * number + 1) % 1000;
	return number;
}


int* permutation(int n)
{
	int i, random, temp;
	int* pointer = new int[n];
	for (i = 0; i < n; i++)
		pointer[i] = i + 1;
	for (i = n; i > 0; i--)
	{
		random = random_number() % i;
		temp = pointer[random];
		pointer[random] = pointer[i - 1];
		pointer[i - 1] = temp;
	}
	return pointer;
}


Node* create_leaf(int x)
{
	Node* result = new Node;
	result->info = x;
	result->left = NULL;
	result->right = NULL;
	return result;
}



BST::BST()
{
	root = NULL;
}


void delete_subtree(Node* pointer)
{
	if (pointer != NULL)
	{
		delete_subtree(pointer->left);
		delete_subtree(pointer->right);
		delete pointer;
	}
}


BST::~BST()
{
	delete_subtree(root);
}


void insert_in_subtree(Node* pointer, int x)
{
	if (x < pointer->info)
	{
		// x is smaller and should be in the left subtree
		if (pointer->left == NULL)
			pointer->left = create_leaf(x);
		else
			insert_in_subtree(pointer->left, x);
	}
	if (x > pointer->info)
	{
		// x is greater and should be in right subtree
		if (pointer->right == NULL)
			pointer->right = create_leaf(x);
		else
			insert_in_subtree(pointer->right, x);
	}
}



void BST::insert(int x)
{
	if (root == NULL)
	{
		root = create_leaf(x);
	}
	else
	{
		insert_in_subtree(root, x);
	}
}


void print_subtree_in_order(Node* pointer)
{
	if (pointer != NULL)
	{
		print_subtree_in_order(pointer->left);
		cout << pointer->info << endl;
		print_subtree_in_order(pointer->right);
	}
}


void BST::traverse()
{
	print_subtree_in_order(root);
}

bool is_present_in_subtree(Node* pointer, int x)
{
	if (pointer == NULL)
		return false;
	if (pointer->info == x)
		return true;
	return (is_present_in_subtree(pointer->left, x) || is_present_in_subtree(pointer->right, x));
}



bool BST::is_present(int x)
{
	return is_present_in_subtree(root, x);
}


void print_subtree(Node* pointer, int depth)
{
	int i;
	for (i = 0; i < depth; i++)
		cout << "    ";
	if (pointer == NULL)
		cout << "--" << endl;
	else
	{
		cout << pointer->info << endl;
		print_subtree(pointer->left, depth + 1);
		print_subtree(pointer->right, depth + 1);
	}
}



void BST::print()
{
	print_subtree(root, 0);
}


int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}


int depth_of_subtree(Node* pointer)
{
	if (pointer == NULL)
		return 0;
	return 1 + max(depth_of_subtree(pointer->left), depth_of_subtree(pointer->right));
}


int BST::depth()
{
	return depth_of_subtree(root);
}