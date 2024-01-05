all:
	gcc -I src/sdl2/include -L src/sdl2/lib -L src/util -L src/tetromino src/main.c src/tetromino/tetromino.c -o Tetris -lSDL2main -lSDL2