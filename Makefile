CC=gcc
EXEC=td1
CFLAGS=-Wall
LDFLAGS=-lm
SRC=./src/
OBJ=./obj/
INC=./include/

all : ${SRC}TD1.o ${SRC}FunctionTD1.o
	${CC} ${CFLAGS} -o ${EXEC} ${SRC}TD1.o ${SRC}FunctionTD1.o ${LDFLAGS}
	./${EXEC}

clean :
	rm -f *~ *.o

clean_all :
	rm -f ${SRC}*.o ${EXEC}
	rm -f ${OBJ}test*
	rm -f ${OBJ}histogram*
