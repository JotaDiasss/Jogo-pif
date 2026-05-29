#ifndef RAYLIB_UTILS_H
#define RAYLIB_UTILS_H

#include <raylib.h>

typedef enum {
    MENU,
    GAME
} GameScreen;

typedef enum {
    CANDY_RED = 'R',
    CANDY_GREEN = 'G',
    CANDY_BLUE = 'B',
    CANDY_YELLOW = 'Y',
    CANDY_PURPLE = 'P'
} CandyType;

#define CANDY_TEXTURE_COUNT 5

extern Texture candyTextures[CANDY_TEXTURE_COUNT];
extern Texture2D background;

Texture GetCandyTexture(char type);
int InitGameTextures(void);
void UnloadGameTextures(void);

#endif
