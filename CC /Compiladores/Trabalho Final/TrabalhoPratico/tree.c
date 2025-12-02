
    /*+=============================================================
    | UNIFAL - Universidade Federal de Alfenas 
    | BACHARELADO EM CIENCIA DA COMPUTACAO.
    | Trabalho : Construcao Arvore Sntatica e Geracao de Codigo
    | Disciplina : Teoria de Linguagens e Compiladores
    | Professor : Luiz Eduardo da Silva
    | Aluno: Eurico Santiago Climaco Rodrigues
    | Data: 30/11/2025
    +=============================================================*/

    
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

// Variáveis e Funções Externas 
extern FILE *yyout; 
extern int ROTULO;
extern int contaVar; 
extern int tipo;
extern int deslocamento;
extern elemTabSimb elemTab;
extern elemTabSimb tabSimb[]; 
extern int buscaSimbolo (char *id);
extern void insereSimbolo(elemTabSimb elem);
extern void empilha (int valor);
extern int desempilha();
extern void yyerror(const char *s);
extern void testaTipo(int tipo1, int tipo2, int ret); 
#define INT 1 // Assumindo definição em utils.h
#define LOG 2 


typedef struct no *ptno;

/* =======================================================
   ENUM: Tipos de nós usados no sintático
   ======================================================= */
/* =======================================================
   ENUM: Tipos de nós usados no sintático (ASA)
   ======================================================= */
typedef enum
{
    /* Estrutura geral */
    PROG, DCVR, TIPO, LIVR, LICM, IDF,

    /* Comandos */
    LER, ESCR, REPE, SELE, ATRI,

    /* Expressões aritméticas */
    SOMA, SUBT, MUL, DIV,

    /* Expressões relacionais */
    MAIOR, MENOR, IGUAL,

    /* Expressões lógicas */
    ELOG, OULOG, NEGA,

    /* Termos */
    VAR, NUM, BOOL

} TipoNo;


// Mapeamento dos tipos de nó para strings (para visualização DOT)
const char *nomeTipo[] = {
    "PROG", "DCVR", "TIPO", "LIVR", "LICM", "IDF",
    "LER", "ESCR", "REPE", "SELE", "ATRI",
    "SOMA", "SUBT", "MUL", "DIV",
    "MAIOR", "MENOR", "IGUAL",
    "ELOG", "OULOG", "NEGA",
    "VAR", "NUM", "BOOL"};


struct no
{
    int tipo;
    char valor[100];
    ptno filho, irmao;
};


//prototipos das funções
ptno criaNo(int, const char *);
void adicionaFilho(ptno, ptno);
void mostraArvore(ptno, int);
void geraDot(ptno Raiz);
void geracod(ptno p);


//criando nos na AS
ptno criaNo(int tipo, const char *valor)
{
    ptno n = (ptno)malloc(sizeof(struct no));
    n->tipo = tipo;
    n->filho = NULL;
    n->irmao = NULL;
    if (valor && valor[0] != '\0') // Copia o valor ou um espaço se vazio
        strcpy(n->valor, valor);
    else
        strcpy(n->valor, " ");
    return n;
}

void adicionaFilho(ptno pai, ptno filho)
{
    if (filho)
    {
        filho->irmao = pai->filho; // O novo filho aponta para o antigo primeiro filho
        pai->filho = filho; // O pai aponta para o novo filho
    }
}

void mostraArvore(ptno Raiz, int nivel) // função para criar vertices no grafo (Estetico)
{
    ptno p;
    for (int i = 0; i < nivel; i++)
        printf(" \t");
    printf("[%c|%s]\n", Raiz->tipo, Raiz->valor);
    p = Raiz->filho;
    while (p)
    {
        mostraArvore(p, nivel + 1);
        p = p->irmao;
    }
}

void geraNos(FILE *f, ptno Raiz) // função para criar o arquivo .dot feito em sala, aqui gera os nos no dot
{
    ptno p;
    fprintf(f, "\tn%p [label=\"%s | %s\"];\n", (void *)Raiz, nomeTipo[Raiz->tipo], Raiz->valor); // o casting da raiz foi feito pq %p espera um void e raiz é ptno
    p = Raiz->filho;
    while (p) // recursão para filhos
    {
        geraNos(f, p);
        p = p->irmao;
    }
}
void geraLigacoes(FILE *f, ptno Raiz) // cria as arestas no dot, Percorre a árvore recursivamente e cria arestas do nó pai para todos os seus filhos.
{
    ptno p;
    p = Raiz->filho;
    while (p)
    {
        fprintf(f, "\tn%p -> n%p\n", Raiz, p);
        geraLigacoes(f, p);
        p = p->irmao;
    }
}
void geraDot(ptno Raiz) // função principal para gerar o arquivo DOT e a imagem PNG.
{
    FILE *f = fopen("arvore.dot", "wt");
    fprintf(f, "digraph {\n"); // Escreve o cabeçalho do arquivo DOT
    fprintf(f, "\tnode [shape=record, height= .1] ;\n"); // Define o formato padrão dos nós (retângulo com campos de registro)
    geraNos(f, Raiz);
    geraLigacoes(f, Raiz);
    fprintf(f, "}\n"); // Fecha o bloco digraph e o arquivo
    fclose(f);
    system("dot -Tpng arvore.dot -o arvore.png &");
}

