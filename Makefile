all: bin/main

bin/main: obj/main.o obj/universalsort.o obj/custo.o obj/arrayparameters.o obj/optimizer.o
	gcc -Wall -Iinclude obj/main.o obj/universalsort.o obj/custo.o obj/arrayparameters.o obj/optimizer.o -o bin/main

obj/main.o: src/main.c include/arrayparameters.h include/optimizer.h
	gcc -Wall -Iinclude -c src/main.c -o obj/main.o

obj/custo.o: src/custo.c include/custo.h
	gcc -Wall -Iinclude -c src/custo.c -o obj/custo.o

obj/arrayparameters.o: src/arrayparameters.c include/arrayparameters.h
	gcc -Wall -Iinclude -c src/arrayparameters.c -o obj/arrayparameters.o

obj/universalsort.o: src/universalsort.c include/universalsort.h include/custo.h
	gcc -Wall -Iinclude -c src/universalsort.c -o obj/universalsort.o

obj/optimizer.o: src/optimizer.c include/optimizer.h include/arrayparameters.h include/custo.h include/universalsort.h
	gcc -Wall -Iinclude -c src/optimizer.c -o obj/optimizer.o