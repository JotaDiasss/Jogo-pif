#include <raylib.h>
#include "render.h"
#include "raylib_utils.h"
#include "game_constants.h"

void DrawBoardGrid(void) {
    for (int i = 0; i <= LINHAS; i++) {
        int y = GRID_Y + i * CELL_SIZE;
        DrawLine(GRID_X, y, GRID_X + COLUNAS * CELL_SIZE, y, GRID_COLOR);
    }
    for (int j = 0; j <= COLUNAS; j++) {
        int x = GRID_X + j * CELL_SIZE;
        DrawLine(x, GRID_Y, x, GRID_Y + LINHAS * CELL_SIZE, GRID_COLOR);
    }
}

void DrawBoardCells(Doce** board) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            int x = GRID_X + j * CELL_SIZE;
            int y = GRID_Y + i * CELL_SIZE;
            Texture tex = GetCandyTexture(board[i][j].tipo);
            if (tex.id != 0) {
                Rectangle src = { 0.0f, 0.0f, (float)tex.width, (float)tex.height };
                Rectangle dest = { (float)x + GRID_PADDING, (float)y + GRID_PADDING,
                                   (float)CELL_SIZE - 2 * GRID_PADDING, (float)CELL_SIZE - 2 * GRID_PADDING };
                DrawTexturePro(tex, src, dest, (Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);
            }
        }
    }
}

void DrawGame(Doce** board) {
    DrawText("Candy Crush C usando raylib!", 190, 40, 24, HUD_TEXT_COLOR);
    DrawBoardGrid();
    DrawBoardCells(board);
}
