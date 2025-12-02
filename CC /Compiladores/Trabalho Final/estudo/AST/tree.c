#include <stdlib.h>
#include <stdio.h>
typedef struct no *ptno;

struct no
{
    int tipo;
    int valor;
    ptno filho, irmao;
};

ptno criaNo (int tipo, int valor){
    ptno n = (ptno)malloc(sizeof(struct no));
    n->valor = valor;
    n->tipo = tipo;
    n->filho = NULL;
    n->irmao = NULL;
    return n;
}

void adicionaFilho (ptno pai, ptno filho){
    if (filho)
    {
        filho->irmao = pai->filho;
        pai->filho = filho;
    }    
}

void mostra(ptno Raiz, int nivel){
    ptno p;
    for (int i = 0; i < nivel; i++)
        printf(" \t");
    printf("[%d|%d]\n", Raiz->tipo, Raiz->valor);
    p = Raiz->filho;
    while (p)
    {
        mostraArvore(p, nivel + 1);
        p = p->irmao;
    }
}


void geraNos(FILE *f, ptno Raiz){
    ptno p;
    fprintf(f,"\tn%p [label=\"%d|%d\"];\n", Raiz, Raiz->tipo, Raiz->valor);
    p = Raiz->filho;
    while (p)
    {
        geraNos(f, p);
        p = p->irmao;
    }
}
void geraLigacoes(FILE *f, ptno Raiz){
    ptno p;
    p = Raiz->filho;
    while (p)
    {
        fprintf(f, "\tn%p -> n%p\n", Raiz, p);
        geraLigacoes(f,p);
        p = p->irmao;
    }
}
void geraDot(ptno Raiz)
{      
    FILE *f = fopen("arvore.dot", "wt");  
    fprintf(f,"digraph {\n");
    fprintf(f, "\tnode [shape=record, height= .1] ;\n");
    geraNos(f, Raiz);
    geraLigacoes(f, Raiz);
    fprintf(f, "}\n");
    fclose(f);
    system("dot -Tpng arvore.dot -o arvore.png &");
    system("eog arvore.png");
}

