#define TAM_TAB 100
#define TAM_PIL 100

//pilha semantica
int Pilha[TAM_PIL];
int topo = -1;

//Tabela de simbolos
struct elem_tab_simbolos {
    char id[100];
    int endereco;
    char tipo;
} TabSimb[TAM_TAB], elem_tab;
int pos_tab = 0;


//Rotinas de pilha
void empilha(int v){
    if (topo == TAM_PIL){
        erro("Pilha cheia!");
    }
    Pilha[++topo] = v;
}

int desempilha(){
    if (topo == -1)
        erro("Pilha Vazia!");
    return Pilha[topo--]; 
}

//Rotinas da pilha semantica
//retorna -1 se ñ encontra o id
int busca_simbolo(char *id){
    int i = pos_tab - 1;
    for (;strcmp(TabSimb[i].id, id) && i >= 0; i--);
    return i;   
}

void insere_simbolo (struct elem_tab_simbolos elem)
{
    int i;
    if (pos_tab == TAM_TAB)
        erro("Tabela Cheia");
    i = busca_simbolo(elem.id);    
    if (i != -1)
        erro("id duplicado");
    TabSimb[pos_tab++] = elem;  
}


void mostra_tabela(){
    int i;
    puts("Tabela de simbolos\n");
    printf("\n%3s | %30s | %s | %s\n", "#", "ID", "ENDEREÇO", "TIPO");
    for (i = 0; i < 55; i++)
        printf("-");
    for ( i = 0; i < pos_tab; i++)
        printf("\n%3d | %30s | %7d  | %3c ", i, TabSimb[i].id, TabSimb[i].endereco, TabSimb[i].tipo);
    puts("\n");
}




