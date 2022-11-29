#include "tree.hpp"

class stack
{
private:
	int capacity;
	tree** array;
public:
	int noe;
	stack(int capacity);
	int push(tree* newtree);
	tree* pop();
	bool is_empty();
	bool is_full();

};