%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.c"
#include "estrut.c"

void erro(char *s);
int yyerror (char *);
int conta = 0;
int rotulo = 0;
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
    : cabecalho variaveis 
        {
            mostra_tabela();
            fprintf(yyout, "\tAMEM\t%d\n", conta);
            empilha(conta);
        }
    T_INICIO lista_comandos T_FIMPROGRAMA
        {

            fprintf(yyout, "\tDMEM\t%d\n", desempilha());
            fprintf(yyout, "\tFIMP");
        }
    ;
cabecalho
    : T_PROGRAMA T_IDENTIFICADOR 
        {fprintf(yyout, "\tINPP\n");}
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
    : lista_variaveis T_IDENTIFICADOR // declara mais variaveis
        {
            strcpy(elem_tab.id,atomo);
            elem_tab.endereco = conta++;
            insere_simbolo(elem_tab);
        }
    | T_IDENTIFICADOR // declara ultima variavel
        {
            strcpy(elem_tab.id,atomo);
            elem_tab.endereco = conta++;
            insere_simbolo(elem_tab);
        }
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
        {
            fprintf(yyout, "\tLEIA\n");
            int pos = busca_simbolo(atomo);
            if (pos == -1)
                erro("Variavel não declarada");
            fprintf(yyout,"\tARZG\t%d\n", TabSimb[pos].endereco);
        }
    ;
escrita
    : T_ESCREVA expr
        {fprintf(yyout, "\tESCR\n");}
    ;
repeticao
    : T_ENQUANTO
        {
            rotulo++;
            fprintf(yyout, "L%d\tNADA\n", rotulo);
            empilha(rotulo);
        }
        expr T_FACA
            {
                rotulo++;
                fprintf(yyout, "\tDSVF\tL%d\n", rotulo);
                empilha(rotulo);
            }
        lista_comandos T_FIMENQUANTO
            {
                int r1 = desempilha();
                int r2 = desempilha();
                fprintf(yyout, "\tDSVS\tL%d\n", r2);
                fprintf(yyout, "L%d\tNADA\n", r1);
            }
    ;
selecao 
    : T_SE expr T_ENTAO
        {
            rotulo++;
            fprintf(yyout, "\tDSVF\tL%d\n", rotulo);
            empilha(rotulo);
        }
     lista_comandos T_SENAO 
        {
            int r = desempilha();
            rotulo++;
            fprintf(yyout, "\tDSVS\tL%d\n", rotulo);
            empilha(rotulo);
            fprintf(yyout, "L%d\tNADA\n", r);
        }
     lista_comandos T_FIMSE
        {
            int r = desempilha();
            fprintf(yyout, "L%d\tNADA\n", r);
        }
    ;

atribuicao//
    : T_IDENTIFICADOR 
        {
            int pos = busca_simbolo(atomo);
            if (pos == -1)
                erro("Variavel não declarada");
            empilha(TabSimb[pos].endereco);
        }
    T_ATRIBUICAO expr
        {
            int end = desempilha();
            fprintf(yyout, "\tARZG\t%d\n", end);
        }
    ;

expr//
    : expr T_SOMA expr
        {fprintf(yyout, "\tSOMA\n");}
    | expr T_SUBTRACAO expr
        {fprintf(yyout, "\tSUBT\n");}
    | expr T_DIVISAO expr
        {fprintf(yyout, "\tDIVI\n");}
    | expr T_MULTIPLICACAO expr
        {fprintf(yyout, "\tMULT\n");}

    | expr T_MAIOR expr
        {fprintf(yyout, "\tCMMA\n");}
    | expr T_MENOR expr
        {fprintf(yyout, "\tCMME\n");}
    | expr T_IGUAL expr
        {fprintf(yyout, "\tCMIG\n");}

    | expr T_E expr
        {fprintf(yyout, "\tCONJ\n");}
    | expr T_OU expr
        {fprintf(yyout, "\tDISJ\n");}

    | termo
    ;

termo //
    : T_IDENTIFICADOR
        {
            int pos = busca_simbolo(atomo);
            if (pos == -1)
                erro("Variavel não declarada");
            fprintf(yyout, "\tCRVG\t%d\n", TabSimb[pos].endereco);
        }
    | T_NUMERO
        {fprintf(yyout, "\tCRCT\t%s\n", atomo);}
    | T_V
        {fprintf(yyout, "\tCRCT\t1\n");}
    | T_F
        {fprintf(yyout, "\tCRCT\t0\n");}
    | T_NAO termo
        {fprintf(yyout, "\tNEGA\n");}
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

int main (int argc, char *argv[]){

    char nameIn[30], nameOut[30], *p;
    if(argc < 2){
        printf("Uso:%s <nomefonte>[.simples]\n\n", argv[0]);
        exit (10);
    }
    p = strstr(argv[1], ".simples");
    if (p) p = 0;
    strcpy(nameIn, argv[1]);
    strcat(nameIn, ".simples");
    strcpy(nameOut, argv[1]);
    strcat(nameOut, ".mvs");

    yyin = fopen(nameIn, "rt");
    if(!yyin)
    {
        puts ("Progama Fonte nao encontrado!");
        exit(10);
    }
    yyout = fopen(nameOut, "wt");


    if(!yyparse())
        puts("programa OK!");
}