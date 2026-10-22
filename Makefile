build:
	gcc -Wall -Wextra -std=c11 -Iinclude main.c src/finestra.c -lSDL3 -o sim
run:
	./sim

clean:
	rm -f sim
