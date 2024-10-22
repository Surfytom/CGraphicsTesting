all:
	gcc -Isrc/include -Lsrc/lib -o main main.c src/vector.c src/Matrix.c src/Shape.c -lmingw32 -lSDL2main -lSDL2