#include "stack.h"

void push(int p[], int *top, int data){
    //verifica se a pilha esta cheia
    if (*top >= MAX-1)
        printf("Stack Is Full\n");
    else {
        *top = *top + 1;
        p[*top] = data;
    }
}

void pop(int *top){
    //verifica que pilha esta vazia
    if (*top == -1)
        printf("Pilha is Empty");
    else
        *top = *top - 1;
}

void show(int p[], int *top){
    for (int i = *top; i >= 0; i--){
        printf("%d\n", p[i]);
    }
}