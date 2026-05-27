#ifndef MATRIZ_H
#define MATRIZ_H

#include "lista.h"  // para usar o tipo Doce

Doce** criar_matriz(int linhas, int colunas);
void preencher_matriz(Doce** matriz, int linhas, int colunas, Node** fila);
void imprimir_matriz(Doce** matriz, int linhas, int colunas);
void liberar_matriz(Doce** matriz, int linhas);
int trocar_doces(Doce** matriz, int linhas, int colunas, int l1, int c1, int l2, int c2);

#endif
