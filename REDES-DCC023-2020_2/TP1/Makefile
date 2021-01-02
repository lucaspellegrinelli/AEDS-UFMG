all:
	gcc -Wall -c common.c
	gcc -Wall -c intlist.c
	gcc -Wall -c stringlist.c
	gcc -Wall -c usertags.c
	gcc -Wall -c tag.c
	gcc -Wall -pthread client.c common.o intlist.o stringlist.o usertags.o -o client
	gcc -Wall -pthread server.c common.o intlist.o stringlist.o usertags.o tag.o -o server

test:
	gcc -Wall -c intlist.c
	gcc -Wall -c stringlist.c
	gcc -Wall -c usertags.c
	gcc -Wall test.c intlist.o stringlist.o usertags.o -o test

clean:
	rm -rf *.o
	rm test server client