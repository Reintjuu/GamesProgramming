#include "BinarySearchTree.h"
#include <iostream>
#include <string>

using namespace std;

template class BST<int>;
template class BST<double>;
template class BST<char>;
template class BST<string>;


template  <typename Type>
Node<Type>* create_leaf(Type x)
{
	Node<Type>* result = new Node<Type>;
	result->info = x;
	result->left = NULL;
	result->right = NULL;
	return result;
}



template  <typename Type>
BST<Type>::BST()
{
	root = NULL;
}


template  <typename Type>
void delete_subtree(Node<Type>* pointer)
{
	if (pointer != NULL)
	{
		delete_subtree(pointer->left);
		delete_subtree(pointer->right);
		delete pointer;
	}
}


template  <typename Type>
BST<Type>::~BST()
{
	delete_subtree(root);
}


template  <typename Type>
void insert_in_subtree(Node<Type>* pointer, Type x)
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



template  <typename Type>
void BST<Type>::insert(Type x)
{
	if (root == NULL)
		root = create_leaf(x);
	else
		insert_in_subtree(root, x);
}


template  <typename Type>
void print_subtree_in_order(Node<Type>* pointer)
{
	if (pointer != NULL)
	{
		print_subtree_in_order(pointer->left);
		cout << pointer->info << endl;
		print_subtree_in_order(pointer->right);
	}
}


template  <typename Type>
void BST<Type>::traverse()
{
	print_subtree_in_order(root);
}

template  <typename Type>
bool is_present_in_subtree(Node<Type>* pointer, Type x)
{
	if (pointer == NULL)
		return false;
	if (pointer->info == x)
		return true;
	return (is_present_in_subtree(pointer->left, x) || is_present_in_subtree(pointer->right, x));
}



template  <typename Type>
bool BST<Type>::is_present(Type x)
{
	return is_present_in_subtree(root, x);
}


template  <typename Type>
void print_subtree(Node<Type>* pointer, int depth)
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


template  <typename Type>
void BST<Type>::print()
{
	cout << "Printing tree with depth " << depth() << endl;
	print_subtree(root, 0);
}


int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}


template  <typename Type>
int depth_of_subtree(Node<Type>* pointer)
{
	if (pointer == NULL)
		return 0;
	return 1 + max(depth_of_subtree(pointer->left), depth_of_subtree(pointer->right));
}


template  <typename Type>
int BST<Type>::depth()
{
	return depth_of_subtree(root);
}


// This function takes a subtree as input together with an element x 
// that needs to be removed. It returns a pointer to this subtree but 
// then without the node with element x. See in function comments for
// the different situations and what to do then.
// Usage: replace the existing pointer to this subtree with the new
// pointer to this subtree. 
template <typename Type>
Node<Type>* remove_from_subtree(Node<Type>* local_root, Type x)
{
	Node<Type>* temp;
	if (local_root == NULL)
	{
		// subtree is empty, element with info 'x' is not in the tree
		return NULL;
	}
	if (x < local_root->info)
	{
		// element with info 'x' is in left subtree
		// replace left subtree with subtree without element with info 'x'
		local_root->left = remove_from_subtree(local_root->left, x);
		return local_root;
	}
	if (x > local_root->info)
	{
		// element with info 'x' is in right subtree
		// replace right subtree with subtree without element with info 'x'
		local_root->right = remove_from_subtree(local_root->right, x);
		return local_root;
	}

	// If we are here, the root of this subtree contains the element that 
	// needs to be removed. How, depends on the number of subtrees this root has.
	
	if (local_root->left == NULL && local_root->right == NULL)
	{
		// 0 subtrees, we can just delete this leaf
		delete local_root;
		return NULL;
	}
	if (local_root->left == NULL || local_root->right == NULL)
	{
		// 1 subtree, remove root and return this subtree
		if (local_root->left == NULL)
			temp = local_root->right;
		else
			temp = local_root->left;
		delete local_root;
		return temp;
	}
	// We need to delete the root of the current subtree, which has two
	// subtrees itself. Swap value in root with smallest of the bigger values
	// and remove the element from the subtree of bigger elements.
	temp = local_root->right;
	while (temp->left != NULL)
		temp = temp->left;
	local_root->info = temp->info;
	temp->info = x;
	local_root->right = remove_from_subtree(local_root->right, x);
	return local_root;
}


template <typename Type>
void BST<Type>::remove(Type x)
{
	root = remove_from_subtree(root, x);
}