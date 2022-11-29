#include "tree.hpp"

tree::tree( std::string data, tree* left, tree* right)
{
	this->data = data;
	this->left = left;
	this->right = right;
	this->frequency = 1;
}
void tree::swap(tree* other)
{
	tree* aux = new tree( other->data, other->left, other->right);
	aux->frequency = other->frequency;

	other->data = this->data;
	other->frequency = this->frequency;
	other->left = this->left;
	other->right = this->right;

	this->data = aux->data;
	this->frequency = aux->frequency;
	this->left = aux->left;
	this->right = aux->right;
}

tree tree::operator+(tree sibling)
{
	// ANATOMY OF FAILURE
	// MORAL OF THE STROY
	// - DO NOT EVER FUCKIN COMPLICATE YOUR LIFE WITH CONCEPTS
	// LIKE OPERATOR OVERLOADING WHEN THERE IS NO FUCKING NEED FOR IT, YOU WILL SOON REGRET IT
	tree newroot( this->data + sibling.data, this, &sibling);
	newroot.frequency = this->frequency + sibling.frequency;
	return newroot;
}

tree* tree::merge( tree* left, tree* right)
{
	tree* root = new tree( left->data + right->data, left, right);
	root->frequency = left->frequency + right->frequency;
	return root;
}

void tree::inorder(tree* curr)
{
	if(curr == NULL) return;
	inorder(curr->left);
	std::cout<<curr->data<<std::endl;
	inorder(curr->right);
}
std::string tree::serialize( tree* curr, std::string meta)
{
	if(curr)
	{
		meta = serialize( curr->left, meta);
		meta = serialize( curr->right, meta);
		if(curr->right == NULL && curr->left == NULL)
			meta += "1" + curr->data;
		else
			meta += "0";
	}
	return meta;
}
std::string tree::get_code( tree* curr, char key, std::string code)
{
	if(curr->left && curr->left->data.find(key) < curr->left->data.length())
		return get_code( curr->left, key, code + "0");
	else if(curr->right && curr->right->data.find(key) < curr->right->data.length())
		return get_code( curr->right, key, code + "1");
	else if(curr->data[0] == key)
		return code;
	return "";
}