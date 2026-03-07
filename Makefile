CFLAGS := $(shell pkg-config --cflags SDL2_ttf)
LIBS := $(shell pkg-config --libs SDL2_ttf)

all:
	gcc *.c -o xdj $(CFLAGS) $(LIBS)

clean:
	rm xdj