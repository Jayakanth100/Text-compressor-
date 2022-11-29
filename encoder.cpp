#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include "tree.hpp"
#include "heap.hpp"

using namespace std;

std::string read_data( std::ifstream fin)
{
	std::string data, buffer;

	if(fin.is_open())
	{
		while( std::getline( fin, buffer))
			data += buffer+'\n';

		fin.close();
		return data;
	}
	return "";
}
int write_data( std::ofstream fout, void* data, int size)
{
	fout.write( (char*)data, size);
	fout.close();
	// _getch();
	return 0;
}

minheap format_data(string data)
{
	int data_size = 0;
	int frequency_array[256] = {0};

	// GENERATE FREQUENCY ARRAY
	for( auto ch : data)
	{
		if(frequency_array[ch] == 0)
			data_size++;
		frequency_array[ch]++;
	}

	// GROW FOREST [ HEAP ] :)
	minheap forest(data_size);
	for( int i = 0; i < 256; i++)
	{
		if(frequency_array[i])
		{
			tree* buffer = new tree( string( 1, (char)i));
			buffer->frequency = frequency_array[i];
			forest.insert(buffer);
		}
	}
	return forest;
}

tree* optimal_merge(minheap forest)
{
	// MERGE HEAP INTO ONE TREE
	while(forest.noe > 1)
	{
		tree* left = forest.pop();
		tree* right = forest.pop();
		forest.insert(tree::merge( left, right));

		/*cout<<"-----------------"<<endl;
		for( int i = 0;  i < forest.noe; i++)
		{
			cout<<forest.array[i]->data<<" "<<forest.array[i]->frequency<<endl;
			if(_getch() == ' ')
			{
				cout<<forest.array[i]->left->data<<forest.array[i]->left->frequency<<endl;
				cout<<forest.array[i]->right->data<<forest.array[i]->right->frequency<<endl;
				cout<<"~~~~~~~~~~~~~~~~~"<<endl;
				_getch();
			}
		}*/

	}
	return forest.pop();
}

string encode(string data, tree* huffman)
{
	char* buffer = new char[data.length()];
	int ndx = 0;
	short bits = 0;

	int end = 0;
	for( int i = 0; i < data.length(); i++)
		buffer[i] = 0;
	for( auto c : data)
	{
		string code = huffman->get_code( huffman, c);
		end += code.length();
		// cout<<code;
		for( auto x : code)
		{
			if(bits > 7)
			{
				// buffer += (char)0;
				ndx++;
				bits = 0;
			}
			buffer[ndx] = buffer[ndx]<<1;
			if(x == '1')
				buffer[ndx]++;
			bits++;
		}
	}
	buffer[ndx] = buffer[ndx]<<(8-bits);
	cout<<end;
	string x = string(buffer);
	cout<<x.length();
	return buffer;
}


int main(int argc, char const *argv[])
{
	// READ FILE
	string filename = "testdrive.txt";
	string data = read_data(ifstream(filename));

	if(data == "")
		// cout<<"\n\t\tFILE NOT FOUND : "<<filename<<"\n\a";
		return 1;

	// GENERATE HUFFMAN TREE
	tree* huffman = optimal_merge(format_data(data));
	// tree::inorder(huffman);

	// ENCODING
	string compressed = encode( data, huffman);

	filename += ".bin";
	string meta = tree::serialize(huffman)+"0"; // The additional 0 is the delimiter

	// HEADER [TREE]
	int size = meta.length();
	write_data( ofstream(filename, ios::binary), (void*)&size, sizeof(int));
	write_data( ofstream(filename, ios::binary|ios::app), (void*)meta.c_str(), size);
	// HEADER [ORIGINAL LENGTH]
	size = data.length();
	write_data( ofstream(filename, ios::binary|ios::app), (void*)&size, sizeof(int));

	// COMPRESSED DATA
	size = compressed.length();
	write_data( ofstream(filename, ios::binary|ios::app), (void*)&size, sizeof(int));
	write_data( ofstream(filename, ios::binary|ios::app), (void*)compressed.c_str(), size);

	return 0;
}