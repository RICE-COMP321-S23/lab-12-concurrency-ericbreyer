COURSE = /clear/www/htdocs/comp321
CC = cc
CFLAGS = -std=gnu11 -Wall -Wextra -Werror -I${COURSE}/include -g -O2
LDFLAGS = -lpthread

PROGS = echo-key sor-pthreads

all: ${PROGS}

echo-key: echo-key.c csapp.o
	${CC} ${CFLAGS} -o echo-key echo-key.c csapp.o ${LDFLAGS}

sor-pthreads: sor-pthreads.c csapp.o
	${CC} ${CFLAGS} -o sor-pthreads sor-pthreads.c csapp.o ${LDFLAGS}

csapp.o: ${COURSE}/src/csapp.c ${COURSE}/include/csapp.h
	${CC} ${CFLAGS} -c ${COURSE}/src/csapp.c -o csapp.o

clean:
	${RM} *.o ${PROGS} core.[1-9]*

.PHONY: all clean
