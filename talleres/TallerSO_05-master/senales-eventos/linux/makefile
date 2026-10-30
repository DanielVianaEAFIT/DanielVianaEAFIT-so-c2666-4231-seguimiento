.phony: clean

SRCS=manejar-senal.c manejar-senal2.c manejar-senal2.2.c captura-senal.c manejadores.c
OBJS=$(SRCS:.c=.o)
EXECS=manejar-senal manejar-senal2 manejar-senal2.2 captura-senal

all: ${EXECS}

manejar-senal: manejar-senal.o
	${CC} -o $@ $<

manejar-senal2: manejar-senal2.o
	${CC} -o $@ $<

manejar-senal2.2: manejar-senal2.2.o
	${CC} -o $@ $<

captura-senal: captura-senal.o manejadores.o
	${CC} -o $@ $^

captura-senal.o: captura-senal.c manejadores.h

manejadores.o: manejadores.c manejadores.h

clean:
	rm -f ${OBJS}
	rm -f ${EXECS}
	rm -f *~
