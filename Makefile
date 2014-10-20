OBJSP = procesos.o quicksort.o
OBJSH =
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
.SUFFIXES: .o .c  # store important suffixes in the .SUFFIXES macro

all: ordenArchivo-p clean

ordenArchivo-p: $(OBJSP)
	$(CC) $(LFLAGS) $(OBJSP) -o $@	
.c.o:
	gcc -c $<
	
clean:
	rm -f *.o
