#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include "game_constants.h"
#include "raylib_utils.h"
#include "render.h"

#include "../include/lista.h"
#include "../include/matriz.h"

int main(void) {
    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;

    srand(time(NULL));
    printf("Candy Crush C...\n");

    Node* fila_entrada = NULL;
    preencher_fila_inicial(&fila_entrada, 50);

    imprimir_fila(fila_entrada);

    Doce** tabuleiro = criar_matriz(LINHAS, COLUNAS);
    preencher_matriz(tabuleiro, LINHAS, COLUNAS, &fila_entrada);

    imprimir_matriz(tabuleiro, LINHAS, COLUNAS);

    InitWindow(screenWidth, screenHeight, "CCC");
    SetTargetFPS(60);

    if (!InitGameTextures()) {
        fprintf(stderr, "Falha ao carregar texturas de doces.\n");
        CloseWindow();
        liberar_matriz(tabuleiro, LINHAS);
        liberar_fila(&fila_entrada);
        return 1;
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BG_COLOR);

        DrawGame(tabuleiro);

        EndDrawing();
    }

    UnloadGameTextures();

    // Teste de Troca (Lógica 1)
    printf("\n--- Testando Lógica de Troca ---\n");
    printf("Troca 1 (Valida: adjacente): (0,0) por (0,1)\n");
    if (trocar_doces(tabuleiro, LINHAS, COLUNAS, 0, 0, 0, 1)) {
        printf("Troca efetuada!\n");
    }
    imprimir_matriz(tabuleiro, LINHAS, COLUNAS);

    printf("\nTroca 2 (Invalida: nao adjacente): (0,0) por (2,2)\n");
    if (trocar_doces(tabuleiro, LINHAS, COLUNAS, 0, 0, 2, 2)) {
        printf("Troca efetuada!\n");
    }

    imprimir_fila(fila_entrada);

    liberar_matriz(tabuleiro, LINHAS);
    liberar_fila(&fila_entrada);

    CloseWindow();
    return 0;
}
