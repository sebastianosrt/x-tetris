FLAGS=-c -ansi -lncurses -o

x-tetris: main.o game.o utils.o print.o tetromino.o
	gcc main.o game.o utils.o print.o tetromino.o -lncurses -o x-tetris

main.o: src/main.c
	gcc src/main.c $(FLAGS) main.o

game.o: src/impl/game.c src/headers/game.h tetromino.o utils.o print.o
	gcc src/impl/game.c $(FLAGS) game.o

utils.o: src/impl/utils.c tetromino.o
	gcc src/impl/utils.c $(FLAGS) utils.o

print.o: src/impl/print.c src/headers/print.h tetromino.o
	gcc src/impl/print.c $(FLAGS) print.o

tetromino.o: src/impl/tetromino.c src/headers/tetromino.h src/headers/constants.h
	gcc src/impl/tetromino.c $(FLAGS) tetromino.o

clean:
	rm -rf *.o x-tetris
