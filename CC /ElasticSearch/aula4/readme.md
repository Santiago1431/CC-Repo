```
GET wikipedia/_search
{
  "query": {
    "bool": {
      "must": [
        {
          "match": {
            "content": {
              "query": "square root",
              "operator": "and"
            }
          }
        },
        {
          "match_phrase": {
            "content": "square root of"
          }
        }
      ],
      "should": [
        {
          "match": {
            "title": "square root"
          }
        }
      ]
    }
  }
}
```

### Exercicio

> Proponha uma consulta usando de boolean query de modo o resultado seja semelhante ao que obtemos do Google ao submeter: `the treap and the "randomized binary" search tree`
