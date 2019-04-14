CPP=gcc 
CFLAGS=-O3 -g

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
LIBS += -lm
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
EXEC=main

all: ${EXEC}

main: $(OBJ)
	$(CPP) $(CFLAGS) -o $@ $^ $(LDFLAGS) ${SDL_LDFLAGS} ${LIBS}

%.o: %.c
	$(CPP)$(CFLAGS) -o $@ -c $< $(CFLAGS) ${SDL_CFLAGS} 

clean:	
	rm -fr *.o

mrproper: clean
	rm -fr ${EXEC}
