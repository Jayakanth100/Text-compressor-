all : encode

encode : encoder.o heap.o tree.o
	clang++ encoder.o heap.o tree.o -o encode.exe
	.\\encode testdrive.txt

decode : decoder.o stack.o tree.o
	clang++ decoder.o stack.o tree.o -o decode.exe
	.\\decode

encoder.o : encoder.cpp
	clang++ -c encoder.cpp

decoder.o : decoder.cpp
	clang++ -c decoder.cpp

tree.o : tree.cpp
	clang++ -c tree.cpp

heap.o : heap.cpp
	clang++ -c heap.cpp

stack.o : stack.cpp
	clang++ -c stack.cpp

clean :
	del *.o