#include <stdio.h>
#include <stdlib.h>
#include "Auxiliares.h"


int num_setores_necessarios(int numCaracteres)
{
    if (numCaracteres == 0)
    {
        return 0;
    }
   //Fórmula para calcular o número de setores necessários
   //divisao COM TETO (celing division)
    return (numCaracteres + TAM_GRANULO - 1) / TAM_GRANULO ;
}

int calcula_espaco_livre(ptnoSet Area)
{
    int total_livre = 0;
    ptnoSet atual = Area;
    while (atual != NULL) {
        // Soma o tamanho do intervalo (fim - inicio + 1)
        total_livre += (atual->fim - atual->inicio) + 1;
        atual = atual->prox;
    }
    return total_livre;
}

/**
 * Aloca 'n_setores' da lista de área livre (Area).
 * Retorna uma lista (ptnoSet) com os setores alocados.
 * Modifica a lista 'Area' para remover os setores alocados.
 * Retorna NULL se não houver espaço suficiente.
 */
ptnoSet aloca_setores(ptnoSet *Area, int n_setores) {
    // Passagem 1: Verificar se há espaço suficiente
    int total_livre = calcula_espaco_livre(*Area); // Assumindo que o nome é calcula_espaco_livre
    if (total_livre < n_setores) {
        printf("Erro: Espaco insuficiente no disco.\n");
        return NULL; // Não há espaço
    }

    ptnoSet lista_alocada = NULL; // A lista de setores que vamos retornar
    int setores_restantes = n_setores;
    
    ptnoSet *ant = Area; // Ponteiro para o ponteiro (para modificar a lista 'Area')
    ptnoSet atual = *Area;

    // Passagem 2: Alocar os setores
    while (setores_restantes > 0 && atual != NULL) {
        int tamanho_bloco = (atual->fim - atual->inicio) + 1;
        
        ptnoSet novo_no_alocado = (ptnoSet)malloc(sizeof(noSet));
        if (novo_no_alocado == NULL) {
            printf("Erro: Falha ao alocar memoria para no de setor.\n");
            // Faltaria liberar a 'lista_alocada' aqui
            return NULL;
        }

        if (tamanho_bloco > setores_restantes) {
            // Caso 1: O bloco livre é MAIOR do que precisamos.
            
            novo_no_alocado->inicio = atual->inicio;
            novo_no_alocado->fim = atual->inicio + setores_restantes - 1;
            
            atual->inicio = novo_no_alocado->fim + 1;
            
            setores_restantes = 0; // Pegamos tudo o que precisávamos

            
            // Como não removemos o nó 'atual', avançamos manualmente.
            ant = &atual->prox;
            atual = atual->prox;

        } else {
            // Caso 2: O bloco livre é MENOR ou IGUAL ao que precisamos.
            
            novo_no_alocado->inicio = atual->inicio;
            novo_no_alocado->fim = atual->fim;
            
            setores_restantes -= tamanho_bloco; // Subtrai o que pegamos
            
            // Remove o bloco 'atual' da lista 'Area'
            *ant = atual->prox;
            free(atual);
            
            // **CORREÇÃO: 'atual' é atualizado para o próximo item**
            // 'ant' não se mexe, pois ele já aponta para o ponteiro 'prox'
            // que agora contém o endereço do novo 'atual'.
            atual = *ant;
        }

        // Adiciona o novo nó no INÍCIO da lista de retorno
        novo_no_alocado->prox = lista_alocada;
        lista_alocada = novo_no_alocado;

        // **CORREÇÃO: O 'if' problemático foi REMOVIDO daqui**
    }
    
    return lista_alocada;
}

/**
 * Devolve uma lista de setores ('setores_arquivo') para a
 * lista de área livre ('Area'), mantendo 'Area' ordenada
 * e coalescida (unida).
 */
void desaloca_setores(ptnoSet *Area, ptnoSet setores_arquivo) {
    ptnoSet bloco_para_inserir = setores_arquivo;

    // Etapa 1: Inserir cada bloco da lista 'setores_arquivo'
    //          na lista 'Area' de forma ordenada.
    while (bloco_para_inserir != NULL) {
        ptnoSet proximo_bloco = bloco_para_inserir->prox; // Guarda o próximo
        
        // Encontra a posição para inserir 'bloco_para_inserir'
        ptnoSet *ant = Area;
        ptnoSet atual = *Area;
        while (atual != NULL && atual->inicio < bloco_para_inserir->inicio) {
            ant = &atual->prox;
            atual = atual->prox;
        }
        
        // Insere o bloco
        *ant = bloco_para_inserir;
        bloco_para_inserir->prox = atual;
        
        bloco_para_inserir = proximo_bloco; // Move para o próximo bloco
    }

    // Etapa 2: Coalescer (unir) blocos contíguos na lista 'Area'
    ptnoSet atual = *Area;
    while (atual != NULL && atual->prox != NULL) {
        ptnoSet proximo = atual->prox;
        
        // Verifica se 'atual' e 'proximo' são contíguos
        // Ex: atual=(5, 6) e proximo=(7, 8)
        if (atual->fim + 1 == proximo->inicio) {
            // Une os blocos: atual=(5, 8)
            atual->fim = proximo->fim;
            
            // Remove o 'proximo' da lista
            atual->prox = proximo->prox;
            free(proximo);
            
            // Não avança 'atual', pois ele pode precisar se unir
            // com o próximo nó também (ex: (5,6) (7,8) (9,10))
        } else {
            // Blocos não são contíguos, apenas avança
            atual = atual->prox;
        }
    }
}
