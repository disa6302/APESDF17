

# FileName        : 	Makefile
# Description     :	Generates executable sort_test in ~/APESDF17/HW2/sorting_syscall

# File Author Name:	Divya Sampath Kumar
# Reference	  :	http://ecee.colorado.edu/~ecen5623/ecen/ex/Linux/example-1/Makefile 




CC=gcc

CFLAGS= -O0 -g -w $(INCLUDE_DIRS) 

OUTPUT=sort_test


CFILES= sort_test.c

SRCS= ${CFILES}
OBJS= $(CFILES:.c=.o) 

all:	${OUTPUT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${OUTPUT} ${GARBAGE}

sort_test:sort_test.o
	$(CC) $(CFLAGS) -o $@ sort_test.o $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<
