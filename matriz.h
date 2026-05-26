#ifndef MATRIZ_H
#define MATRIZ_H

#include "lista.h"  // para usar o tipo Doce

Doce** criar_matriz(int linhas, int colunas);
void preencher_matriz(Doce** matriz, int linhas, int colunas, Node** fila);
void imprimir_matriz(Doce** matriz, int linhas, int colunas);
void liberar_matriz(Doce** matriz, int linhas);

#endif