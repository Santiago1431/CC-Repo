

# INDICES, DOCUMENTOS E ANALYSIS

### COMANDOS
 - Criar indice -> PUT
 - Adicionar documento -> POST

 ---
#### Exemplos:

`PUT /produtos`
```
POST /produtos/_doc
{
    "nome": "cafeteira",
    "preco": "50",
    "estoque": 20
}
```

</b> Adicionando mais documentos através da api bulk:

```
POST /_bulk
{"index":{"_index": "produtos"}}
{"nome":"máquina de café espresso", "preco": "300", "estoque": 10}
{"create":{"_index": "produtos"}}
{"nome":"moedor de café", "preco": 40, "estoque": 10}
```

---
# ANALYSIS

### Analyzer
<strong> Etapas </strong>
- Character Filters
- Token Filters
- Tokenizers

### Character Filters (Limpeza)
- Momento: Antes da quebra do texto.
- Função: Limpa o "ruído" dos caracteres.
- Exemplos: Remover tags HTML (html_strip), substituir símbolos ou converter emojis em texto.

### Tokenizer (Divisão)
- <strong>Momento</strong>: O coração do processo (obrigatório ter exatamente um).
- <strong>Função</strong>: Quebra a string em pedaços (tokens), geralmente baseando-se em espaços ou pontuação.
- <strong>Exemplos</strong>: O standard separa por regras gramaticais; o whitespace apenas por espaços; o ngram para buscas parciais (tipo "autocomplete").

### Token Filters (Refino)
- <strong>Momento</strong>: Após a criação dos tokens.
- <strong>Função</strong>: Modifica, remove ou adiciona novos tokens à lista.
- <strong>Exemplos</strong>: 
    -   lowercase: Deixa tudo minúsculo.
    - asciifolding: Remove acentos (Transforma "maçã" em "maca").
    - stop: Remove palavras que não agregam valor (como "de", "a", "o").
    - synonym: Adiciona variações (se buscar "carro", ele também acha "automóvel").
---
### Resumo Visual do Fluxo
<b> Texto Bruto ➔ [Char Filter] ➔ Texto Limpo ➔ [Tokenizer] ➔ Lista de Tokens ➔ [Token Filter] ➔ Índice Final</b>

---

### Brincando com ANALYZER no Dev tools

```
POST /_analyze
{
    "text": "2 guys walk into     a bar, but the third... DUCKS! :-)",
    "analyzer": "standard"
}
```
<b>Montando filtro manualmente:

```
POST /_analyze
{
    "text": "2 guys walk into     a bar, but the third... DUCKS! :-)",
    "char_filter": [],
    "tokenizer": "standard",
    "filter": ["lowercase"]
}
```
---
### char_filter html_strip
```
POST /_analyze
{
    "text": "<p>I&apos:m so <b>happy",
    "char_filter": ["html_strip"],
    "tokenizer": "standard",
    "filter": ["lowercase"]
}

## Response

{
  "tokens": [
    {
      "token": "i",
      "start_offset": 3,
      "end_offset": 4,
      "type": "<ALPHANUM>",
      "position": 0
    },
    {
      "token": "apos:m",
      "start_offset": 5,
      "end_offset": 11,
      "type": "<ALPHANUM>",
      "position": 1
    },
    {
      "token": "so",
      "start_offset": 12,
      "end_offset": 14,
      "type": "<ALPHANUM>",
      "position": 2
    },
    {
      "token": "happy",
      "start_offset": 18,
      "end_offset": 23,
      "type": "<ALPHANUM>",
      "position": 3
    }
  ]
}
```
---
### char_filter mapping

```

POST /_analyze
{
    "text": "I am so happy",
    "char_filter": [
        {
            "type": "mapping",
            "mappings": [
                "happy => sad"
                
            ]
        }
    ],
    "tokenizer": "standard",
    "filter": ["lowercase"]
}

## Response

{
  "tokens": [
    {
      "token": "i",
      "start_offset": 0,
      "end_offset": 1,
      "type": "<ALPHANUM>",
      "position": 0
    },
    {
      "token": "am",
      "start_offset": 2,
      "end_offset": 4,
      "type": "<ALPHANUM>",
      "position": 1
    },
    {
      "token": "so",
      "start_offset": 5,
      "end_offset": 7,
      "type": "<ALPHANUM>",
      "position": 2
    },
    {
      "token": "sad",
      "start_offset": 8,
      "end_offset": 13,
      "type": "<ALPHANUM>",
      "position": 3
    }
  ]
}
```
---

