#ifndef BACKGROUND
#define BACKGROUND
#include "consts.h"
#include "raylib.h"
float backgroundOffset = 0;
const float backgroundSpeed = 40.0f;

Texture2D backgroundTexture;

void LoadBackgroundTexture() {
    Image backgroundImage = LoadImage("assets/background.png");
    backgroundTexture = LoadTextureFromImage(backgroundImage);
}

void UpdateBackground()
{
    backgroundOffset += backgroundSpeed * GetFrameTime();
    if (backgroundOffset >= gameHeight) {
        backgroundOffset = 0;
    }
}

void DrawBackground()
{
    DrawTexture(backgroundTexture, 0, backgroundOffset, WHITE);
    DrawTexture(backgroundTexture, 0, backgroundOffset - backgroundTexture.height, WHITE);
}

#endif
