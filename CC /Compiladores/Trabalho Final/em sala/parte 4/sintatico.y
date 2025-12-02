%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    void msg(char *);
    int yylex();
    int yyerror(char *);
    extern char atomo[100];
    extern FILE *yyin;
    extern FILE *yyout;
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
    : cabecalho
        {fprintf(yyout, "\tINPP\n");}

      variaveis
        {fprintf(yyout, "\tAMEM\tx\n");}

      T_INICIO lista_comandos T_FIM
        {
           fprintf(yyout, "\tDMEM\tx\n");
           fprintf(yyout, "\tFIMP\n");   
        }
    ;

cabecalho
    : T_PROGRAMA T_IDENTIF
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
        {
           fprintf(yyout, "\tLEIA\n");
           fprintf(yyout, "\tARZG\tx\n");
        }
    ;

escrita
    : T_ESCREVA expressao
        {
           fprintf(yyout, "\tESCR\n");
        }
    ;

repeticao
    : T_ENQTO
        {printf("Lx\tNADA\n");}
      expressao T_FACA 
        {printf("\tDSVF\tLy\n");}
      lista_comandos T_FIMENQTO
        {
           fprintf(yyout, "\tDSVS\tLx\n");
           fprintf(yyout, "Ly\tNADA\n");
        }
    ;

selecao
    : T_SE expressao T_ENTAO 
        { fprintf(yyout, "\tDSVF\tLx\n"); }
    
      lista_comandos T_SENAO 
        {
           fprintf(yyout, "\tDSVS\tLy\n");
           fprintf(yyout, "Lx\tNADA\n");
        }
    
      lista_comandos T_FIMSE
        { fprintf(yyout, "Ly\tNADA\n"); }
    ;

atribuicao
    : T_IDENTIF T_ATRIB expressao
        { fprintf(yyout, "\tARZG\tx\n");}
    ;

expressao
    : expressao T_VEZES expressao
        {printf("\tMULT\n");}
    | expressao T_DIV expressao
        {printf("\tDIV\n");}
    | expressao T_MAIS expressao
        {printf("\tSOMA\n");}
    | expressao T_MENOS expressao
        {printf("\tSUBT\n");}
    | expressao T_MAIOR expressao
        {printf("\tCMMA\n");}
    | expressao T_MENOR expressao
        {printf("\tCMME\n");}
    | expressao T_IGUAL expressao
        {printf("\tCMIG\n");}
    | expressao T_E expressao
        {printf("\tCONJ\n");}
    | expressao T_OU expressao
        {printf("\tDISJ\n");}
    | termo
        
    ;

termo
    : T_IDENTIF
        {printf("\tCRVG\tX\n");}
    | T_NUM
        {printf("\tCRCT\t%s\n", atomo);}
    | T_V
        {printf("\tCRCT\t1\n");}
    | T_F
       {printf("\tCRCT\t0\n");}
    | T_NAO termo
        {printf("\tNEGA\n");}
    | T_ABRE expressao T_FECHA
    ;

%%

int yyerror(char *s){
    msg(s);

}

void msg(char *texto) {
    fprintf(stderr, "Erro: %s\n", texto);
}

int main(int argc, char *argv[]) {
    char nameIn[30], nameOut[30], *p;
    if (argc < 2){
       printf("Uso:\n\t%s <nomefonte>[.simples]\n\n", argv[0]);
        return 10;
    }
    p = strstr(argv[1], ".simples");
    if(p) p = 0;
    strcpy(nameIn,argv[1]);
    strcpy(nameOut,argv[1]);
    strcat(nameIn, ".simples");
    strcat(nameOut, ".mvs");
    yyin = fopen(nameIn, "rt");
    yyout = fopen(nameOut, "wt");

    yyparse();
    printf("programa OK!\n");
}

