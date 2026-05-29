#ifndef RENDER_H
#define RENDER_H

#include "lista.h"
#include <raylib.h>

void DrawGame(Doce** board, int linha_sel, int col_sel, int pontuacao, int jogadas);
void DrawBoardGrid(void);
void DrawBoardCells(Doce** board);

#endif // RENDER_H
