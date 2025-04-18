CC=gcc
TD1=td1
TD2=td2
TD3=td3
CFLAGS=-Wall -g
LDFLAGS=-lm
SRC=./src/
OBJ=./obj/
INC=./include/

all :
	make td1
	make td2
	make td3

td1 : ${SRC}TD1.o ${SRC}FunctionTD1.o
	${CC} ${CFLAGS} -o ${TD1} ${SRC}TD1.o ${SRC}FunctionTD1.o ${LDFLAGS}
	./${TD1}

td2 : ${SRC}TD2.o ${SRC}FunctionTD1.o ${SRC}FunctionTD2.o ${INC}TD2.h
	${CC} ${CFLAGS} -o ${TD2} ${SRC}TD2.o ${SRC}FunctionTD1.o ${SRC}FunctionTD2.o ${LDFLAGS}
	./${TD2}
	rm -f ./${TD2}

td3 : ${SRC}TD3.o ${SRC}FunctionTD3.o ${SRC}FunctionTD2.o ${SRC}FunctionTD1.o ${INC}TD3.h
	${CC} ${CFLAGS} -o ${TD3} ${SRC}TD3.o ${SRC}FunctionTD3.o ${SRC}FunctionTD2.o ${SRC}FunctionTD1.o ${LDFLAGS}
	./${TD3}
	rm -f ./${TD3}

clean :
	rm -f *~ *.o

clean_all :
	rm -f ${SRC}*.o ${TD1} ${TD2}
	rm -f ${OBJ}test*
	rm -f ${OBJ}histogram*
	rm -f ${OBJ}extract.pgm
