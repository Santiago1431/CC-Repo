# Nome do executável
EXEC = avl

# Compilador e flags
CC = gcc
CFLAGS = -Wall -O2

# Fontes e objetos
SRCS = main.c Arvore.c
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -f *.o *.exe

.PHONY: all clean