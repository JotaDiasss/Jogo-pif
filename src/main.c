#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <raylib.h>
#include "game_constants.h"
#include "raylib_utils.h"
#include "render.h"
#include "score_manager.h"

#include "../include/lista.h"
#include "../include/matriz.h"

typedef enum {
    STATE_HOME,
    STATE_PLAYING,
    STATE_GAME_OVER
} GameState;

#define MAX_ANIMATION_QUEUE 128

static CandyAnimation animationQueue[MAX_ANIMATION_QUEUE];
static int animationCount = 0;
static bool animating = false;
static float animationElapsed = 0.0f;
static float animationDuration = 0.18f;
static bool swapPending = false;
static bool cascadePending = false;
static int pendingScore = 0;
static Doce nextBoard[LINHAS][COLUNAS];

static void ResetAnimationQueue(void)
{
    animationCount = 0;
    animating = false;
    animationElapsed = 0.0f;
}

static void QueueCandyAnimation(int fromRow, int fromCol, int toRow, int toCol, Doce doce, float duration)
{
    if (animationCount >= MAX_ANIMATION_QUEUE) return;

    animationQueue[animationCount].active = true;
    animationQueue[animationCount].fromRow = fromRow;
    animationQueue[animationCount].fromCol = fromCol;
    animationQueue[animationCount].toRow = toRow;
    animationQueue[animationCount].toCol = toCol;
    animationQueue[animationCount].elapsed = 0.0f;
    animationQueue[animationCount].duration = duration;
    animationQueue[animationCount].doce = doce;
    animationCount++;
}

static void BeginAnimationQueue(float duration)
{
    for (int i = 0; i < animationCount; i++)
    {
        animationQueue[i].duration = duration;
        animationQueue[i].elapsed = 0.0f;
    }
    animationElapsed = 0.0f;
    animating = (animationCount > 0);
}

static void CopyNextBoardToBoard(Doce **board)
{
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            board[i][j] = nextBoard[i][j];
        }
    }
}

static void StartGravityAnimationAfterCombo(Doce **board, Node **fila);

static void UpdateAnimation(float dt, Doce **board, Node **fila, int *score)
{
    if (!animating) return;

    animationElapsed += dt;
    for (int i = 0; i < animationCount; i++)
    {
        animationQueue[i].elapsed = animationElapsed;
    }

    if (animationElapsed >= animationDuration)
    {
        CopyNextBoardToBoard(board);
        animating = false;

        if (swapPending)
        {
            swapPending = false;
            cascadePending = true;
            StartGravityAnimationAfterCombo(board, fila);
        }
        else if (cascadePending)
        {
            StartGravityAnimationAfterCombo(board, fila);
        }

        if (!animating && pendingScore > 0)
        {
            *score += pendingScore;
            pendingScore = 0;
        }
    }
}

static void GetAnimationHideMask(bool hide[LINHAS][COLUNAS])
{
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            hide[i][j] = false;
        }
    }

    if (animating)
    {
        for (int i = 0; i < animationCount; i++)
        {
            if (!animationQueue[i].active) continue;
            int fromR = animationQueue[i].fromRow;
            int fromC = animationQueue[i].fromCol;
            int toR = animationQueue[i].toRow;
            int toC = animationQueue[i].toCol;
            if (fromR >= 0 && fromR < LINHAS && fromC >= 0 && fromC < COLUNAS) hide[fromR][fromC] = true;
            if (toR >= 0 && toR < LINHAS && toC >= 0 && toC < COLUNAS) hide[toR][toC] = true;
        }
    }
}

static void StartSwapAnimation(Doce **board, int l1, int c1, int l2, int c2)
{
    Doce candyA = board[l1][c1];
    Doce candyB = board[l2][c2];

    ResetAnimationQueue();
    QueueCandyAnimation(l1, c1, l2, c2, candyA, animationDuration);
    QueueCandyAnimation(l2, c2, l1, c1, candyB, animationDuration);

    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            nextBoard[i][j] = board[i][j];
        }
    }
    nextBoard[l1][c1] = candyB;
    nextBoard[l2][c2] = candyA;

    BeginAnimationQueue(animationDuration);
    swapPending = true;
}

