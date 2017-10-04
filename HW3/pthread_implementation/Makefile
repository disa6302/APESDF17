

# FileName        : 	Makefile
# Description     :	Generates executable threads in ~/APESDF17/HW3/pthread_implementation

# File Author Name:	Divya Sampath Kumar
# Reference	  :	http://ecee.colorado.edu/~ecen5623/ecen/ex/Linux/example-1/Makefile 




CC=gcc

CFLAGS= -O0 -g -w -pthread

OUTPUT=threads


CFILES= threads.c

SRCS= ${CFILES}
OBJS= $(CFILES:.c=.o) 

all:	${OUTPUT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${OUTPUT} ${GARBAGE}

threads:threads.o
	$(CC) $(CFLAGS) -o $@ threads.o $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<
