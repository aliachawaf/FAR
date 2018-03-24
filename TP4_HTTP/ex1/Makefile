# $Id$

GCC=gcc
FILES=tcp_client.c
OBJ=$(FILES:%.c=%.o)
BIN=tcp_client

all: $(OBJ)
	$(GCC) -o tcp_client tcp_client.o

clean:
	rm -f *~ *.o $(BIN)

.SUFFIXES: .c .o

.zf.res:
	$(GCC) -c $<
