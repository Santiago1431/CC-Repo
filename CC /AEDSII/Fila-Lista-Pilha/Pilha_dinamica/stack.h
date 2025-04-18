#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int data;
    struct node *next;
} No;

typedef struct {
   struct node *top;
}Stack;

//Função Push
void push(Stack *p, int data);

//Função pop
int pop(Stack *p);


//Função exibir
void show(Stack *p);