static void StartGravityAnimationAfterCombo(Doce **board, Node **fila)
{
    int removidos = verificar_combinacoes(board, LINHAS, COLUNAS);
    if (removidos <= 0)
    {
        cascadePending = false;
        return;
    }

    pendingScore += removidos * 10;
    ResetAnimationQueue();

    for (int j = 0; j < COLUNAS; j++)
    {
        int write = LINHAS - 1;
        for (int i = LINHAS - 1; i >= 0; i--)
        {
            if (board[i][j].tipo != ' ' && board[i][j].tipo != 0)
            {
                nextBoard[write][j] = board[i][j];
                if (write != i)
                {
                    QueueCandyAnimation(i, j, write, j, board[i][j], animationDuration);
                }
                write--;
            }
        }

        while (write >= 0)
        {
            Doce d = remover_fila_entrada(fila);
            if (d.id == -1)
            {
                preencher_fila_inicial(fila, 50);
                d = remover_fila_entrada(fila);
            }
            nextBoard[write][j] = d;
            QueueCandyAnimation(-1, j, write, j, d, animationDuration);
            write--;
        }
    }

    BeginAnimationQueue(animationDuration);
    cascadePending = true;
}

static void StartNewGame(Doce ***tabuleiroPtr, Node **filaPtr, int *pontuacao, int *jogadas, int *linha_sel, int *col_sel)
{
    if (*tabuleiroPtr != NULL)
    {
        liberar_matriz(*tabuleiroPtr, LINHAS);
        *tabuleiroPtr = NULL;
    }

    if (*filaPtr != NULL)
    {
        liberar_fila(filaPtr);
        *filaPtr = NULL;
    }

    preencher_fila_inicial(filaPtr, 50);
    *tabuleiroPtr = criar_matriz(LINHAS, COLUNAS);
    preencher_matriz(*tabuleiroPtr, LINHAS, COLUNAS, filaPtr);
    resolver_cascatas(*tabuleiroPtr, LINHAS, COLUNAS, filaPtr);

    *pontuacao = 0;
    *jogadas = 20;
    *linha_sel = -1;
    *col_sel = -1;
    pendingScore = 0;
    ResetAnimationQueue();
}

