#ifndef HEAP_H
#define HEAP_H

#include "tree.hpp"

#define PARENT(i) (i-1)/2
#define RIGHT(i) (2*i)+1
#define LEFT(i)  (2*i)+2

class minheap
{
private:
	int capacity;
public:
	tree** array;
	int noe;
	minheap( int capacity);
	int insert( tree* newtree);
	tree* pop();
	void heapify(int i);
};

#endif // HEAP_H