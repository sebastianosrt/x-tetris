FLAGS=-c -ansi -lncurses -o

x-tetris: main.o utils.o
	gcc main.o utils.o -lncurses -o x-tetris

main.o: src/main.c src/utils.h
	gcc src/main.c $(FLAGS) main.o

utils.o: src/utils.c src/utils.h src/constants.h src/types.h
	gcc src/utils.c $(FLAGS) utils.o

clean:
	rm -rf *.o x-tetris
