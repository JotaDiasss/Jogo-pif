#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include "render.h"
#include "raylib_utils.h"
#include "game_constants.h"
#include "score_manager.h"

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

void DrawCandyAtScreen(float x, float y, Doce doce)
{
    Texture tex = GetCandyTexture(doce.tipo);
    if (tex.id != 0)
    {
        Rectangle src = {0.0f, 0.0f, (float)tex.width, (float)tex.height};
        Rectangle dest = {x + GRID_PADDING, y + GRID_PADDING,
                          (float)CELL_SIZE - 2 * GRID_PADDING, (float)CELL_SIZE - 2 * GRID_PADDING};
        DrawTexturePro(tex, src, dest, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
    }
}

void DrawBoardCellsWithMask(Doce **board, bool hide[LINHAS][COLUNAS])
{
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            if (hide && hide[i][j])
                continue;

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

void DrawBoardCells(Doce **board)
{
    DrawBoardCellsWithMask(board, NULL);
}

void DrawHomeScreen(const char *playerName, bool cursorVisible, ScoreEntry *ranking, int rankingCount)
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
    }

    DrawRectangle(50, 50, 560, 620, Fade(BLACK, 0.55f));
    DrawText("BEM VINDO", 70, 70, 40, HUD_TEXT_COLOR);
    DrawText("Digite seu nome:", 70, 140, 28, HUD_TEXT_COLOR);

    Rectangle inputBox = {70, 180, 520, 60};
    DrawRectangleRec(inputBox, Fade(WHITE, 0.10f));
    DrawRectangleLinesEx(inputBox, 3.0f, WHITE);

    char displayName[MAX_NAME_LEN + 3] = "";
    if (cursorVisible && playerName[0] != '\0')
    {
        sprintf(displayName, "%s_", playerName);
    }
    else if (cursorVisible && playerName[0] == '\0')
    {
        sprintf(displayName, "_");
    }
    else
    {
        strncpy(displayName, playerName, MAX_NAME_LEN);
        displayName[MAX_NAME_LEN] = '\0';
    }

    DrawText(displayName, 90, 195, 30, WHITE);

    Rectangle playButton = {70, 270, 260, 70};
    DrawRectangleRec(playButton, Fade((Color){72, 136, 240, 255}, 0.95f));
    DrawRectangleLinesEx(playButton, 3.0f, WHITE);
    DrawText("PLAY", playButton.x + 82, playButton.y + 18, 40, WHITE);

    DrawText("Clique no botão ou pressione ENTER para começar", 70, 350, 20, HUD_TEXT_COLOR);

    DrawText("RANKING", 690, 70, 40, HUD_TEXT_COLOR);
    Rectangle rankingBox = {640, 120, 600, 560};
    DrawRectangleRec(rankingBox, Fade(BLACK, 0.45f));
    DrawRectangleLinesEx(rankingBox, 3.0f, WHITE);

    if (rankingCount == 0)
    {
        DrawText("Nenhum score registrado ainda", 660, 160, 22, WHITE);
    }
    else
    {
        for (int i = 0; i < rankingCount && i < MAX_RANKING_ENTRIES; i++)
        {
            DrawText(TextFormat("%d. %s - %d", i + 1, ranking[i].name, ranking[i].score),
                     660, 160 + i * 34, 24, WHITE);
        }
    }
}

void DrawGame(Doce **board, int linha_sel, int col_sel, int pontuacao, int jogadas, bool hide[LINHAS][COLUNAS], const CandyAnimation *animations, int animationCount)
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

        DrawBoardCellsWithMask(board, hide);

        for (int i = 0; i < animationCount; i++)
        {
            if (!animations[i].active) continue;

            float t = animations[i].elapsed / animations[i].duration;
            if (t < 0.0f) t = 0.0f;
            if (t > 1.0f) t = 1.0f;

            Vector2 start = {GRID_X + animations[i].fromCol * CELL_SIZE, GRID_Y + animations[i].fromRow * CELL_SIZE};
            Vector2 end = {GRID_X + animations[i].toCol * CELL_SIZE, GRID_Y + animations[i].toRow * CELL_SIZE};
            float x = start.x + (end.x - start.x) * t;
            float y = start.y + (end.y - start.y) * t;
            DrawCandyAtScreen(x, y, animations[i].doce);
        }
        
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