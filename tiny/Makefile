COURSE = /clear/www/htdocs/comp321
CC = cc
CFLAGS = -std=gnu11 -Wall -Wextra -Werror -I${COURSE}/include -g
LDFLAGS = -lpthread

all: tiny cgi

tiny: tiny.c csapp.o
	${CC} ${CFLAGS} -o tiny tiny.c csapp.o ${LDFLAGS}

csapp.o: ${COURSE}/src/csapp.c ${COURSE}/include/csapp.h
	${CC} ${CFLAGS} -c ${COURSE}/src/csapp.c -o csapp.o

cgi:
	(cd cgi-bin; make)

clean:
	${RM} *.o tiny core.[1-9]*
	(cd cgi-bin; make clean)

.PHONY: all cgi clean
