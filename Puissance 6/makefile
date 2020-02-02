CC=gcc

//CFLAGS= -w -wall -ansi -pedantic
LDFLAGS= 
EXEC= puiss6
all: $(EXEC)
puiss6: puiss6.o main.o
	$(CC) -o puiss6 puiss6.o main.o $(LDFLAGS)
puiss6.o: puiss6.c
	$(CC) -o puiss6.o -c puiss6.c $(LDFLAGS)
main.o: main.c puissance.h
	$(CC) -o main.o -c main.c $(LDFLAGS)
