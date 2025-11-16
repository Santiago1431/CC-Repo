# Makefile para o projeto do Simulador de Sistema de Arquivos FAT
CC = gcc

CFLAGS = -Wall -Wextra -g -std=c99

# O nome do executável
TARGET = simuladorFAT

SRCS = FAT.c Auxiliares.c Principais.c Defragmentacao.c


OBJS = $(SRCS:.c=.o)

# --- Regras (Targets) ---

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Dependências dos arquivos .o
FAT.o: FAT.c Principais.h Auxiliares.h Defragmentacao.h

Principais.o: Principais.c Principais.h Auxiliares.h

Defragmentacao.o: Defragmentacao.c Defragmentacao.h Auxiliares.h

Auxiliares.o: Auxiliares.c Auxiliares.h


# Remove o executável e TODOS os arquivos .o
clean:
	rm -f $(TARGET) $(OBJS)

# Compila (se necessário) e roda o programa
run: all
	./$(TARGET)

# Declara regras que não são nomes de arquivos
.PHONY: all clean run