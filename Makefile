CC=gcc
TD1=td1
TD2=td2
CFLAGS=-Wall -g
LDFLAGS=-lm
SRC=./src/
OBJ=./obj/
INC=./include/



TD1 : ${SRC}TD1.o ${SRC}FunctionTD1.o
	${CC} ${CFLAGS} -o ${TD1} ${SRC}TD1.o ${SRC}FunctionTD1.o ${LDFLAGS}
	./${TD1}

TD2 : ${SRC}TD2.o ${SRC}FunctionTD1.o ${SRC}FunctionTD2.o ${INC}TD2.h
	${CC} ${CFLAGS} -o ${TD2} ${SRC}TD2.o ${SRC}FunctionTD1.o ${SRC}FunctionTD2.o ${LDFLAGS}
	./${TD2}

clean :
	rm -f *~ *.o

clean_all :
	rm -f ${SRC}*.o ${TD1} ${TD2}
	rm -f ${OBJ}test*
	rm -f ${OBJ}histogram*
