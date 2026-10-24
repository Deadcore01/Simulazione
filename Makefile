build:
	gcc -Wall -Wextra -std=c11 -Iinclude src/*.c -lSDL3 -lSDL3_ttf -o sim
run:
	./sim

clean:
	rm -f sim
