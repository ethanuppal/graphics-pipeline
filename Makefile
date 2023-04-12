# Copyright (C) Ethan Uppal 2023. All rights reserved.

CFLAGS   += -Iinclude -std=c99 -pedantic
WARNINGS += -Wall -Wextra
SRC      := $(wildcard src/*.c)
OBJ      := ${SRC:.c=.o}
BIN      := bin
PRG      := main
PRODUCT  := ${BIN}/out.ppm
CFLAGS   += ${WARNINGS}

test: ${PRG}
	${BIN}/${PRG} > ${PRODUCT}
	open ${PRODUCT}

${PRG}: ${OBJ} main.c
	${CC} ${CFLAGS} $^ -o ${BIN}/${PRG}

.c.o:
	${CC} ${CFLAGS} $< -c -o ${<:.c=.o}

clean:
	rm -rf ${BIN}/* ${OBJ}
