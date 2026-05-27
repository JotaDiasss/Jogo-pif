#include <stdio.h>
#include <stdlib.h>
#include "../include/matriz.h"

Doce** criar_matriz(int linhas, int colunas) {
    Doce **matriz = (Doce **)malloc(linhas * sizeof(Doce *));
    if (matriz == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (Doce *)malloc(colunas * sizeof(Doce));
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

// Troca dois doces de lugar na matriz se forem posições válidas e adjacentes.
// Retorna 1 se a troca foi realizada com sucesso, e 0 caso contrário.
int trocar_doces(Doce** matriz, int linhas, int colunas, int l1, int c1, int l2, int c2) {
    // 1. Verifica limites
    if (l1 < 0 || l1 >= linhas || c1 < 0 || c1 >= colunas ||
        l2 < 0 || l2 >= linhas || c2 < 0 || c2 >= colunas) {
        printf("Posicao fora do tabuleiro!\n");
        return 0;
    }
    
    // 2. Verifica adjacência (apenas horizontal ou vertical, não diagonal)
    int dist_linhas = abs(l1 - l2);
    int dist_colunas = abs(c1 - c2);
    
    if ((dist_linhas == 1 && dist_colunas == 0) || (dist_linhas == 0 && dist_colunas == 1)) {
        Doce temp = matriz[l1][c1];
        matriz[l1][c1] = matriz[l2][c2];
        matriz[l2][c2] = temp;
        return 1;
    }
    
    printf("Os doces nao sao adjacentes!\n");
    return 0;
}
