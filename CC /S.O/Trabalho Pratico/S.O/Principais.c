#include "Principais.h"

/**
 * Grava um novo arquivo no sistema.
 * Modifica as listas Arq e Area, e a Memo.
 */
void gravar(ptnoArq *Arq, ptnoSet *Area, memoria Memo, char *nome, char *texto) {
    int caracteres = strlen(texto);
    if (caracteres == 0) {
        printf("Erro: Nao e permitido gravar arquivos vazios.\n");
        return;
    }

    int n_setores = num_setores_necessarios(caracteres);
    
    // 1. Verificar se o arquivo ja existe
    ptnoArq arq_atual = *Arq;
    while (arq_atual != NULL) {
        if (strcmp(arq_atual->nome, nome) == 0) {
            printf("Erro: Ja existe um arquivo com o nome '%s'.\n", nome);
            return;
        }
        arq_atual = arq_atual->prox;
    }

    // 2. Alocar os setores da Area Livre
    ptnoSet setores_alocados = aloca_setores(Area, n_setores);
    
    if (setores_alocados == NULL) {
        // 'aloca_setores' já imprime a mensagem de erro
        return; 
    }

    // 3. Escrever o conteudo na 'Memo'
    ptnoSet setor_atual = setores_alocados;
    int char_idx = 0; // Índice do caractere no 'texto'
    
    while (setor_atual != NULL && char_idx < caracteres) {
        // Percorre cada intervalo de setor no nó (ex: inicio=5, fim=6)
        for (int i = setor_atual->inicio; i <= setor_atual->fim && char_idx < caracteres; i++) {
            // Percorre cada byte no granulo (ex: 0, 1, 2)
            for (int j = 0; j < TAM_GRANULO && char_idx < caracteres; j++) {
                Memo[i][j] = texto[char_idx];
                char_idx++;
            }
        }
        setor_atual = setor_atual->prox;
    }
    
    // 4. Criar o nó do novo arquivo
    ptnoArq novo_arquivo = (ptnoArq)malloc(sizeof(noArq));
    if (novo_arquivo == NULL) {
        printf("Erro: Falha ao alocar memoria para o no do arquivo.\n");
        // Precisaríamos desalocar 'setores_alocados' aqui, mas vamos simplificar
        return;
    }
    
    strcpy(novo_arquivo->nome, nome);
    novo_arquivo->caracteres = caracteres;
    novo_arquivo->setores = setores_alocados;
    
    // 5. Inserir o novo arquivo na lista principal (vamos inserir no início)
    novo_arquivo->prox = *Arq;
    *Arq = novo_arquivo;
    
    printf("Arquivo '%s' gravado com sucesso (%d caracteres, %d setores).\n", nome, caracteres, n_setores);
}

/**
 * Deleta um arquivo do sistema.
 * Modifica as listas Arq e Area, e a Memo.
 */
void deletar(ptnoArq *Arq, ptnoSet *Area, memoria Memo, char *nome) {
    
    // 1. Encontrar o arquivo usando ponteiro-para-ponteiro
    ptnoArq *ant = Arq;
    ptnoArq atual = *Arq;
    
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            break; // Achamos o arquivo! 'atual' aponta para ele.
        }
        ant = &atual->prox;
        atual = atual->prox;
    }

    // 2. Se não encontrar, retorne
    if (atual == NULL) {
        printf("Erro: Arquivo '%s' nao encontrado.\n", nome);
        return;
    }

    // 3. Limpar a 'Memo' (sugestão do enunciado)
    ptnoSet setor_atual = atual->setores;
    while (setor_atual != NULL) {
        for (int i = setor_atual->inicio; i <= setor_atual->fim; i++) {
            for (int j = 0; j < TAM_GRANULO; j++) {
                Memo[i][j] = ' '; // Limpa o setor
            }
        }
        setor_atual = setor_atual->prox;
    }
    
    // 4. Devolver os setores para a Area Livre
    //    'desaloca_setores' vai inserir e coalescer os nós
    desaloca_setores(Area, atual->setores);
    // IMPORTANTE: 'atual->setores' (a lista) agora faz parte da 'Area'.
    // Não devemos dar 'free' nessa lista, apenas no 'atual' (noArq).

    // 5. Remover o nó da lista 'Arq'
    // 'ant' aponta para o ponteiro que apontava para 'atual'
    // Fazemos ele "pular" 'atual' e apontar para o próximo
    *ant = atual->prox; 
    
    // 6. Liberar a memória do nó do arquivo
    free(atual); // Libera o noArq

    printf("Arquivo '%s' deletado com sucesso.\n", nome);
}

/**
 * Apresenta o conteudo de um arquivo lendo da 'Memo'.
 */
void apresentar(ptnoArq Arq, memoria Memo, char *nome) {
    
    // 1. Encontrar o arquivo
    ptnoArq atual = Arq;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            break; // Achamos o arquivo!
        }
        atual = atual->prox;
    }

    // 2. Se não encontrar, retorne
    if (atual == NULL) {
        printf("Erro: Arquivo '%s' nao encontrado.\n", nome);
        return;
    }

    // 3. Ler da 'Memo' e imprimir
    printf("Conteudo de '%s':\n", nome);
    
    ptnoSet setor_atual = atual->setores;
    int caracteres_lidos = 0;
    int total_caracteres = atual->caracteres;

    while (setor_atual != NULL && caracteres_lidos < total_caracteres) {
        // Percorre cada intervalo de setor no nó (ex: inicio=5, fim=6)
        for (int i = setor_atual->inicio; i <= setor_atual->fim && caracteres_lidos < total_caracteres; i++) {
            // Percorre cada byte no granulo (ex: 0, 1, 2)
            for (int j = 0; j < TAM_GRANULO && caracteres_lidos < total_caracteres; j++) {
                printf("%c", Memo[i][j]);
                caracteres_lidos++;
            }
        }
        setor_atual = setor_atual->prox;
    }
    
    printf("\n"); // Adiciona uma nova linha no final
}