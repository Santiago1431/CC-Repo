#ifndef ARVORE_H
#define ARVORE_H
#include <stdlib.h>
#include <stdio.h>

//Stuct do no
typedef struct node{
    struct node *dir, *esq;
    int valor, fb;
}No;

int fb(No *n);
int altura(No *n);
No* rotacaoEsquerda(No* raiz);
No* rotacaoDireita(No *raiz);
No* rotacaoDuplaDireita(No *raiz);
No* rotacaoDuplaEsquerda(No *raiz);
No* balancear(No* raiz);
No* inserir(No* r, int valor);
No* encontrarMinimo(No* raiz);
No* remover(No* raiz, int valor);
void imprimir(No* raiz);


#endif // ARVORE_H