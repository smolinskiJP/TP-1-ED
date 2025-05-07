all: bin/main

bin/main: obj/main.o obj/universalsort.o
	gcc -Wall -Iinclude obj/main.o obj/universalsort.o -o bin/main

obj/main.o: src/main.c
	gcc -Wall -Iinclude -c src/main.c -o obj/main.o
	
obj/universalsort.o: src/universalsort.c
	gcc -Wall -Iinclude -c src/universalsort.c -o obj/universalsort.o