/**
 * @brief Função principal de Geração de Código. Percorre a ASA em pré-ordem
 * e traduz cada nó em instruções MVS, realizando a Análise Semântica (Tipagem).
 * @param p O nó atual da ASA.
 */
void geracod(ptno p){
    if (p==NULL) return;
    ptno p1,p2,p3;
    switch (p->tipo)
    {
    case PROG:
        p1 = p->filho; //IDF cabecalho
        p2 = p1->irmao; // DCVR
        p3 = p2->irmao; //LICM

        fprintf(yyout,"\tINPP\n");
        
        int NUMVAL = 0;
        geracod(p2); // Processa declarações de variáveis
        fprintf(yyout, "\tAMEM\t%d\n", contaVar); // Aloca memória para variáveis
        geracod(p3); // Processa lista de comandos
        fprintf(yyout, "\tDMEM\t%d\n", contaVar); // Desaloca memória
        fprintf(yyout,"\tFIMP"); // Fim do programa
        break;
    case IDF:
        break;;
    case DCVR:
        p1 = p->filho; //TIPO 
        p2 = p1->irmao; // LIVR
        p3 = p2->irmao; //IDF

        geracod(p1); // Processa tipo (inteiro ou logico)
    
        geracod(p2); // Processa lista de variáveis
    
        if (p3) {
            geracod(p3); // Processa próxima declaração
        }
        break;
    case TIPO:
        if (strcmp(p->valor, "inteiro") == 0) {
            tipo = INT;
        } else if (strcmp(p->valor, "logico") == 0) {
            tipo = LOG;
        }
        break;
    case LIVR:
        p1 = p->filho; // Identificador atual
        p2 = p1->irmao; // Próxima lista de variáveis
        
        // Insere variável na tabela de símbolos com tipo e endereço
        strcpy(elemTab.id, p1->valor);
        elemTab.tip = tipo;
        elemTab.end = contaVar++; 
        insereSimbolo(elemTab);
        
        if (p2) {
            geracod(p2); // Processa próximas variáveis
        }
        break;
    case LICM:
        p1 = p->filho;  // Comando
        p2 = p1->irmao; // Próximos comandos

        geracod(p1); // Processa comando atual
        
        if (p2) {
            geracod(p2); // Processa restante da lista
        }
        break;
    case ESCR: 
        p1 = p->filho; // Expressão a ser impressa

        geracod(p1); // Avalia a expressão
        desempilha(); // Remove tipo da pilha
        fprintf(yyout, "\tESCR\n"); // Instrução de escrita
        break;
    case MUL:
        p1 = p->filho; // Operando esquerdo
        p2 = p1->irmao; // Operando direito
        
        geracod(p2); // Avalia segundo operando
        geracod(p1); // Avalia primeiro operando

        testaTipo(INT, INT, INT); // Valida tipos
        fprintf(yyout, "\tMULT\n"); // Multiplicação
        break;
    case NUM:
        fprintf(yyout, "\tCRCT\t%s\n", p->valor); // Carrega constante
        empilha(INT); // Tipo na pilha de tipos
        break;
    case VAR:
        int pos_var = buscaSimbolo(p->valor); // Localiza variável
        
        if (pos_var == -1) {
            char msg[200];
            sprintf(msg, "Variável [%s] não declarada!", p->valor);
            yyerror(msg);
            return;
        }
        
        deslocamento = tabSimb[pos_var].end; // Obtém endereço
        fprintf(yyout, "\tCRVG\t%d\n", deslocamento); // Carrega variável
        empilha(tabSimb[pos_var].tip); // Tipo na pilha
        break;
    case LER:
        p1 = p->filho; // Identificador para leitura

        fprintf(yyout, "\tLEIA\n"); // Instrução de leitura

        int pos = buscaSimbolo(p1->valor);
        
        if (pos == -1) {
            char msg[200];
            sprintf(msg, "Variável [%s] não declarada!", p1->valor);
            yyerror(msg);
            return;
        }
        
        deslocamento = tabSimb[pos].end;
        fprintf(yyout, "\tARZG\t%d\n", deslocamento); // Armazena valor lido
        break;
    case REPE:
        p1 = p->filho; // Condição
        p2 = p1->irmao; // Corpo do loop
        
        fprintf(yyout, "L%d\tNADA\n", ++ROTULO); // Marca início do loop
        empilha(ROTULO);
        
        geracod(p1); // Avalia condição

        fprintf(yyout, "\tDSVF\tL%d\n", ++ROTULO); // Salta se falso
        empilha(ROTULO);
        
        geracod(p2); // Executa corpo

        int r1 = desempilha();
        int r2 = desempilha();
        fprintf(yyout, "\tDSVS\tL%d\n", r2); // Retorna ao início
        fprintf(yyout, "L%d\tNADA\n", r1); // Marca fim do loop
        break;
    case ATRI:
        p1 = p->filho; // Variável alvo
        p2 = p1->irmao; // Expressão
        
        geracod(p2); // Avalia expressão
        
        int pos_atri = buscaSimbolo(p1->valor);
        int tipo_variavel = tabSimb[pos_atri].tip;
        int tipo_expressao = desempilha();
        if (tipo_variavel != tipo_expressao) {
            yyerror("Incompatibilidade de tipo na atribuicao!");
            return;
        }
        
        if (pos_atri == -1) {
            char msg[200];
            sprintf(msg, "Variável [%s] não declarada!", p1->valor);
            yyerror(msg);
            return;
        }
        
        deslocamento = tabSimb[pos_atri].end;
        fprintf(yyout, "\tARZG\t%d\n", deslocamento); // Armazena resultado
        break;
    case SUBT:
        p1 = p->filho;  // Minuendo
        p2 = p1->irmao; // Subtraendo
        
        geracod(p1); // Avalia minuendo
        geracod(p2); // Avalia subtraendo

        testaTipo(INT, INT, INT);
        fprintf(yyout, "\tSUBT\n"); // Subtração
        break;
    case MENOR:
        p1 = p->filho; // Operando esquerdo
        p2 = p1->irmao; // Operando direito
        
        geracod(p1);
        geracod(p2);
        testaTipo(INT, INT, LOG);
        fprintf(yyout, "\tCMME\n"); // Compara menor
        break;
    case SOMA:
        p1 = p->filho; // Primeiro operando
        p2 = p1->irmao; // Segundo operando
        
        geracod(p1);
        geracod(p2);

        testaTipo(INT, INT, INT);
        fprintf(yyout, "\tSOMA\n"); // Adição
        break;
    case SELE: 
        p1 = p->filho; // Condição
        p2 = p1->irmao; // Bloco então
        p3 = p2->irmao; // Bloco senão

        geracod(p1); // Avalia condição

        fprintf(yyout, "\tDSVF\tL%d\n", ++ROTULO); // Salta para senão se falso
        int L_SENAO = ROTULO;
        empilha(L_SENAO);
        
        geracod(p2); // Executa bloco então
        
        fprintf(yyout, "\tDSVS\tL%d\n", ++ROTULO); // Salta para fim
        int L_FIMSE = ROTULO;
        empilha(L_FIMSE);
        int r_sen = desempilha();
        int r_then = desempilha();
        fprintf(yyout, "L%d\tNADA\n", r_then); // Marca início senão
        
        if (p3) {
            geracod(p3); // Executa bloco senão se existir
        }
        
        fprintf(yyout, "L%d\tNADA\n", r_sen); // Marca fim condicional
        break;
    case BOOL: 
        if (strcmp(p->valor, "V") == 0) {
            fprintf(yyout, "\tCRCT\t1\n"); // Verdadeiro = 1
        } else if (strcmp(p->valor, "F") == 0) {
            fprintf(yyout, "\tCRCT\t0\n"); // Falso = 0
        }
        empilha(LOG);
        break;
    case DIV:
        p1 = p->filho;  // Dividendo
        p2 = p1->irmao; // Divisor
        
        geracod(p1);
        geracod(p2);

        testaTipo(INT, INT, INT);
        fprintf(yyout, "\tDIVI\n"); // Divisão inteira
        break;
    case MAIOR:
        p1 = p->filho;  // Operando esquerdo
        p2 = p1->irmao; // Operando direito
        
        geracod(p1);
        geracod(p2);

        testaTipo(INT, INT, LOG);
        fprintf(yyout, "\tCMMA\n"); // Compara maior
        break;
    case IGUAL: 
        p1 = p->filho;  // Operando esquerdo
        p2 = p1->irmao; // Operando direito
        
        geracod(p1);
        geracod(p2);

        testaTipo(INT, INT, LOG);
        fprintf(yyout, "\tCMIG\n"); // Compara igualdade
        break;
    case ELOG: 
        p1 = p->filho;  // Operando esquerdo lógico
        p2 = p1->irmao; // Operando direito lógico
        
        geracod(p1);
        geracod(p2);

        testaTipo(LOG, LOG, LOG);
        fprintf(yyout, "\tCONJ\n"); // E lógico
        break;
    case OULOG: 
        p1 = p->filho;  // Operando esquerdo lógico
        p2 = p1->irmao; // Operando direito lógico
        
        geracod(p1);
        geracod(p2);
        testaTipo(LOG, LOG, LOG);
        fprintf(yyout, "\tDISJ\n"); // OU lógico
        break;
    case NEGA: 
        p1 = p->filho;  // Operando lógico
        
        geracod(p1);

        int t = desempilha();
        if (t != LOG) {
            yyerror("Tipo esperado LOGICO para operacao NAO!");
        }
        fprintf(yyout, "\tNEGA\n"); // Negação lógica
        break;
    default:
        break;
    }
}