int main(void)
{
    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;

    srand(time(NULL));
    printf("Candy Crush C...\n");

    InitWindow(screenWidth, screenHeight, "CCC");
    SetTargetFPS(60);

    if (!InitGameTextures()) {
        fprintf(stderr, "Falha ao carregar texturas de doces.\n");
        CloseWindow();
        return 1;
    }

    Node *fila_entrada = NULL;
    Doce **tabuleiro = NULL;
    int linha_selecionada = -1;
    int coluna_selecionada = -1;
    int pontuacao = 0;
    int jogadas_restantes = 20;
    char playerName[MAX_NAME_LEN] = "";
    int nameLength = 0;
    bool showNameError = false;
    GameState gameState = STATE_HOME;
    bool scoreSaved = false;
    ScoreEntry ranking[MAX_RANKING_ENTRIES];
    int rankingCount = LoadScores(ranking, MAX_RANKING_ENTRIES);

    StartNewGame(&tabuleiro, &fila_entrada, &pontuacao, &jogadas_restantes, &linha_selecionada, &coluna_selecionada);

    while (!WindowShouldClose())
    {
        if (gameState == STATE_HOME)
        {
            if (IsKeyPressed(KEY_BACKSPACE) && nameLength > 0)
            {
                nameLength--;
                playerName[nameLength] = '\0';
            }

            int key = GetCharPressed();
            while (key > 0)
            {
                if (key >= 32 && key <= 125 && nameLength < MAX_NAME_LEN - 1)
                {
                    playerName[nameLength++] = (char)key;
                    playerName[nameLength] = '\0';
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                if (nameLength == 0)
                {
                    showNameError = true;
                }
                else
                {
                    gameState = STATE_PLAYING;
                    showNameError = false;
                    scoreSaved = false;
                    StartNewGame(&tabuleiro, &fila_entrada, &pontuacao, &jogadas_restantes, &linha_selecionada, &coluna_selecionada);
                }
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mousePos = GetMousePosition();
                Rectangle playButton = {70, 270, 260, 70};

                if (CheckCollisionPointRec(mousePos, playButton))
                {
                    if (nameLength == 0)
                    {
                        showNameError = true;
                    }
                    else
                    {
                        gameState = STATE_PLAYING;
                        showNameError = false;
                        scoreSaved = false;
                        StartNewGame(&tabuleiro, &fila_entrada, &pontuacao, &jogadas_restantes, &linha_selecionada, &coluna_selecionada);
                    }
                }
            }
        }
        else if (gameState == STATE_PLAYING)
        {
            if (!animating && jogadas_restantes > 0)
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    Vector2 mousePos = GetMousePosition();

                    if (mousePos.x >= GRID_X && mousePos.x <= GRID_X + COLUNAS * CELL_SIZE &&
                        mousePos.y >= GRID_Y && mousePos.y <= GRID_Y + LINHAS * CELL_SIZE)
                    {
                        int col_clicada = (mousePos.x - GRID_X) / CELL_SIZE;
                        int lin_clicada = (mousePos.y - GRID_Y) / CELL_SIZE;

                        if (linha_selecionada == -1)
                        {
                            linha_selecionada = lin_clicada;
                            coluna_selecionada = col_clicada;
                        }
                        else
                        {
                            if (linha_selecionada == lin_clicada && coluna_selecionada == col_clicada)
                            {
                                linha_selecionada = -1;
                                coluna_selecionada = -1;
                            }
                            else
                            {
                                if (trocar_doces(tabuleiro, LINHAS, COLUNAS, linha_selecionada, coluna_selecionada, lin_clicada, col_clicada))
                                {
                                    // Reverte a troca para animar o movimento por vez
                                    Doce temp = tabuleiro[linha_selecionada][coluna_selecionada];
                                    tabuleiro[linha_selecionada][coluna_selecionada] = tabuleiro[lin_clicada][col_clicada];
                                    tabuleiro[lin_clicada][col_clicada] = temp;

                                    jogadas_restantes--;
                                    StartSwapAnimation(tabuleiro, linha_selecionada, coluna_selecionada, lin_clicada, col_clicada);
                                }

                                linha_selecionada = -1;
                                coluna_selecionada = -1;
                            }
                        }
                    }
                }
            }

            if (animating)
            {
                UpdateAnimation(GetFrameTime(), tabuleiro, &fila_entrada, &pontuacao);
            }

            if (jogadas_restantes <= 0 && !scoreSaved && !animating)
            {
                AddScore(ranking, &rankingCount, playerName, pontuacao);
                SaveScores(ranking, rankingCount);
                scoreSaved = true;
                gameState = STATE_GAME_OVER;
            }
        }
        else if (gameState == STATE_GAME_OVER)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                gameState = STATE_HOME;
                playerName[0] = '\0';
                nameLength = 0;
                showNameError = false;
                scoreSaved = false;
                StartNewGame(&tabuleiro, &fila_entrada, &pontuacao, &jogadas_restantes, &linha_selecionada, &coluna_selecionada);
            }
        }

        BeginDrawing();

        if (gameState == STATE_HOME)
        {
            bool cursorVisible = ((int)(GetTime() * 2.0)) % 2 == 0;
            DrawHomeScreen(playerName, cursorVisible, ranking, rankingCount);

            if (showNameError)
            {
                DrawText("Digite seu nome antes de iniciar.", 70, 430, 22, RED);
            }
        }
        else
        {
            bool hide[LINHAS][COLUNAS] = {0};
            if (animating)
            {
                GetAnimationHideMask(hide);
            }
            DrawGame(tabuleiro, linha_selecionada, coluna_selecionada, pontuacao, jogadas_restantes, hide, animationQueue, animationCount);

            if (gameState == STATE_GAME_OVER)
            {
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 180});
                DrawText("FIM DE JOGO!", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 80, 50, RED);
                DrawText(TextFormat("%s, sua pontuacao: %d", playerName, pontuacao), SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 10, 32, WHITE);
                DrawText("Pressione ENTER para voltar ao menu inicial", SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 + 50, 24, WHITE);
            }
        }

        EndDrawing();
    }

    UnloadGameTextures();
    liberar_matriz(tabuleiro, LINHAS);
    liberar_fila(&fila_entrada);
    CloseWindow();

    return 0;
}
