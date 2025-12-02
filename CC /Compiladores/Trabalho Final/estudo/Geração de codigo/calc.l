%{

#include "calc.h"
#include <stdlib.h>
void yyerror(char *);
%}

%%
[0-9]+    { yylval = atoi(yytext); return T_NUM; }
[A-Z] {yylval = *yytext - 'A'; return T_VAR;}
[a-z] {yylval = *yytext - 'a'; return T_VAR;}
"=" {return T_RECEBE;}
"+"    { return T_MAIS; }
"-"    { return T_MENOS; }
"*"    { return T_MULT; }
"/"    { return T_DIV;}
"("    { return T_ABRE; }
")"    { return T_FECHA; }
"\n"    { return T_ENTER; }

[ \t]    /* faz nada */
.  yyerror("erro lexico - simbolo desconhecido ");

%%

int yywrap (void){
    return 1;
}