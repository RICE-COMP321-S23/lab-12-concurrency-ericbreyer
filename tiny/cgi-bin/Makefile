COURSE = /clear/www/htdocs/comp321
CC = cc
CFLAGS = -std=gnu11 -Wall -Wextra -Werror -I${COURSE}/include -g

all: adder

adder: adder.c
	${CC} ${CFLAGS} -o adder adder.c

clean:
	${RM} adder core.[1-9]*

.PHONY: all clean
