CC=gcc
EXEC=td1
CFLAGS=-Wall
LDFLAGS=-lm
OBJ=../obj/

all : TD1.o FunctionTD1.o
	${CC} ${CFLAGS} -o ${EXEC} TD1.o FunctionTD1.o ${LDFLAGS}
	./${EXEC}

clean :
	rm -f *~ *.o

clean_all :
	rm -f *~ *.o ${EXEC}
	rm -f ${OBJ}test*
	rm -f ${OBJ}histogram*
