%{
      #include "sintatico.h"
      char atomo[100];
      void yyerror(char *);
      int nlin = 1;  /* variável para contar as linhas, mantido na versão anterior, alterado na do Luizinho */
%}

identificador [a-zA-z]([a-zA-Z0-9])*
numero 	      [0-9]+
espaco 	      [ \t]+
novalinha     [\n]

%x coment
%%

programa      { return T_PROGRAMA; }
inicio        { return T_INICIO; }
fimprograma   { return T_FIM; }
leia          { return T_LEIA; }
escreva       { return T_ESCREVA; }
se            { return T_SE; }
entao	        { return T_ENTAO; }
senao         { return T_SENAO; }
fimse         { return T_FIMSE; }
enquanto      { return T_ENQTO; }
faca          { return T_FACA; }
fimenquanto   { return T_FIMEQTO; } /* nome está errado no sintático */

"+"           { return T_MAIS; }
"-"           { return T_MENOS; }
"*"           { return T_VEZES; }
"div"         { return T_DIV; }

">"           { return T_MAIOR; }
"<"           { return T_MENOR; }
"="           { return T_IGUAL; }

"e"           { return T_E; }
"ou"          { return T_OU; }
"nao"         { return T_NAO; }

"<-"          { return T_ATRIB; }
"{"           { return T_ABRE; }
"}"           { return T_FECHA; }

inteiro       { return T_INTEIRO; }
logica        { return T_LOGICO; }

V             { return T_V; }
F             { return T_F; }

{identificador} {
                  strcpy (atomo, yytext);
                  return T_IDENTIF;
               }
{numero}       {
                  strcpy (atomo, yytext);
                  return T_NUMERO;
               }

{espaco}      /* nao faz nada */
{novalinha}   { ++yylineno; }

"//".* 	     /* faz nada */
"/*"	        BEGIN(coment);
<coment>"*/"  BEGIN(INITIAL);
<coment>.     /* faz nada */
<coment>\n    { yylineno++; }

.             { yyerror("ERRO LEXICO - simbolo desconhecido!"); }

%%

//corpo da função yyerror
void yyerror(char *s) {
    printf("\n%d: %s\n\n", yylineno, s);
    exit(10);
}

int yywrap(void) { return 1; }



