CFLAGS=-Wall -Werror -Wfatal-errors

main: main.o node.o binary_search_tree.o
	g++ -o main main.o node.o binary_search_tree.o

main.o: main.cpp node.h binary_search_tree.h
	g++ -c $(CFLAGS) main.cpp

node.o: node.cpp node.h
	g++ -c $(CFLAGS) node.cpp

binary_search_tree.o: binary_search_tree.cpp binary_search_tree.h
	g++ -c $(CFLAGS) binary_search_tree.cpp

clean:
	rm -rf *.o main