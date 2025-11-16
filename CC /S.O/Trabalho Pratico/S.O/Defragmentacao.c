#include "Defragmentacao.h"

/**
 * Libera toda a memória de uma lista encadeada de setores.
 */
void libera_lista_setores(ptnoSet lista) {
    ptnoSet atual = lista;
    while (atual != NULL) {
        ptnoSet proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

/**
 * Realiza a defragmentação do disco.
 * Reorganiza todos os arquivos de forma contígua no início da 'Memo'
 * e atualiza as listas 'Arq' (setores) e 'Area'.
 */
void defragmentar(ptnoArq *Arq, ptnoSet *Area, memoria Memo) {
    memoria Memo_Nova; // A "garagem" temporária
    int proximo_setor_livre = 0; // Onde o próximo arquivo será escrito
    
    // 1. Limpa a Memo_Nova (preenche com espaços)
    for (int i = 0; i < TAM_MEMORIA; i++) {
        for (int j = 0; j < TAM_GRANULO; j++) {
            Memo_Nova[i][j] = ' ';
        }
    }

    // 2. Percorre a lista de arquivos
    ptnoArq arq_atual = *Arq;
    while (arq_atual != NULL) {
        int n_setores = num_setores_necessarios(arq_atual->caracteres);
        int total_caracteres = arq_atual->caracteres;
        int caracteres_lidos = 0;

        // 3. Lê da 'Memo' antiga e escreve na 'Memo_Nova'
        ptnoSet setor_antigo = arq_atual->setores;
        
        int novo_setor_idx = proximo_setor_livre;
        int novo_granulo_idx = 0;

        // Loop de leitura (da Memo antiga)
        while (setor_antigo != NULL && caracteres_lidos < total_caracteres) {
            for (int i = setor_antigo->inicio; i <= setor_antigo->fim && caracteres_lidos < total_caracteres; i++) {
                for (int j = 0; j < TAM_GRANULO && caracteres_lidos < total_caracteres; j++) {
                    
                    char c = Memo[i][j]; // Lê da 'Memo' antiga

                    // Escreve na 'Memo_Nova' de forma contígua
                    Memo_Nova[novo_setor_idx][novo_granulo_idx] = c;

                    // Avança o cursor de escrita
                    novo_granulo_idx++;
                    if (novo_granulo_idx == TAM_GRANULO) {
                        novo_granulo_idx = 0;
                        novo_setor_idx++;
                    }
                    caracteres_lidos++;
                }
            }
            setor_antigo = setor_antigo->prox;
        }

        // 4. Atualiza a lista de setores do arquivo
        libera_lista_setores(arq_atual->setores); // Libera a lista antiga

        // Cria a nova lista de setores (agora contígua)
        ptnoSet novo_no_setor = (ptnoSet)malloc(sizeof(noSet));
        novo_no_setor->inicio = proximo_setor_livre;
        novo_no_setor->fim = proximo_setor_livre + n_setores - 1;
        novo_no_setor->prox = NULL;
        
        arq_atual->setores = novo_no_setor; // Atribui a nova lista
        
        // 5. Atualiza o ponteiro para o próximo espaço livre
        proximo_setor_livre += n_setores;

        // Avança para o próximo arquivo
        arq_atual = arq_atual->prox;
    }

    // 6. Atualiza a lista 'Area'
    libera_lista_setores(*Area); // Libera a lista antiga de área livre
    
    if (proximo_setor_livre < TAM_MEMORIA) {
        // Se sobrou espaço, cria um novo nó de área livre
        *Area = (ptnoSet)malloc(sizeof(noSet));
        (*Area)->inicio = proximo_setor_livre;
        (*Area)->fim = TAM_MEMORIA - 1;
        (*Area)->prox = NULL;
    } else {
        // Disco está cheio
        *Area = NULL;
    }

    // 7. Copia a 'Memo_Nova' (organizada) de volta para a 'Memo' principal
    memcpy(Memo, Memo_Nova, sizeof(memoria));

    printf("Defragmentacao concluida.\n");
}