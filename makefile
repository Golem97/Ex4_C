CC = gcc
FLAGS = -Wall
.PHONY: all clear

all: frequency

frequency: Trie.c
	$(CC) $(FLAGS) Trie.c -o frequency

clean:
	rm frequency