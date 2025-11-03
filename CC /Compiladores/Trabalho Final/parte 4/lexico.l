%{
    #include "sintatico.h"
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>

    char atomo[100];
    void msg(char *);
    int nLin = 1; /* Contador de linhas */
%}

identificador [a-zA-Z][a-zA-Z0-9]*
numero [0-9]+
espaco [ \t]+
novalinha [\n]

%x coment

%%
programa        { return T_PROGRAMA; }
inicio          { return T_INICIO; }
fimprograma     { return T_FIM; }

leia            { return T_LEIA; }
escreva         { return T_ESCREVA; }

se              { return T_SE; }
entao           { return T_ENTAO; }
senao           { return T_SENAO; }
fimse           { return T_FIMSE; }

enquanto        { return T_ENQTO; }
faca            { return T_FACA; }
fimenquanto     { return T_FIMENQTO; }

"+"             { return T_MAIS; }
"-"             { return T_MENOS; }
"*"             { return T_VEZES; }

"div"           { return T_DIV; }

">"             { return T_MAIOR; }
"<"             { return T_MENOR; }
"="             { return T_IGUAL; }

"e"             { return T_E; }
"ou"            { return T_OU; }
"nao"           { return T_NAO; }

"<-"            { return T_ATRIB; }
"("             { return T_ABRE; }
")"             { return T_FECHA; }

inteiro         { return T_INTEIRO; }
logico          { return T_LOGICO; }
V               { return T_V; }
F               { return T_F; }

{identificador} {
    strcpy(atomo, yytext);
    return T_IDENTIF;
}

{numero} {
    strcpy(atomo, yytext);
    return T_NUM;
}

{espaco}        /* Ignora espaços e tabulações */

{novalinha}     ++nLin;

"//".*          ;   /* Comentário de linha única */

"/*"            BEGIN(coment);
<coment>"*/"    BEGIN(INITIAL);
<coment>.       ;   /* Ignora qualquer caractere */
<coment>\n      ++nLin;

.               ;   /* Ignora caracteres não reconhecidos (poderia dar erro léxico) */

%%

int yywrap(void) {
    return 1;
}


/*int main(char *s){
    printf("\n%d: %s\n\n", nLin, s);
    exit(10);
}*/
