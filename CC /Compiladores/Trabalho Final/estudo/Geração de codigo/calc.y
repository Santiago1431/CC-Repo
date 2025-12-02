%{
#include "lexico.c"
%}

%token T_NUM
%token T_ENTER
%token T_MAIS
%token T_MENOS
%token T_MULT
%token T_DIV
%token T_ABRE
%token T_FECHA
%token T_VAR
%token T_RECEBE

%start linha

%left T_MAIS T_MENOS
%left T_DIV T_MULT

%%

linha : linha comando T_ENTER 
    | ;

comando
    : expr          {  }
    | T_VAR T_RECEBE expr {printf("\tARGZ\t%d\n", $1);}
    ;
expr : T_NUM    {printf("\tCRCT\t%d\n", $1);}
    | T_VAR     {printf("\tCRVG\t%d\n", $1);}
    | expr T_MAIS expr  {printf("\tSOMA\n");}
    | expr T_MENOS expr {printf("\tSUBT\n");}
    | expr T_DIV expr {printf("\tDIVI\n");}
    | expr T_MULT expr  {printf("\tMULT\n");}
    | T_ABRE expr T_FECHA {}
    ;

%%

void yyerror(char *s) {
    printf("Erro: %s\n", s);
    exit(10);
}

int main() {
    return yyparse();
}

