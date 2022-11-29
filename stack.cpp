#include "stack.hpp"

stack::stack(int capacity)
{
	this->capacity = capacity;
	array = new tree*[capacity];
	noe = 0;
}
int stack::push(tree* newtree)
{
	if(noe < capacity)
		array[noe++] = newtree;
	return noe;
}
tree* stack::pop()
{
	if(noe)
		return array[--noe];
	return NULL;
}
bool stack::is_empty()
{
	return noe==0;
}
bool stack::is_full()
{
	return noe==capacity;
}