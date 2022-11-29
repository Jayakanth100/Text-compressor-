#include <iostream>
#include <fstream>
#include <conio.h>
#include "tree.hpp"
#include "stack.hpp"
using namespace std;

int write_data( std::ofstream fout, void* data, int size)
{
	fout.write( (char*)data, size);
	fout.close();
	// _getch();
	return 0;
}

tree* rise_from_the_ashes( string meta)
{
	stack forest(meta.length());

	for( int i = 0;  i < meta.length(); i++)
	{
		switch(meta[i])
		{
		case '1':
			forest.push(new tree(string(1,meta[++i])));
			break;
		case '0':
			if(forest.noe == 1)
				return forest.pop();
			else
			{
				tree* right = forest.pop();
				tree* left = forest.pop();
				forest.push(tree::merge( left, right));
			}
		}
	}
	return NULL;
}

string decode( string compressed, tree* huffman, int size)
{
	tree* curr = huffman;
	string data = "";
	for( auto ch : compressed)
	{
		for( int i = 0; i < 8; i++)
		{
			char mask = 1;
			char the_all_seeing_eye = (mask & (ch>>(7-i)));
			// cout<<(int)the_all_seeing_eye;
			switch (the_all_seeing_eye)
			{
			case 1:
				curr = curr->right;
				break;
			case 0:
				curr = curr->left;
				break;
			default:
				return "WTF";
			}
			if(curr->right or curr->left)
				continue;
			data += curr->data;
			// _getch();
			if(--size == 0)
				return data;
			curr = huffman;
		}
	}

	return "PSYCHE";
}

int main(int argc, char const *argv[])
{
	int size;
	char* buffer;
	ifstream fin( "testdrive.txt.bin", ios::binary);

	fin.read( (char*)&size, sizeof(int));
	buffer = new char[size];
	fin.read( (char*)buffer, size);

	tree* huffman = rise_from_the_ashes(buffer);
	// tree::inorder(huffman);

	int og_size;
	fin.read( (char*)&og_size, sizeof(int));
	cout<<og_size;

	fin.read( (char*)&size, sizeof(int));
	buffer = new char[size];
	fin.read( (char*)buffer, size);

	string data = decode( buffer, huffman, og_size);
	write_data( ofstream("result.txt"), (void*)data.c_str(), data.length());

	return 0;
}