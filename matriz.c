#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

Doce** criar_matriz(int linhas, int colunas) {
    Doce **matriz = (Doce **)malloc(6 * sizeof(Doce *));
    if (matriz == NULL)
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    for (int i=0; i<6; i++) {
        matriz[i] = (Doce *)malloc(6 * sizeof(Doce));
        if (matriz[i] == NULL) {
            printf("Erro de alocacao de memoria.\n");
            exit(1);
        }
        // Inicializa cada célula como vazia
        for (int j = 0; j < colunas; j++) {
            matriz[i][j].id = -1;
            matriz[i][j].tipo = ' ';
            matriz[i][j].especial = 0;
        }
    }
    return matriz;
}

// Consome doces da fila de entrada para preencher a matriz
void preencher_matriz(Doce** matriz, int linhas, int colunas, Node** fila) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            Doce d = remover_fila_entrada(fila);
            if (d.id == -1) {
                printf("Fila insuficiente para preencher a matriz!\n");
                return;
            }
            matriz[i][j] = d;
        }
    }
}

// Exibe a matriz no terminal
void imprimir_matriz(Doce** matriz, int linhas, int colunas) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("[%c] ", matriz[i][j].tipo);
        }
        printf("\n");
    }
}

// Libera toda a memória da matriz
void liberar_matriz(Doce** matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);   // libera cada linha
    }
    free(matriz);          // libera o array de ponteiros
}