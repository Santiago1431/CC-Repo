#include "stack.h"

//Função Push
void push(Stack *p, int data){
    No *newNode = malloc(sizeof(No));
    if (!newNode){
        printf("Error, Stack Overflow or element not alloc successful\n");
        return;
    }
    newNode->data = data;
    newNode->next = p->top;
    p->top = newNode;
}

//Função pop
int pop(Stack *p){
    No *aux = p->top;
    int result;
    if(!aux){
        printf("Erro, Stack is Empty\n");
        return -1;
    }else
        p->top = aux->next;
        aux->next = NULL;
        result = aux->data;
        free(aux);
        return result;
}


//Função exibir
void show(Stack *p){
    No *aux = p->top;
    if(!aux){
       printf("Error, Stack is Empty\n");
       return;
    }
    
    while(aux != NULL){
        printf("%d\n", aux->data);
        aux = aux->next;
    }
}