%{
#include <stdio.h>
#include <stdlib.h>
#include "lexico.c"

void erro(char *s);
int yyerror (char *);
%}

%start programa

%token T_PROGRAMA
%token T_INICIO
%token T_FIMPROGRAMA
%token T_LEIA
%token T_ESCREVA
%token T_SE
%token T_ENTAO
%token T_SENAO
%token T_FIMSE
%token T_ENQUANTO
%token T_FACA
%token T_FIMENQUANTO
%token T_SOMA
%token T_SUBTRACAO
%token T_MULTIPLICACAO
%token T_DIVISAO
%token T_MAIOR
%token T_MENOR
%token T_IGUAL
%token T_E
%token T_OU
%token T_NAO
%token T_ATRIBUICAO
%token T_ABRE
%token T_FECHA
%token T_INTEIRO
%token T_LOGICO
%token T_V
%token T_F
%token T_IDENTIFICADOR
%token T_NUMERO

%left T_E T_OU
%left T_IGUAL
%left T_MAIOR T_MENOR 
%left T_SOMA T_SUBTRACAO
%left T_MULTIPLICACAO T_DIVISAO

%%
programa
    : cabecalho variaveis T_INICIO lista_comandos T_FIMPROGRAMA
    ;
cabecalho
    : T_PROGRAMA T_IDENTIFICADOR
    ;
variaveis
    : /* vazio */
    | declaracao_variaveis
    ;
declaracao_variaveis // declara variaveis do mesmo tipo
    : tipo lista_variaveis declaracao_variaveis // declara mais variaveis
    | tipo lista_variaveis // declara ultima variavel
    ;
tipo
    : T_INTEIRO
    | T_LOGICO
    ;
lista_variaveis
    : T_IDENTIFICADOR  lista_variaveis // declara mais variaveis
    | T_IDENTIFICADOR // declara ultima variavel
    ;
lista_comandos
    : 
    | comando lista_comandos // mais comandos
    ;
comando 
    : leitura 
    | escrita
    | repeticao
    | selecao
    | atribuicao
    ;
leitura
    : T_LEIA T_IDENTIFICADOR
    ;
escrita
    : T_ESCREVA expr
    ;
repeticao
    : T_ENQUANTO expr T_FACA lista_comandos T_FIMENQUANTO
    ;
selecao 
    : T_SE expr T_ENTAO lista_comandos T_SENAO lista_comandos T_FIMSE
    ;

atribuicao//
    : T_IDENTIFICADOR T_ATRIBUICAO expr
    ;

expr//
    : expr T_SOMA expr
    | expr T_SUBTRACAO expr
    | expr T_DIVISAO expr
    | expr T_MULTIPLICACAO expr

    | expr T_MAIOR expr
    | expr T_MENOR expr
    | expr T_IGUAL expr

    | expr T_E expr
    | expr T_OU expr

    | termo
    ;

termo //
    : T_IDENTIFICADOR
    | T_NUMERO
    | T_V
    | T_F
    | T_NAO termo
    | T_ABRE expr T_FECHA
    ;

%%

void erro(char *s){
    printf("ERRO: %s\n", s);
    exit(10);
}

int yyerror (char *s){
    erro (s);
}

int main (void){
    if (!yyparse())
        puts ("Programa ok");
}