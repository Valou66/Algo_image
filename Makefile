CC=gcc
TD1=td1
TD2=td2
TD3=td3
TD3n=td3n
TD4=td4
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

td3n : ${SRC}TD3n.o ${SRC}FunctionTD3n.o ${SRC}FunctionTD2.o ${SRC}FunctionTD1.o ${INC}TD3n.h
	${CC} ${CFLAGS} -o ${TD3n} ${SRC}TD3n.o ${SRC}FunctionTD3n.o ${SRC}FunctionTD2.o ${SRC}FunctionTD1.o ${LDFLAGS}
	./${TD3n}
	rm -f ./${TD3n}

td4 : ${SRC}TD4.o ${SRC}FunctionTD4.o ${SRC}FunctionTD1.o ${INC}TD3.h
	${CC} ${CFLAGS} -o ${TD4} ${SRC}TD4.o ${SRC}FunctionTD4.o ${SRC}FunctionTD1.o ${LDFLAGS}
	./${TD4}
	rm -f ./${TD4}


clean :
	rm -f *~ *.o

clean_all :
	rm -f ${SRC}*.o ${TD1} ${TD2}
	rm -f ${OBJ}test*
	rm -f ${OBJ}histogram*
	rm -f ${OBJ}extract.pgm
