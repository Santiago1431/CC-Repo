%{
    /*+=============================================================
    | UNIFAL - Universidade Federal de Alfenas 
    | BACHARELADO EM CIENCIA DA COMPUTACAO.
    | Trabalho : Construcao Arvore Sntatica e Geracao de Codigo
    | Disciplina : Teoria de Linguagens e Compiladores
    | Professor : Luiz Eduardo da Silva
    | Aluno: Eurico Santiago Climaco Rodrigues
    | Data: 30/11/2025
    +=============================================================*/
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "utils.h"
    #include "lexico.c"

    void yyerror(const char *s);
    int yylex();
    
    
    void msg(char *);

    
    ptno raiz;
%}

%token T_PROGRAMA T_INICIO T_FIM T_IDENTIF  T_LEIA T_ESCREVA
%token T_ENQTO T_FACA T_FIMENQTO  T_SE T_ENTAO T_SENAO T_FIMSE
%token T_ATRIB T_VEZES T_DIV T_MAIS T_MENOS T_MAIOR T_MENOR T_IGUAL 
%token T_E T_OU T_NAO T_V T_F T_NUM
%token T_ABRE T_FECHA T_LOGICO T_INTEIRO

%define parse.trace
%define parse.error verbose


%start programa

%left T_E T_OU
%left T_IGUAL
%left T_MAIOR T_MENOR
%left T_MAIS T_MENOS
%left T_VEZES T_DIV
%right T_NAO

%%

programa: cabecalho  variaveis T_INICIO lista_comandos T_FIM
        {
            raiz = criaNo(PROG, "");
            adicionaFilho(raiz, $4);
            adicionaFilho(raiz, $2);
            adicionaFilho(raiz, $1);

            geraDot(raiz);
            geracod(raiz);
        }
    ;
cabecalho: T_PROGRAMA T_IDENTIF
    {
        $$ = $2;
    }
    ;

variaveis
    : /* vazio */ {$$ = NULL;}
    | declaracao_variaveis
    ;

declaracao_variaveis
    : tipo lista_variaveis declaracao_variaveis
        {
            ptno p = criaNo(DCVR, "");
            adicionaFilho(p, $3);
            adicionaFilho(p, $2);
            adicionaFilho(p, $1);
            $$ = p;
        }
    | tipo lista_variaveis
        {
            ptno p = criaNo(DCVR, "");
            adicionaFilho(p, $2);
            adicionaFilho(p, $1);
            $$ = p;
        }
    ;

tipo
    : T_LOGICO
        {$$ = criaNo(TIPO, "logico");}
    | T_INTEIRO
        {$$ = criaNo(TIPO, "inteiro");}
    ;

lista_variaveis : T_IDENTIF 
        {
            ptno p = criaNo(LIVR, "");
            adicionaFilho(p, $1);
            $$ = p;
        }
    | T_IDENTIF lista_variaveis
        {
            ptno p = criaNo(LIVR, "");
            adicionaFilho(p, $2);
            adicionaFilho(p, $1);
            $$ = p;
        }
    ;

lista_comandos
    : /* vazio */ {$$ = NULL;}
    | comando lista_comandos
        {
            ptno p = criaNo(LICM, "");
            adicionaFilho(p, $2);
            adicionaFilho(p, $1);
            $$ = p;
        }
    ;

comando
    : leitura {$$ = $1;}
    | escrita {$$ = $1;}
    | repeticao {$$ = $1;}
    | selecao {$$ = $1;}
    | atribuicao {$$ = $1;}
    ;

leitura : T_LEIA T_IDENTIF
        {
            ptno p = criaNo(LER, "");
            adicionaFilho(p, $2);
            $$ = p;
        }
    ;

escrita : T_ESCREVA expressao
        {
            ptno p = criaNo(ESCR, "");
            adicionaFilho(p, $2);
            $$ = p;
        }
    ;

repeticao
    : T_ENQTO expressao T_FACA lista_comandos T_FIMENQTO
        {
            ptno p = criaNo(REPE, "");
            adicionaFilho(p, $4);
            adicionaFilho(p, $2);
            $$ = p;
        }
    ;

selecao
    : T_SE expressao T_ENTAO lista_comandos T_SENAO lista_comandos T_FIMSE
        {
            ptno p = criaNo(SELE, "");
            adicionaFilho(p, $6);
            adicionaFilho(p, $4);
            adicionaFilho(p, $2);
            $$ = p;
        }
    ;

atribuicao
    : T_IDENTIF T_ATRIB expressao
        {
            ptno p = criaNo(ATRI, "");
            adicionaFilho(p, $3);
            adicionaFilho(p, $1);
            $$ = p;
        }
    ;

expressao
    : expressao T_VEZES expressao
        {
            ptno p = criaNo(MUL, "");
            adicionaFilho(p, $3);
            adicionaFilho(p, $1);
            $$ = p;
        }
    | expressao T_DIV expressao
        {
            ptno p = criaNo(DIV, "");
            adicionaFilho(p, $3);
            adicionaFilho(p, $1);
            $$ = p;
        }
    | expressao T_MAIS expressao
        {
            ptno p = criaNo(SOMA, "");
            adicionaFilho(p, $3);
            adicionaFilho(p, $1);
            $$ = p;
        }
    | expressao T_MENOS expressao
        {
            ptno p = criaNo(SUBT, "");
            adicionaFilho(p, $3);
            adicionaFilho(p, $1);
            $$ = p;
        }
    | expressao T_MAIOR expressao
        {
            ptno p = criaNo(MAIOR, "");
            adicionaFilho(p, $3);
            adicionaFilho(p, $1);
            $$ = p;
        }
    | expressao T_MENOR expressao
        {
            ptno p = criaNo(MENOR, "");
            adicionaFilho(p, $3);
            adicionaFilho(p, $1);
            $$ = p;
        }
    | expressao T_IGUAL expressao
        {
            ptno p = criaNo(IGUAL, "");
            adicionaFilho(p, $3);
            adicionaFilho(p, $1);
            $$ = p;
        }
    | expressao T_E expressao
        {
            ptno p = criaNo(ELOG, "");
            adicionaFilho(p, $3);
            adicionaFilho(p, $1);
            $$ = p;
        }
    | expressao T_OU expressao
        {
            ptno p = criaNo(OULOG, "");
            adicionaFilho(p, $3);
            adicionaFilho(p, $1);
            $$ = p;
        }
    | termo
    ;

termo
    : T_IDENTIF
        { 
            ptno n = $1;
            n->tipo = VAR;
            $$ = n;
        }
    | T_NUM {$$ = $1;}
    | T_V {$$ = criaNo(BOOL, "V");}
    | T_F {$$ = criaNo(BOOL, "F");}
    | T_NAO termo
        {
            ptno p = criaNo(NEGA, "");
            adicionaFilho(p, $2);
            $$ = p;
        }
    | T_ABRE expressao T_FECHA {$$ = $2;}
    ;

%%

void msg(char *s){ // <--- Deve ser const char *
    printf("ERRO na linha %d: %s\n", yylineno, s); 
    exit(10);
}

void yyerror(const char *s){
    msg("Erro sintatico");
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

    extern int yydebug;
    yydebug = 1;

    if(!yyparse())
        puts("programa OK!");
}


