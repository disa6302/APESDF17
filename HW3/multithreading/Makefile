

# FileName        : Makefile
# Description     :	Generates executable sort_test in ~/APESDF17/HW3/multithreading

# File Author Name:	Divya Sampath Kumar
# Reference	      :	http://ecee.colorado.edu/~ecen5623/ecen/ex/Linux/example-1/Makefile 




CC=gcc

CFLAGS= -O0 -g -w $(INCLUDE_DIRS) -pthread

OUTPUT=multithread


CFILES= IO_multithread.c

SRCS= ${CFILES}
OBJS= $(CFILES:.c=.o) 

all:	${OUTPUT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${OUTPUT} ${GARBAGE}

multithread:IO_multithread.o
	$(CC) $(CFLAGS) -o $@ IO_multithread.o $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<
