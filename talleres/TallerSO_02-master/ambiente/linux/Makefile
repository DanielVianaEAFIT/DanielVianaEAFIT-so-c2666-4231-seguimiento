CC = gcc
CFLAGS = -Wall

all: ambiente variable

ambiente: ambiente.c
	$(CC) $(CFLAGS) -o ambiente ambiente.c

variable: variable.c
	$(CC) $(CFLAGS) -o variable variable.c

clean:
	rm -f ambiente variable
