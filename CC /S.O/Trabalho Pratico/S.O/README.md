# Simulador de Sistema de Arquivos FAT

## Introdução

Este projeto é um simulador de um sistema de arquivos baseado em uma Tabela de Alocação de Arquivos (FAT). Ele demonstra as operações básicas de um sistema de arquivos, como criar, deletar e exibir arquivos, bem como a alocação e desalocação de espaço em disco. O simulador também inclui uma funcionalidade de desfragmentação de disco.

O sistema de arquivos simulado gerencia um disco com um tamanho total de 30 setores, onde cada setor (ou grânulo) pode armazenar 3 caracteres.

## Como Compilar e Executar

O projeto inclui um `Makefile` para facilitar a compilação e execução.

*   **Para compilar o projeto:**
    ```bash
    make
    ```
    Isso irá gerar o executável `simuladorFAT`.

*   **Para executar o simulador:**
    ```bash
    make run
    ```
    ou diretamente:
    ```bash
    ./simuladorFAT
    ```

*   **Para limpar os arquivos de objeto e o executável:**
    ```bash
    make clean
    ```

## Comandos

O simulador oferece os seguintes comandos:

*   `G <arquivo.txt> <texto>`: Grava o `<texto>` em um novo arquivo chamado `<arquivo.txt>`.
*   `D <arquivo.txt>`: Deleta o arquivo `<arquivo.txt>` do disco.
*   `A <arquivo.txt>`: Apresenta (exibe) o conteúdo do arquivo `<arquivo.txt>`.
*   `M`: Mostra as estruturas de dados utilizadas: a lista de áreas livres, a lista de arquivos e o estado atual da memória.
*   `O`: Otimiza (desfragmenta) o disco, movendo todos os arquivos para o início da memória de forma contígua.
*   `H`: Apresenta a lista de comandos disponíveis.
*   `F`: Finaliza a simulação.

## Estruturas de Dados

As principais estruturas de dados são definidas em `Auxiliares.h`:

*   `memoria`: Uma matriz 2D `char[TAM_MEMORIA][TAM_GRANULO]` que representa o disco.
*   `noSet`: Um nó de uma lista encadeada que representa um bloco de setores contíguos. Contém um `inicio`, um `fim` e um ponteiro `prox` para o próximo nó.
*   `noArq`: Um nó de uma lista encadeada que representa um arquivo. Contém o `nome` do arquivo, o número de `caracteres`, um ponteiro para uma lista de `setores` que o arquivo ocupa, e um ponteiro `prox` para o próximo arquivo.

## Descrição dos Arquivos

*   **`FAT.c`**: Contém a função `main` que é o ponto de entrada do programa. É responsável pelo loop principal da simulação, processando os comandos do usuário e chamando as funções apropriadas. Também contém funções para exibir o estado da memória e das listas.

*   **`Principais.c`**: Implementa as principais operações do sistema de arquivos:
    *   `gravar()`: Cria um novo arquivo, aloca os setores necessários e escreve o conteúdo na memória.
    *   `deletar()`: Remove um arquivo, libera seus setores e apaga seu conteúdo da memória.
    *   `apresentar()`: Exibe o conteúdo de um arquivo específico.

*   **`Auxiliares.c`**: Fornece funções de suporte para o gerenciamento de memória:
    *   `num_setores_necessarios()`: Calcula quantos setores são necessários para armazenar um determinado número de caracteres.
    *   `calcula_espaco_livre()`: Retorna o número total de setores livres no disco.
    *   `aloca_setores()`: Aloca um número de setores da lista de áreas livres. Trata a fragmentação pegando blocos de onde estiverem disponíveis.
    *   `desaloca_setores()`: Libera os setores de um arquivo, devolvendo-os à lista de áreas livres e mantendo a lista ordenada e coalescida (unindo blocos adjacentes).

*   **`Defragmentacao.c`**: Implementa a funcionalidade de desfragmentação do disco:
    *   `defragmentar()`: Reorganiza o disco movendo todos os arquivos para o início da memória, tornando-os contíguos. Atualiza as informações de alocação de arquivos e a lista de áreas livres.
    *   `libera_lista_setores()`: Função auxiliar para liberar a memória de uma lista de setores.

*   **`.h` (Arquivos de Cabeçalho)**: `Principais.h`, `Auxiliares.h`, e `Defragmentacao.h` contêm os protótipos das funções e as definições das estruturas de dados, permitindo a comunicação entre os diferentes módulos do projeto.

## Autor e Data

*   **Aluno**: Eurico Santiago Climaco Rodrigues
*   **Data**: 15/11/2025
