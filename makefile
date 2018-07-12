#Flags
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
LIB = lib/

#rules
main: 
	$(CC) $(CFLAGS) -L$(LIB) src/main.c -lHashTableAPI -Iinclude -o bin/main
	
test:
	$(CC) $(CFLAGS) -L$(LIB) src/testMain.c -lHashTableAPI -Iinclude -o bin/test
	
HashAPI:
	$(CC) $(CFLAGS) -c src/HashTableAPI.c -Iinclude -o assets/HashTableAPI.o
	ar rc lib/libHashTableAPI.a assets/HashTableAPI.o
	ranlib lib/libHashTableAPI.a
