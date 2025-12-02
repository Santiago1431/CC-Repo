    /*+=============================================================
    | UNIFAL - Universidade Federal de Alfenas 
    | BACHARELADO EM CIENCIA DA COMPUTACAO.
    | Trabalho : Construcao Arvore Sntatica e Geracao de Codigo
    | Disciplina : Teoria de Linguagens e Compiladores
    | Professor : Luiz Eduardo da Silva
    | Aluno: Eurico Santiago Climaco Rodrigues
    | Data: 30/11/2025
    +=============================================================*/

#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h> // Adicionado para incluir exit(), usado em yyerror

// --- Definições da Tabela de Símbolos ---

#define TAM_TAB 100

// enum tipos
enum
{
    INT,
    LOG
};

// struct elemTabSimb 
typedef struct {
    char id[100];
    int end;
    int tip;
 } elemTabSimb;

// Variáveis globais (declaradas como 'extern' para indicar que estão definidas em utils.c)
extern elemTabSimb tabSimb[TAM_TAB];
extern int topoTab; // Indica a última posição ocupada da tabela

// Declarações das funções da Tabela de Símbolos
void insereSimbolo (elemTabSimb elem);
int buscaSimbolo (char *id);


// --- Definições da Pilha ---

#define TAM_PIL 100

// Variáveis globais da pilha
extern int Pilha[TAM_PIL];
extern int topo;

// Declarações das funções da Pilha
void empilha (int valor);
int desempilha();

// Declaração da função de verificação de tipo
void testaTipo(int tipo1, int tipo2, int ret);


// --- Declaração do manipulador de erros (externo) ---

// Essa função é geralmente definida em sintatico.y (ou sintatico.c) ou em utils.c
// Mas é declarada aqui para ser acessível globalmente.
extern void yyerror(const char *s);

#endif // UTILS_H