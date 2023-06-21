# Copyright (C) Ethan Uppal 2023. All rights reserved.

CFLAGS   += -Iinclude -std=c99 -pedantic
WARNINGS += -Wall -Wextra
DEBUG    := -g # -D DEBUG_COUNTS
RELEASE  := -O3
SRC      := $(wildcard src/*.c)
OBJ      := ${SRC:.c=.o}
BIN      := bin
PRG      := main
BENCH	 := benchmark
PRODUCT  := ${BIN}/out
CFLAGS   += ${WARNINGS}
# CFLAGS   += ${RELEASE}
CFLAGS   += ${DEBUG}
CFLAGS	 += -D DEBUG_COUNTS

test: ${PRG}
	${BIN}/${PRG} > ${PRODUCT}.ppm
	pnmtopng ${PRODUCT}.ppm > ${PRODUCT}.png
	open ${PRODUCT}.png

test_gif: ${PRG}
	${BIN}/${PRG}
	./generate_gif.bash

${PRG}: ${OBJ} ${PRG}.c
	${CC} ${CFLAGS} $^ -o ${BIN}/${PRG}


${BENCH}: ${OBJ} ${BENCH}.c
	${CC} ${CFLAGS} $^ -o ${BIN}/${BENCH}
	${BIN}/${BENCH} 2> ${PRODUCT}-benchmark.ppm

.c.o:
	${CC} ${CFLAGS} $< -c -o ${<:.c=.o}

clean:
	rm -rf ${BIN}/* ${OBJ}
