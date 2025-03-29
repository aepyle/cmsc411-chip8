chip8: sdl-basecode.c mychip8.c
	gcc -o chip8 sdl-basecode.c mychip8.c `pkg-config sdl --cflags --libs` -lm