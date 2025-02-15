CC=gcc
EXEC=td1
CFLAGS=-Wall

all : TD1.o FunctionTD1.o
	${CC} ${CFLAGS} -o ${EXEC} TD1.o FunctionTD1.o
	rm -f *~ *.o
	./${EXEC}

clean :
	rm -f *~ *.o ${EXEC}