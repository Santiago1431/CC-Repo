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

#include "tree.c"
#define YYSTYPE ptno
#include "sintatico.h"
void msg(char *);
char atomo[100];

%}

identificador [a-zA-z]([a-zA-Z0-9])*
numero 	      [0-9]+
espaco 	      [ \t]+
novalinha     [\n]

%x coment
%option noyywrap
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
fimenquanto   { return T_FIMENQTO; } 

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
"("           { return T_ABRE; }
")"           { return T_FECHA; }

inteiro       { return T_INTEIRO; }
logico        { return T_LOGICO; }

V             { return T_V; }
F             { return T_F; }

{identificador} {
                  yylval = criaNo(IDF, yytext);
                  return T_IDENTIF;
               }
{numero}       {
                  yylval = criaNo(NUM, yytext);
                  return T_NUM;
               }

{espaco}      /* nao faz nada */
{novalinha}   { ++yylineno; }

"//".* 	     /* faz nada */
"/*"	        BEGIN(coment);
<coment>"*/"  BEGIN(INITIAL);
<coment>.     /* faz nada */
<coment>\n    { yylineno++; }

.             { msg("ERRO LEXICO - simbolo desconhecido!"); }

%%



