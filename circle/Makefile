CPP=gcc 
CFLAGS=-O3 

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
LIBS += -lm

EXEC=prime

all: ${EXEC}

${EXEC}: ${EXEC}.o
	${CPP} $(CFLAGS) -o ${EXEC} ${EXEC}.o ${SDL_LDFLAGS} ${LIBS}

${EXEC}.o: ${EXEC}.c
	${CPP} $(CFLAGS) -o ${EXEC}.o -c ${EXEC}.c ${SDL_CFLAGS} 

clean:	
	rm -fr *.o

mrproper: clean
	rm -fr ${EXEC}