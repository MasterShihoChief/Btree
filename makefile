
B+Tree: main.o
	g++ -o B+Tree main.o

main.o: B_tree.h B_node.h util.h
	g++ -Wall -pedantic -c main.cpp

clean:
	rm -f main.o B+Tree
