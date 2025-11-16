#ifndef PRINCIPAIS_H
#define PRINCIPAIS_H
#include "Auxiliares.h"

void gravar(ptnoArq *Arq, ptnoSet *Area, memoria Memo, char *nome, char *texto);
void deletar(ptnoArq *Arq, ptnoSet *Area, memoria Memo, char *nome);
void apresentar(ptnoArq Arq, memoria Memo, char *nome);

#endif /* PRINCIPAIS_H */