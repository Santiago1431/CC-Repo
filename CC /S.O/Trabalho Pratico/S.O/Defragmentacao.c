#include "Defragmentacao.h"

/**
 * Libera toda a memória de uma lista encadeada de setores.
 * Função simples pra limpar a bagunça depois.
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
 * A ideia é simples:
 * 1. Cria uma memória nova (e vazia).
 * 2. Copia todos os arquivos da memória antiga para a nova, um após o outro, de forma contígua.
 * 3. Atualiza os ponteiros dos arquivos para refletir suas novas localizações.
 * 4. A área livre se torna um único bloco contínuo no final da memória.
 * 5. Copia a memória nova (já organizada) de volta para a memória principal.
 */
void defragmentar(ptnoArq *Arq, ptnoSet *Area, memoria Memo) {
    memoria Memo_Nova; // A "garagem" temporária pra organizar os carros
    int proximo_setor_livre = 0; // Onde o próximo arquivo será escrito na Memo_Nova

    // 1. Zera a memória nova pra não ter lixo
    for (int i = 0; i < TAM_MEMORIA; i++) {
        for (int j = 0; j < TAM_GRANULO; j++) {
            Memo_Nova[i][j] = ' ';
        }
    }

    // 2. Itera sobre cada arquivo existente
    ptnoArq arq_atual = *Arq;
    while (arq_atual != NULL) {
        int n_setores = num_setores_necessarios(arq_atual->caracteres);
        int total_caracteres = arq_atual->caracteres;
        int caracteres_lidos = 0;

        // 3. Lê o conteúdo do arquivo da memória antiga (fragmentada)
        // e escreve na memória nova (de forma contígua)
        ptnoSet setor_antigo = arq_atual->setores;

        int novo_setor_idx = proximo_setor_livre;
        int novo_granulo_idx = 0;

        // Loop pra ler byte a byte da memória antiga e passar pra nova
        while (setor_antigo != NULL && caracteres_lidos < total_caracteres) {
            for (int i = setor_antigo->inicio; i <= setor_antigo->fim && caracteres_lidos < total_caracteres; i++) {
                for (int j = 0; j < TAM_GRANULO && caracteres_lidos < total_caracteres; j++) {

                    char c = Memo[i][j]; // Lê da 'Memo' antiga

                    // Escreve na 'Memo_Nova' de forma sequencial
                    Memo_Nova[novo_setor_idx][novo_granulo_idx] = c;

                    // Avança o "cursor" de escrita na memória nova
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

        // 4. A parte mais importante: atualizar a lista de setores do arquivo
        libera_lista_setores(arq_atual->setores); // A lista antiga de setores (fragmentada) não serve mais

        // Cria a nova lista de setores (agora é um bloco só, contíguo)
        ptnoSet novo_no_setor = (ptnoSet)malloc(sizeof(noSet));
        novo_no_setor->inicio = proximo_setor_livre;
        novo_no_setor->fim = proximo_setor_livre + n_setores - 1;
        novo_no_setor->prox = NULL;

        arq_atual->setores = novo_no_setor; // O arquivo agora aponta pra nova lista

        // 5. Prepara o terreno para o próximo arquivo
        proximo_setor_livre += n_setores;

        // Vai para o próximo arquivo
        arq_atual = arq_atual->prox;
    }

    // 6. Finalmente, atualiza a lista de Area Livre
    libera_lista_setores(*Area); // A lista antiga, toda fragmentada, já era

    if (proximo_setor_livre < TAM_MEMORIA) {
        // Se sobrou espaço, cria um único nó que representa todo o espaço livre contíguo
        *Area = (ptnoSet)malloc(sizeof(noSet));
        (*Area)->inicio = proximo_setor_livre;
        (*Area)->fim = TAM_MEMORIA - 1;
        (*Area)->prox = NULL;
    } else {
        // Se não sobrou nada, a área livre é nula
        *Area = NULL;
    }

    // 7. Copia a memória nova e organizada de volta para a memória principal do sistema
    memcpy(Memo, Memo_Nova, sizeof(memoria));

    printf("Defragmentacao concluida.\n");
}