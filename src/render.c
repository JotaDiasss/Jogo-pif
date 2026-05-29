#include <raylib.h>
#include "render.h"
#include "raylib_utils.h"
#include "game_constants.h"

void DrawBoardGrid(void)
{

    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            int x = GRID_X + j * CELL_SIZE;
            int y = GRID_Y + i * CELL_SIZE;

            Color cor;

            if ((i + j) % 2 == 0)
                cor = CELL_BG_COLOR1;
            else
                cor = CELL_BG_COLOR2;

            DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, cor);
        }
    }
    for (int i = 0; i <= LINHAS; i++)
    {
        int y = GRID_Y + i * CELL_SIZE;
        DrawLineEx(
            (Vector2){GRID_X, y},
            (Vector2){(GRID_X + LINHAS * CELL_SIZE)+2, y},
            4.0f,
            GRID_COLOR);
    }
    for (int j = 0; j <= COLUNAS; j++)
    {
        int x = GRID_X + j * CELL_SIZE;
        DrawLineEx(
            (Vector2){x, GRID_Y},
            (Vector2){x, (GRID_Y + LINHAS * CELL_SIZE)+2},
            4.0f,
            GRID_COLOR);
    }
}

void DrawBoardCells(Doce **board)
{
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            int x = GRID_X + j * CELL_SIZE;
            int y = GRID_Y + i * CELL_SIZE;
            Texture tex = GetCandyTexture(board[i][j].tipo);
            if (tex.id != 0)
            {
                Rectangle src = {0.0f, 0.0f, (float)tex.width, (float)tex.height};
                Rectangle dest = {(float)x + GRID_PADDING, (float)y + GRID_PADDING,
                                  (float)CELL_SIZE - 2 * GRID_PADDING, (float)CELL_SIZE - 2 * GRID_PADDING};
                DrawTexturePro(tex, src, dest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
            }
        }
    }
}

void DrawGame(Doce **board, int linha_sel, int col_sel, int pontuacao, int jogadas)
{
    if (background.id != 0)
    {
        DrawTexturePro(
            background,
            (Rectangle){0, 0, background.width, background.height},
            (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
            (Vector2){0, 0},
            0.0f,
            WHITE);

        DrawBoardGrid();
        
        // Desenha a seleção do jogador
        if (linha_sel >= 0 && col_sel >= 0) {
            int x = GRID_X + col_sel * CELL_SIZE;
            int y = GRID_Y + linha_sel * CELL_SIZE;
            DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, (Color){255, 255, 0, 100}); // Fundo Amarelo
            DrawRectangleLinesEx((Rectangle){x, y, CELL_SIZE, CELL_SIZE}, 4.0f, YELLOW); // Borda
        }

        DrawBoardCells(board);
        
        // Desenha a HUD (Interface de Usuário)
        DrawText(TextFormat("PONTOS: %d", pontuacao), 50, 50, 40, HUD_TEXT_COLOR);
        DrawText(TextFormat("JOGADAS: %d", jogadas), 50, 100, 40, HUD_TEXT_COLOR);
        
        // Tela de Fim de Jogo
        if (jogadas <= 0) {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 150});
            DrawText("FIM DE JOGO!", SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 - 50, 50, RED);
            DrawText(TextFormat("Sua Pontuacao: %d", pontuacao), SCREEN_WIDTH/2 - 180, SCREEN_HEIGHT/2 + 20, 40, WHITE);
        }
    }
}