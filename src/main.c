#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 6
#define COLUNAS 6

#include "../include/lista.h"
#include "../include/matriz.h"

int main() {
    srand(time(NULL));
    printf("Candy Crush C...\n");
    
    Node* fila_entrada = NULL;
    preencher_fila_inicial(&fila_entrada, 50);
    
    imprimir_fila(fila_entrada);
    
    Doce** tabuleiro = criar_matriz(LINHAS, COLUNAS);
    preencher_matriz(tabuleiro, LINHAS, COLUNAS, &fila_entrada);
    
    imprimir_matriz(tabuleiro, LINHAS, COLUNAS);
    
    imprimir_fila(fila_entrada);
    
    liberar_matriz(tabuleiro, LINHAS);
    liberar_fila(&fila_entrada);
    
    return 0;
}
