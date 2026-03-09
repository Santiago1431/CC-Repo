# Aula 1 -> Preparação de Ambiente no Docker Compose
## Comandos: 
Caso algum container esteja executando, é necessário pará-lo antes. O comando a seguir para todos os containers em execução:
`docker stop $(docker ps -aq)`

Remover todos os containers:

`docker rm $(docker ps -aq)`

Remover todos os recursos não utilizados:

`docker system prune -a --volumes`

Remove todos os volumes. Apenas use em ambiente de desenvolvimento.

`docker volume rm $(docker volume ls -q)`

Subir Imagem Docker

`docker compose up -d`

Para acessar:

http://0.0.0.0:5601/

## Credenciais:

`usuário: elastic`
`senha: user123`

## Dev Tools

Console das Apis do ELK Stack

### Reqs da aula

`GET /_cat/nodes`
`GET /_cat/nodes?v`
`GET /_cat/health?v`


# shards

- Shards são maneiras de se dividir um `indice` em pedaços menores `indice == Schema SQL`

- Os shards dividem o índice em partes menores. Por exemplo, ao dividir um índice de 100GB em 2 shards, ficam 50GB para cada parte. Cada shard pode ser processado em paralelo (em threads ou nós diferentes); ao invés de processar um único bloco de 100GB, o sistema processa dois de 50GB simultaneamente, melhorando a velocidade de processamento.

### Desvantagens de muitos Shards (Oversharding)

- **Overhead de Recursos**: Cada shard é, na verdade, um índice Lucene completo que consome recursos de CPU, memória e descritores de arquivo. Ter muitos shards pequenos pode desperdiçar recursos significativos.
- **Performance de Busca**: Buscas que precisam consultar muitos shards podem ser mais lentas, pois o nó coordenador precisa gerenciar a busca em cada shard e depois agregar os resultados.
- **Gerenciamento do Cluster**: Um número excessivo de metadados de shards aumenta o tamanho do estado do cluster, o que pode sobrecarregar o nó mestre e tornar as atualizações do cluster mais lentas.


# Criando Índices

`PUT /wiki_documents1`

```
{
  "acknowledged": true,
  "shards_acknowledged": true,
  "index": "wiki_documents1"
}
```


```GET /wiki_documents1```

```
{
  "wiki_documents1": {
    "aliases": {},
    "mappings": {},
    "settings": {
      "index": {
        "routing": {
          "allocation": {
            "include": {
              "_tier_preference": "data_content"
            }
          }
        },
        "number_of_shards": "1",
        "provided_name": "wiki_documents1",
        "creation_date": "1773066193994",
        "number_of_replicas": "1",
        "uuid": "BCkwyApeQbGK5lasxS9uVg",
        "version": {
          "created": "8521000"
        }
      }
    }
  }
}
```
-  Observação: O Indice foi criado com um Shard

### Criando com N shards

```
PUT /wiki_documents2
{
    "settings": {
        "number_of_shards": 2
    }
}
```

`GET /wiki_documents2`

```
{
  "wiki_documents2": {
    "aliases": {},
    "mappings": {},
    "settings": {
      "index": {
        "routing": {
          "allocation": {
            "include": {
              "_tier_preference": "data_content"
            }
          }
        },
        "number_of_shards": "2",
        "provided_name": "wiki_documents2",
        "creation_date": "1773066544691",
        "number_of_replicas": "1",
        "uuid": "VwCWhFH6TGKg5LcIe2FaUQ",
        "version": {
          "created": "8521000"
        }
      }
    }
  }
}
```

# Replicas

- Diferente dos shards a replica não divide o indice, mas duplica evitando ponto unico de erro

```
PUT /wiki_documents3
{
    "settings": {
        "number_of_shards": 1,
        "number_of_replicas": 3
    }
}
```