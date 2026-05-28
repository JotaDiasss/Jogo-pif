#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#include "../include/lista.h"
#include "../include/matriz.h"

#define LINHAS 6
#define COLUNAS 6
#define CELL_SIZE 90
#define GRID_PADDING 8
#define GRID_X 220
#define GRID_Y 120
#define GRID_COLOR LIGHTGRAY
#define BACKGROUND_COLOR BLACK

static Texture GetCandyTexture(char type, Texture red, Texture green, Texture blue, Texture yellow, Texture purple) {
    switch (type) {
        case 'R': return red;
        case 'G': return green;
        case 'B': return blue;
        case 'Y': return yellow;
        case 'P': return purple;
        default: return (Texture){0};
    }
}

int main(void) {
    const int screenWidth = 1280;
    const int screenHeight = 720;

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

    Texture RedCandy = LoadTexture("assets/RedCandy.png");
    Texture GreenCandy = LoadTexture("assets/GreenCandy.png");
    Texture BlueCandy = LoadTexture("assets/BlueCandy.png");
    Texture YellowCandy = LoadTexture("assets/YellowCandy.png");
    Texture PurpleCandy = LoadTexture("assets/PurpleCandy.png");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        DrawText("Candy Crush C usando raylib!", 190, 40, 24, WHITE);

        for (int i = 0; i <= LINHAS; i++) {
            int y = GRID_Y + i * CELL_SIZE;
            DrawLine(GRID_X, y, GRID_X + COLUNAS * CELL_SIZE, y, GRID_COLOR);
        }
        for (int j = 0; j <= COLUNAS; j++) {
            int x = GRID_X + j * CELL_SIZE;
            DrawLine(x, GRID_Y, x, GRID_Y + LINHAS * CELL_SIZE, GRID_COLOR);
        }

        for (int i = 0; i < LINHAS; i++) {
            for (int j = 0; j < COLUNAS; j++) {
                int x = GRID_X + j * CELL_SIZE;
                int y = GRID_Y + i * CELL_SIZE;
                Texture tex = GetCandyTexture(tabuleiro[i][j].tipo, RedCandy, GreenCandy, BlueCandy, YellowCandy, PurpleCandy);
                if (tex.id != 0) {
                    Rectangle src = { 0.0f, 0.0f, (float)tex.width, (float)tex.height };
                    Rectangle dest = { (float)x + GRID_PADDING, (float)y + GRID_PADDING,
                                       (float)CELL_SIZE - 2 * GRID_PADDING, (float)CELL_SIZE - 2 * GRID_PADDING };
                    DrawTexturePro(tex, src, dest, (Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
                }
            }
        }

        EndDrawing();
    }

    UnloadTexture(RedCandy);
    UnloadTexture(GreenCandy);
    UnloadTexture(BlueCandy);
    UnloadTexture(YellowCandy);
    UnloadTexture(PurpleCandy);

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
