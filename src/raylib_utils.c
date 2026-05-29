#include "raylib_utils.h"
#include "game_constants.h"

Texture candyTextures[CANDY_TEXTURE_COUNT];

Texture2D background;

static const char* candyTexturePaths[CANDY_TEXTURE_COUNT] = {
    "assets/RedCandy.png",
    "assets/GreenCandy.png",
    "assets/BlueCandy.png",
    "assets/YellowCandy.png",
    "assets/PurpleCandy.png"
};

static const char* backgroundPath = "assets/BackGround.png";

static const Color candyFallbackColors[CANDY_TEXTURE_COUNT] = {
    { 220,  60,  60, 255 },
    {  60, 190, 100, 255 },
    {  70, 150, 230, 255 },
    { 240, 220,  75, 255 },
    { 170,  90, 210, 255 }
};

static const Color backgroundFallbackColor = { 15, 18, 35, 255 };

static Image GenCandyPlaceholder(Color color) {
    Image image = GenImageColor(64, 64, Fade(color, 0.20f));
    ImageDrawCircle(&image, 32, 32, 22, color);
    ImageDrawCircleLines(&image, 32, 32, 22, WHITE);
    ImageDrawCircle(&image, 22, 22, 6, Fade(WHITE, 0.9f));
    ImageDrawCircle(&image, 42, 38, 8, Fade(WHITE, 0.35f));
    return image;
}

static Texture2D LoadTextureOrPlaceholder(const char* path, Color fallbackColor) {
    Texture2D texture = LoadTexture(path);
    if (texture.id == 0) {
        Image placeholder = GenCandyPlaceholder(fallbackColor);
        texture = LoadTextureFromImage(placeholder);
        UnloadImage(placeholder);
    }
    return texture;
}

static Texture2D LoadBackgroundTexture(void) {
    Texture2D texture = LoadTexture(backgroundPath);
    if (texture.id == 0) {
        Image placeholder = GenImageColor(SCREEN_WIDTH, SCREEN_HEIGHT, backgroundFallbackColor);
        texture = LoadTextureFromImage(placeholder);
        UnloadImage(placeholder);
    }
    return texture;
}

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
        candyTextures[i] = LoadTextureOrPlaceholder(candyTexturePaths[i], candyFallbackColors[i]);
        if (candyTextures[i].id == 0) {
            return 0;
        }
    }

    background = LoadBackgroundTexture();
    if (background.id == 0) {
        return 0;
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

    if (background.id != 0) {
        UnloadTexture(background);
        background = (Texture2D){ 0 };
    }
}
