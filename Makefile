# Copyright (C) Ethan Uppal 2023. All rights reserved.

CFLAGS   += -Iinclude -std=c99 -pedantic
WARNINGS += -Wall -Wextra
DEBUG    := -g
RELEASE  := -O3
SRC      := $(wildcard src/*.c)
OBJ      := ${SRC:.c=.o}
BIN      := bin
PRG      := main
PRODUCT  := ${BIN}/out
CFLAGS   += ${WARNINGS} ${DEBUG} ${RELEASE}

test: ${PRG}
	${BIN}/${PRG} > ${PRODUCT}.ppm
	pnmtopng ${PRODUCT}.ppm > ${PRODUCT}.png
	open ${PRODUCT}.png

test_gif: ${PRG}
	${BIN}/${PRG}
	./generate_gif.bash

${PRG}: ${OBJ} main.c
	${CC} ${CFLAGS} $^ -o ${BIN}/${PRG}

.c.o:
	${CC} ${CFLAGS} $< -c -o ${<:.c=.o}

clean:
	rm -rf ${BIN}/* ${OBJ}
