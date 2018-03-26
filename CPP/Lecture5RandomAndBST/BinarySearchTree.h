#ifndef BINARY_SEARCH_TREE_HEADER
#define BINARY_SEARCH_TREE_HEADER


int random_number();
int* permutation(int n);


struct Node
{
	int info;
	Node* left;
	Node* right;
};


class BST
{
private:
	Node* root;

public:
	BST();
	~BST();
	void insert(int x);
	void traverse();
	bool is_present(int x);
	void print();
	int depth();
};



#endif