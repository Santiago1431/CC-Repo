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

%start linha

%left T_MAIS T_MENOS
%left T_DIV T_MULT

%%

linha : linha expr T_ENTER     { printf(" Resultado: %d\n", $2);}
    |
    ;
expr : T_NUM    {$$ = $1;}
    | expr T_MAIS expr  {$$ = $1 + $3;}
    | expr T_MENOS expr {$$ = $1 - $3;}
    | expr T_DIV expr {$$ = $1 / $3;}
    | expr T_MULT expr   {$$ = $1 * $3;}
    | T_ABRE expr T_FECHA {$$ = $2;}
    ;

%%

void yyerror(char *s) {
    printf("Erro: %s\n", s);
    exit(10);
}

int main() {
    return yyparse();
}

