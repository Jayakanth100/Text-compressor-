#ifndef TREE_H
#define TREE_H

#include <iostream>

#define MAX 256

class tree
{
public:
	std:: string data;
	int frequency;
	tree* left;
	tree* right;

	tree(std::string = "", tree* left = NULL, tree* right = NULL);

	void insert(std::string);
	void swap(tree* other);
	tree operator+(tree sibling);
	static tree* merge( tree* left, tree* right);
	static void inorder(tree* curr);
	static std::string serialize( tree* curr, std::string meta = "");
	std::string get_code( tree* curr, char key, std::string code = "");
};

#endif // TREE_H