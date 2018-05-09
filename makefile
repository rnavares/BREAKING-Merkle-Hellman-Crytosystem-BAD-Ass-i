#makefile

CFLAGS = -ansi -Wall -pedantic

COMPILER = gcc
IDIRS = -I /usr/include
LDIRS = -L /usr/lib
LDIRS = -L .


all: main

#objects
cript.o: cript.c cript.h
	$(COMPILER) $(CFLAGS) $(IDIRS) -c -g cript.c

main.o: main.c cript.h 
	$(COMPILER) $(CFLAGS) $(IDIRS) -c -g main.c


#executables
main: main.o cript.o cript.h  
	$(COMPILER) -o main main.o cript.o $(LDIRS) -lm

clean:
	rm -fr core *.o p1 p2 p3 p4 p5 p6 p7 p8 *~ 	
#end  MAKEFILE
