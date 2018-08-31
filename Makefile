NAME := eli

SRCFILES := $(wildcard src/*.c)
OBJFILES := $(patsubst %.c,%.o,${SRCFILES})

CC := clang

CFLAGS := -std=c11 -pedantic-errors -Werror -Weverything -static \
			-fdiagnostics-show-option
#            -Wno-cast-qual -Wno-missing-prototypes -Wno-vla

${NAME}:
	${CC} ${CFLAGS} ${SRCFILES} -o ${NAME}

clean:
	find -name '*.o' -delete
	-rm ${NAME}

.PHONY: clean
