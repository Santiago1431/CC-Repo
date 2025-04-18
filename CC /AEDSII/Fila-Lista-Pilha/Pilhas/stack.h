#ifndef PILHA_H
#define PILHA_H
#include <stdlib.h>
#include <stdio.h>

#define MAX 10

void push(int p[], int *top, int data);
void pop(int *top);
void show(int p[], int *top);

#endif