    /*+=============================================================
    | UNIFAL - Universidade Federal de Alfenas 
    | BACHARELADO EM CIENCIA DA COMPUTACAO.
    | Trabalho : Construcao Arvore Sntatica e Geracao de Codigo
    | Disciplina : Teoria de Linguagens e Compiladores
    | Professor : Luiz Eduardo da Silva
    | Aluno: Eurico Santiago Climaco Rodrigues
    | Data: 30/11/2025
    +=============================================================*/

#include "utils.h"



elemTabSimb tabSimb[TAM_TAB], elemTab;
int topoTab = 0; // Indica a última posição ocupada da tabela
int contaVar = 0;
int tipo;
int deslocamento;
int ROTULO = 0;
int AUX_ROTULO = 0;
void insereSimbolo (elemTabSimb elem){
    int i;
    if(topoTab == TAM_TAB)
        yyerror ("Tabela de símbolos cheia!");
    for (i = topoTab - 1; strcmp(tabSimb[i].id, elem.id) && i >= 0; i--);

    if(i != -1){
        char msg[200];
        sprintf(msg, "O identificador [%s] é duplicado", elem.id);
        yyerror(msg);
    }
    tabSimb[topoTab++] = elem; 
}

int buscaSimbolo (char *id){
    int i;
    if (topoTab == 0)
        yyerror("Não existem identificadores cadastrados!");
    for(i = topoTab - 1; strcmp(tabSimb[i].id, id) && i >= 0; i--);

    if(i == -1){
        char msg[200];
        sprintf(msg, "O identificador [%s] não foi encontrado", id);
            yyerror(msg);
    }
    return i;
}

#define TAM_PIL 100

int Pilha[TAM_PIL];
int topo = -1;

void empilha (int valor){
    if(topo == TAM_PIL - 1)
        yyerror("Pilha cheia!");
    Pilha[++topo] = valor;
}

int desempilha(){
    if(topo == -1)
        yyerror("Pilha vazia!");
    return Pilha[topo--];
}

// tipo1 e tipo2 são os tipos esperados na expressão
// ret é o tipo que será empilhado com resultado de expressão (novo)
void testaTipo(int tipo1, int tipo2, int ret){
// Renomeando para clareza:
    int tipo_real_E2 = desempilha(); // Pega o tipo do topo (E2)
    int tipo_real_E1 = desempilha(); // Pega o tipo debaixo (E1)
    
    // A verificação deve ser: (Tipo Real E1 == Tipo Esperado E1) E (Tipo Real E2 == Tipo Esperado E2)
    if(tipo_real_E1 != tipo1 || tipo_real_E2 != tipo2){ 
        yyerror("Incompativilidade de tipo!");
    }
    empilha(ret);
}