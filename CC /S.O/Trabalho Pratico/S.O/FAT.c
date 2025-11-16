/*
+-------------------------------------------------------------+
 | UNIFAL – Universidade Federal de Alfenas. |
 | BACHARELADO EM CIENCIA DA COMPUTACAO. |
 | Trabalho..: SIMULACAO DE SISTEMA DE ARQUIVOS FAT |
 | Disciplina: Sistemas Operacionais |
 | Professor.: Luiz Eduardo da Silva e Romario da Silva Borges |
 | Aluno(s)..: Eurico Santiago Climaco Rodrigues |
 | Data......: 15/11/2025 |
 +-------------------------------------------------------------+
 */

/*-------------------------------------------------
 * Simulador de FAT - File Allocation Table
 * Luiz Eduardo da Silva
 *-------------------------------------------------*/
#include <ctype.h>
#include "Auxiliares.h"
#include "Principais.h"
#include "Defragmentacao.h"

void mostraSetores(ptnoSet S, char *n)
{
    printf("%s = [", n);
    while (S)
    {
        printf("(%d,%d)", S->inicio, S->fim);
        S = S->prox;
        if (S)
            printf(",");
    }
    printf("]\n");
}

void mostraArquivos(ptnoArq A)
{
    printf("Arquivos:\n");
    while (A)
    {
        printf(" %12s, %2d caracter(es). ", A->nome, A->caracteres);
        mostraSetores(A->setores, "Setores");
        A = A->prox;
    }
    printf("\n");
}

void mostraMemoria(memoria Memo)
{
    int i, j;
    for (i = 0; i < TAM_MEMORIA; i++)
    {
        printf("%3d:[", i);
        for (j = 0; j < TAM_GRANULO - 1; j++)
            printf("%c,", Memo[i][j]);
        printf("%c]", Memo[i][TAM_GRANULO - 1]);
        if ((i + 1) % 10 == 0)
            printf("\n");
    }
}

void inicia(ptnoSet *Area, ptnoArq *Arq, memoria Memo)
{
    int i, j;
    *Area = (ptnoSet)malloc(sizeof(noSet));
    (*Area)->inicio = 0;
    (*Area)->fim = TAM_MEMORIA - 1;
    (*Area)->prox = NULL;
    *Arq = NULL;
    for (i = 0; i < TAM_MEMORIA; i++)
        for (j = 0; j < TAM_GRANULO; j++)
            Memo[i][j] = ' ';
}

/*---------------------------------------------
 * Implementar as rotinas para simulacao da FAT
 *---------------------------------------------*/
void ajuda()
{
    printf("\nCOMANDOS\n");
    printf("--------\n");
    printf("G <arquivo.txt> <texto><ENTER>\n");
    printf(" -Grava o <arquivo.txt> e conteúdo <texto> no disco\n");
    printf("D <arquivo.txt>\n");
    printf(" -Deleta o <arquivo.txt> do disco\n");
    printf("A <arquivo.txt>\n");
    printf(" -Apresenta o conteudo do <arquivo.txt>\n");
    printf("M\n");
    printf(" -Mostra as estruturas utilizadas\n");
    printf("O\n"); // linha da Defragmentação adicionada
    printf(" -Otimiza (defragmenta) o disco\n"); // linha da Defragmentação adicionada
    printf("H\n");
    printf(" -Apresenta essa lista de comandos\n");
    printf("F\n");
    printf(" -Fim da simulacao\n");
}

/*------------------------------------------
 * CORPO PRINCIPAL DO PROGRAMA
 *------------------------------------------*/
int main(void)
{
    ptnoSet Area, set;
    ptnoArq Arq, ant;
    memoria Memo;
    char com[3];
    char nome[13];
    char texto[TAM_MEMORIA * TAM_GRANULO];
    inicia(&Area, &Arq, Memo);
    do
    {
        // Alterações feitas aqui para melhorar a interface
        printf("\nDigite H para ajuda\n");
        printf("\n=> ");
        scanf("%3s", com);
        com[0] = toupper(com[0]);
        switch (com[0])
        {
        case 'G':
            scanf("%s", nome);     // Lê o nome
            scanf(" %[^\n]", texto); // Lê o texto (com espaços) até o ENTER
            // Debug: Imprime o que foi lido
            printf("nome = %s\n", nome);
            printf("texto = %s\n", texto);
            // Chama a função que implementamos
            gravar(&Arq, &Area, Memo, nome, texto);
            break;
        case 'D':
            scanf("%s", nome);
            // printf("nome %s\n", nome); // debug
            // Chama a função que implementamos
            deletar(&Arq, &Area, Memo, nome);
            
            break;
        case 'A':
            scanf("%s", nome);
            // printf("nome %s\n", nome); // Debug
            
            // Chama a função que implementamos
            apresentar(Arq, Memo, nome);
            
            break;
        case 'M':
            mostraSetores(Area, "Area");
            mostraArquivos(Arq);
            printf("Memoria:\n");
            mostraMemoria(Memo);
            break;
        case 'H':
            ajuda();
            break;
        case 'O': // Caso da Defragmentação
            defragmentar(&Arq, &Area, Memo);
            printf("Disco otimizado com sucesso.\n");
            break;
        }
    } while (com[0] != 'F');
    printf("\nFim da Execucao\n\n");
    return (EXIT_SUCCESS);
}

