#include "raylib_utils.h"

Texture candyTextures[CANDY_TEXTURE_COUNT];

static const char* candyTexturePaths[CANDY_TEXTURE_COUNT] = {
    "./assets/RedCandy.png",
    "./assets/GreenCandy.png",
    "./assets/BlueCandy.png",
    "./assets/YellowCandy.png",
    "./assets/PurpleCandy.png"
};

static int GetCandyIndex(char type) {
    switch (type) {
        case CANDY_RED: return 0;
        case CANDY_GREEN: return 1;
        case CANDY_BLUE: return 2;
        case CANDY_YELLOW: return 3;
        case CANDY_PURPLE: return 4;
        default: return -1;
    }
}

Texture GetCandyTexture(char type) {
    int index = GetCandyIndex(type);
    if (index < 0 || index >= CANDY_TEXTURE_COUNT) {
        return (Texture){ 0 };
    }
    return candyTextures[index];
}

int InitGameTextures(void) {
    for (int i = 0; i < CANDY_TEXTURE_COUNT; i++) {
        candyTextures[i] = LoadTexture(candyTexturePaths[i]);
    }
    return 1;
}

void UnloadGameTextures(void) {
    for (int i = 0; i < CANDY_TEXTURE_COUNT; i++) {
        if (candyTextures[i].id != 0) {
            UnloadTexture(candyTextures[i]);
            candyTextures[i] = (Texture){ 0 };
        }
    }
}
