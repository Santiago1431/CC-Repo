#define TAM_TAB 100

extern void yyerror(char *s);

enum
{
    INT,
    LOG
};

typedef struct {
    char id[100];
    int end;
    int tip;
 } elemTabSimb;

elemTabSimb tabSimb[TAM_TAB], elemTab;
int topoTab = 0; // Indica a última posição ocupada da tabela

void insereSimbolo (elemTabSimb elem){
    int i;
    if(topoTab == TAM_TAB)
        yyerror ("Tabela de símbolos cheia!");
    for (i = topoTab - 1; strcmp(tabSimb[i].id, elem.id) && i >= 0; i--);

    if(i != -1){
        char msg[200];
        sprintf(msg, "O identificador [%s] é duplicado", elem.id);
        yyerror(msg);
    }
    tabSimb[topoTab++] = elem; 
}

int buscaSimbolo (char *id){
    int i;
    if (topoTab == 0)
        yyerror("Não existem identificadores cadastrados!");
    for(i = topoTab - 1; strcmp(tabSimb[i].id, id); i--);

    if(i == -1){
        char msg[200];
        sprintf(msg, "O identificador [%s] não foi encontrado", id);
            yyerror(msg);
    }
    return i;
}

#define TAM_PIL 100

int Pilha[TAM_PIL];
int topo = 1;

void empilha(int valor){
    if(topo == TAM_PIL)
        yyerror("Pilha cheia");
    Pilha[topo++] = valor;
}

int desempilha (){
    if (topo == -1)
        yyerror("Pilha vazia");
    return Pilha[topo--];
}
