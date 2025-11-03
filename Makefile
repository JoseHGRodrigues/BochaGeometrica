PROJ_NAME=ted
ALUNO=
LIBS=-lm

OBJETOS= main.o geo.o qry.o figure.o collision.o queue.o stack.o svg.o

CC=gcc

CFLAGS= -ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration -Wall -Wextra

LDFLAGS=-O0

$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(LDFLAGS) $(OBJETOS) $(LIBS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

main.o: main.c figure.h geo.h qry.h queue.h svg.h

geo.o: geo.c geo.h figure.h queue.h

qry.o: qry.c qry.h collision.h figure.h queue.h stack.h svg.h

figure.o: figure.c figure.h

collision.o: collision.c collision.h figure.h

queue.o: queue.c queue.h

stack.o: stack.c stack.h

svg.o: svg.c svg.h figure.h queue.h
