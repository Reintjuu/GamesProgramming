#ifndef BINARY_SEARCH_TREE_HEADER
#define BINARY_SEARCH_TREE_HEADER


template <typename Type>
struct Node
{
	Type info;
	Node* left;
	Node* right;
};

template <typename Type>
class BST
{
private:
	Node<Type>* root;

public:
	BST();
	~BST();
	void insert(Type x);
	void traverse();
	bool is_present(Type x);
	void print();
	int depth();
	void remove(Type x);
};



#endif