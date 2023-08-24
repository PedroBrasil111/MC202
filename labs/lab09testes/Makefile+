lab09: lab09.o heap.o
	gcc lab09.o heap.o -lm -o lab09

lab09.o: lab09.c heap.h
	gcc -std=c99 -Wall -Werror -c lab09.c

heap.o: heap.c heap.h
	gcc -std=c99 -Wall -Werror -c heap.c