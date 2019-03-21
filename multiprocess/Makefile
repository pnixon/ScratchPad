CC = gcc
LIBS = -pthread

all : shared_memory.o
	$(CC) $(LIBS) shared_memory.c -o shared_memory -lrt

clean :
	rm shared_memory