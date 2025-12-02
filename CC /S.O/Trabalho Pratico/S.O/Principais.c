#include "Principais.h"

/**
 * Grava um novo arquivo no sistema.
 * Essa é a função principal de escrita.
 */
void gravar(ptnoArq *Arq, ptnoSet *Area, memoria Memo, char *nome, char *texto) {
    int caracteres = strlen(texto);
    if (caracteres == 0) {
        printf("Erro: Nao e permitido gravar arquivos vazios.\n");
        return;
    }

    int n_setores = num_setores_necessarios(caracteres);

    // 1. Checa se o arquivo já existe, não vamos sobrescrever
    ptnoArq arq_atual = *Arq;
    while (arq_atual != NULL) {
        if (strcmp(arq_atual->nome, nome) == 0) {
            printf("Erro: Ja existe um arquivo com o nome '%s'.\n", nome);
            return;
        }
        arq_atual = arq_atual->prox;
    }

    // 2. Pede para o alocador os setores que precisamos
    ptnoSet setores_alocados = aloca_setores(Area, n_setores);

    if (setores_alocados == NULL) {
        // Se não conseguiu alocar, a função aloca_setores já avisou o usuário
        return;
    }

    // 3. Agora, vamos de fato escrever o conteúdo na memória
    ptnoSet setor_atual = setores_alocados;
    int char_idx = 0; // Controla qual caractere do texto estamos escrevendo

    // Itera sobre a lista de setores que nos foi dada
    while (setor_atual != NULL && char_idx < caracteres) {
        // Itera dentro de um bloco de setores (ex: de 5 a 7)
        for (int i = setor_atual->inicio; i <= setor_atual->fim && char_idx < caracteres; i++) {
            // Itera nos bytes do grânulo
            for (int j = 0; j < TAM_GRANULO && char_idx < caracteres; j++) {
                Memo[i][j] = texto[char_idx];
                char_idx++;
            }
        }
        setor_atual = setor_atual->prox;
    }

    // 4. Cria o registro do arquivo (o nó na lista de arquivos)
    ptnoArq novo_arquivo = (ptnoArq)malloc(sizeof(noArq));
    if (novo_arquivo == NULL) {
        printf("Erro: Falha ao alocar memoria para o no do arquivo.\n");
        // TODO: Se falhar aqui, deveríamos desalocar os 'setores_alocados'. Fica pra próxima.
        return;
    }

    strcpy(novo_arquivo->nome, nome);
    novo_arquivo->caracteres = caracteres;
    novo_arquivo->setores = setores_alocados;

    // 5. Insere o novo arquivo na lista de arquivos (no começo, que é mais fácil)
    novo_arquivo->prox = *Arq;
    *Arq = novo_arquivo;

    printf("Arquivo '%s' gravado com sucesso (%d caracteres, %d setores).\n", nome, caracteres, n_setores);
}

/**
 * Deleta um arquivo do sistema.
 */
void deletar(ptnoArq *Arq, ptnoSet *Area, memoria Memo, char *nome) {

    // 1. Achar o arquivo na lista. Usar ponteiro duplo aqui facilita a remoção da lista.
    ptnoArq *ant = Arq;
    ptnoArq atual = *Arq;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            break; // Achou!
        }
        ant = &atual->prox;
        atual = atual->prox;
    }

    // 2. Se o loop terminar e atual for NULL, o arquivo não existe.
    if (atual == NULL) {
        printf("Erro: Arquivo '%s' nao encontrado.\n", nome);
        return;
    }

    // 3. Limpa o conteúdo do arquivo da memória. O enunciado pediu pra fazer isso.
    // Em um sistema real, isso não é sempre necessário, só marcar como livre já bastaria.
    ptnoSet setor_atual = atual->setores;
    while (setor_atual != NULL) {
        for (int i = setor_atual->inicio; i <= setor_atual->fim; i++) {
            for (int j = 0; j < TAM_GRANULO; j++) {
                Memo[i][j] = ' '; // Limpa o setor
            }
        }
        setor_atual = setor_atual->prox;
    }

    // 4. Devolve os setores para a Área Livre.
    // A função desaloca_setores cuida de inserir e juntar os blocos.
    desaloca_setores(Area, atual->setores);
    // IMPORTANTE: A lista 'atual->setores' agora é parte da Área Livre.
    // Não podemos dar free nela aqui.

    // 5. Remove o nó da lista de arquivos.
    // O ponteiro 'ant' aponta para o campo 'prox' do nó anterior (ou para a cabeça da lista),
    // então fazer isso efetivamente "pula" o nó 'atual'.
    *ant = atual->prox;

    // 6. Agora sim, libera a memória do nó do arquivo que foi removido.
    free(atual);

    printf("Arquivo '%s' deletado com sucesso.\n", nome);
}

/**
 * Apresenta o conteúdo de um arquivo.
 */
void apresentar(ptnoArq Arq, memoria Memo, char *nome) {

    // 1. Procura o arquivo na lista.
    ptnoArq atual = Arq;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            break; // Achou!
        }
        atual = atual->prox;
    }

    // 2. Se não encontrou, avisa e sai.
    if (atual == NULL) {
        printf("Erro: Arquivo '%s' nao encontrado.\n", nome);
        return;
    }

    // 3. Se encontrou, lê da memória e imprime na tela.
    printf("Conteudo de '%s':\n", nome);

    ptnoSet setor_atual = atual->setores;
    int caracteres_lidos = 0;
    int total_caracteres = atual->caracteres;

    // Lógica parecida com a de gravação, mas agora lendo.
    while (setor_atual != NULL && caracteres_lidos < total_caracteres) {
        for (int i = setor_atual->inicio; i <= setor_atual->fim && caracteres_lidos < total_caracteres; i++) {
            for (int j = 0; j < TAM_GRANULO && caracteres_lidos < total_caracteres; j++) {
                printf("%c", Memo[i][j]);
                caracteres_lidos++;
            }
        }
        setor_atual = setor_atual->prox;
    }

    printf("\n"); // Pra ficar bonitinho no terminal
}