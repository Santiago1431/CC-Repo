%{
#include "sintatico.h"
void erro(char *s);
char atomo[100];
int contadorLin = 1;
%}

identificador [a-zA-Z][a-zA-Z0-9]*
numero [0-9]+
espaco [ \t]+
novalinha [\n]

%x coment
%option noyywrap

%%

programa     { return T_PROGRAMA;}
inicio    { return T_INICIO;}
fimprograma    { return T_FIMPROGRAMA;}

leia    { return T_LEIA;}
escreva    { return T_ESCREVA;}

se    { return T_SE;}
entao    { return T_ENTAO;}
senao    { return T_SENAO;}
fimse    { return T_FIMSE;}

enquanto    { return T_ENQUANTO;}
faca    { return T_FACA;}
fimenquanto    { return T_FIMENQUANTO;}
"+"    { return T_SOMA;}
"-"    { return T_SUBTRACAO;}
"*"    { return T_MULTIPLICACAO;}

"div"    { return T_DIVISAO;}
">"    { return T_MAIOR;}
"<"    { return T_MENOR;}
"="    { return T_IGUAL;}
"e"    { return T_E;}
"ou"    { return T_OU;}
"nao"    { return T_NAO;}

"<-"    { return T_ATRIBUICAO;}
"("    { return T_ABRE;}
")"    { return T_FECHA;}

inteiro    { return T_INTEIRO;}
logico    { return T_LOGICO;}
V    { return T_V;}
F    { return T_F;}

{identificador}    { strcpy(atomo, yytext); return T_IDENTIFICADOR;}
{numero}    { strcpy(atomo, yytext); return T_NUMERO;}
{espaco}    /* nada */
{novalinha} { ++contadorLin;}
"//".*          ;   /* Comentário de linha única */
"/*"            BEGIN(coment);
<coment>"*/"    BEGIN(INITIAL);
<coment>.       ;   /* Ignora qualquer caractere */
<coment>\n      ++contadorLin;
.           { erro("caractere invalido -> erro lexico"); }


%%
