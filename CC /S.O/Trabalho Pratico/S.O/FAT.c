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

// Funcao pra printar os setores, ajuda a debugar
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

// Mostra a lista de arquivos e os setores que eles ocupam
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

// Printa a memoria pra ver o que tem dentro
void mostraMemoria(memoria Memo)
{
    int i, j;
    for (i = 0; i < TAM_MEMORIA; i++)
    {
        printf("%3d:[", i);
        for (j = 0; j < TAM_GRANULO - 1; j++)
            printf("%c,", Memo[i][j]);
        printf("%c]", Memo[i][TAM_GRANULO - 1]);
        if ((i + 1) % 10 == 0) // Quebra a linha a cada 10 setores pra ficar mais legivel
            printf("\n");
    }
}

// Prepara o sistema pra comecar
void inicia(ptnoSet *Area, ptnoArq *Arq, memoria Memo)
{
    int i, j;
    // A area livre comeca como um bloco unico pegando a memoria toda
    *Area = (ptnoSet)malloc(sizeof(noSet));
    (*Area)->inicio = 0;
    (*Area)->fim = TAM_MEMORIA - 1;
    (*Area)->prox = NULL;
    // Nenhum arquivo no comeco
    *Arq = NULL;
    // Limpa a memoria, preenche com espacos
    for (i = 0; i < TAM_MEMORIA; i++)
        for (j = 0; j < TAM_GRANULO; j++)
            Memo[i][j] = ' ';
}

/*---------------------------------------------
 * Menu de ajuda, basico
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
    printf("O\n"); // Adicionei o comando de otimizar (defragmentar)
    printf(" -Otimiza (defragmenta) o disco\n");
    printf("H\n");
    printf(" -Apresenta essa lista de comandos\n");
    printf("F\n");
    printf(" -Fim da simulacao\n");
}

/*------------------------------------------
 * CORPO PRINCIPAL DO PROGRAMA
 * Onde a magica acontece
 *------------------------------------------*/
int main(void)
{
    ptnoSet Area; // Nao precisa de 'set' e 'ant' aqui, as funcoes cuidam disso
    ptnoArq Arq;
    memoria Memo;
    char com[3];
    char nome[13];
    char texto[TAM_MEMORIA * TAM_GRANULO]; // Buffer pra ler o texto do usuario

    inicia(&Area, &Arq, Memo); // Prepara tudo

    do
    {
        // Interface simples pro usuario
        printf("\nDigite H para ajuda\n");
        printf("\n=> ");
        scanf("%2s", com); // Le o comando, no maximo 2 chars + \0
        com[0] = toupper(com[0]); // Ignora se o usuario digitou 'g' ou 'G'

        switch (com[0])
        {
        case 'G':
            scanf("%s", nome);     // Le o nome
            scanf(" %[^\n]", texto); // Le o texto (com espacos) ate o ENTER. O espaco antes do % e importante!
            // Deixei uns prints pra debugar e ver se o scanf tava funcionando direito
            // printf("nome = %s\n", nome);
            // printf("texto = %s\n", texto);
            gravar(&Arq, &Area, Memo, nome, texto);
            break;
        case 'D':
            scanf("%s", nome);
            // printf("nome %s\n", nome); //  debug
            deletar(&Arq, &Area, Memo, nome);
            break;
        case 'A':
            scanf("%s", nome);
            // printf("nome %s\n", nome); //  debug
            apresentar(Arq, Memo, nome);
            break;
        case 'M':
            // O "dump" de memoria, pra ver como as coisas estao
            mostraSetores(Area, "Area");
            mostraArquivos(Arq);
            printf("Memoria:\n");
            mostraMemoria(Memo);
            break;
        case 'H':
            ajuda();
            break;
        case 'O': 
            defragmentar(&Arq, &Area, Memo);
            // Nao precisa de msg de sucesso aqui, a funcao ja imprime
            break;
        }
    } while (com[0] != 'F');

    printf("\nFim da Execucao\n\n");
    return (EXIT_SUCCESS);
}

