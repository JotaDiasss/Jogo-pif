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

    // Limpa o tabuleiro de qualquer combinação aleatória gerada na inicialização
    resolver_cascatas(tabuleiro, LINHAS, COLUNAS, &fila_entrada);

    int linha_selecionada = -1;
    int coluna_selecionada = -1;
    int pontuacao = 0;
    int jogadas_restantes = 20; // Limite de jogadas para o fim de jogo

    while (!WindowShouldClose()) {
        
        // Só permite clicar se o jogo não acabou
        if (jogadas_restantes > 0) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                
                // Verifica se o clique ocorreu dentro dos limites da grade
                if (mousePos.x >= GRID_X && mousePos.x <= GRID_X + COLUNAS * CELL_SIZE &&
                    mousePos.y >= GRID_Y && mousePos.y <= GRID_Y + LINHAS * CELL_SIZE) {
                    
                    int col_clicada = (mousePos.x - GRID_X) / CELL_SIZE;
                    int lin_clicada = (mousePos.y - GRID_Y) / CELL_SIZE;
                    
                    if (linha_selecionada == -1) {
                        // Primeiro doce selecionado
                        linha_selecionada = lin_clicada;
                        coluna_selecionada = col_clicada;
                    } else {
                        // Segundo clique
                        if (linha_selecionada == lin_clicada && coluna_selecionada == col_clicada) {
                            // Clicou no mesmo doce, então cancela a seleção
                            linha_selecionada = -1;
                            coluna_selecionada = -1;
                        } else {
                            // Tenta realizar a troca (trocar_doces já valida adjacência e se forma combinação)
                            if (trocar_doces(tabuleiro, LINHAS, COLUNAS, linha_selecionada, coluna_selecionada, lin_clicada, col_clicada)) {
                                // Troca foi um sucesso! Consome 1 jogada.
                                jogadas_restantes--;
                                
                                // Resolve todas as combinações e cascatas
                                int doces_estourados = resolver_cascatas(tabuleiro, LINHAS, COLUNAS, &fila_entrada);
                                
                                // Incrementa a pontuação
                                pontuacao += doces_estourados * 10;
                            }
                            
                            // Reseta a seleção para a próxima jogada
                            linha_selecionada = -1;
                            coluna_selecionada = -1;
                        }
                    }
                }
            }
        }

        BeginDrawing();

        DrawGame(tabuleiro, linha_selecionada, coluna_selecionada, pontuacao, jogadas_restantes);

        EndDrawing();
    }

    UnloadGameTextures();
    liberar_matriz(tabuleiro, LINHAS);
    liberar_fila(&fila_entrada);
    CloseWindow();
    return 0;
}
