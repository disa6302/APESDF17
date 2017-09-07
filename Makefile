INCLUDE_DIRS = -Iinclude
CC=gcc

CFLAGS= -O0 -g -w $(INCLUDE_DIRS) 

OUTPUT=cbuffer dlinkedlist


HFILES= circularbuffer.h doubleLL.h
CFILES= circularbuffer.c doubleLL.c

SRCS= ${HFILES} ${CFILES}
OBJS= $(CFILES:.c=.o) 

all:	${OUTPUT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${OUTPUT} ${GARBAGE}

cbuffer:circularbuffer.o
	$(CC) $(CFLAGS) -o $@ circularbuffer.o $(LIBS)

dlinkedlist:doubleLL.o
	$(CC) $(CFLAGS) -o $@ doubleLL.o $(LIBS)


.c.o:
	$(CC) $(CFLAGS) -c $<
