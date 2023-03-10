CC=gcc
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: exec

%.o : %.c headers.h 
	$(CC) -c $< -o $@

exec: $(OBJ)
	$(CC) $^ -o $@ -lm

