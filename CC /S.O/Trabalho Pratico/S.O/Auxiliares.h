#ifndef AUXILIARES_H
#define AUXILIARES_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TAM_GRANULO 3
#define TAM_MEMORIA 30
#define TRUE 1
#define FALSE 0
typedef struct noSet *ptnoSet;
typedef struct noSet
{
    int inicio, fim;
    ptnoSet prox;
} noSet;
typedef struct noArq *ptnoArq;
typedef struct noArq
{
    char nome[13];
    int caracteres;
    ptnoSet setores;
    ptnoArq prox;
} noArq;

typedef char memoria[TAM_MEMORIA][TAM_GRANULO];


int num_setores_necessarios(int numCaracteres);
int calcula_espaco_livre(ptnoSet Area);
ptnoSet aloca_setores(ptnoSet *Area, int n_setores);
void desaloca_setores(ptnoSet *Area, ptnoSet setores_arquivo);


#endif /* AUXILIARES_H */