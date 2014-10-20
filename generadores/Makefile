CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
.SUFFIXES: .o .c  # store important suffixes in the .SUFFIXES macro

all: generador random imprimir

generador:
	$(CC) $(LFLAGS) generador.c -o $@

random:
	$(CC) $(LFLAGS) generadorR.c -o $@

imprimir:
	$(CC) $(LFLAGS) imprimir.c -o $@
	
.c.o:
	gcc -c $<
	
clean:
	rm -f *.o
