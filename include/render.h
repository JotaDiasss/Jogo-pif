#ifndef RENDER_H
#define RENDER_H

#include <stdbool.h>
#include <raylib.h>
#include "game_constants.h"
#include "lista.h"
#include "score_manager.h"

typedef struct {
    bool active;
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
    float elapsed;
    float duration;
    Doce doce;
} CandyAnimation;

void DrawGame(Doce** board, int linha_sel, int col_sel, int pontuacao, int jogadas, bool hide[LINHAS][COLUNAS], const CandyAnimation *animations, int animationCount);
void DrawBoardGrid(void);
void DrawBoardCells(Doce** board);
void DrawBoardCellsWithMask(Doce** board, bool hide[LINHAS][COLUNAS]);
void DrawCandyAtScreen(float x, float y, Doce doce);
void DrawHomeScreen(const char *playerName, bool cursorVisible, ScoreEntry *ranking, int rankingCount);

#endif // RENDER_H
