clean: sudoku
	rm grid.o
sudoku: sudoku.c sudoku.h grid.o
	gcc -Wall -ansi -pedantic -o sudoku sudoku.c grid.o
grid.o: grid.c grid.h
	gcc -c -Wall -ansi -pedantic grid.c
