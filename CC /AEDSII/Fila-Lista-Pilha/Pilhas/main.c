#include <stdio.h>
#include "stack.h"


int main() {
    int stack[MAX];
    int top = -1; // Inicializa o topo da pilha como vazio

    // Operações na pilha
    printf("Empilhando elementos...\n");
    push(stack, &top, 10);
    push(stack, &top, 20);
    push(stack, &top, 30);

    printf("Conteúdo da pilha:\n");
    show(stack, &top);

    printf("Desempilhando um elemento...\n");
    pop(&top);

    printf("Conteúdo da pilha após desempilhar:\n");
    show(stack, &top);

    return 0;
}