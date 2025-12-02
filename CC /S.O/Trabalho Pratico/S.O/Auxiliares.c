#include <stdio.h>
#include <stdlib.h>
#include "Auxiliares.h"


// Função matemática simples.
// Calcula quantos setores um arquivo precisa com base no seu tamanho em bytes.
int num_setores_necessarios(int numCaracteres)
{
    if (numCaracteres == 0)
    {
        return 0;
    }
   // Truque de programador pra fazer divisão com teto (ceiling division) com inteiros.
   // Ex: 7 caracteres, granulo de 3. (7 + 3 - 1) / 3 = 9 / 3 = 3 setores. Correto.
    return (numCaracteres + TAM_GRANULO - 1) / TAM_GRANULO ;
}

// Percorre a lista de área livre e soma o tamanho de cada bloco.
int calcula_espaco_livre(ptnoSet Area)
{
    int total_livre = 0;
    ptnoSet atual = Area;
    while (atual != NULL) {
        // O tamanho de um bloco é (fim - inicio + 1). Ex: (5,7) -> 7-5+1=3 setores.
        total_livre += (atual->fim - atual->inicio) + 1;
        atual = atual->prox;
    }
    return total_livre;
}

/**
 * Aloca 'n_setores' da lista de área livre (Area).
 * Essa é a função mais chatinha. Ela tem que encontrar espaço livre,
 * quebrar os blocos de área livre e retornar uma nova lista com os setores alocados.
 */
ptnoSet aloca_setores(ptnoSet *Area, int n_setores) {
    // Primeiro, vamos ver se tem espaço suficiente no total.
    // Se não tiver, nem adianta começar a procurar.
    if (calcula_espaco_livre(*Area) < n_setores) {
        printf("Erro: Espaco insuficiente no disco.\n");
        return NULL;
    }

    ptnoSet lista_alocada = NULL; // Lista que vamos retornar com os setores que encontramos.
    int setores_restantes = n_setores;

    // Ponteiro duplo pra facilitar a remoção/modificação dos nós da lista 'Area'.
    ptnoSet *ant = Area;
    ptnoSet atual = *Area;

    // Agora sim, vamos procurar os blocos e alocar.
    while (setores_restantes > 0 && atual != NULL) {
        int tamanho_bloco = (atual->fim - atual->inicio) + 1;

        // Prepara o nó que vamos adicionar na lista de retorno.
        ptnoSet novo_no_alocado = (ptnoSet)malloc(sizeof(noSet));
        if (novo_no_alocado == NULL) {
            printf("Erro: Falha ao alocar memoria para no de setor.\n");
            // TODO: Se falhar aqui no meio, a gente deveria liberar a 'lista_alocada' que já montamos.
            return NULL;
        }

        if (tamanho_bloco > setores_restantes) {
            // Caso 1: O bloco de espaço livre é MAIOR do que o que a gente precisa agora.
            // Então a gente pega só um pedaço dele.

            // O novo nó alocado vai do início do bloco até o tanto que precisamos.
            novo_no_alocado->inicio = atual->inicio;
            novo_no_alocado->fim = atual->inicio + setores_restantes - 1;

            // O bloco de área livre 'atual' encolhe, começando de onde a gente parou de pegar.
            atual->inicio = novo_no_alocado->fim + 1;

            setores_restantes = 0; // Acabou, já pegamos tudo.

        } else {
            // Caso 2: O bloco é MENOR ou IGUAL ao que a gente precisa.
            // Então a gente pega o bloco inteiro.

            novo_no_alocado->inicio = atual->inicio;
            novo_no_alocado->fim = atual->fim;

            setores_restantes -= tamanho_bloco; // Diminui o que ainda falta pegar.

            // Remove o bloco 'atual' da lista de área livre, porque pegamos ele todo.
            *ant = atual->prox;
            free(atual);
            atual = *ant; // 'atual' agora aponta para o próximo item da lista.
        }

        // Adiciona o novo nó alocado na lista de retorno (no início, que é mais rápido).
        novo_no_alocado->prox = lista_alocada;
        lista_alocada = novo_no_alocado;

        // Se o 'if' de cima não removeu o nó 'atual', a gente precisa avançar os ponteiros manualmente.
        if (atual != NULL && tamanho_bloco > setores_restantes) { // Correção de bug: faltava essa checagem
             ant = &atual->prox;
             atual = atual->prox;
        }
    }

    return lista_alocada; // Retorna a lista de setores que o arquivo vai usar.
}

/**
 * Devolve uma lista de setores para a área livre.
 * Tão chata quanto a de alocar. Precisa inserir os blocos de volta na
 * lista de área livre, mantendo a ordem, e depois juntar (coalescer)
 * blocos vizinhos pra evitar fragmentação.
 */
void desaloca_setores(ptnoSet *Area, ptnoSet setores_arquivo) {
    ptnoSet bloco_para_inserir = setores_arquivo;

    // Etapa 1: Inserir cada bloco da lista de setores do arquivo
    // de volta na lista de Área Livre, mantendo a ordem por endereço.
    while (bloco_para_inserir != NULL) {
        ptnoSet proximo_bloco = bloco_para_inserir->prox; // Guarda o próximo pra não perder a referência.

        // Acha a posição correta pra inserir o bloco.
        ptnoSet *ant = Area;
        ptnoSet atual = *Area;
        while (atual != NULL && atual->inicio < bloco_para_inserir->inicio) {
            ant = &atual->prox;
            atual = atual->prox;
        }

        // Insere o bloco na lista 'Area'.
        *ant = bloco_para_inserir;
        bloco_para_inserir->prox = atual;

        bloco_para_inserir = proximo_bloco; // Pega o próximo bloco da lista do arquivo.
    }

    // Etapa 2: Coalescer. Percorrer a lista de Área Livre e juntar blocos vizinhos.
    // Ex: (5,6) e (7,8) viram (5,8).
    ptnoSet atual = *Area;
    while (atual != NULL && atual->prox != NULL) {
        ptnoSet proximo = atual->prox;

        // Se o fim de um bloco é vizinho do começo do outro...
        if (atual->fim + 1 == proximo->inicio) {
            // ...eles se tornam um só.
            atual->fim = proximo->fim; // O bloco 'atual' agora se estende até o fim do 'proximo'.
            atual->prox = proximo->prox; // O 'atual' aponta para o que vinha depois do 'proximo'.
            free(proximo); // Libera o nó 'proximo', que não é mais usado.

            // IMPORTANTE: Não avança o 'atual' aqui!
            // Porque o novo 'atual' (maior) pode precisar se juntar com o próximo também.
            // Ex: (5,6) (7,8) (9,10). Primeiro junta (5,6) com (7,8) -> (5,8).
            // Na próxima iteração, vai juntar (5,8) com (9,10) -> (5,10).
        } else {
            // Se não são vizinhos, só avança na lista.
            atual = atual->prox;
        }
    }
}
