%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.c"

//void msg(char *);
extern void yyerror (char *);
extern int yylex();
extern char atomo[100];
extern FILE *yyin;
extern FILE *yyout;

int contaVar = 0;
int tipo;
int rotulo;

%}

%token T_PROGRAMA
%token T_INICIO
%token T_FIM
%token T_IDENTIF
%token T_LEIA
%token T_ESCREVA
%token T_ENQTO
%token T_FACA
%token T_FIMEQTO
%token T_SE
%token T_ENTAO
%token T_SENAO
%token T_FIMSE
%token T_ATRIB
%token T_VEZES
%token T_DIV
%token T_MAIS
%token T_MENOS
%token T_MAIOR
%token T_MENOR
%token T_IGUAL
%token T_E
%token T_OU
%token T_V
%token T_F
%token T_NUMERO
%token T_NAO
%token T_ABRE
%token T_FECHA
%token T_LOGICO
%token T_INTEIRO

%start programa

%left T_E T_OU
%left T_IGUAL
%left T_MAIOR T_MENOR
%left T_MAIS T_MENOS
%left T_VEZES T_DIV

%%

programa
    : cabecalho
        { fprintf(yyout,"\tINPP\n"); }
    variaveis
        { fprintf(yyout,"\tAMEM\t%d\n", contaVar); 
            empilha(contaVar);
        } 
    T_INICIO lista_comandos T_FIM
        { 
            int conta = desempilha(contaVar);
            fprintf(yyout,"\tDMEM\t%d\n", conta); 
            fprintf(yyout,"\tFIMP\n");
        }
    ;

cabecalho
    : T_PROGRAMA T_IDENTIF
    ;

variaveis
    :  /* vazio */;
    | declaracao_variaveis
    ;

declaracao_variaveis
    : tipo lista_variaveis declaracao_variaveis
    | tipo lista_variaveis
    ;

tipo
    : T_LOGICO
        { tipo = LOG; }
    | T_INTEIRO // T_IDENTIF
        { tipo = INT; }
    ;

lista_variaveis
    : lista_variaveis 
    T_IDENTIF 
        {
            strcpy (elemTab.id, atomo);
            elemTab.tip = tipo;
            elemTab.end = contaVar++;
            insereSimbolo(elemTab);
        }
    |
    T_IDENTIF
        {
            strcpy (elemTab.id, atomo);
            elemTab.tip = tipo;
            elemTab.end = contaVar++;
            insereSimbolo(elemTab);
        }
    ;

/* parte1 (lexico)/makefile */

lista_comandos
    : /* vazio */
    | comando lista_comandos
    ;

comando
    : leitura
    | escrita
    | repeticao
    | selecao
    | atribuicao
    ;

leitura
    : T_LEIA T_IDENTIF
    {
        int pos = buscaSimbolo(atomo);
        fprintf(yyout,"\tLEIA\n");
        fprintf(yyout,"\tARZG\t%d\n", tabSimb[pos].end);
    }
    ;

escrita
    : T_ESCREVA expressao
        { fprintf(yyout,"\tESCR\n"); }
    ;

repeticao
    : T_ENQTO 
        { 
            fprintf(yyout,"L%d\tNADA\n", ++rotulo); 
            empilha(rotulo);
        }
    expressao T_FACA
        { 
            fprintf(yyout,"\tDSVF\tL%d\n", ++rotulo); 
            empilha(rotulo);
        }
    lista_comandos T_FIMEQTO
    {
        int y = desempilha();
        int x = desempilha();
        fprintf(yyout,"\tDSVS\tL%d\n", x);
        fprintf(yyout,"L%d\tNADA\n", y);
    }
    ;

selecao
    : T_SE expressao T_ENTAO // T_ENQTO
    { 
        fprintf(yyout,"\tDSVF\tL%d\n", ++rotulo); 
        empilha(rotulo);
    }
    lista_comandos T_SENAO
    {
        int x = desempilha();
        fprintf(yyout,"\tDSVS\tL%d\n", ++rotulo);
        empilha(rotulo);
        fprintf(yyout,"L%d\tNADA\n", x);
    }
    lista_comandos T_FIMSE
        { 
            int y = desempilha();
            fprintf(yyout,"L%d\tNADA\n", y); 
            }
    ;

atribuicao
    : T_IDENTIF 
    {
        int pos = buscaSimbolo(atomo);
        empilha(pos);
    }
    T_ATRIB expressao
        {
            int pos = desempilha();
            fprintf(yyout,"\tARZG\t%d\n", tabSimb[pos].end); 
        }
    ;

expressao
    : expressao T_VEZES expressao
        { fprintf(yyout,"\tMULT\n"); }
    | expressao T_DIV expressao
        { fprintf(yyout,"\tDIV\n"); }
    | expressao T_MAIS expressao
        { fprintf(yyout,"\tSOMA\n"); }
    | expressao T_MENOS expressao
        { fprintf(yyout,"\tSUBT\n"); }
    | expressao T_MAIOR expressao
        { fprintf(yyout,"\tCMMA\n"); }
    | expressao T_MENOR expressao
        { fprintf(yyout,"\tCMME\n"); }
    | expressao T_IGUAL expressao
        { fprintf(yyout,"\tCMIG\n"); }
    | expressao T_E expressao
        { fprintf(yyout,"\tCONJ\n"); }
    | expressao T_OU expressao
        { fprintf(yyout,"\tDISJ\n"); }
    | termo
    ;

termo
    : T_IDENTIF
        {
            int pos = buscaSimbolo(atomo); 
            fprintf(yyout,"\tCRVG\t%d\n", tabSimb[pos].end); 
        }
    | T_NUMERO
        { fprintf(yyout,"\tCRCT\t%s\n", atomo); }
    | T_V
        { fprintf(yyout,"\tCRCT\t1\n"); }
    | T_F
        { fprintf(yyout,"\tCRCT\t0\n");}
    | T_NAO termo
        { fprintf(yyout,"\tNEGA\n"); }
    | T_ABRE expressao T_FECHA
    ;
%%

/*adicionei definição da função msg
void msg(char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}*/

int main(int argc, char *argv[]){
    char nameIn[30], nameOut[30], *p;
    if(argc < 2){
        printf("Uso:%s <nomefonte>[.simples]\n\n", argv[0]);
        return 10;
    }
    p = strstr(argv[1], ".simples");
    if (p) p = 0;
    strcpy(nameIn, argv[1]);
    strcpy(nameOut, argv[1]);
    strcat(nameIn, ".simples");
    strcat(nameOut, ".mvs");
    yyin = fopen(nameIn, "rt");
    yyout = fopen(nameOut, "wt");

    yyparse();
    printf("Programa OK!\n");
}