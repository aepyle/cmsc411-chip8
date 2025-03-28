chip8: sdl-basecode.c mychip8.c
	gcc -o chip8 sdl-basecode.c mychip8.c `pkg-config sdl --cflags --libs` -lm

basecode.o: sdl-basecode.c sdl-basecode.h
	gcc -c sdl-basecode.c sdl-basecode.h

run: sdl-basecode.c mychip8.c
	gcc -o chip8 sdl-basecode.c mychip8.c `pkg-config --cflags --libs` -lm & ./chip8
