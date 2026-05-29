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

void DrawGame(Doce **board)
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
        DrawBoardCells(board);
    }
}