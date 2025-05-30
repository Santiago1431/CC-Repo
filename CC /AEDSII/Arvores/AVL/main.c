#include "arvore.h"

int main() {
    No *raiz = NULL;

    // Inserindo elementos
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 25);

    printf("Árvore em ordem:\n");
    imprimir(raiz);
    printf("\n");

    // Removendo um elemento
    raiz = remover(raiz, 20);
    printf("Árvore após remover 20:\n");
    imprimir(raiz);
    printf("\n");

    // Liberando memória
    free(raiz);

    return 0;
}