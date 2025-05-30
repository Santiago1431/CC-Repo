#include "Arvore.h"
#include <stdio.h>
#include <stdlib.h>

int altura(No *n) {
    if (n == NULL) {
        return 0;
    }
    int alt_esq = altura(n->esq);
    int alt_dir = altura(n->dir);
    return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

int fb(No *n){
    if (n == NULL) {
        return 0;
    }
    return altura(n->esq) - altura(n->dir);
}

No* rotacaoEsquerda(No* raiz){
    No *temp = raiz->dir;
    raiz->dir = temp->esq;
    temp->esq = raiz;

    raiz->fb = fb(raiz);
    temp->fb = fb(temp);

    return temp;
}

No* rotacaoDireita(No *raiz){
    No *temp = raiz->esq;
    raiz->esq = temp->dir;
    temp->dir = raiz;

    raiz->fb = fb(raiz);
    temp->fb = fb(temp);

    return temp;
}

No* rotacaoDuplaDireita(No *raiz){
    raiz->esq = rotacaoEsquerda(raiz->esq);
    return rotacaoDireita(raiz);
}

No* rotacaoDuplaEsquerda(No *raiz){
    raiz->dir = rotacaoDireita(raiz->esq);
    return rotacaoEsquerda(raiz);
}

No* balancear(No* raiz){
    raiz->fb = fb(raiz);

    if (raiz->fb > 1){
        if (fb(raiz->esq) >= 0){
            return rotacaoDireita(raiz);
        }else {
            rotacaoDuplaDireita(raiz);
        } 
    }

    if (raiz->fb < -1){
        if (fb(raiz->dir) <= 0){
            return rotacaoEsquerda(raiz);
        }else {
            rotacaoDuplaEsquerda(raiz);
        } 
    }
    return raiz;
}

No* inserir(No* r, int valor){
    if (r == NULL){
        No* novo = (No*)malloc(sizeof(No));
        novo->valor = valor;
        novo->dir = novo->esq = NULL;
        novo->fb = 0;
        return novo;
    }

    if (valor < r->valor){
        r->esq = inserir(r->esq, valor);
    }else if (valor > r->valor){
        r->dir = inserir(r->dir, valor);
    } else{
        return r;
    }
    return balancear(r);  
}

No* encontrarMinimo(No* raiz) {
    if (raiz == NULL) return NULL;
    while (raiz->esq != NULL) {
        raiz = raiz->esq;
    }
    return raiz;
}

No* remover(No* raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        if (raiz->esq == NULL || raiz->dir == NULL) {
            No* temp = raiz->esq ? raiz->esq : raiz->dir;
            free(raiz);
            return temp;
        } else {
            No* temp = encontrarMinimo(raiz->dir);
            raiz->valor = temp->valor;
            raiz->dir = remover(raiz->dir, temp->valor);
        }
    }
    return balancear(raiz);
}


void imprimir(No* raiz) {
    if (raiz == NULL) return;
    imprimir(raiz->esq);
    printf("%d\n", raiz->valor);
    imprimir(raiz->dir);
}