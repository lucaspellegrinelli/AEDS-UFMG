all:
	gcc -Wall -c common.c
	gcc -Wall -c tag.c
	gcc -Wall client.c common.o -o client
	gcc -Wall -pthread server.c common.o tag.o -o server