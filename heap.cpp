#include "heap.hpp"

minheap::minheap(int capacity)
{
	this->capacity = capacity;
	array = new tree*[capacity];
	noe = 0;
}

int minheap::insert(tree* newtree)
{
	if(noe == capacity)
	{
		std::cout<<"\n\t\tHEAP OVERFLOW\n\a";
		return noe;
	}
	int i = noe++;
	array[i] = newtree;
	while( i != 0 && array[PARENT(i)]->frequency > array[i]->frequency)
	{
		array[i]->swap(array[PARENT(i)]);
		i = PARENT(i);
	}
	return noe;
}
tree* minheap::pop()
{
	if(noe > 0)
	{
		tree* top = array[0];
		array[0] = array[--noe];

		if(noe) heapify(0);
		return top;
	}
	return NULL;
}
void minheap::heapify(int i)
{
	int left = LEFT(i);
	int right = RIGHT(i);
	int min = i;

	if(right < noe && array[right]->frequency < array[min]->frequency)
		min = right;
	if(left < noe && array[left]->frequency < array[min]->frequency)
		min = left;

	if(min != i)
	{
		array[i]->swap(array[min]);
		heapify(min);
	}
}