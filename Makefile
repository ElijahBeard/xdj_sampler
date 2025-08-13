all:
	gcc *.c -o xdj -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2

clean:
	rm xdj