# O que é uma Pilha?

O termo **Pilha** é utilizado para descrever qualquer agrupamento ou arranjo de itens dispostos de forma ordenada. Na Pilha, os itens são “empilhados” (colocados/dispostos) uns em cima dos outros, geralmente formando uma estrutura vertical. Essa estrutura é amplamente utilizada em ciência da computação para resolver problemas que exigem controle de ordem de execução ou armazenamento temporário de dados.

---

## Exemplos e Analogias

Para entender melhor o conceito de Pilha, podemos usar algumas analogias do dia a dia:

### 1. Pilha de Livros ou Pratos
Imagine uma pilha de livros ou pratos:
- Quando você adiciona um novo item, ele é colocado no topo da pilha.
- Para remover um item, você sempre começa pelo topo, seguindo a ordem inversa à de inserção.

### 2. Pilha de Energia (Baterias)
Pense em como uma pilha de energia funciona:
- À medida que a energia é consumida, o que acontece com a ordem de uso das baterias?
- A última bateria colocada no dispositivo será a primeira a ser usada.

Essas analogias ajudam a visualizar o comportamento de uma Pilha e sua característica principal.

---

## Características de uma Pilha

A Pilha é uma estrutura de dados que segue o princípio **LIFO** (*Last In, First Out* – O último que entra é o primeiro que sai). Isso significa que:
- O último elemento inserido na Pilha será o primeiro a ser removido.
- Essa característica é útil em diversas aplicações, como controle de chamadas de funções, navegação em páginas da web (histórico), e muito mais.

---

## Operações Básicas do TAD Pilha

O **TAD (Tipo Abstrato de Dados) Pilha** define um conjunto de operações básicas que podem ser realizadas em uma Pilha. Essas operações são:

### 1. **Empilhar (push)**
Adiciona um novo elemento no topo da Pilha.
- Exemplo: Se a Pilha contém `[A, B, C]` e você empilha `D`, a Pilha resultante será `[A, B, C, D]`.

### 2. **Desempilhar (pop)**
Remove o elemento do topo da Pilha.
- Exemplo: Se a Pilha contém `[A, B, C, D]` e você desempilha, o elemento `D` será removido, deixando `[A, B, C]`.

### 3. **Topo (top/peek)**
Verifica qual elemento está no topo da Pilha sem removê-lo.
- Exemplo: Se a Pilha contém `[A, B, C]`, o topo será `C`.

### 4. **Pilha Cheia (isFull)**
Verifica se a Pilha atingiu sua capacidade máxima.
- Exemplo: Em uma Pilha com capacidade para 5 elementos, se ela já contém `[A, B, C, D, E]`, ela estará cheia.

### 5. **Pilha Vazia (isEmpty)**
Verifica se a Pilha está vazia.
- Exemplo: Se a Pilha não contém nenhum elemento, ela estará vazia.

---

## Aplicações Práticas de Pilhas

As Pilhas são amplamente utilizadas em diversas áreas da computação, como:
- **Recursão:** Controle de chamadas de funções recursivas.
- **Navegadores Web:** Gerenciamento do histórico de navegação.
- **Compiladores:** Análise de expressões matemáticas e sintáticas.
- **Algoritmos de Backtracking:** Resolução de problemas como labirintos e quebra-cabeças.

---

Compreender o funcionamento de uma Pilha é essencial para resolver problemas que exigem controle de ordem e armazenamento temporário de dados. Sua simplicidade e eficiência tornam essa estrutura de dados indispensável em várias aplicações.


## Como Compilar e Executar o Programa

Para compilar e executar o programa siga os passos abaixo:

### 1. Compilação
Use um compilador como o `gcc` para compilar os arquivos. Execute o seguinte comando no terminal:

```bash
gcc -o programa main.c stack.c
```

Esse comando gera um executável chamado `programa`.

### 2. Execução
Após a compilação, execute o programa com o comando:

```bash
./programa
```
