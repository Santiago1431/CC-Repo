%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    void msg(char *);
    int yylex();
    int yyerror(char *);
%}

%token T_PROGRAMA T_INICIO T_FIM T_IDENTIF
%token T_LEIA T_ESCREVA
%token T_ENQTO T_FACA T_FIMENQTO
%token T_SE T_ENTAO T_SENAO T_FIMSE
%token T_ATRIB T_VEZES T_DIV T_MAIS T_MENOS
%token T_MAIOR T_MENOR T_IGUAL T_E T_OU T_NAO
%token T_ABRE T_FECHA
%token T_LOGICO T_INTEIRO
%token T_V T_F T_NUM

%start programa

%left T_E T_OU
%left T_IGUAL
%left T_MAIOR T_MENOR
%left T_MAIS T_MENOS
%left T_VEZES T_DIV
%right T_NAO

%%

programa
    : T_PROGRAMA variaveis T_INICIO lista_comandos T_FIM
    ;

variaveis
    : /* vazio */
    | declaracao variaveis
    ;

declaracao
    : tipo lista_variaveis
    ;

tipo
    : T_LOGICO
    | T_INTEIRO
    ;

lista_variaveis
    : T_IDENTIF lista_variaveis
    | T_IDENTIF
    ;

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
    ;

escrita
    : T_ESCREVA expressao
    ;

repeticao
    : T_ENQTO expressao T_FACA lista_comandos T_FIMENQTO
    ;

selecao
    : T_SE expressao T_ENTAO lista_comandos T_SENAO lista_comandos T_FIMSE
    ;

atribuicao
    : T_IDENTIF T_ATRIB expressao
    ;

expressao
    : expressao T_VEZES expressao
    | expressao T_DIV expressao
    | expressao T_MAIS expressao
    | expressao T_MENOS expressao
    | expressao T_MAIOR expressao
    | expressao T_MENOR expressao
    | expressao T_IGUAL expressao
    | expressao T_E expressao
    | expressao T_OU expressao
    | termo
    ;

termo
    : T_IDENTIF
    | T_NUM
    | T_V
    | T_F
    | T_NAO termo
    | T_ABRE expressao T_FECHA
    ;

%%

int yyerror(char *s){
    msg(s);
    return 0;
}

int main() {
    yyparse();
    printf("programa OK!\n");
    return 0;
}
